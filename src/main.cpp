#include "RobotMap.h"
#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Chassis.h"
#include "Arm.h"
#include "Linesensor.h"
#include "Ultrasonic.h"
#include "Gyro.h"

unsigned long timeForPush;

// Linesensor linesensor; TRIGGERS AT BLACK TAPE AT 335 ANALOG READ
Chassis chassis;
Ultrasonic ultrasonic;
Gyro gyro;

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
  gyro.init();

  lcd.begin(16,1);
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
        ultrasonic.update();
        gyro.update();
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
