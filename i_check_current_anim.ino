void checkCurrentIllumination() {
  switch (currentIllumination) {
  case 1:
    // PULSE
    LED.Pulse(LED.Color(currentR, currentG, currentB), 40, 20);
    LED.Reverse();
    break;
  case 2:
    // WAVE
    LED.Wave(LED.Color(currentR, currentG, currentB), 100, 20);
    LED.Reverse();
    break;
  case 3:
    // BEAT
    LED.Beat(LED.Color(currentR, currentG, currentB), 100);
    break;
  case 4:
    // SUNRISE
    LED.Fade(SUNRISE, LED.Wheel(21), LED.Wheel(0), 20, 200);
    LED.Reverse();
    break;
  case 5:
    // UNICORN
    LED.Fade(UNICORN, LED.Wheel(148), LED.Wheel(233), 40, 100);
    LED.Reverse();
    break;
  case 6:
    // TROPICAL
    LED.Fade(TROPICAL, LED.Wheel(84), LED.Wheel(42), 20, 100);
    LED.Reverse();
    break;
  case 7:
    // RELAX
    LED.Fade(RELAX, LED.Color(255, 24, 195), LED.Color(40, 0, 255), 150, 50);
    LED.Reverse();
    break;
  case 8:
    // ICE
    LED.Fade(ICE, LED.Color(20, 255, 223), LED.Color(65, 253, 234), 15, 50);
    LED.Reverse();
    break;
  case 9:
    // RAINBOW
    LED.Rainbow(20, 255);
    LED.Reverse();
    break;
  default:
    // NONE
    LED.Direction = FORWARD;
    break;
  }
}
