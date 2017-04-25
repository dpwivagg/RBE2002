#include <Arduino.h>
#include <Servo.h>
#include "FlameSense.h"

int turn = 0;
int tilt = 45;
int count=0;


int countLess50 = 0;
int countLess20 = 0;
int countLess100 = 0;
int lowest = 5000;

void FlameSense::init() {
    servoTurn.attach(servoTurnDigitalPin,500,2500);
    servoTilt.attach(servoTiltDigitalPin, 800, 2200);
}



double FlameSense::getTurn() {
    return lowestTurn - 90;
}

bool FlameSense::updateClose() {
    if(tilt<=110){
        if(turn<=110) {

            if(turn %2 == 0){

                if(sampleNumber < 10){ // goes through so man times to take readings
                    count += analogRead(A0);
                    sampleNumber++;
                } else {
                    if (count/10<=lowest){//sets position and number of lowest read
                      lowest = count/10;
                      lowestTurn = turn - turnError;
                      lowestTilt = tilt - tiltError;
                    }//end if count<lowest
                    if(count/10<=100){
                        countLess100++;
                        if(count/10<=50){
                            countLess50++;
                            if(count/10<=20){
                                countLess20++;
                            }
                        }
                    }
                    sampleNumber = 0;
                    count = 0;
                    turn++;
                }
            } else {//end of if turn % 5
                turn++;
            }
        } else {
            turn  = 70;
            tilt += 5;
        }

    } else {
        tilt = 50;
        turn  = 70;
        radiusClose = GuessRadClose(countLess100,countLess50,countLess20);
        countLess20 = 0;
        countLess50 = 0;
        countLess100 = 0;
    }
    servoTurn.write(turn);
    servoTilt.write(tilt);
    return count > 0;
}
bool FlameSense::updateFar() {
        if(turn<=110) {
            if(turn %5 == 0){
                if(sampleNumber < 5){ // goes through so man times to take readings
                    count += analogRead(A0);
                    sampleNumber++;
                } else {
                    if (count/5<=lowest){//sets position and number of lowest read
                      lowest = count/5;
                      lowestTurn = turn - turnError;
                      lowestTilt = tilt - tiltError;
                    }//end if count<lowest
                    sampleNumber = 0;
                    count = 0;
                    turn++;
                }
            } else {//end of if turn % 5
                turn++;
            }
        } else {
            turn  = 0;
        }
    servoTurn.write(turn);
    return count > 0;
}

void setTurn(int t){
  servoTurn.write(turn);
}

void setTilt(int t){
  servoTilt.write(t);
}

double FlameSense::GuessRadClose(int less100,int less50, int less20){
  if(less100>1){
    if(less100>10){
      if(less50>35){
        if(less20>0){
          if(less20>20){
            return(5);
          }
          return(6);
        }
        return(8);
      }
      return(10);
    }
    return(12);
  }
  return(15);
}

double FlameSense::getX(int angle, int radius){
   return(radius*cos(angle*3.1415/180));
}

double FlameSense::getY(int angle, int radius){
   return(radius*sin(angle*3.1415/180));
}

double FlameSense::getZ(int angle, int radius, int height){
   double h = (height+radius*sin(angle*3.1415/180));
   if (h<6.5){
    return(6.5);
   }
   if (h>10){
    return(9.5);
   }
   return(h);
}
bool FlameSense::putOutFlame(){
  servoTurn.write(lowestTurn);
  servoTilt.write(lowestTilt);
  fanState() = true
  if (read>850){
    return true;
  }
  fanState() = false
  return false;
}
bool FlameSense::fanState(){
  return fanOn;
}

bool isItLit(){
    if (isItLit){
      isItLit = !putOutFlame();
    }
    return isItLit;

}
