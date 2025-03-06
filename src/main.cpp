#include "lib/joystick/joystick.h"
#include "lib/communication/communication.h"

Joystick joystick;
Communication communication;

void setup() {
  Serial.begin(115200);

  pinMode(PIN_JOYSTICK_X, INPUT);
  pinMode(PIN_JOYSTICK_Y, INPUT);
  pinMode(PIN_JOYSTICK_TURRET, INPUT);
  pinMode(PIN_JOYSTICK_CANNON, INPUT);
  pinMode(PIN_FIRE_BUTTON, INPUT);

  joystick.calibrate();
  communication.initialize();
}

void loop() {
  JoystickData joystickData = joystick.readValues();
  communication.sendJoystickData(joystickData);

  Serial.printf("Joystick: X = %d, Y = %d, Turret = %d, Cannon = %d, Fire = %d\n", joystickData.xAxis, joystickData.yAxis, joystickData.turretAxis, joystickData.cannonAxis, joystickData.fire);
  delay(100);
}