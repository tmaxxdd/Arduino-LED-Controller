![Project logo](led_controller_logo.png)

This part of the project establish Arduino code that with no effort allows you to communicate with your LED strips. Project is focused on WS2812b LED strips as they are one of the cheapest and powerful available on the market.

# Setup

### What's needed
* Any Arduino board. Uno is perfect just to start
* Addressable LED strip compatible with 

### Installation
Just download Arduino code and put it on the board

### Connection
WS28212b standard uses three pins (5V, GND, DIN) and they must be connected to Arduino board. For default it uses pin number 6 to send digital signals (DIN).

![Connection illustration](connection_illustration.png)

### Configuration
First you need configure number of your pixels on the strip.
```cpp
#define DIODECOUNT 5
```
Next select serial commands receiver. During development was used HC-05 Bluetooth module.
```cpp
SoftwareSerial bt(10, 11); // RX, TX
```
For development reason you may want to uncomment all serial prints which should help to find out what commands are properly handled.
```cpp
//   Serial.println(F("LED receiver started"));
```
