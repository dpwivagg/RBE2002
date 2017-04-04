/*
 * Messages.h
 *
 *  Created on: 10/1/16
 *      Author: joest
 */
#include "PID.h"
#include "Arduino.h"

//Class constructor
PID::PID(){

}

//Function to set PID gain values
void PID::setpid(float P, float I, float D){
  kp=P;
  ki=I;
  kd=D;
}

//Write this function to calculate a control signal from the set velocity
//and the current velocity
float PID::calc(double setVel, double curVel){

    // calculate error
    float error = (setVel - curVel);

    // calculate derivative of error
    float derivative = (error - last_error);


    // calculate integral error. Running average is best but hard to implement
    sum_error += (error * (millis() - last_time));

    // sum up the error value to send to the motor based off gain values.
    float pid = (kp * error) + (ki * (sum_error)) + (kd * (derivative));
    Serial.println(pid);
    // limit control value to 0-254
    //return the control signal

    return constrain(pid, 0, 254);
}
