# Adafruit_nRF52_Arduino_Peripheral
An example implementation of the Adafruit UART over BLE client for Arudino.

This code should be the basis on which NUS can be used by a peripheral to
respond to central's messages.

This code is almost entirely based on the Dual Roles BLEUART and Central BLEUART
examples from Adafruit. (Likely to interface with the BLE applications on mobile
platforms.)

However, there doesn't seem to be an equivalent Peripheral example, so this
repository seeks to create a Peripheral example to be a basis on which
chip-to-chip communications can be established.

## Status
Compile: Working
Testing: TODO
Version: alpha-1

## TODO
Need to test sketch upload and initial behavior.

## Testing Hardware
- Adafruit nRF52840 Feather (TODO: List the exact product and link)

## Misc
The data seems to be transmitted 20 bytes at a time.

Remember that C-style strings are null terminated. This is why str array
allocates memory for 20+1 characters. (Otherwise, Serial.println(str) will print
past the array.)

### Future testing
Can we modify the amount of data that can be transmitted at once? (Make sure to
make similar changes on the central side as well).