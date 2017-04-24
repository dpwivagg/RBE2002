#include "RobotMap.h"
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Encoder.h>
#include "Chassis.h"
#include "Arm.h"
#include "Linesensor.h"
#include "Ultrasonic.h"
#include "Navigation.h"

unsigned long timeForPushSubsysFreq = 0;
unsigned long timeForPushGyroFreq   = 0;

int robotHeading = 0;
signed short last, curr, speedMode;

Chassis chassis;
Ultrasonic ultrasonic;
Navigation nav;
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

  lcd.begin(16,1);

  lcd.clear();

  if (nav.init()) {
      lcd.print("GYRO SUCCESS");
  } else {
      lcd.print("GYRO FAILED");
  }

  delay(1000);

}

void auton () {
    // TODO : Use nav.getDir() to provide angle of turning to chassis.Drive()
    // TODO : Get the robot to drive in straight lines and execute 90 degree turns
    // TODO : Implement autonomous field navigation using ultrasonic sensors
    // TODO : Create timer ISR for flame sensing routine--pause the robot and search
    curr = ultrasonic.get();
    switch(curr) {
        case drive : lcd.clear();
            lcd.print("drive     ");
            speedMode = 30;
            // chassis.drive(30, (robotHeading + nav.getDir()));
        break;
        case closeWall: lcd.clear();
            lcd.print("close    ");
            if(last != closeWall) robotHeading -= 10;
            speedMode = 28;
            break;
        case wall : lcd.clear();
            lcd.print("wall     ");
            if(last != wall) {
                robotHeading -= 100;
            }
            speedMode = 0;
            // if(nav.getDir() < robotHeading) {
            //     ultrasonic.lock();
            //     chassis.drive(0, -25);
            // }
            // else {
            //     // chassis.stop();
            //     ultrasonic.unlock();
            // }
        break;
        case edge : lcd.clear();
            lcd.print("edge     ");
            if(last != edge) robotHeading += 100;
            speedMode = 0;
            // if(nav.getDir() > robotHeading) {
            //     ultrasonic.lock();
            //     chassis.drive(0, 25);
            // }
            // else {
            //     // chassis.stop();
            //     ultrasonic.unlock();
            // }
        break;
        case halfDrive : lcd.clear();
            lcd.print("half     ");
            speedMode = 20;
            // chassis.drive(20, 0);
        break;
        default : chassis.stop();
        break;
    }
    last = curr;
    chassis.drive(speedMode, (robotHeading + nav.getDir()));
    //chassis.drive(40, nav.getDir());
}

void updateSubsys () {
    chassis.update();
    ultrasonic.update();
    nav.updateEnc(encLeft.read(), encRight.read());
    // arm.update();
}



///////////////////////////////////////////////
// Stuff that shouldn't be touched too hard. //
// Just saying.                              //
///////////////////////////////////////////////

void loop() {
  auton();  //calls the auton method
  // if () {
  //
  // }
  if (millis() > timeForPushSubsysFreq) {
      timeForPushSubsysFreq = millis() + 100;
      updateSubsys();
  }
  // if (millis() > timeForPushGyroFreq) {
  //   timeForPushGyroFreq = millis() + 20;
  //   updateGyro();
  // }
  nav.updateGyro(); //nav.updateGyro()
}
