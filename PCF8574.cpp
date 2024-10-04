/*
    pcf8574.cpp
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

#include "PCF8574.h"

bool PCF8574::available() {
    // Attempt to initiate a transmission to the PCF8574 address
    wire->beginTransmission(address);
    int result = wire->endTransmission(); // End the transmission

    // If endTransmission returns 0, the device is available
    return (result == 0);
}

// Write to the register (8 bits)
// Returns 0 for success, 1 for transmission error, 2 for address error
uint8_t PCF8574::WriteAll(uint8_t value) {
    wire->beginTransmission(address);
    wire->write(value);
    int result = wire->endTransmission();
    if (result == 0) this->reg = value; // Update the stored register value if successful
    return result;
}

// Read from the register (8 bits)
uint8_t PCF8574::ReadAll() {
    int result = wire->requestFrom(address, (uint8_t) 1);
    // if (result == 0) return 0xFF;  // Error, return 0xFF
    if (result == 0 || wire->available() == 0) {
       Serial.println("Error: No byte received from PCF8574.");
       return 0xFF;  // Error, return 0xFF
    }
    return wire->read(); // Return the read value
}

// Return the current value of the register
uint8_t PCF8574::getReg() {
    return reg; // Return the stored register value
}

// Invert all bits in the register
void PCF8574::ToggleAll() {
    reg = ~reg; // Bitwise NOT operation to invert all bits
    WriteAll(reg); // Write the inverted value to the register
}

// Set the same mode (INPUT/OUTPUT) for all pins
void PCF8574::SetAllPinMode(uint8_t mode) {
    if (mode == OUTPUT) {
        reg = 0x00; // Set all pins to OUTPUT
    } else {
        reg = 0xFF; // Set all pins to INPUT (default HIGH for pull-up)
    }
    WriteAll(reg); // Write the updated register value
}

// Reverse the bits of a single byte
uint8_t PCF8574::ReverseByte(uint8_t byte) {
    byte = ((byte & 0xF0) >> 4) | ((byte & 0x0F) << 4);
    byte = ((byte & 0xCC) >> 2) | ((byte & 0x33) << 2);
    byte = ((byte & 0xAA) >> 1) | ((byte & 0x55) << 1);
    return byte; // Return the reversed byte
}

// Reverse all bits in the current register
void PCF8574::ReverseAllBit() {
    reg = ReverseByte(reg); // Reverse the current register value
    WriteAll(reg); // Write the updated value to the register
}

// Shift the register right by 'positions' bits
// and return the new value of the register
uint8_t PCF8574::ShiftRight(uint8_t positions) {
    // Check if the number of positions to shift is valid
    if (positions > 0 && positions < 8) {
        reg >>= positions; // Perform right shift
    } else if (positions >= 8) {
        reg = 0; // If shifting 8 or more positions, set the register to 0
    }
    WriteAll(reg); // Write the updated value to the register
    return reg; // Return the new register value
}

// Shift the register left by 'positions' bits
// and return the new value of the register
uint8_t PCF8574::ShiftLeft(uint8_t positions) {
    // Check if the number of positions to shift is valid
    if (positions > 0 && positions < 8) {
        reg <<= positions; // Perform left shift
    } else if (positions >= 8) {
        reg = 0; // If shifting 8 or more positions, set the register to 0
    }
    WriteAll(reg); // Write the updated value to the register
    return reg; // Return the new register value
}

// Check if a specific pin is high
bool PCF8574::IsPinHigh(uint8_t pin) {
    if (pin < 8) {
        return (reg & (1 << pin)) != 0; // Return true if the pin is high
    }
    return false; // Default value for invalid pin
}

// Check if a specific pin is low
bool PCF8574::IsPinLow(uint8_t pin) {
    if (pin < 8) {
        return (reg & (1 << pin)) == 0; // Return true if the pin is low
    }
    return false; // Default value for invalid pin
}

// Set the mode of a specific pin
void pinMode(PCF8574& pcf, uint8_t pin, uint8_t mode) {
    // Check if the pin is valid
    if (!pcf.isValidPin(pin)) {
        Serial.println("Error: Invalid pin.");
        return; // Handle the error
    }

    // Update the register using getReg() method
    uint8_t reg = pcf.getReg();
    uint8_t mask = (1 << pin);
    if (mode == INPUT) {
        reg |= mask; // Set the pin's bit to 1 for INPUT
    } else {
        reg &= ~mask; // Set the pin's bit to 0 for OUTPUT
    }

    // Write the updated register value
    pcf.WriteAll(reg);
}

// Set the digital value of a specific pin
void digitalWrite(PCF8574& pcf, uint8_t pin, bool value) {
    // Check if the pin is valid
    if (!pcf.isValidPin(pin)) {
        Serial.println("Error: Invalid pin.");
        return; // Handle the error
    }

    // Update the register using getReg() method
    uint8_t reg = pcf.getReg();
    uint8_t mask = (1 << pin);
    if (value) {
        reg &= ~mask; // Set the pin's bit to 0 for HIGH
    } else {
        reg |= mask; // Set the pin's bit to 1 for LOW
    }

    // Write the updated register value
    pcf.WriteAll(reg);
}

// Read the digital value of a specific pin
bool digitalRead(PCF8574& pcf, uint8_t pin) {
    // Check if the pin is valid
    if (!pcf.isValidPin(pin)) {
        Serial.println("Error: Invalid pin.");
        return false; // Handle the error
    }

    // Read the register and return the pin value
    uint8_t currentState = pcf.ReadAll();
    return !(currentState & (1 << pin)); // Return LOW if the bit is 0, HIGH if it is 1
}

// Toggle the digital value of a specific pin
void digitalToggle(PCF8574& pcf, uint8_t pin) {
    // Check if the pin is valid
    if (!pcf.isValidPin(pin)) {
        Serial.println("Error: Invalid pin.");
        return; // Handle the error
    }

    // Toggle the pin's bit using getReg() method
    uint8_t reg = pcf.getReg();
    uint8_t mask = (1 << pin);
    reg ^= mask; // Toggle the pin's bit

    // Write the updated register value
    pcf.WriteAll(reg);
}
