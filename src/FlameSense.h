#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

#include <Arduino.h>
#include <Servo.h>
#include <math.h>

class FlameSense {
    public:
        void init();
        void update();
        void get(bool close);

    private:
        Servo servoTurn;
        Servo servoTilt;

        double GuessRadFar(int less8,int less5, int less1);
        double GuessRadClose(int less100,int less50, int less20);
        double getX(int angle, int radius);
        double getY(int angle, int radius);
        double getZ(int angle, int radius, int height);

        int lowestTurn;
        int lowestTilt;
        int radius;
        static const unsigned int turnError=0;//this value is the difference between the servors write value and the value relative to the robot
        static const unsigned int tiltError = 85;//same as
        static const unsigned char servoTurnDigitalPin = 9;
        static const unsigned char servoTiltDigitalPin = 8;
};

#endif
