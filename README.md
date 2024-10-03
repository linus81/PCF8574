# PCF8574
Arduino library for PCF8574 - 8 channel I2C IO expander.

# PCF8574 Library for Arduino

The `PCF8574` library provides a simple interface for controlling the PCF8574 I/O expander using the I2C communication protocol. It allows you to read and write values to the PCF8574's registers, configure pin modes, and perform bit manipulations.

## Features

- Check the availability of the PCF8574 device.
- Read and write 8-bit values from/to the PCF8574.
- Set all pins as INPUT or OUTPUT simultaneously.
- Toggle the state of all pins.
- Shift bits left or right in the register.
- Check the state of individual pins (HIGH/LOW).

## Installation

1. Download or clone this repository.
2. Copy the `PCF8574` folder into your Arduino libraries directory, usually found in `Documents/Arduino/libraries/`.
3. Restart the Arduino IDE to recognize the library.

## Usage

### Include the Library

```cpp
#include <PCF8574.h>
```
Initialize the PCF8574
To use the library, you need to create an instance of the PCF8574 class. You can optionally specify the I2C address and configuration parameters.

```cpp
PCF8574 pcf(0x20); // Create an instance with the default address
```

Configuration Structure
You can customize the I2C settings by creating a PCF8574Config structure:

```cpp
PCF8574Config config;
config.sdaPin = 21; // Set SDA pin (optional)
config.sclPin = 22; // Set SCL pin (optional)
config.clockSpeed = 400000; // Set I2C clock speed to 400kHz (optional)

PCF8574 pcf(0x20, config); // Create an instance with custom configuration
```

Basic Functions
Check Availability

```cpp
if (pcf.available()) {
    Serial.println("PCF8574 is available.");
} else {
    Serial.println("PCF8574 is not available.");
}
```

Write to the Register

```cpp
uint8_t result = pcf.WriteAll(0xFF); // Write 255 to the register
if (result == 0) {
    Serial.println("Write successful.");
} else {
    Serial.println("Write error.");
}
```

Read from the Register

```cpp
uint8_t value = pcf.ReadAll(); // Read the current value of the register
Serial.print("Current register value: ");
Serial.println(value, BIN); // Print value in binary format
```

Set Pin Mode

```cpp
pinMode(pcf, 0, OUTPUT); // Set pin 0 as OUTPUT
pinMode(pcf, 1, INPUT);  // Set pin 1 as INPUT
```

Digital Write and Read

```cpp
digitalWrite(pcf, 0, HIGH); // Set pin 0 HIGH
bool pinState = digitalRead(pcf, 1); // Read the state of pin 1
```

Toggle Pin State

```cpp
pcf.ToggleAll(); // Invert the state of all pins
```

Shift Bits

```cpp
pcf.ShiftRight(1); // Shift the register right by 1 bit
pcf.ShiftLeft(2);  // Shift the register left by 2 bits
```

Example
Here’s a simple example demonstrating the basic usage of the PCF8574 library:

```cpp
#include <Wire.h>
#include <PCF8574.h>

PCF8574 pcf(0x20);

void setup() {
    Serial.begin(9600);
    if (pcf.available()) {
        Serial.println("PCF8574 is available.");
    }
    pcf.SetAllPinMode(OUTPUT); // Set all pins to OUTPUT
}

void loop() {
    digitalWrite(pcf, 0, HIGH); // Set pin 0 HIGH
    delay(1000);
    digitalWrite(pcf, 0, LOW);  // Set pin 0 LOW
    delay(1000);
}
```

License
This library is released under the MIT License.

Contributing
Contributions are welcome! Please open an issue or submit a pull request for any improvements, bug fixes, or new features.

Support
For any questions or issues, please open an issue on the repository.


### Key Sections Explained:
- **Introduction**: Briefly explains what the library does.
- **Features**: Highlights key functionalities.
- **Installation**: Guides on how to install the library.
- **Usage**: Includes code snippets demonstrating how to use various functionalities.
- **Example**: Provides a full example for practical understanding.
- **License and Contributing**: Basic information about contributions and the library's license.

Feel free to modify any sections to better fit your project's specifics or to add more detailed explanations as necessary!

