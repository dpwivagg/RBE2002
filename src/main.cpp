#include "RobotMap.h"
#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Chassis.h"
#include "Arm.h"
#include "Linesensor.h"

unsigned long timeForPush;

// Linesensor linesensor; TRIGGERS AT BLACK TAPE AT 335 ANALOG READ
Chassis chassis;
Encoder encLeft(encLeft1, encLeft2);
Encoder encRight(encRight1, encRight2);

long newLeft, newRight, encError;
long positionLeft  = -999;
long positionRight = -999;

// Arm arm;

void setup() {

  Serial.begin(9600);



  Serial.println("Starting");
  timeForPush = millis() + 100;

  chassis.attach(mtrLF, mtrLR);
  // arm.attach(mtrArm, potArm, srvClmp);
  chassis.attachLimit(22); //this would be the linsensor in the front

  chassis.instantStop();
  // linesensor.init();

}

long compError() {
  encError = abs(positionLeft - positionRight);
  return encError;
}


void auton () {

}

void update () {
    if (false) {
        chassis.instantStop();
        // arm.instantStop();
    } else {
        chassis.update();
        // arm.update();
    }

}



///////////////////////////////////////////////
// Stuff that shouldn't be touched too hard. //
// Just saying.                              //
///////////////////////////////////////////////

void loop() {
  auton();  //calls the auton method
  if (millis() > timeForPush) {
    timeForPush = millis() + 100;
    update();
  }
}
