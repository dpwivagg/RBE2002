#include "RobotMap.h"
#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Chassis.h"
#include "Arm.h"
#include "Linesensor.h"
#include "Ultrasonic.h"

unsigned long timeForPush;

// Linesensor linesensor; TRIGGERS AT BLACK TAPE AT 335 ANALOG READ
Chassis chassis;
Ultrasonic ultrasonic;
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

}

long compError() {
  encError = abs(positionLeft - positionRight);
  return encError;
}


void auton () {
    /*Chassis test routine*/
    // chassis.instantGo(90);
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


    /*Test of basic ultrasonic safeToDrive function
    ultrasonic.update();
    if(ultrasonic.safeToDrive()) {
        Serial.println("go");
        chassis.drive(110);
    }
    else {
        Serial.println("stop");
        chassis.stop();
    }
    delay(250);*/
    /*Test of all possible ultrasonic cases + LCD output
    ultrasonic.update();
    switch(ultrasonic.get()) {
        case drive : lcd.clear();
        lcd.print("drive     ");
        break;
        case edge : lcd.clear();
        lcd.print("edge          ");
        break;
        case halfDrive : lcd.clear();
        lcd.print("halfDrive   ");
        break;
        case wall : lcd.clear();
        lcd.print("wall");
        break;
        default : lcd.clear();
        lcd.print("no info    ");
        break;
    }*/
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
