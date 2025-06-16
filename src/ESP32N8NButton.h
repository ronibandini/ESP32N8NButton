#ifndef ESP32N8NButton_H
#define ESP32N8NButton_H

#include <Arduino.h>

class ESP32N8NButton {
  public:
    ESP32N8NButton(const char* ssid, const char* password, const char* url, uint8_t buttonPin);
    void begin();
    void loop();

  private:
    const char* _ssid;
    const char* _password;
    const char* _url;
    uint8_t _buttonPin;
    bool _previouslyPressed;
    void sendRequest();
};

#endif
