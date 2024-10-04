#include <Wire.h>
#include "PCF8574_LH.h"

PCF8574_LH pcf;

// Pin definitions
const uint8_t BUTTON_PIN = 0;  // Pin 0 on the PCF8574
const uint8_t LED_PIN = 1;     // Pin 1 on the PCF8574

void setup() {
    Serial.begin(9600);
    while (!Serial);

    // Initialize the PCF8574
    if (!pcf.available()) {
        Serial.println("PCF8574 not found!");
        while (1);
    }

    // Set button pin as INPUT and LED pin as OUTPUT
    pinMode(pcf, BUTTON_PIN, INPUT);
    pinMode(pcf, LED_PIN, OUTPUT);
}

void loop() {
    // Read the state of the button
    bool buttonState = digitalRead(pcf, BUTTON_PIN);
    
    // Toggle the LED based on the button state
    digitalWrite(pcf, LED_PIN, buttonState ? LOW : HIGH);

    delay(200);  // Small debounce delay
}
