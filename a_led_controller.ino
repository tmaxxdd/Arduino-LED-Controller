/*
 * This software manages serial communication in order to drive 
 * connected led strips. Implementation and tests were made on HC-05 
 * Bluetooth module and WS2812b led strip. Any other variations may be 
 * possible but weren't tested.For LED management and step iteration is 
 * used NeoAnimations class linked below. Commmunication is made in 
 * standard Arduino way with usage SoftwareSerial lib.There are preset 
 * LED illuminations that can be adjusted, but definitions of them must 
 * be declared on the host and client side, which means if someone wants 
 * to add new illumination, it's name must be added to the list 
 * on transmitter device.Code uses own communications messages.
 * 
 * Code for Android app is placed on Github:
 * https://github.com/tmaxxdd/LEDControler
 * 
 * Last modification: 29-02-2020
 * Created by Tomasz Kądziołka
 * 
*/

#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

// A set of defined illuminations
enum illumination {
  NONE,
  BT_CONNECTED,
  BT_DISCONNECTED,
  FADE,
  COLOR_WIPE,
  STATIC_COLOR,
  PULSE,
  WAVE,
  BEAT,
  SUNRISE,
  UNICORN,
  TROPICAL,
  RELAX,
  ICE,
  RAINBOW
};

enum direction {
  FORWARD,
  REVERSE
};

// Inherit from Adafruit_NeoPixel class
// Based on: https://learn.adafruit.com/multi-tasking-the-arduino-part-3
class NeoAnimations: public Adafruit_NeoPixel {

  public:
    // Member Variables:  
    illumination ActiveIllumination; // which pattern is running
  direction Direction;

  unsigned long Interval; // milliseconds between updates
  unsigned long lastUpdate; // last update of position

  uint32_t Color1,
  Color2; // What colors are in use
  uint16_t TotalSteps; // total number of steps in the pattern
  uint16_t Index; // current step within the pattern

  void( * OnComplete)(); // Callback on completion of pattern

  // Constructor - calls base-class constructor to initialize strip
  NeoAnimations(uint16_t pixels, uint8_t pin, uint8_t type, void( * callback)()): Adafruit_NeoPixel(pixels, pin, type) {
    OnComplete = callback;
  }

  // Update the illumination
  void Update() {
    if ((millis() - lastUpdate) > Interval) {
      lastUpdate = millis();
      switch (ActiveIllumination) {
      case BT_CONNECTED:
        BtConnectedUpdate();
        break;
      case BT_DISCONNECTED:
        BtDisconnectedUpdate();
        break;
      case PULSE:
        PulseUpdate();
        break;
      case WAVE:
        WaveUpdate();
        break;
      case BEAT:
        BeatUpdate();
        break;
      case FADE:
        FadeUpdate();
        break;
      case SUNRISE:
        FadeUpdate();
        break;
      case UNICORN:
        FadeUpdate();
        break;
      case TROPICAL:
        FadeUpdate();
        break;
      case RELAX:
        FadeUpdate();
        break;
      case ICE:
        FadeUpdate();
        break;
      case RAINBOW:
        RainbowUpdate();
        break;
      case COLOR_WIPE:
        ColorWipeUpdate();
        break;
      case STATIC_COLOR:
        StaticColorUpdate();
        break;
      default:
        break;
      }
    }
  }

  // Increment the Index and reset at the end
  void Increment() {
    if (Direction == FORWARD) {
      Index++;
      if (Index >= TotalSteps) {
        Index = 0;
        if (OnComplete != NULL)
          OnComplete(); // call the completion callback
      }
    } else { // Direction == REVERSE
      --Index;
      if (Index <= 0) {
        Index = TotalSteps - 1;
        if (OnComplete != NULL)
          OnComplete(); // call the completion callback
      }
    }
  }

  // Reverse pattern direction
  void Reverse() {
    if (Direction == FORWARD) {
      Direction = REVERSE;
      Index = TotalSteps - 1;
    } else {
      Direction = FORWARD;
      Index = 0;
    }
  }

  void Pulse(uint32_t color, uint8_t interval, uint16_t steps) {
    ActiveIllumination = PULSE;
    Interval = interval;
    TotalSteps = steps;
    Color1 = color;
    Index = 0;
  }

