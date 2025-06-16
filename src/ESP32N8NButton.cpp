#include "ESP32N8NButton.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti wifiMulti;

ESP32N8NButton::ESP32N8NButton(const char* ssid, const char* password, const char* url, uint8_t buttonPin)
  : _ssid(ssid), _password(password), _url(url), _buttonPin(buttonPin), _previouslyPressed(false) {}

void ESP32N8NButton::begin() {
  pinMode(_buttonPin, INPUT_PULLUP);
  wifiMulti.addAP(_ssid, _password);
}

void ESP32N8NButton::loop() {
  if (wifiMulti.run() == WL_CONNECTED) {
    bool pressed = (digitalRead(_buttonPin) == LOW);
    if (pressed && !_previouslyPressed) {
      sendRequest();
    }
    _previouslyPressed = pressed;
  }
}

void ESP32N8NButton::sendRequest() {
  HTTPClient http;
  String fullUrl = String(_url) + "?device=esp32&event=button_press";
  Serial.printf("[HTTP] GET %s\n", fullUrl.c_str());
  http.begin(fullUrl);
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.printf("[HTTP] Response code: %d\n", httpCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.printf("[HTTP] Request failed: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}
