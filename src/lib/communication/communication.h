#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <esp_now.h>
#include <WiFi.h>
#include "../joystick/joystick.h"

constexpr uint8_t BROADCAST_ADDRESS[] = {0xCC, 0xDB, 0xA7, 0x31, 0xB7, 0xA8};

class Communication {
public:
    void initialize();
    void sendJoystickData(const JoystickData& data) const;

private:
    static void onDataSent(const uint8_t* macAddr, esp_now_send_status_t status);
};

#endif
