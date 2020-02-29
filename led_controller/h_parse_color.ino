void parseColor(char hexValue[]) {
    //Convert string to long
    long converted = (long) strtol(&hexValue[1], NULL, 16);

    //Check if converted value is valid
    if (converted < 1000000L) {
      //If not, take the earlier value.
      //This is only for smoother change.
      converted = currentColor;
    } else {
      //If value is correct, store it in memory.
      currentColor = converted;
    }
    
    // Split them up into r, g, b values
    long r = converted >> 16;
    long g = converted >> 8 & 0xFF;
    long b = converted & 0xFF;

    currentR = r;
    currentG = g;
    currentB = b;

    //Change current color WITHOUT animation
    LED.Color1 = LED.Color(currentR, currentG, currentB);   
}
