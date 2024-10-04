#include <Wire.h>
#include "PCF8574_LH.h"

PCF8574_LH pcf;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    // Initialize the PCF8574
    if (!pcf.available()) {
        Serial.println("PCF8574 not found!");
        while (1);
    }

    // Set all pins to OUTPUT mode
    pcf.SetAllPinMode(OUTPUT);

    // Initialize the register to a known state
    pcf.WriteAll(0b00000001);  // Start with the first bit set to HIGH
}

void loop() {
    // Shift the bits in the register to the right
    pcf.ShiftRight(1);
    delay(500);

    // Shift the bits in the register to the left
    pcf.ShiftLeft(1);
    delay(500);
}
