# ESP32N8NButton

Trigger [N8N](https://n8n.io/) workflows from an ESP32 device button using a simple HTTP GET call 

Roni Bandini, Buenos Aires, Argentina, June 2025

![ESP32PhysicalButton](https://github.com/user-attachments/assets/a3db4a44-663e-46c5-b1c5-b05d09122f68)


## 📦 Overview

`ESP32N8NButton` is a lightweight Arduino library for ESP32 that sends HTTP GET requests to a user-defined webhook URL. 
It's designed to trigger a N8N node using a button. 

Great for:

- Physical IoT triggers for workflows
- Simple smart buttons
- ESP32-to-N8N communication without external services

## 🔧 Features

- Sends HTTP GET request on button press (GPIO)
- WiFi connection via built-in ESP32 WiFi
- Simple API (`begin()` + `handle()`)
- Designed to work with N8N webhooks

### 📥 Installation

1. Install with Arduino IDE, Sketch, Include library, Add Zip Library
2. Open the BasicWebHook.ino example
3. Edit WiFi credentials, Webhook URL and GPIO 
4. Press the button
