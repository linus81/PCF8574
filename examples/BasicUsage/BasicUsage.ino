#include <Wire.h>
#include "PCF8574_LH.h"

// PCF8574 I2C address (default: 0x20)
PCF8574 pcf;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    // Initialize the PCF8574
    Serial.println("Initializing PCF8574...");
    if (pcf.available()) {
        Serial.println("PCF8574 found!");
    } else {
        Serial.println("PCF8574 not found!");
        while (1);
    }

    // Set all pins to OUTPUT mode
    pcf.SetAllPinMode(OUTPUT);
}

void loop() {
    // Toggle all pins
    Serial.println("Toggling all pins...");
    pcf.ToggleAll();
    delay(1000);
}
