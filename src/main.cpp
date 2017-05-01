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
signed short last, curr, speedMode;
int pos = 0;
int read, t;
bool found = false;
bool closeFlame = false;
bool flameSensed = false;
char buffer[50];
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

  lcd.begin(16,2);

  lcd.clear();

  // if (nav.init()) {
  //     lcd.print("GYRO SUCCESS");
  // } else {
  //     lcd.print("GYRO FAILED");
  // }

  pinMode(fan, OUTPUT);
  digitalWrite(fan, LOW);

  delay(1000);

}

void auton () {
    if(!found) {
        curr = ultrasonic.get();
        switch(curr) {
            case drive :
                lcd.clear();
                lcd.print("drive     ");
                speedMode = 30;
            break;
            case closeWall:
                lcd.clear();
                lcd.print("close    ");
                if(last!=closeWall) {
                    robotHeading += 3;
                    speedMode = 30;
                }
            break;
            case wall :
                lcd.clear();
                lcd.print("wall     ");
                if(last != wall) {
                    robotHeading -= 100;
                    nav.right();
                }
                speedMode = 0;
            break;
            case edge :
                lcd.clear();
                lcd.print("edge     ");
                if(last != edge) {
                    robotHeading += 100;
                    nav.left();
                }
                speedMode = 0;
            break;
            case halfDrive :
                lcd.clear();
                lcd.print("half     ");
                speedMode = 20;
            break;
            default : chassis.stop();
            break;
        }
        last = curr;
    }

    for(int i = 0; i < 5; i++) {
        read += analogRead(A0);
    }

    read = read / 5;

    if(read < 200 && !found) {
        digitalWrite(fan, HIGH);
        robotHeading += (flame.getTurn()-90);
        speedMode = 0;
        found = true;
        lcd.clear();
        lcd.print("Found!");
        t = millis();
    }

    chassis.drive(speedMode, (robotHeading + nav.getDir()));

    if(found && (t + millis()) > 6000) {
      digitalWrite(fan, LOW);
      lcd.clear();
      lcd.print("Extinguished");
      lcd.setCursor(0,2);
      sprintf(buffer, "X: %d Y: %d", nav.getXpos(), nav.getYpos());
      lcd.print(buffer);
    }
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
    // if () {
    //
    // }
    if (millis() > timeForPushSubsysFreq) {
        timeForPushSubsysFreq = millis() + 100;
        updateSubsys();
    }
    if (millis() > timeForPushGyroFreq) {
        flame.servoSpin(found);
        timeForPushGyroFreq = millis() + 25;
    }

    // nav.updateGyro(); //nav.updateGyro()
}
