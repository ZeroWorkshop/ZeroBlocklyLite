
#include "ZWHuskyLens.h"

volatile int newvalue;

ZWHuskyLens huskylens;

void setup(){
  huskylens.writeAlgorithm(ALGORITHM_FACE_RECOGNITION);
  newvalue = 0;
  //combo_setup();

}

void loop(){
  if (huskylens.isAppearDirect(HUSKYLENSResultArrow)) {
    newvalue = huskylens.readArrowParameter(1,1).xOrigin;

  }

}