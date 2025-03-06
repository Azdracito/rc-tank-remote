#include "joystick.h"
#include <array>

void Joystick::calibrate() {
    std::array<int, 4> neutralValues = {0, 0, 0, 0};

    for (int i = 0; i < MAX_CALIBRATE; i++) {
        neutralValues[0] += analogRead(PIN_JOYSTICK_X);
        neutralValues[1] += analogRead(PIN_JOYSTICK_Y);
        neutralValues[2] += analogRead(PIN_JOYSTICK_TURRET);
        neutralValues[3] += analogRead(PIN_JOYSTICK_CANNON);
        delay(10);
    }
    
    neutralX = neutralValues[0] / MAX_CALIBRATE;
    neutralY = neutralValues[1] / MAX_CALIBRATE;
    neutralTurret = neutralValues[2] / MAX_CALIBRATE;
    neutralCannon = neutralValues[3] / MAX_CALIBRATE;

    Serial.printf("Joystick calibrated: X = %d, Y = %d, Turret = %d, Cannon = %d\n", neutralX, neutralY, neutralTurret, neutralCannon);
    delay(1000);
}

JoystickData Joystick::readValues() const {
    return {
        .xAxis = mapAxisValue(analogRead(PIN_JOYSTICK_X), neutralX),
        .yAxis = mapAxisValue(analogRead(PIN_JOYSTICK_Y), neutralY),
        .turretAxis = mapAxisValue(analogRead(PIN_JOYSTICK_TURRET), neutralTurret),
        .cannonAxis = mapAxisValue(analogRead(PIN_JOYSTICK_CANNON), neutralCannon),
        .fire = digitalRead(PIN_FIRE_BUTTON)
    };
}

int Joystick::mapAxisValue(int rawValue, int neutralPosition) const {
    int deviation = rawValue - neutralPosition;
    if (std::abs(deviation) < DEAD_ZONE) {
        return 0;
    }
    return map(deviation, -neutralPosition, MAX_ANALOG_VALUE - neutralPosition, MAPPED_MIN, MAPPED_MAX);
}