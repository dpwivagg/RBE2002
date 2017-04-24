/*
 * this code is used to find the initial flame
 * it is good for searching between 10 and 30 inches
*/

#include <Servo.h>
#include <math.h>

Servo servoTurn;  
Servo servoTilt;
//eveything is in inches or degrees
int turn = 0;
int tilt = 45;
int servoTurnDigitalPin = 9;
int servoTiltDigitalPin = 8;
int count=0;
int lowest = 5000;
int lowestTurn;
int lowestTilt;
int countLess100;
int countLess500;
int countLess800;
int turnError=0;//this value is the difference between the servors write value and the value relative to the robot
int tiltError = 85;//same as above
double sensorHeight= 8.5;//needs to be measured
int radius;
void setup() {
  servoTurn.attach(servoTurnDigitalPin,500,2500); 
  servoTilt.attach(servoTiltDigitalPin, 800, 2200);
  Serial.begin(9600);
}
  
void loop() {
  countLess100=0;
  countLess500=0;
  countLess800=0;
  Serial.println("begin...");
  for(int tilt = 60; tilt<=110; tilt+=5){
    Serial.println();
    for(int turn = 0; turn<100; turn+=1){
      servoTurn.write(turn);
      servoTilt.write(tilt);
      delay(20);//lets servo settle before reading
      count = 0;
      if(turn%5==0){
        for(int i = 0; i <= 10; i++){ // goes through so man times to take readings
          count += analogRead(A0); // takes reading  A0 is the flame sensor pin
          delay(20);//make this nonblocking
        }//end for loop of count
        count = count/10;
        Serial.print(count); // prints reading
        Serial.print("\t"); //tabs over 
        if (count<=lowest){//sets position and number of lowest read
          lowest = count;
          lowestTurn = turn - turnError;
          lowestTilt = tilt - tiltError;
        }//end if count<lowest
        if(count<=800){
          countLess800++;
          if(count<=500){
            countLess500++;
            if(count<=100){
              countLess100++;
            }
          }
        }
      
        
      }//end of if turn % 5
    }    
    for(int turn = 100; turn>=0; turn-=1){//spins servo back slowly
      delay(10);//allows it to turn smoothly
      servoTurn.write(turn);
      }
  }
  radius = GuessRadius(countLess800,countLess500,countLess100);
  Serial.println();
  Serial.print("Lowest Value = ");
  Serial.println(lowest);
  Serial.print("Lowest adjusted turn = ");
  Serial.println(lowestTurn);
  Serial.print("Lowest adjusted tilt = ");
  Serial.println(lowestTilt);
  Serial.print("Guess X= ");
  Serial.println(getX(lowestTurn,radius));
  Serial.print("Guess Y= ");
  Serial.println(getY(lowestTurn,radius));  
  Serial.print("Guess Z= ");
  Serial.println(getZ(lowestTilt,radius,sensorHeight));  
    Serial.print("Guess radius= ");
  Serial.println(radius);  
  while(true){}
}

double getX(int angle, int radius){
   return(radius*cos(angle*3.1415/180));
}

double getY(int angle, int radius){
   return(radius*sin(angle*3.1415/180));
}

double getZ(int angle, int radius, int height){
   return(height+radius*sin(angle*3.1415/180));
}

double GuessRadius(int less8,int less5, int less1){
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


