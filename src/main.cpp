#include "RobotMap.h"
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Encoder.h>
#include "Chassis.h"
#include "Linesensor.h"
#include "Ultrasonic.h"
#include "Navigation.h"
#include "FlameSense.h"

unsigned long timeForPushSubsysFreq = 0;
unsigned long timeForPushGyroFreq   = 0;
double sensorHeight= 8.5;
int robotHeading = 0;
signed short last = 0, curr = 0, speedMode = 0;
int pos = 0;

bool found = false;
bool closeFlame = false;
bool flameSensed = false;
Chassis chassis;
Ultrasonic ultrasonic;
Navigation nav;
FlameSense flame;
Encoder encLeft(encLeft1, encLeft2);
Encoder encRight(encRight1, encRight2);

LiquidCrystal lcd(40,41,42,43,44,45);

// Arm arm;

void setup() {

  Serial.begin(9600);

  Serial.println("Starting");
  timeForPushSubsysFreq = millis() + 100;
  chassis.attach(mtrLF, mtrLR);
  ultrasonic.init();

  curr = ultrasonic.get();
  last = curr;

  flame.init();

  lcd.begin(16,1);

  lcd.clear();

  // if (nav.init()) {
  //     lcd.print("GYRO SUCCESS");
  // } else {
  //     lcd.print("GYRO FAILED");
  // }

  pinMode(fan, OUTPUT);

  delay(1000);



}

void auton () {
   chassis.tank(45, 40);

   delay(4250);

   chassis.tank(40, -37);

   delay(1000);

   chassis.tank(45, 40);

   delay(9000);

   chassis.tank(40, -40);

   delay(1000);

   chassis.tank(0, 0);

   delay(1000);

   chassis.tank(45, 40);

   delay(2000);

   chassis.tank(0, 0);

   delay(1000);

   digitalWrite(fan, HIGH);

}

void updateSubsys () {
    chassis.update();
    ultrasonic.update();
    // flame.update(found, pos);
    nav.updateEnc(encLeft.read(), encRight.read());
    // arm.update();
}



///////////////////////////////////////////////
// Stuff that shouldn't be touched too hard. //
// Just saying.                              //
///////////////////////////////////////////////

void loop() {
    auton();  //calls the auton method
    // // if () {
    // //
    // // }
    // if (millis() > timeForPushSubsysFreq) {
    //     timeForPushSubsysFreq = millis() + 100;
    //     updateSubsys();
    // }
    // if (millis() > timeForPushGyroFreq) {
    //     flame.servoSpin(found);
    //     timeForPushGyroFreq = millis() + 25;
    // }
    //
    // // nav.updateGyro(); //nav.updateGyro()

    while(1) ;
}
