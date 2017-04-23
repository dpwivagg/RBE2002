#include "RobotMap.h"
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Encoder.h>
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
Encoder encLeft(encLeft1, encLeft2);
Encoder encRight(encRight1, encRight2);

LiquidCrystal lcd(40,41,42,43,44,45);

// Arm arm;

void setup() {

  Serial.begin(9600);

  Serial.println("Starting");
  timeForPush = millis() + 100;

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
    chassis.drive(110);
    Serial.print(encLeft.read());
    Serial.print("\t");
    Serial.println(encRight.read());
    delay(250);
}

void update () {
    if (false) {
        chassis.instantStop();
        // arm.instantStop();
    } else {
        chassis.update();
        ultrasonic.update();
        nav.updateGyro();
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
  if (millis() > timeForPush) {
    timeForPush = millis() + 100;
    update();
  }
}
