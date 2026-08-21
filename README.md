# 🔘⚡ ESP32N8NButton

**Trigger n8n workflows from a physical ESP32 button using a lightweight Arduino library and HTTP webhooks.**

ESP32N8NButton connects the physical world to **n8n automation workflows**.

Pressing a button connected to an ESP32 sends an HTTP `GET` request to an n8n webhook. From there, the workflow can execute virtually any automation supported by n8n: send a message, launch a backup, request data, control another service, start an AI Agent, or provide a physical **human-in-the-loop** approval.

The library is intentionally small and exposes a simple API:

```cpp
begin()
loop()
```

The reference build uses a **DFRobot Beetle ESP32-C3**, whose onboard BOOT button can be used without adding any external components.

---

# ✨ Features

* 🔘 Trigger n8n workflows from a physical button
* 📡 ESP32 Wi-Fi connectivity
* 🌐 HTTP `GET` webhook requests
* 🪶 Lightweight Arduino library
* ⚙️ Simple `begin()` + `loop()` API
* 🔄 Automatic Wi-Fi reconnection through `WiFiMulti`
* 🚫 One request per button press rather than continuous triggering while held
* 🔧 Configurable GPIO
* 🧩 Compatible with different ESP32 boards
* 🧠 Suitable for human-in-the-loop AI workflows
* 📦 Available through Arduino Library Manager
* 📦 Available through PlatformIO Registry
* 📜 MIT licensed

---

# 🧠 Concept

A normal n8n workflow is usually triggered by software:

```text
Web form
API
Schedule
Email
Chat
Webhook
```

ESP32N8NButton adds a physical input:

```text
               ┌──────────────┐
               │    Button    │
               └──────┬───────┘
                      │
                      ▼
               ┌──────────────┐
               │    ESP32     │
               │              │
               │ Wi-Fi        │
               │ HTTP Client  │
               └──────┬───────┘
                      │
                      │ HTTP GET
                      ▼
               ┌──────────────┐
               │ n8n Webhook  │
               └──────┬───────┘
                      │
                      ▼
              ┌────────────────┐
              │  n8n Workflow  │
              │                │
              │ APIs           │
              │ AI Agents      │
              │ Messaging      │
              │ Databases      │
              │ Automation     │
              └────────────────┘
```

The ESP32 does not need to understand the workflow.

Its only job is:

```text
Detect button press
        ↓
Connect to Wi-Fi
        ↓
Call webhook
```

All automation logic remains inside n8n.

---

# 📡 Request format

Every valid button press generates:

```text
GET <WEBHOOK_URL>?device=esp32&event=button_press
```

For example:

```text
https://example.com/webhook/my-button?device=esp32&event=button_press
```

The two query parameters are:

| Parameter | Value          |
| --------- | -------------- |
| `device`  | `esp32`        |
| `event`   | `button_press` |

The request is created in the library with:

```cpp
String fullUrl =
    String(_url) +
    "?device=esp32&event=button_press";
```

This allows the n8n workflow to identify the source and event without requiring a JSON request body.

---

# ⚙️ How the library works

```text
ESP32 starts
     │
     ▼
button configured as INPUT_PULLUP
     │
     ▼
Wi-Fi credentials registered
     │
     ▼
loop()
     │
     ▼
Wi-Fi connected?
     │
     ▼
Read button GPIO
     │
     ▼
HIGH → LOW transition?
     │
     ├── No ──→ Continue
     │
     └── Yes
          │
          ▼
       HTTP GET
          │
          ▼
     n8n Webhook
          │
          ▼
 Print HTTP response
```

---

# 🔘 Button detection

The button pin is configured as:

```cpp
pinMode(_buttonPin, INPUT_PULLUP);
```

This means the button should normally read:

```text
HIGH
```

and become:

```text
LOW
```

when pressed.

The library checks:

```cpp
bool pressed =
    (digitalRead(_buttonPin) == LOW);
```

