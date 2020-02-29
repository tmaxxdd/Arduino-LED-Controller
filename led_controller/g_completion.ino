void LEDComplete() {
  if (!startupShown) {
    showStartupIllumination();  
  } else {
    // If no illumination is pending
    LED.StaticColor(LED.Color(currentR, currentG, currentB), 50);
  }
  checkCurrentIllumination();
}

void showStartupIllumination() {
  int interval = 50;
  switch(startupStep) {
      case 0:
        LED.ColorWipe(LED.Color(255, 0, 0), interval);
        break;
      case 1:
        LED.ColorWipe(LED.Color(0, 255, 0), interval);
        break;
      case 2:        
        LED.ColorWipe(LED.Color(0, 0, 255), interval);
        break;
      case 3:
        LED.ColorWipe(LED.Color(255, 255, 255), interval);
        break;
      default:
        startupShown = true;
    }
    startupStep++;
}
