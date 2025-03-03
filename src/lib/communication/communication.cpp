#include "communication.h"

void Communication::initialize() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        delay(5000);
        ESP.restart();
    }

    // esp_now_register_send_cb(onDataSent);

    esp_now_peer_info_t peerInfo{};
    memcpy(peerInfo.peer_addr, BROADCAST_ADDRESS, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        delay(5000);
        ESP.restart();
    }
}

void Communication::sendJoystickData(const JoystickData& data) const {
    esp_err_t result = esp_now_send(BROADCAST_ADDRESS, reinterpret_cast<const uint8_t*>(&data), sizeof(data));
    // Serial.println(result == ESP_OK ? "Sent successfully" : "Failed to send data");
}

void Communication::onDataSent(const uint8_t* macAddr, esp_now_send_status_t status) {
    Serial.printf("Packet Send Status: %s\n", status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failed");
}
