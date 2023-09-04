Stair Light with Dual PIR Sensors
Project Description
This project involves an LED strip that is controlled by two PIR motion sensors at both ends of a stairwell. The LED strip lights up in one direction when one sensor detects motion and in the opposite direction when the other sensor is triggered. The strip will turn off automatically if no motion is detected for a period of time.

Features
Bidirectional lighting: Lights up in the direction corresponding to the triggered PIR sensor.
Timeout: Turns off automatically if no motion is detected for 10 seconds.
WiFi Enabled: Uses ESP8266 for OTA updates.
Hardware Requirements
1 x ESP8266 (NodeMCU or similar)
1 x LED Strip (162 pixels in my case, sk6812 GRBW)
2 x PIR Motion Sensors
Jumper Wires
Power Supply for the LED Strip
Resistor and Capacitor for signal smoothing (Optional, I did not use)
Software Requirements
Arduino IDE
Adafruit NeoPixel library
ArduinoOTA library for Over-the-Air updates
Pin Configuration
LED Strip: Pin 15
PIR Sensor 1: Pin 13
PIR Sensor 2: Pin 14
Installation
Clone this repository.
Open the project using Arduino IDE.
Install the required libraries (Adafruit_NeoPixel and ArduinoOTA).
Update your WiFi credentials in the code.
Upload the code to your ESP8266.
Usage
Walk past either of the PIR sensors to activate the LED strip. It will light up in a direction corresponding to the triggered sensor and will turn off after 10 seconds of inactivity.

Contributing
Feel free to submit pull requests to enhance the functionalities of this stair light project.

License
This project is under the MIT License. See the LICENSE.md file for details.

