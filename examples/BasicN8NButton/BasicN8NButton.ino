// Basic ESP32 N8N button trigger example
// Roni Bandini, June 2025
// https://bandini.medium.com/
// Edit WiFi credentials, URL and button GPIO before uploading

#include <ESP32N8NButton.h>

#define WIFI_SSID     "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"
#define TARGET_URL    "http://your-n8n-instance.com/webhook/..."
#define BUTTON_GPIO   0  // GPIO for button

ESP32N8NButton webhook(WIFI_SSID, WIFI_PASSWORD, TARGET_URL, BUTTON_GPIO);

void setup() {
  Serial.begin(115200);
  webhook.begin();
  Serial.println("ESP32 N8N Button trigger started...");
}

void loop() {
  webhook.loop();
  delay(50); // Simple debounce
}