A request is only sent when the state changes from not pressed to pressed:

```cpp
if (pressed && !_previouslyPressed) {
    sendRequest();
}
```

Holding the button down therefore produces only one webhook request.

The next request can occur after the button is released and pressed again.

---

# 🧰 Hardware

The reference project uses:

| Qty | Component                   | Link                                                                                                                           |
| --: | --------------------------- | ------------------------------------------------------------------------------------------------------------------------------ |
|   1 | **DFRobot Beetle ESP32-C3** | [DFRobot](https://www.dfrobot.com/product-2566.html?tracking=hOuIhw4fDaJRTdy4abz04npbQC78dqxBkqVt7XMFYxEXj2s0ukWgm71wbut0ewUP) |

An external push button can also be used with any suitable ESP32 GPIO.

The library itself is not specific to the Beetle ESP32-C3.

---

# 🐞 Beetle ESP32-C3

The **DFRobot Beetle ESP32-C3** is a compact ESP32-C3 development board based on a 32-bit RISC-V processor.

Relevant features include:

* ESP32-C3
* 160 MHz CPU
* 400 KB SRAM
* 4 MB Flash
* Wi-Fi
* Bluetooth 5 LE
* USB-C
* battery charging support
* 13 digital I/O pins
* onboard BOOT button

The reference project uses the onboard:

```text
BOOT → GPIO 9
```

button.

This means the basic n8n button can be built without soldering an additional switch.

---

# 🔌 Wiring

## Using the Beetle ESP32-C3 onboard button

No additional button wiring is required.

Configure:

```cpp
#define BUTTON_GPIO 9
```

---

## Using an external button

Connect:

```text
ESP32 GPIO
    │
    │
    ├──── Push Button ──── GND
    │
```

Because the library uses:

```cpp
INPUT_PULLUP
```

an external pull-up resistor is not normally required.

Example:

```text
GPIO 4 ─── Push Button ─── GND
```

Then configure:

```cpp
#define BUTTON_GPIO 4
```

---

# 📦 Installation

## Arduino Library Manager

ESP32N8NButton is distributed as an Arduino library.

In Arduino IDE:

```text
Sketch
→ Include Library
→ Manage Libraries
```

Search for:

```text
ESP32N8NButton
```

and install the library.

Library index:

**[ESP32N8NButton — Arduino Libraries](https://www.arduinolibraries.info/libraries/esp32-n8-n-button)**

Current library version:

```text
1.0.0
```

Supported architecture:

```text
esp32
```

---

# 🛠️ Manual installation

Clone the repository:

```bash
git clone https://github.com/ronibandini/ESP32N8NButton.git
```

or download the repository as ZIP and install it using:

```text
Arduino IDE
→ Sketch
→ Include Library
→ Add .ZIP Library
```

---

# 🚀 Basic example

The repository includes:

```text
examples/
└── BasicN8NButton/
    └── BasicN8NButton.ino
```

A minimal implementation looks like this:

```cpp
#include <ESP32N8NButton.h>

#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"

#define TARGET_URL "http://your-n8n-instance.com/webhook/..."

#define BUTTON_GPIO 9

ESP32N8NButton webhook(
    WIFI_SSID,
    WIFI_PASSWORD,
    TARGET_URL,
    BUTTON_GPIO
);

void setup() {
    Serial.begin(115200);
    webhook.begin();

    Serial.println(
        "ESP32 N8N Button trigger started..."
    );
}

void loop() {
    webhook.loop();
    delay(50);
}
```

---

# 📚 API

## Constructor

```cpp
ESP32N8NButton(
    const char* ssid,
    const char* password,
    const char* url,
    uint8_t buttonPin
);
```

### Parameters

| Parameter   | Description                  |
| ----------- | ---------------------------- |
| `ssid`      | Wi-Fi SSID                   |
| `password`  | Wi-Fi password               |
| `url`       | n8n webhook URL              |
| `buttonPin` | GPIO connected to the button |

Example:

```cpp
ESP32N8NButton webhook(
    "MyWiFi",
    "MyPassword",
    "https://n8n.example.com/webhook/button",
    9
);
```

---

## `begin()`

```cpp
webhook.begin();
```

Initializes:

* the button GPIO as `INPUT_PULLUP`
* the configured Wi-Fi network through `WiFiMulti`

Call once from:

```cpp
setup()
```

---

## `loop()`

```cpp
webhook.loop();
```

Performs:

* Wi-Fi connection management
* button-state polling
* press-edge detection
* webhook request triggering

Call continuously from the Arduino:

```cpp
loop()
```

---

# 📶 Wi-Fi

The library uses:

```cpp
WiFiMulti
```

and registers the configured network with:

```cpp
wifiMulti.addAP(
    _ssid,
    _password
);
```

During each library loop:

```cpp
wifiMulti.run()
```

checks whether Wi-Fi is available.

Button requests are processed when:

```cpp
wifiMulti.run() == WL_CONNECTED
```

---

# 🌐 HTTP request

When the button is pressed, the library creates an:

```cpp
HTTPClient
```

instance and performs:

```cpp
http.GET();
```

The request URL is printed to Serial:

```text
[HTTP] GET ...
```

If the request succeeds, the library prints:

```text
[HTTP] Response code: 200
```

followed by the returned body.

If the request fails, the HTTP error is printed instead.

---

# 🔄 n8n setup

## 1. Create a workflow

Create a new workflow in n8n.

Add a:

```text
Webhook
```

node.

---

## 2. Configure the webhook

Set the webhook method to:

```text
GET
```

Copy the production webhook URL.

It will look similar to:

```text
https://YOUR_N8N_HOST/webhook/xxxxxxxx
```

---

## 3. Connect your workflow

Connect the Webhook node to whatever automation should occur when the physical button is pressed.

For example:

```text
Webhook
   │
   ├── Send Telegram message
   │
   ├── Send WhatsApp message
   │
   ├── Run AI Agent
   │
   ├── Call API
   │
   ├── Start backup
   │
   ├── Update database
   │
   └── Request human approval
```

---

# 🔍 Reading the event in n8n

The ESP32 sends:

```text
device=esp32
event=button_press
```

These values can be used inside the workflow to identify the trigger.

The webhook receives a request equivalent to:

```text
GET /webhook/...
    ?device=esp32
    &event=button_press
```

This also allows the Webhook node to be shared with downstream logic that branches according to the received event.

---

# 🧑‍💻 Human-in-the-loop workflows

A physical button can provide an explicit approval step for automations and AI Agents.

Example:

```text
AI Agent prepares action
        │
        ▼
Wait for approval
        │
        ▼
Physical button
        │
        ▼
ESP32 webhook
        │
        ▼
Continue workflow
```

Possible approval scenarios include:

* sending a prepared message
* publishing generated content
* executing a deployment
* confirming an automation
* allowing a physical process to continue
* acknowledging an alert

For high-impact operations, the workflow should still validate the request and apply appropriate authorization controls.

---

# 🧪 Serial Monitor

The example uses:

```text
115200 baud
```

A successful interaction may look like:

```text
ESP32 N8N Button trigger started...

[HTTP] GET https://example.com/webhook/button?device=esp32&event=button_press
[HTTP] Response code: 200
Workflow was started
```

The Serial Monitor is useful for diagnosing:

* Wi-Fi connectivity
* incorrect webhook URLs
* HTTP errors
* n8n responses

---

# ⏱️ Debouncing

The example sketch includes:

```cpp
delay(50);
```

after each call to:

```cpp
webhook.loop();
```

This provides a simple delay between GPIO reads.

The library also records whether the button was previously pressed:

```cpp
bool _previouslyPressed;
```

which prevents repeated HTTP calls while the button remains held.

---

# 📁 Repository structure

```text
ESP32N8NButton/
├── examples/
│   └── BasicN8NButton/
│       └── BasicN8NButton.ino
│
├── src/
│   ├── ESP32N8NButton.cpp
│   └── ESP32N8NButton.h
│
├── LICENSE
├── README.md
├── keywords.txt
└── library.properties
```

### `ESP32N8NButton.cpp`

Implements:

* Wi-Fi management
* button detection
* HTTP requests
* serial response logging

### `ESP32N8NButton.h`

Defines the public library API.

### `BasicN8NButton.ino`

Minimal example demonstrating library initialization and polling.

### `library.properties`

Arduino library metadata:

```text
Name: ESP32N8NButton
Version: 1.0.0
Category: Communication
Architecture: esp32
License: MIT
```

---

# 🎥 Demo

**[▶️ n8n Physical Button demo on X](https://x.com/RoniBandini/status/1934617385643778056)**

The demonstration uses the Beetle ESP32-C3 onboard button to trigger an n8n workflow.

---

# 🔬 Ideas for extending the project

1. **🔘 Multiple buttons and events** — allow several GPIO inputs to send different event names to the same n8n webhook.

2. **🔐 Authenticated requests** — add configurable HTTP headers, tokens, and secure webhook authentication.

---

# 📰 External references

## 🛠️ Hackster.io

### n8n Physical Button

**[n8n Physical Button — Hackster.io](https://www.hackster.io/roni-bandini/n8n-physical-button-ddfa0f)**

The complete build tutorial covers:

* n8n Webhook configuration
* Beetle ESP32-C3 hardware
* onboard GPIO 9 button
* Arduino library installation
* Wi-Fi configuration
* webhook URL configuration
* example workflow uses
* project demo

Published June 16, 2025.

---

## 🛠️ DFRobot Maker Community

### n8n physical button with Beetle ESP32C3

**[Automate Workflows with n8n and ESP32C3 Button](https://community.dfrobot.com/makelog-317871.html)**

DFRobot Maker Community documents the project using the Beetle ESP32-C3.

The article includes:

* hardware configuration
* GPIO 9 onboard BOOT button
* n8n webhook setup
* ESP32N8NButton installation
* usage examples
* demo
* GitHub repository link

---

## 💬 Reddit — r/n8n

### How to add a physical Button to n8n

**[Read the r/n8n discussion](https://www.reddit.com/r/n8n/comments/1ldmjxn/how_to_add_a_physical_button_to_n8n/)**

The discussion also covers:

* human-in-the-loop approvals
* alternative physical-button designs
* webhook security
* desk automation
* messaging workflows

---

## 📦 Arduino Libraries

### ESP32N8NButton

**[ESP32N8NButton — Arduino Libraries](https://www.arduinolibraries.info/libraries/esp32-n8-n-button)**

The library is indexed as an Arduino Communication library for:

```text
esp32
```

with version:

```text
1.0.0
```

and links back to this repository.

---


## ✍️ Medium

### Botón físico para n8n

**[Botón físico para n8n — Medium](https://bandini.medium.com/bot%C3%B3n-f%C3%ADsico-para-n8n-6eab1a0e4c6d)**

Spanish-language article covering the physical-button concept, ESP32 configuration, and n8n webhook integration.

---

## ⚡ n8n

### n8n official social reference

**[n8n — LinkedIn](https://www.linkedin.com/posts/n8n_remember-the-n8n-physical-button-its-creator-activity-7364204732686475265-Px9r)**

n8n's official account later referenced the original **n8n physical button** when presenting the follow-up n8n Terminal project.

**[n8n — X](https://x.com/n8n_io/status/1958438951473000487)**

The official n8n X account also referenced the physical-button project as the predecessor to the screen-and-button terminal.

---

# 📚 Useful references

* **[n8n](https://n8n.io/)**
* **[n8n Webhook documentation](https://docs.n8n.io/integrations/builtin/core-nodes/n8n-nodes-base.webhook/)**
* **[Arduino](https://www.arduino.cc/)**
* **[ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)**
* **[DFRobot Beetle ESP32-C3](https://www.dfrobot.com/product-2566.html?tracking=hOuIhw4fDaJRTdy4abz04npbQC78dqxBkqVt7XMFYxEXj2s0ukWgm71wbut0ewUP)**

---

# 🔗 You may also be interested in...

Other projects by **Roni Bandini** combining n8n, ESP32 hardware, physical controls, and AI automation.

## 🖥️🔘 n8n Terminal

**Physical buttons, screen, RGB feedback, audio, and QR codes for n8n workflows.**

n8n Terminal extends the physical-button idea into a dedicated ESP32-based interface that can both send information to n8n and display workflow responses.

**[github.com/ronibandini/n8nTerminal](https://github.com/ronibandini/n8nTerminal)**

---

## 🟩🤖 n8n Matrix Display

**32×16 RGB LED information display driven by ESP32, n8n, APIs, and AI.**

n8n generates a compact information feed that the ESP32 displays as scrolling text between retro animations.

**[github.com/ronibandini/n8nMatrixDisplay](https://github.com/ronibandini/n8nMatrixDisplay)**

---

## 🖥️🤖 AI Retro Console

**Repurpose an old notebook as a text-based interface for n8n workflows and AI Agents.**

The console uses natural-language commands to interact with n8n integrations such as Gmail, Calendar, Telegram, RSS, market data, and Linux commands.

**[github.com/ronibandini/AIRetroConsole](https://github.com/ronibandini/AIRetroConsole)**

---

# 🔐 Security notes

## Webhook URL

The webhook URL is stored directly in the Arduino sketch:

```cpp
#define TARGET_URL "http://your-n8n-instance.com/webhook/..."
```

Anyone who obtains a usable webhook URL may potentially trigger the associated workflow unless additional controls are implemented.

Avoid publishing configured webhook URLs.

---

## Authentication

Version `1.0.0` sends a simple HTTP `GET` request and does not add custom authorization headers.

If the workflow requires:

```text
API key
Bearer token
Basic authentication
custom header
signed request
```

the library must be extended accordingly or the authentication architecture implemented elsewhere.

---

## Credentials

Wi-Fi credentials are compiled into the ESP32 firmware:

```cpp
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"
```

Do not commit configured credentials to a public repository.

---

## Delivery

A failed HTTP request is reported through Serial but is not automatically queued for later delivery.

A temporary network or n8n outage can therefore cause a button event to be lost.

Workflows requiring guaranteed delivery should add retry, acknowledgement, or queueing logic.

---

## Workflow permissions

A physical button can be used as a human approval mechanism, but possession of or access to the device should not automatically grant unlimited workflow authority.

Apply additional authorization for workflows capable of:

* deleting data
* publishing content
* spending money
* opening locks
* deploying software
* changing infrastructure
* executing privileged commands

---

# 📜 License

ESP32N8NButton is released under the **MIT License**.

See [`LICENSE`](LICENSE) for details.

---

# 👤 Author

**Roni Bandini**

Maker, AI developer, electronic artist and writer.

* 🐙 GitHub: **[@ronibandini](https://github.com/ronibandini)**
* 💼 LinkedIn: **[Roni Bandini](https://www.linkedin.com/in/ronibandini/)**
* 📸 Instagram: **[@ronibandini](https://www.instagram.com/ronibandini/)**
* 🐦 X: **[@RoniBandini](https://x.com/RoniBandini)**
* ✍️ Medium: **[bandini.medium.com](https://bandini.medium.com/)**
* 🛠️ Hackster: **[Roni Bandini](https://www.hackster.io/roni-bandini)**

Contributions, forks, additional button events, authentication methods, and new n8n integrations are welcome.
