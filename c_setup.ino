void setup() {
  // Initialize terminal
  Serial.begin(serialSpeed);
  //Initialize bluetooth communication
  bt.begin(serialSpeed);
  //Initialize the strips
  LED.begin(); // Without this led's won't turn on
  Serial.println(F("LED receiver started"));
  
  LED.setBrightness(100);
  LED.Fade(FADE, LED.Color(0,0,0), LED.Color(0,0,0), 1, 1);
}
