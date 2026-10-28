#include <Servo.h>

Servo servolr; //left right
Servo servoud; //up down
const int slrpin = 5; //servo lr pin
const int sudpin = 6; //servo ud pin
const int plpin = A0; //photoresistor left pin
const int prpin = A1; //photoresistor right pin
const int pupin = A2; //photoresistor up pin
const int pdpin = A3; //photoresistor down pin

int plval;
int prval;
int puval;
int pdval;

int hPos = 90;
int vPos = 90;

const int THRESHOLD = 20;
const int STEP = 1;

void setup() {
  servolr.attach(slrpin);
  servoud.attach(sudpin);
  servolr.write(hPos);
  servoud.write(vPos);
}

void loop() {
  plval = analogRead(plpin);
  prval = analogRead(prpin);
  puval = analogRead(pupin);
  pdval = analogRead(pdpin);
  
  plval = map(plval, 54, 974, 0, 180); //54 and 974 found by testing
  prval = map(prval, 54, 974, 0, 180);
  if (abs(plval - prval) > THRESHOLD) {
    hPos += (plval-prval > 0) ? STEP : -STEP;
    hPos = constrain(hPos, 0, 180);
    servolr.write(hPos);
  }
  
  puval = map(puval, 54, 974, 0, 180);
  pdval = map(pdval, 54, 974, 0, 180);
  if (abs(puval - pdval) > THRESHOLD) {
    vPos += (puval-pdval > 0) ? STEP : -STEP;
    vPos = constrain(vPos, 0, 180);
    servoud.write(vPos);
  }
  delay(10);
}