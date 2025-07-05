# Smart-IoT-Smoke-Weather-Monitoring-System-with-Mobile-Integration

---

### Project Summary

A complete IoT-based environmental monitor using an ESP32, capable of:

* Reading temperature and humidity using DHT11
* Detecting smoke/gas via MQ2 sensor
* Displaying data on OLED 128x64 screen
* Pushing sensor data to Blynk mobile application
* Triggering a buzzer alert on smoke detection
* Showing real-time clock (date and time) on OLED

---

### Hardware Used

1. ESP32 Dev Board
2. DHT11 Temperature and Humidity Sensor
3. MQ2 Gas Sensor (Flying Fish)
4. OLED Display (SSD1306, 128x64, I2C)
5. Active Buzzer Module
6. Jumper Wires
7. Breadboard
8. Power via USB or 4xAA Battery Pack (6V to VIN)

---

### Wiring Summary

**DHT11:**

* VCC → 3.3V
* GND → GND
* DATA → GPIO 15

**MQ2:**

* VCC → 3.3V or VIN
* GND → GND
* AO → GPIO 34
* DO → GPIO 27

**OLED (I2C):**

* VCC → 3.3V
* GND → GND
* SDA → GPIO 21
* SCL → GPIO 22

**Buzzer:**

* * → GPIO 25
* – → GND

---

### Power Supply Options

* USB power during development
* 4xAA Battery Pack (6V) to VIN and GND
* Ensure common GND for all modules

---

### Blynk Setup

* Platform: [https://blynk.cloud](https://blynk.cloud)
* Template created with:

  * V0: Temperature (float)
  * V1: Humidity (float)
  * V2: Smoke (int)
  * V3: Smoke Alert (0 or 1)
* Blynk Auth Token copied and used in code

---

### Initial Mistakes and Fixes

| Mistake                        | Fix                                     |
| ------------------------------ | --------------------------------------- |
| OLED screen blinking or fading | Used 3.3V only, removed overload        |
| Blynk not connecting           | Checked Auth Token and WiFi             |
| Smoke values stuck             | Used AO pin for analog read             |
| OLED not printing              | Ran I2C scanner to confirm 0x3C address |
| ESP32 overheating              | Never use 6V on 3.3V pin (only VIN)     |

---

### Final Tips to Keep in Mind

* Use Wire.begin(21, 22) for ESP32 I2C
* Use Adafruit libraries, not unofficial ones
* Double-check power source and GND commonality
* Push sensor data every 2 seconds (not too frequent)
* Use I2C scanner if OLED is not detected
* Use analogRead for smoke level, digitalRead for alerts
* Use configTime() to set RTC from NTP server

---

### Final Verdict

This project is a solid entry-level IoT and Embedded system. It provides:

* Real-time feedback via OLED
* Mobile integration through Blynk
* Safety alert through buzzer
* Time-stamped data display

Ideal for smart home applications, industrial safety setups, or college-level projects.

---

### Suggested Upgrades

* Add a relay to control an exhaust fan
* Add push notification via Telegram
* Replace DHT11 with DHT22 or BME280 for better accuracy
* Use Firebase or Google Sheets for logging
* Solar power with battery backup
* Add logging timestamp to Blynk via V4

