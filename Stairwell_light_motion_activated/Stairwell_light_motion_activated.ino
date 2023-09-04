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
int lastTriggeredSensor = 0;  // 1 for PIR_SENSOR_PIN, 2 for PIR_SENSOR_PIN2
unsigned long lastMotionTime = 0;
unsigned long lastMotionTime2 = 0;

void setup() {
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(PIR_SENSOR_PIN2, INPUT);  // Initialize the second PIR sensor
  strip.setBrightness(220);
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


void loop() {
  int pirValue = digitalRead(PIR_SENSOR_PIN);
  int pirValue2 = digitalRead(PIR_SENSOR_PIN2);
  unsigned long currentTime = millis();

  if (pirValue == HIGH) {
    pirState = HIGH;
    lightUpStrip();
    lastMotionTime = currentTime;
    lastTriggeredSensor = 1;
  }

  if (pirValue2 == HIGH) {
    pirState2 = HIGH;
    lightUpStripReverse();
    lastMotionTime2 = currentTime;
    lastTriggeredSensor = 2;
  }

  if (pirValue == LOW && pirValue2 == LOW) {
    if (pirState == HIGH && currentTime - lastMotionTime > 10000) {
      if (lastTriggeredSensor == 1) {
        turnOffStrip();  // Turns off the LED strip in the normal direction
      } else {
        turnOffStripReverse();  // Turns off the LED strip in the reverse direction
      }
      pirState = LOW;
    }

    if (pirState2 == HIGH && currentTime - lastMotionTime2 > 10000) {
      if (lastTriggeredSensor == 2) {
        turnOffStripReverse();  // Turns off the LED strip in the reverse direction
      } else {
        turnOffStrip();  // Turns off the LED strip in the normal direction
      }
      pirState2 = LOW;
    }
  }

  // Handle OTA
  ArduinoOTA.handle();
}

void lightUpStrip() {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setBrightness(220);
    strip.setPixelColor(i, strip.Color(204, 90, 0, 100));
    strip.show();
    delay(8);
  }
}

void lightUpStripReverse() {
  for (int i = NUMPIXELS - 1; i >= 0; i--) {
    strip.setBrightness(220);
    strip.setPixelColor(i, strip.Color(204, 90, 0, 100));
    strip.show();
    delay(8);
  }
}

void turnOffStrip() {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setBrightness(20);
    strip.setPixelColor(i, strip.Color(255, 0, 60, 0));
    strip.show();
    delay(8);
  }
}

void turnOffStripReverse() {
  for (int i = 0; i < NUMPIXELS; i++) {  // Starts from 0 to NUMPIXELS - 1
    strip.setBrightness(20);
    strip.setPixelColor(i, strip.Color(255, 0, 60, 0)); // Turn off the pixel or dim low
    strip.show();
    delay(8);  // Delay for 8 milliseconds to control the speed of progression
  }
}