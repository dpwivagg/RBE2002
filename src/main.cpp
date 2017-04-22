#include "RobotMap.h"
#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Chassis.h"
#include "Arm.h"
#include "Linesensor.h"
#include "Ultrasonic.h"
#include "Navigation.h"

unsigned long timeForPush;

// Linesensor linesensor; TRIGGERS AT BLACK TAPE AT 335 ANALOG READ
Chassis chassis;
Ultrasonic ultrasonic;
Navigation nav;
LiquidCrystal lcd(40,41,42,43,44,45);

long newLeft, newRight, encError;
long positionLeft  = -999;
long positionRight = -999;

// Arm arm;

void setup() {

  Serial.begin(9600);

  Serial.println("Starting");
  timeForPush = millis() + 100;

  chassis.attach(mtrLF, mtrLR);
  ultrasonic.init();

  lcd.begin(16,1);
  // arm.attach(mtrArm, potArm, srvClmp);
  // linesensor.init();

  lcd.clear();

  // lcd.print("GYRO INIT");

  // delay(100);

  if (nav.init()) {
      lcd.print("GYRO SUCCESS");
  } else {
      lcd.print("GYRO FAILED");
  }

  delay(1000);

}

long compError() {
  encError = abs(positionLeft - positionRight);
  return encError;
}


void auton () {

    switch(ultrasonic.get()) {
        case drive : lcd.clear();
        lcd.print("drive     ");
        chassis.drive(40);
        break;
        case edge : lcd.clear();
        lcd.print("edge          ");
        chassis.drive(25, 90);
        break;
        case halfDrive : lcd.clear();
        lcd.print("halfDrive   ");
        chassis.drive(25, 90);
        break;
        case wall : lcd.clear();
        lcd.print("wall");
        chassis.instantStop();
        break;
        default : lcd.clear();
        lcd.print("no info    ");
        chassis.instantStop();
        break;
    }

}

void update () {
    if (false) {
        chassis.instantStop();
        // arm.instantStop();
    } else {
        chassis.update();
        ultrasonic.update();
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
