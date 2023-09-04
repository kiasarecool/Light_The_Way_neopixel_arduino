#include <ArduinoOTA.h>  // for OTA
#include <ESP8266WiFi.h> // for WiFi
#include <Adafruit_NeoPixel.h>

// WiFi settings
const char* ssid = "YOUR WIFI NETWORK NAME";
const char* password = "YOUR WIFI PASSWORD";

#define PIN            15
#define NUMPIXELS      162
#define PIR_SENSOR_PIN 13

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

int pirState = LOW;
unsigned long lastMotionTime = 0;

void setup() {
  pinMode(PIR_SENSOR_PIN, INPUT);
  strip.begin();
  strip.setBrightness(230);
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

void loop() {
  int pirValue = digitalRead(PIR_SENSOR_PIN);

  if (pirValue == HIGH) {
    if (pirState == LOW) {
      pirState = HIGH;
      lightUpStrip();
    }
    lastMotionTime = millis();
  } else {
    if (pirState == HIGH && millis() - lastMotionTime > 30000) {
      turnOffStrip();
      pirState = LOW;
    }
  }

  // Handle OTA
  ArduinoOTA.handle();
}

void lightUpStrip() {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(204, 85, 0, 100));
    strip.show();
    delay(20);
  }
}

void turnOffStrip() {
  for (int j = 0; j <= 128; j += 5) {
    strip.setBrightness(j);
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, strip.Color(255, 0, 0, 0));
    }
    strip.show();
    delay(50);
  }
  for (int j = 128; j >= 0; j -= 5) {
    strip.setBrightness(j);
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, strip.Color(255, 0, 0, 0));
    }
    strip.show();
    delay(50);
  }
}
