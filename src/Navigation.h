/*
 * Navigation.h
 *
 *  Created on: 4/19/17
 *      Author: james
 */

#ifndef NAVIGATION_H_
#define NAVIGATION_H_


/**
 * Handles nav information
 */
class Navigation {
    public:
        Navigation();
        void update(int encoderTicksL, int encoderTicksR);
        void init();

    private:
        int encoderTicksL;
        int encoderTicksR;

};

#endif /* NAVIGATION_H_ */
