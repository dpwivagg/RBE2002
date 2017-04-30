#ifndef FLAMESENSE_H_
#define FLAMESENSE_H_

#include <Arduino.h>
#include <Servo.h>
#include <math.h>

class FlameSense {
    public:
        void init();
        bool update();
        double get(bool close);
        double getTurn();

    private:
        int tilt = 60;
        int turn = 0;
        Servo servoTurn;
        Servo servoTilt;

        unsigned int sampleNumber;

        double GuessRadFar(int less8,int less5, int less1);
        double GuessRadClose(int less100,int less50, int less20);
        double getX(int angle, int radius);
        double getY(int angle, int radius);
        double getZ(int angle, int radius, int height);

        int lowestTurn;
        int lowestTilt;
        int radius;
        int radiusClose = 0;
        int radiusFar = 0;
        static const unsigned int turnError = 0;//this value is the difference between the servors write value and the value relative to the robot
        static const unsigned int tiltError = 85;//same as
        static const unsigned char servoTurnDigitalPin = 9;
        static const unsigned char servoTiltDigitalPin = 8;
};

#endif
