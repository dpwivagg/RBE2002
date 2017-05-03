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
int flameSenseCount = 0;
int lowest = 5000;
int lowestTurn;
int lowestTilt;
int countLess20;
int countLess50;
int countLess100;
int turnError=0;//this value is the difference between the servors write value and the value relative to the robot
int tiltError = 95;//same as above
double sensorHeight= 8.5;//needs to be measured
int radius;

void setup() {
  servoTurn.attach(servoTurnDigitalPin,500,2500); 
  servoTilt.attach(servoTiltDigitalPin, 800, 2200);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}
  
void loop() {
  lowest = 4000;
  countLess100=0;
  countLess50=0;
  countLess20=0;
  Serial.println("begin...");
  for(int tilt = 50; tilt<=110; tilt+=5){
    Serial.println();
    for(int turn = 70; turn<110; turn+=1){
      servoTurn.write(turn);
      servoTilt.write(tilt);
      delay(20);//lets servo settle before reading
      count = 0;
      if(turn%2==0){
        for(int i = 1; i <= 5; i++){ // goes through so man times to take readings
          count += analogRead(A0); // takes reading  A0 is the flame sensor pin
          delay(20);//make this nonblocking
        }//end for loop of count
        count = count/5;
        Serial.print(count); // prints reading
        Serial.print("\t"); //tabs over 
        if (count<=lowest){//sets position and number of lowest read
          lowest = count;
          lowestTurn = turn - turnError;
          lowestTilt = tilt - tiltError;
        }//end if count<lowest
        if(count<100){
          countLess100++;
          if(count<50){
            countLess50++;
            if(count<20){
              countLess20++;
            }
          }
        } 
      }
    }    
    for(int turn = 110; turn>=70; turn-=1){//spins servo back slowly
      delay(10);//allows it to turn smoothly
      servoTurn.write(turn);
      }
  }

  radius = GuessRadius(countLess100,countLess50,countLess20);
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
  servoTurn.write(lowestTurn+turnError);
  servoTilt.write(lowestTilt+tiltError);
  delay(1000);
  digitalWrite(7,HIGH);
  while(flameSenseCount<25){
    if(analogRead(A0)>1000){
      delay(500);
      flameSenseCount++;
    }
  }
  digitalWrite(7,LOW);
  Serial.println("FLAME OUT!!!!");
  delay(500);
  
  while(1){
  }
  
}

double getX(int angle, int radius){
   return(radius*cos(angle*3.1415/180));
}

double getY(int angle, int radius){
   return(radius*sin(angle*3.1415/180));
}

double getZ(int angle, int radius, int height){
   double h = (height+radius*sin(angle*3.1415/180));
   if (h<6.5){
    return(6.5);
   }
   if (h>10){
    return(9.5);
   }
   return(h);
}

int GuessRadius(int less100,int less50, int less20){
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


