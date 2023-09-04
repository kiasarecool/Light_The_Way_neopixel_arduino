#include <ArduinoOTA.h>  // for OTA
#include <ESP8266WiFi.h> // for WiFi
#include <Adafruit_NeoPixel.h>

// WiFi settings
const char* ssid = "YOUR SSID";
const char* password = "YOUR PASSWORD";

#define PIN            15
#define NUMPIXELS      162
#define PIR_SENSOR_PIN 13
#define PIR_SENSOR_PIN2 14  // Second PIR sensor

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

int pirState = LOW;
int pirState2 = LOW;
//int lastTriggeredSensor = 0;  // 0 for None, 1 for PIR_SENSOR_PIN, 2 for PIR_SENSOR_PIN2
bool isStripOn = false;  // true if the LED strip is on, false if off
unsigned long lastMotionTime = 0;
//unsigned long lastMotionTime2 = 0;

void setup() {
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(PIR_SENSOR_PIN2, INPUT);  // Initialize the second PIR sensor
  strip.begin();
  strip.show();

  // Initialize the WiFi module
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }

  // Initialize OTA
  ArduinoOTA.begin();
}

int lastTriggeredSensor = 0;  // 0 = none, 1 = PIR1, 2 = PIR2

void loop() {
  int pirValue = digitalRead(PIR_SENSOR_PIN);
  int pirValue2 = digitalRead(PIR_SENSOR_PIN2);

  if (pirValue == HIGH || pirValue2 == HIGH) {
    if (pirValue == HIGH && lastTriggeredSensor == 0) {
      lastTriggeredSensor = 1;
    }
    if (pirValue2 == HIGH && lastTriggeredSensor == 0) {
      lastTriggeredSensor = 2;
    }
    lastMotionTime = millis();

    if (pirValue == HIGH) {
      lightUpStrip();
    }
    if (pirValue2 == HIGH) {
      lightUpStripReverse();
    }

  } else {
    if (millis() - lastMotionTime > 10000) {
      if (lastTriggeredSensor == 1) {
        turnOffStrip();
      } else if (lastTriggeredSensor == 2) {
        turnOffStripReverse();
      }
      lastTriggeredSensor = 0;
    }
  }

  // Handle OTA
  ArduinoOTA.handle();
}


void lightUpStrip() {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setBrightness(240);
    strip.setPixelColor(i, strip.Color(224, 100, 20, 255));
    strip.show();
    delay(8);
  }
}

void lightUpStripReverse() {
  for (int i = NUMPIXELS - 1; i >= 0; i--) {
    strip.setBrightness(240);
    strip.setPixelColor(i, strip.Color(224, 100, 20, 255));
    strip.show();
    delay(8);
  }
}

void turnOffStrip() {
  for (int i = 0; i < NUMPIXELS; i++) {
   // strip.setBrightness(40);
    strip.setPixelColor(i, strip.Color(0, 0, 30, 0));
    strip.show();
    delay(8);
  }
}

void turnOffStripReverse() {
  for (int i = NUMPIXELS - 1; i >= 0; i--) { // Starts from 0 to NUMPIXELS - 1
   // strip.setBrightness(40);
    strip.setPixelColor(i, strip.Color(0, 0, 30, 0)); // Turn off the pixel or dim low
    strip.show();
    delay(8);  // Delay for 8 milliseconds to control the speed of progression
  }
}