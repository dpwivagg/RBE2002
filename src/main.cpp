#include "RobotMap.h"
#include <Arduino.h>
#include <NewPing.h>

#include "Chassis.h"
#include "Arm.h"
#include "Linesensor.h"
#include "Encoder.h"

unsigned long timeForPush;

// Linesensor linesensor;
Chassis chassis;
Encoder encLeft(2,3);
Encoder encRight(18,19);

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


void auton () {
  long newLeft, newRight, encError;
  newLeft = knobLeft.read();
  newRight = knobRight.read();

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
