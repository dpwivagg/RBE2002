/*
 * Ultrasonic.h
 *
 *  Created on: 4/15/17
 *      Author: james
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/**
 * Handles Ultrasonic information
 */
class Ultrasonic {
    public:
        Ultrasonic();
        unsigned short get();
        void update();
        void init(unsigned char analogPort);

    private:
        bool sensorState;
        unsigned char port = 0;
        unsigned short getSensor();
};

#endif /* Ultrasonic_H_ */
