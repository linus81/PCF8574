#include <Wire.h>
#include "PCF8574_LH.h"

// Pin definitions
const int SDA_PIN = 21;  // Custom SDA pin for ESP32 
const int SCL_PIN = 22;  // Custom SCL pin for ESP32 
const uint32_t CLOCK_SPEED = 100000;  // 400kHz I2C speed

// Create a PCF8574Config structure with custom settings
PCF8574Config customConfig;

// Declare the PCF8574 instance globally without initialization
PCF8574_LH pcf; // Declaration only

void setup() {
    Serial.begin(9600);
    while (!Serial);

    // Set custom I2C configuration
    customConfig.sdaPin = SDA_PIN;     
    customConfig.sclPin = SCL_PIN;      
    customConfig.clockSpeed = CLOCK_SPEED;

    // Initialize the PCF8574 instance with custom configuration
    pcf = PCF8574_LH(0x20, customConfig); // Initialize with customConfig

    // Check if PCF8574 is available
    if (pcf.available()) {
        Serial.println("PCF8574 with custom I2C configuration initialized successfully!");
    } else {
        Serial.println("Failed to initialize PCF8574!");
        while (1);
    }

    // Set all pins to OUTPUT
    pcf.SetAllPinMode(OUTPUT);

    // Set initial value to all HIGH (0xFF)
    pcf.WriteAll(0xFF);
}

void loop() {
    // Toggle all pins
    pcf.ToggleAll();
    delay(1000);
}
