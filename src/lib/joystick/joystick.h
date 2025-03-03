#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

constexpr int MIN_ANALOG_VALUE = 0;
constexpr int MAX_ANALOG_VALUE = 4095;
constexpr int DEAD_ZONE = 200;
constexpr int MAPPED_MIN = -100;
constexpr int MAPPED_MAX = 100;
constexpr int MAX_CALIBRATE = 100;

constexpr int PIN_JOYSTICK_X = 35;
constexpr int PIN_JOYSTICK_Y = 34;

struct JoystickData {
    int xAxis;
    int yAxis;
};

class Joystick {
public:
    void calibrate();
    JoystickData readValues() const;

private:
    int neutralX = 0;
    int neutralY = 0;

    int mapAxisValue(int rawValue, int neutralPosition) const;
};

#endif
