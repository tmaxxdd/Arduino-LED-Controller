void parseData() {
  interpreteMessage(command);
  newData = false;
}

bool isNumber(char chars[]) {
  for (int i = 0; i < strlen(chars); i++){
    if (!isDigit(chars[i]))
      return false;
  }
  
  return true;
}

bool isValidColor(char hexColor[]) {
  // Skip '#' char
  for (int i = 1; i < strlen(hexColor) - 1; i++) 
    if(!isAlphaNumeric(hexColor[i])) return false;
    
  return true;
}

bool isValidBrightness(char brightness[]) {
  if(!isNumber(brightness)) return false;
  
  int intBrightness = atoi(brightness);
  return (intBrightness >= 0 && intBrightness <= 255);
}

bool isValidIlluminationIndex(char index[]) {
  if (!isNumber(index)) return false;
  int intIndex = atoi(index);
  // Depends on your illuminations implementation
  return (intIndex >= 0 && intIndex <= 9);
}

void interpreteMessage(char message[]) {
  // Connection
  if (strncmp(message, CONNECTED, strlen(CONNECTED)) == 0){
    LED.BtConnected(25);
//     Serial.println(F("Connected"));
  }

  if (strncmp(message, DISCONNECTED, strlen(DISCONNECTED)) == 0){
    LED.BtDisconnected(25);
//     Serial.println(F("Disconnected"));
  }

  // Configuration
  if (strncmp(message, GET_CONFIGURATION, strlen(GET_CONFIGURATION)) == 0){
    String configuration = (String) "CONF=" + 
    "clr:" + hexColor + "," + 
    "brig:" + LED.getBrightness() + "," + 
    "illu:" + currentIllumination + "\n";
    bt.print(configuration);
//     Serial.println(F("Configuration = "));
//     Serial.print(configuration);
  }

  // Color
  if (strncmp(message, SET_COLOR, strlen(SET_COLOR)) == 0){
    char arr[strlen(message) - strlen(SET_COLOR) + 1];
    char* result = rmvstr(message, SET_COLOR, arr);
    if (isValidColor(result)) {
      parseColor(result);
      hexColor = result;     
//       Serial.print(F("Color = "));
//       Serial.println(result);
    } else {
//       Serial.println(F("Invalid color!"));
    }
  }

  // Brightness
  if (strncmp(message, SET_BRIGHTNESS, strlen(SET_BRIGHTNESS)) == 0){
    char arr[strlen(message) - strlen(SET_BRIGHTNESS) + 1];
    char* result = rmvstr(message, SET_BRIGHTNESS, arr);
    if (isValidBrightness(result)){
      LED.setBrightness(atoi(result));     
//       Serial.print(F("Brightness = "));
//       Serial.println(result);
    } else {
//       Serial.println(F("Invalid brightness!"));
    }
  }

  // Illumination
  if (strncmp(message, SET_ILLUMINATION, strlen(SET_ILLUMINATION)) == 0){
    char arr[strlen(message) - strlen(SET_ILLUMINATION) + 1];
    char* result = rmvstr(message, SET_ILLUMINATION, arr);
    if (isValidIlluminationIndex(result)){
      currentIllumination = atoi(result);     
//       Serial.print(F("Illumination = "));
//       Serial.println(result);
    } else {
//       Serial.println(F("Invalid illumination index!"));
    }
  }
}
