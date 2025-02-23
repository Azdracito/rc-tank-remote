#include "joystick.h"

void Joystick::calibrate() {
    neutralX = analogRead(PIN_JOYSTICK_X);
    neutralY = analogRead(PIN_JOYSTICK_Y);
    Serial.printf("Joystick calibrated: X = %d, Y = %d\n", neutralX, neutralY);
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
