#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

constexpr int MIN_ANALOG_VALUE = 0;
constexpr int MAX_ANALOG_VALUE = 4095;
constexpr int DEAD_ZONE = 200;
constexpr int MAPPED_MIN = -100;
constexpr int MAPPED_MAX = 100;
constexpr int MAX_CALIBRATE = 100;

constexpr int PIN_JOYSTICK_X = 35;  // Avancer / Reculer  
constexpr int PIN_JOYSTICK_Y = 34;  // Rotation gauche / droite
constexpr int PIN_JOYSTICK_TURRET = 33;  // Rotation de la tourelle
constexpr int PIN_JOYSTICK_CANNON = 32;  // Monter / descendre le canon
constexpr int PIN_FIRE_BUTTON = 25;      // Bouton pour tirer

struct JoystickData {
    int xAxis;
    int yAxis;
    int turretAxis;
    int cannonAxis;
    int fire;
};

class Joystick {
public:
    void calibrate();
    JoystickData readValues() const;

private:
    int neutralX = 0;
    int neutralY = 0;
    int neutralTurret = 0;
    int neutralCannon = 0;

    int mapAxisValue(int rawValue, int neutralPosition) const;
};

#endif
