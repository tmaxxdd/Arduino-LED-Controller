void loop() {
  LED.Update();
  readIncomingData();
  if (newData) {
    parseData();
  }
}
