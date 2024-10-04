/*
    pcf8574.h
    Version 1.0.0
    Created 03.10.2024
    Author: Linus81 aka Giuseppe Musciacchio (github.com/linus81)

    Copyright (C) 2024 Linus81 aka Giuseppe Musciacchio

    This file is part of the Arduino pcf8574.h library.

    The pcf8574.h library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    
    The Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU Lesser General Public License for more details.
    
    You should have received a copy of the GNU Lesser General Public
    License along with the GNU C Library; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PCF8574_H
#define PCF8574_H

#include <Arduino.h>
#include <Wire.h>

// Configuration structure for the PCF8574
struct PCF8574Config {
    int8_t sdaPin = -1;             // -1 indicates that no SDA pin has been specified
    int8_t sclPin = -1;             // -1 indicates that no SCL pin has been specified
    uint32_t clockSpeed = 100000;   // Default I2C frequency (100kHz)
    TwoWire *wire = &Wire;          // Pointer to the I2C bus (default: primary I2C bus)

    // Default constructor
    PCF8574Config() {}
};

class PCF8574 {

    private:
        uint8_t address;               // I2C address of the PCF8574
        uint8_t reg = 0xFF;            // Initial value of the register (0xFF in hexadecimal, equivalent to 255 decimal)
        TwoWire *wire;                 // Pointer to the I2C bus

    public:
        static const uint8_t DEFAULT_ADDRESS = 0x20; // Default I2C address for the PCF8574

        // Constructor with address and configuration
        PCF8574(uint8_t address = DEFAULT_ADDRESS, PCF8574Config config = PCF8574Config()) {
            this->address = address;             // Assign the specified address
            this->wire = config.wire;            // Assign the selected I2C bus

            // Check if the SDA and SCL pins have been specified
            if (config.sdaPin != -1 && config.sclPin != -1) {
                wire->begin(config.sdaPin, config.sclPin); // Begin I2C communication with specified pins
            } else {
                wire->begin(); // Use the default platform pins for I2C
            }

            // Set the I2C clock speed
            wire->setClock(config.clockSpeed);
        }

        bool available(); // Check if the PCF8574 is available for communication
        bool isValidPin(uint8_t pin); // Verify the validity of the pin

        // Method to write an 8-bit value to the register
        uint8_t WriteAll(uint8_t value);

        // Method to read an 8-bit value from the register
        uint8_t ReadAll();

        // Retrieve the stored value of the register (8 bits)
        uint8_t getReg();

        void ToggleAll();                            // Invert all bits in the register
        void SetAllPinMode(uint8_t mode);            // Set the mode (INPUT/OUTPUT) for all pins
        uint8_t ReverseByte(uint8_t byte);           // Invert the bits of a byte
        void ReverseAllBit();                        // Invert all bits in the current register
        uint8_t ShiftRight(uint8_t positions);       // Shift the register to the right by 'positions' bits
        uint8_t ShiftLeft(uint8_t positions);        // Shift the register to the left by 'positions' bits
        bool IsPinHigh(uint8_t pin);                 // Check if a specific pin is high
        bool IsPinLow(uint8_t pin);                  // Check if a specific pin is low
};

// Declarations of utility functions to operate on pins using uint8_t
void pinMode(PCF8574&, uint8_t pin, uint8_t mode); // Set the pin mode (INPUT/OUTPUT)
void digitalWrite(PCF8574&, uint8_t pin, uint8_t value); // Write a digital value to a pin
bool digitalRead(PCF8574&, uint8_t pin); // Read the digital value from a pin
void digitalToggle(PCF8574&, uint8_t pin); // Toggle the state of a pin


#endif /* PCF8574_H */