  void PulseUpdate() {
    fill(Color1);
    setBrightness(int(pow(Index, 3 / 2)));
    show();
    Increment();
  }

  void Wave(uint32_t color, uint8_t interval, uint16_t steps) {
    ActiveIllumination = WAVE;
    Interval = interval;
    TotalSteps = steps;
    Color1 = color;
    Index = 0;
  }

  void WaveUpdate() {
    fill(Color1);
    setBrightness(int(255 / Index));
    show();
    Increment();
  }

  void Beat(uint32_t color, uint8_t interval) {
    ActiveIllumination = BEAT;
    Interval = interval;
    TotalSteps = 1;
    Color1 = color;
  }

  void BeatUpdate() {
    fill(Color1);
    setBrightness(random(50, 255));
    show();
    Increment();
  }

  void Rainbow(uint8_t interval, uint16_t steps) {
    ActiveIllumination = RAINBOW;
    Interval = interval;
    TotalSteps = steps;
    Color1 = Wheel(0);
  }

  void RainbowUpdate() {
    Color1 = Wheel(Index);
    fill(Color1);
    show();
    Increment();
  }

  /* BT_CONNECTED */
  void BtConnected(uint8_t interval) {
    ActiveIllumination = BT_CONNECTED;
    Interval = interval;
    TotalSteps = numPixels();
    Color1 = Color(0, 0, 255);
    Index = 0;
    Direction = FORWARD;
  }

  void BtConnectedUpdate() {
    setPixelColor(Index, 0, 0, 255 * 0.1 * Index);
    show();
    Increment();
  }

  /* BT_DISCONNECTED */
  void BtDisconnected(uint8_t interval) {
    ActiveIllumination = BT_DISCONNECTED;
    Interval = interval;
    TotalSteps = numPixels();
    Color1 = Color(0, 0, 255);
    Index = numPixels() - 1;
    Direction = REVERSE;
  }

  void BtDisconnectedUpdate() {
    setPixelColor(Index, 0, 0, 255 - (255 * 0.1 * Index));
    show();
    Increment();
  }

  void StaticColor(uint32_t color, uint8_t interval) {
    ActiveIllumination = COLOR_WIPE;
    Interval = interval;
    TotalSteps = numPixels();
    Color1 = color;
    Index = 0;
  }

  void StaticColorUpdate() {
    ColorSet(Color1);
  }

  void ColorWipe(uint32_t color, uint8_t interval, direction dir = FORWARD) {
    ActiveIllumination = COLOR_WIPE;
    Interval = interval;
    TotalSteps = numPixels();
    Color1 = color;
    Index = 0;
    Direction = dir;
  }

  void ColorWipeUpdate() {
    setPixelColor(Index, Color1);
    show();
    Increment();
  }

  void Fade(illumination anim, uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval) {
    ActiveIllumination = anim;
    Interval = interval;
    TotalSteps = steps;
    Color1 = color1;
    Color2 = color2;
    Index = 0;
  }

  // Update the Fade Pattern
  void FadeUpdate() {
    // Calculate linear interpolation between Color1 and Color2
    // Optimise order of operations to minimize truncation error
    uint8_t red = ((Red(Color1) * (TotalSteps - Index)) + (Red(Color2) * Index)) / TotalSteps;
    uint8_t green = ((Green(Color1) * (TotalSteps - Index)) + (Green(Color2) * Index)) / TotalSteps;
    uint8_t blue = ((Blue(Color1) * (TotalSteps - Index)) + (Blue(Color2) * Index)) / TotalSteps;

    ColorSet(Color(red, green, blue));
    show();
    Increment();
  }

  // Set all pixels to a color (synchronously)
  void ColorSet(uint32_t color) {
    for (int i = 0; i < numPixels(); i++) {
      setPixelColor(i, color);
    }
    show();
  }

  // Returns the Red component of a 32-bit color
  uint8_t Red(uint32_t color) {
    return (color >> 16) & 0xFF;
  }

  // Returns the Green component of a 32-bit color
  uint8_t Green(uint32_t color) {
    return (color >> 8) & 0xFF;
  }

  // Returns the Blue component of a 32-bit color
  uint8_t Blue(uint32_t color) {
    return color & 0xFF;
  }

  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
      return Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if (WheelPos < 170) {
      WheelPos -= 85;
      return Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
      WheelPos -= 170;
      return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
  }

};
