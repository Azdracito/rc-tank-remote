#include "lib/joystick/joystick.h"
#include "lib/communication/communication.h"

Joystick joystick;
Communication communication;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_JOYSTICK_X, INPUT);
  pinMode(PIN_JOYSTICK_Y, INPUT);

  communication.initialize();
  joystick.calibrate();
}

void loop() {
  JoystickData joystickData = joystick.readValues();
  communication.sendJoystickData(joystickData);
  delay(50);
}
