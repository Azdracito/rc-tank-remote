#include "joystick.h"

void Joystick::calibrate() {
    int sommeX = 0, sommeY = 0;

    for (int i = 0; i < MAX_CALIBRATE; i++) {
      sommeX += analogRead(PIN_JOYSTICK_X);
      sommeY += analogRead(PIN_JOYSTICK_Y);
      delay(10);
    }
    
    neutralX = sommeX / MAX_CALIBRATE;
    neutralY = sommeY / MAX_CALIBRATE;

    Serial.printf("Joystick calibrated: X = %d, Y = %d\n", neutralX, neutralY);
    delay(1000);
}

JoystickData Joystick::readValues() const {
    return {
        .xAxis = mapAxisValue(analogRead(PIN_JOYSTICK_X), neutralX),
        .yAxis = mapAxisValue(analogRead(PIN_JOYSTICK_Y), neutralY)
    };
}

int Joystick::mapAxisValue(int rawValue, int neutralPosition) const {
    int deviation = rawValue - neutralPosition;
    if (abs(deviation) < DEAD_ZONE) {
        return 0;
    }
    return map(deviation, -neutralPosition, MAX_ANALOG_VALUE - neutralPosition, MAPPED_MIN, MAPPED_MAX);
}