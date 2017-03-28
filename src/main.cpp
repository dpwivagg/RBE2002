#include "RobotMap.h"
#include <Arduino.h>

#include "Chassis.h"
#include "Arm.h"
#include "Linesensor.h"

unsigned long timeForPush;

Linesensor linesensor;
Chassis chassis;
Arm arm;

void setup() {

  Serial.begin(9600);

  // pinMode(c_LeftEncoderPinA, INPUT_PULLUP);      // sets pin A as input
  // pinMode(c_LeftEncoderPinB, INPUT_PULLUP);      // sets pin B as input
  // attachInterrupt(c_LeftEncoderInterruptA, HandleLeftMotorInterruptA, CHANGE);
  // attachInterrupt(c_LeftEncoderInterruptB, HandleLeftMotorInterruptB, CHANGE);
  //
  // pinMode(c_RightEncoderPinA, INPUT_PULLUP);      // sets pin A as input
  // pinMode(c_RightEncoderPinB, INPUT_PULLUP);      // sets pin B as input
  // attachInterrupt(c_RightEncoderInterruptA, HandleRightMotorInterruptA, CHANGE);
  // attachInterrupt(c_RightEncoderInterruptB, HandleRightMotorInterruptB, CHANGE);


  Serial.println("Starting");
  timeForPush = millis() + 100;

  chassis.attach(mtrLF, mtrLR, mtrRF, mtrRR);
  arm.attach(mtrArm, potArm, srvClmp);
  chassis.attachLimit(22);

  chassis.instantStop();
  arm.instantStop();
  linesensor.init();

}


void auton () {
}

void update () {
    if (false) {
        chassis.instantStop();
        arm.instantStop();
    } else {
        chassis.update();
        arm.update();
    }

}



//////////////////////////////////////////////
// Stuff that shouldn't be touched too hard //
// Just saying.                             //
//////////////////////////////////////////////

void loop() {
  auton();  //calls the auton method
  if (millis() > timeForPush) {
    timeForPush = millis() + 100;
    update();
    // Serial.println("pushed");
  }
}
