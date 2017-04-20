#include "RobotMap.h"
#include <Arduino.h>
#include <NewPing.h>

#include "Chassis.h"
#include "Arm.h"
#include "Linesensor.h"

unsigned long timeForPush;

// Linesensor linesensor;
Chassis chassis;
// Arm arm;

void setup() {

  Serial.begin(9600);



  Serial.println("Starting");
  timeForPush = millis() + 100;

  chassis.attach(mtrLF, mtrLR);
  // arm.attach(mtrArm, potArm, srvClmp);
  chassis.instantStop();
  // linesensor.init();

}


void auton () {
    chassis.drive(90, 0);
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
