
/*
 * Gyro.h
 *
 *  Created on: 4/19/17
 *      Author: james, adapted from Joe St. Germain's code
 */

#ifndef GYRO_H_
#define GYRO_H_

#include <L3G.h>
#include <LSM303.h>

/**
 * Handles Gyro information
 */

class Gyro {
    public:
        Gyro();
        bool init();
        void update();
        // int getX();
        // int getY();
        int getZ();

    private:

        void gyroZero();
        void updateGyro();
        void printGyro();
        void Accel_Init();
        void accelZero();
        void updateAccel();
        void complimentaryFilter();

        float G_Dt=0.02;    // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible

        long timer=0;   //general purpose timer
        long timer1=0;
        long timer2=0;

        float G_gain=.00875; // gyros gain factor for 250deg/sec
        float gyro_x; //gyro x val
        float gyro_y; //gyro x val
        float gyro_z; //gyro x val
        float gyro_xold; //gyro cummulative x value
        float gyro_yold; //gyro cummulative y value
        float gyro_zold; //gyro cummulative z value
        float gerrx; // Gyro x error
        float gerry; // Gyro y error
        float gerrz; // Gyro z error

        float A_gain=.00875; // gyros gain factor for 250deg/sec
        float accel_x; //gyro x val
        float accel_y; //gyro x val
        float accel_z; //gyro x val
        float accel_xold; //gyro cummulative x value
        float accel_yold; //gyro cummulative y value
        float accel_zold; //gyro cummulative z value
        float aerrx; // Accel x error
        float aerry; // Accel y error
        float aerrz; // Accel 7 error
        L3G gyro;
        LSM303 accel;

};

#endif /* NAVIGATION_H_ */
