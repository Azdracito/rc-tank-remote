// CC:DB:A7:31:B7:A8

#include <esp_now.h>
#include <WiFi.h>

const int minValue = 0;
const int maxValue = 4095;
const int joyX = 35;
const int joyY = 34;
const int deadZone = 20;

int neutralX = 0;
int neutralY = 0;

uint8_t broadcastAddress[] = {0xCC, 0xDB, 0xA7, 0x31, 0xB7, 0xA8};

typedef struct struct_message {
  int VRx;
  int VRy;
} struct_message;

struct_message myData;

int mapJoystick(int value, int neutral) {
  if (abs(value - neutral) < deadZone) {
    return 0;
  }

  return map(value, minValue, maxValue, -100, 100);
}

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
 
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  neutralX = analogRead(joyX);
  neutralY = analogRead(joyY);
}

void loop() {
  int rawX = analogRead(joyX);
  int rawY = analogRead(joyY);

  myData.VRx = mapJoystick(rawX, neutralX);
  myData.VRy = mapJoystick(rawY, neutralY);
  
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  delay(50);
}