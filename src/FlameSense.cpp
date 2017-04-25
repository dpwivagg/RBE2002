#include <Arduino.h>
#include <Servo.h>
#include "FlameSense.h"

int turn = 0;
int tilt = 45;
int count=0;


int countLess50 = 0;
int countLess20 = 0;
int countLess100 = 0;
int countLess500 = 0;
int countLess800 = 0;
int lowest = 5000;

void FlameSense::init() {
    servoTurn.attach(servoTurnDigitalPin,500,2500);
    servoTilt.attach(servoTiltDigitalPin, 800, 2200);
}

double FlameSense::get(bool close) {
    return close?radiusClose:radiusFar;
}

bool FlameSense::update() {

    if(tilt<=110){
        if(turn<100) {

            if(turn %5 == 0){

                if(sampleNumber < 10){ // goes through so man times to take readings
                    count += analogRead(A0);
                    sampleNumber++;
                } else {


                    if (count/10<=lowest){//sets position and number of lowest read
                      lowest = count/10;
                      lowestTurn = turn - turnError;
                      lowestTilt = tilt - tiltError;
                    }//end if count<lowest
                    if(count/10<=800){
                        countLess800++;
                        if(count/10<=500){
                            countLess500++;
                            if(count/10<=100){
                                countLess100++;
                            }
                        }
                    }

                    sampleNumber = 0;
                    count = 0;
                    turn++;
                    // turn+=5;

                }


            } else {//end of if turn % 5
                turn++;
                // turn+=5;
            }
        } else {
            turn  = 0;
            tilt += 5;
        }

    } else {
        tilt = 60;
    }

    radiusClose = GuessRadClose(countLess100,countLess50,countLess20);
    radiusFar = GuessRadFar(countLess800,countLess500,countLess100);

    servoTurn.write(turn);
    servoTilt.write(tilt);

    return count > 0;
}

double FlameSense::GuessRadFar(int less8,int less5, int less1){
  if(less8>1){
    if(less5>10){
      if(less1>8){
        return(10);
      }
      return(15);
    }
    return(20);
  }
  return(25);
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
