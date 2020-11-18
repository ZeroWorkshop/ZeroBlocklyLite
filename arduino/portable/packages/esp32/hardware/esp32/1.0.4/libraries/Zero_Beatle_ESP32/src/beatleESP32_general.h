﻿bool targetReached(int timeout) {
  uint8_t tempBuffer;
  
	int timer = millis();
	
  while (!Serial.available()) {
    if (millis() - timer > timeout) return false;
  }
  while (Serial.available()) {
    tempBuffer = Serial.read();
    Serial.println(tempBuffer, HEX);
    if (tempBuffer == 0xCC) {
      tempBuffer = Serial.read();
      if (tempBuffer == 0xDD) {
        return true;
      }
    }
  }
  return false;
}