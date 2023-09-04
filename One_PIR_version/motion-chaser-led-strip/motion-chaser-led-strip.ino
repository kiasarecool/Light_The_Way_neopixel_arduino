#include <Adafruit_NeoPixel.h>

#define PIN            D8  // Define the pin where the data line is connected to
#define NUMPIXELS      162  // Number of pixels in the strip
#define PIR_SENSOR_PIN D7  // Define the pin where the PIR sensor is connected to

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

int pirState = LOW; // Initialize the PIR state to low (no motion)
unsigned long lastMotionTime = 0; // Timestamp when the last motion was detected

void setup() {
  pinMode(PIR_SENSOR_PIN, INPUT);
  strip.begin(); // Initialize the strip
  strip.setBrightness(80); // Set brightness to x out of 255
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  int pirValue = digitalRead(PIR_SENSOR_PIN); // Read the value from the PIR sensor

  if (pirValue == HIGH) { // If motion is detected
    if (pirState == LOW) { // If it's the first time motion has been detected
      pirState = HIGH; // Update the state to high
      lightUpStrip(); // Call the function to light up the strip
    }
    lastMotionTime = millis(); // Update the last motion time
  } else { // If no motion is detected
    if (pirState == HIGH && millis() - lastMotionTime > 30000) { // If x seconds have passed since the last motion
      turnOffStrip(); // Call the function to turn off the strip
      pirState = LOW; // Update the state to low
    }
  }
}

void lightUpStrip() {
  for (int i = NUMPIXELS - 1; i >= 0; i--) {
    strip.setPixelColor(i, strip.Color(204, 85, 0, 100)); // Set the pixel color to fuscha (adjust as needed)
    strip.show();
    delay(20); // Delay for 20 milliseconds to control the speed of progression
  }
}

void turnOffStrip() {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setBrightness(50); // Set brightness to 128 out of 255
    strip.setPixelColor(i, strip.Color(30, 0, 0, 0)); // Turn off the pixel or dim low
    strip.show();
    delay(20); // Delay for 20 milliseconds to control the speed of progression
  }
}
