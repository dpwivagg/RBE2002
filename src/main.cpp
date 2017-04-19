#include "RobotMap.h"
#include <Arduino.h>
#include <NewPing.h>
#include <LiquidCrystal.h>

#include "Chassis.h"
#include "Arm.h"
#include "Linesensor.h"
#include "Encoder.h"

unsigned long timeForPush;

// Linesensor linesensor;
Chassis chassis;
Encoder encLeft(encLeft1, encLeft2);
Encoder encRight(encRight1, encRight2);

NewPing sonarFront(sonarFrontOut, sonarFrontIn, 300);
NewPing sonarRight(sonarRightOut, sonarRightIn, 300);
NewPint sonarBack(sonarBackOut, sonarBackIn, 300);

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
  encError = abs(newLeft - newRight);
  return encError;
}


void auton () {
  chassis.drive(mtrFwd);
  long newLeft, newRight, encError;
  newLeft = knobLeft.read();
  newRight = knobRight.read();

  // if we are approaching a wall or a cliff, stop and turn
  if(sonarFront.ping_cm() <= 10 || !sonarFront.ping_cm()) {
    chassis.instantStop();
    // create some function here for a right angle turn
/*    while(sonarRight.ping_cm() < 10 || sonarLeft.ping_cm() < 10)
    chassis.turn(mtrFwd);
    chassis.instantStop();
*/  }

  positionLeft = newLeft;
  positionRight = newRight;
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
