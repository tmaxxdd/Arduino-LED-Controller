void readIncomingData() {
  if (bt.available() > 0 && newData == false) {
    char rc = bt.read();
    if (rc != '\n') {
      command[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      command[ndx] = '\0';
      ndx = 0;
      newData = true;
    }
  }
}
