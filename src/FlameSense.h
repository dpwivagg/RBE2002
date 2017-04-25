#ifndef FLAMESENSE_H_
#define FLAMESENSE_H_

#include <Arduino.h>
#include <Servo.h>
#include <math.h>

class FlameSense {
    public:

        void init();
        void update(bool found, int pos);
        int getTurn();
        void servoSpin(bool found);

    private:

        Servo servoTurn;
        Servo servoTilt;

        void setTurn(int t);

        static const unsigned char servoTurnDigitalPin = 9;
        static const unsigned char servoTiltDigitalPin = 8;
};

#endif
