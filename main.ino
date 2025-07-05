#define BLYNK_TEMPLATE_ID "Your_Template_ID"
#define BLYNK_TEMPLATE_NAME "Your_Project"
#define BLYNK_AUTH_TOKEN "Your_Auth_Token"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "time.h"

// WiFi credentials
char ssid[] = "Your_SSID";
char pass[] = "Your_PASSWORD";

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT11
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ2
#define MQ2_AO 34
#define MQ2_DO 27
#define BUZZER 25

// Time settings
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;
const int daylightOffset_sec = 0;

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(MQ2_DO, INPUT);
  pinMode(BUZZER, OUTPUT);
  dht.begin();

  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (1);
  }

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  timer.setInterval(2000L, sendSensorData);

  display.clearDisplay();
  display.setCursor(10, 10);
  display.println("Booting...");
  display.display();
  delay(2000);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensorData() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  int smoke = analogRead(MQ2_AO);
  int alert = digitalRead(MQ2_DO);

  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, humi);
  Blynk.virtualWrite(V2, smoke);
  Blynk.virtualWrite(V3, alert == LOW ? 1 : 0);

  if (alert == LOW) {
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
  }

  // Get Time
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  char timeStr[10];
  strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
  char dateStr[20];
  strftime(dateStr, sizeof(dateStr), "%d %b %Y", &timeinfo);

  // OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("T:"); display.print(temp); display.print("C");
  display.setCursor(70, 0);
  display.print("H:"); display.print(humi); display.print("%");
  display.setCursor(0, 12);
  display.print("Smoke:"); display.print(smoke);
  display.setCursor(0, 24);
  display.print((alert == LOW) ? "SMOKE DETECTED" : "Air Clean");
  display.setCursor(0, 40);
  display.print(dateStr);
  display.setCursor(0, 52);
  display.print(timeStr);
  display.display();
}
