#include "SelfTest.h"


double mapValues(double input){
  double value = map(input, analogLow, analogHigh, voltageLow, voltageHigh);
  return value;
}

bool selfTest(){
  initialX = getXAcceleration();
  initialY = getYAcceleration();
  initialZ = getZAcceleration();

  setSTPinHigh();

  delay(10);

  accelerationX = getXAcceleration();
  accelerationY = getYAcceleration();
  accelerationZ = getZAcceleration();
//add a tolerance to our expected changed
  if ((expectedChangeX - tolerance <= accelerationX - initialX <= expectedChangeX + tolerance) && 
      (expectedChangeY - tolerance <= accelerationY - initialY <= expectedChangeY + tolerance) && 
      (expectedChangeZ - tolerance <= accelerationZ - initialZ <= expectedChangeZ + tolerance)){
    return true;
  }
  else{
    return false;
  }

  setSTPinLow();

}


void setSTPinHigh(){
 digitalWrite(SELF_TEST_PIN, HIGH);
}

void setSTPinLow(){
 digitalWrite(SELF_TEST_PIN, LOW);
}

int getXAcceleration(){
  double beforeMappedXValue = analogRead(FILTERED_X_AXIS_PIN);
  return mapValues(beforeMappedXValue);
}

int getYAcceleration(){
  double beforeMappedYValue = analogRead(FILTERED_Y_AXIS_PIN);
  return mapValues(beforeMappedYValue);
}

int getZAcceleration(){
  double beforeMappedZValue = analogRead(FILTERED_Z_AXIS_PIN);
  return mapValues(beforeMappedZValue);
}
