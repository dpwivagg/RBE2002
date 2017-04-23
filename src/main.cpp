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

// Linesensor linesensor; TRIGGERS AT BLACK TAPE AT 335 ANALOG READ
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

    //chassis.drive(40, nav.getDir());
    //Serial.println(nav.getDir());
    //chassis.drive(40, 0);
}

void updateSubsys () {
    if (false) {
        chassis.instantStop();
        // arm.instantStop();
    } else {
        chassis.update();
        ultrasonic.update();
        nav.updateEnc(encLeft.read(), encRight.read());
        // arm.update();
    }

}



///////////////////////////////////////////////
// Stuff that shouldn't be touched too hard. //
// Just saying.                              //
///////////////////////////////////////////////

void loop() {
  auton();  //calls the auton method
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
