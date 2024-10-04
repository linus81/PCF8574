# PCF8574 Library Documentation

## Overview
The PCF8574 library allows for easy control of the I2C-based PCF8574 port expander. Below is a detailed description of the available methods.

## Class: PCF8574

## PCF8574(uint8_t address = 0x20, PCF8574Config config = PCF8574Config())
Class constructor. Initializes an instance of the PCF8574 expander with the given I2C address and an optional configuration.

#### Parameters:

- address: I2C address of the PCF8574 device. Default value: 0x20.

- config: Configuration structure PCF8574Config containing optional parameters like SDA, SCL pins, and I2C clock speed.

Example:

```cpp
PCF8574 pcf; // Initializes with the default address 0x20
PCF8574 pcf(0x21); // Initializes with address 0x21
```

Configuration Structure
You can customize the I2C settings by creating a PCF8574Config structure:

```cpp
// Create a PCF8574Config structure with custom settings
PCF8574Config customConfig;

// Declare the PCF8574 instance globally without initialization
PCF8574 pcf; // Declaration only

void setup() {
    ...

    // Set custom I2C configuration
    customConfig.sdaPin = 21;   // Set SDA pin (optional)  
    customConfig.sclPin = 22;   // Set SCL pin (optional)   
    customConfig.clockSpeed = 400000; // Set I2C clock speed to 400kHz (optional)

    // Initialize the PCF8574 instance with custom configuration
    pcf = PCF8574(0x20, customConfig); // Initialize with customConfig

    ...
```


## bool available()
Checks if the PCF8574 device is available for communication.

- Returns: true if the device is available, false otherwise.

Example:

```cpp
if (pcf.available()) {
    Serial.println("PCF8574 found!");
}
```


## uint8_t WriteAll(uint8_t value)
Writes an 8-bit value to the PCF8574 register, controlling the state of all pins.

#### Parameters:

- value: The value to write (0-255), where each bit represents the state of a pin.
- Returns: The value written to the register.

Example:

```cpp
pcf.WriteAll(0xFF); // Sets all pins to HIGH
```


## uint8_t ReadAll()
Reads the 8-bit value from the PCF8574 register.

- Returns: The current value of the register, where each bit represents the state of a pin.

Example:

```cpp
uint8_t regValue = pcf.ReadAll();
```


## uint8_t getReg()
Retrieves the internally stored value of the PCF8574 register.

- Returns: The current value of the register (stored in the object).

Example:

```cpp
uint8_t currentValue = pcf.getReg();
```


## void ToggleAll()
Inverts the state of all pins, switching them from HIGH to LOW or vice versa.

Example:

```cpp
pcf.ToggleAll(); // Toggles the state of all pins
```


## void SetAllPinMode(uint8_t mode)
Sets the mode (INPUT or OUTPUT) for all pins.

#### Parameters:

- mode: Use INPUT or OUTPUT to set the mode.
  
Example:

```cpp
pcf.SetAllPinMode(OUTPUT); // Sets all pins as OUTPUT
```


## uint8_t ReverseByte(uint8_t byte)
Reverses the bits of the given value.

#### Parameters:

- byte: The value to reverse (0-255).
- Returns: The reversed value.

Example:

```cpp
uint8_t reversed = pcf.ReverseByte(0b11001100); // Returns 0b00110011
```


## void ReverseAllBit()
Reverses all bits currently stored in the register.

Example:

```cpp
pcf.ReverseAllBit(); // Reverses the bits in the current register
```


## uint8_t ShiftRight(uint8_t positions)
Performs a right shift on the register by a specified number of positions.

#### Parameters:

- positions: The number of positions to shift.
- Returns: The value of the register after the shift.

Example:

```cpp
uint8_t shifted = pcf.ShiftRight(2); // Shifts the bits right by 2 positions
```


## uint8_t ShiftLeft(uint8_t positions)
Performs a left shift on the register by a specified number of positions.

#### Parameters:

- positions: The number of positions to shift.
- Returns: The value of the register after the shift.

Example:

```cpp
uint8_t shifted = pcf.ShiftLeft(2); // Shifts the bits left by 2 positions
```


## bool IsPinHigh(uint8_t pin)
Checks if the specified pin is set to HIGH.

#### Parameters:

- pin: The pin number to check (from 0 to 7).
- Returns: true if the pin is HIGH, false if it is LOW.

Example:

```cpp
if (pcf.IsPinHigh(0)) {
    Serial.println("Pin 0 is HIGH");
}
```


## bool IsPinLow(uint8_t pin)
Checks if the specified pin is set to LOW.

#### Parameters:

- pin: The pin number to check (from 0 to 7).
- Returns: true if the pin is LOW, false if it is HIGH.

Example:

```cpp
if (pcf.IsPinLow(1)) {
    Serial.println("Pin 1 is LOW");
}
```



### Global Functions


## void pinMode(PCF8574& pcf, uint8_t pin, uint8_t mode)
Sets the mode of a specific pin.

#### Parameters:

- pcf: Reference to the PCF8574 instance.
- pin: The pin number (from 0 to 7).
- mode: INPUT or OUTPUT.

Example:

```cpp
pinMode(pcf, 2, OUTPUT); // Sets pin 2 as OUTPUT
```


## void digitalWrite(PCF8574& pcf, uint8_t pin, uint8_t value)
Writes a digital value to a specific pin.

#### Parameters:

- pcf: Reference to the PCF8574 instance.
- pin: The pin number (from 0 to 7).
- value: HIGH or LOW.

Example:

```cpp
digitalWrite(pcf, 3, HIGH); // Sets pin 3 to HIGH
```


## bool digitalRead(PCF8574& pcf, uint8_t pin)
Reads the digital value of a specific pin.

#### Parameters:

- pcf: Reference to the PCF8574 instance.
- pin: The pin number (from 0 to 7).
- Returns: true if the pin is HIGH, false if it is LOW.

Example:

```cpp
bool value = digitalRead(pcf, 4); // Reads the value of pin 4
```


## void digitalToggle(PCF8574& pcf, uint8_t pin)
Toggles the state of a specific pin.

#### Parameters:

- pcf: Reference to the PCF8574 instance.
- pin: The pin number (from 0 to 7).
  
Example:

```cpp
digitalToggle(pcf, 5); // Toggles the state of pin 5
```
