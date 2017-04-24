#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

#include <Arduino.h>


/**
 * static const unsigned char chassis_/arm_
 */


static const unsigned char mtrLF =  10;
static const unsigned char mtrLR =  11;

static const unsigned char mtrArm = 5;
static const unsigned char srvClmp = 3;
static const unsigned char potArm = A1;

static const unsigned char sonarFrontIn = A10;
static const unsigned char sonarFrontOut = 24;
static const unsigned char sonarRightIn = A9;
static const unsigned char sonarRightOut = 23;
static const unsigned char sonarBackIn = A8;
static const unsigned char sonarBackOut = 22;

static const unsigned char encLeft1 = 2;
static const unsigned char encLeft2 = 3;
static const unsigned char encRight1 = 18;
static const unsigned char encRight2 = 19;

static const unsigned char lineSense = A1;

static const signed char mtrFwd = -50; // run motor full-speed 'forward'
static const signed char mtrRwd = 50; // run motor full-speed 'reverse'
static const signed char mtrStop = 0; // stop motor
#define MTRSTOP 90

static const unsigned char ledpindebug = 13;

static const unsigned char linesensorArray [8] = {A0, A2, A3, A4, A5, A6, A7, A8};

enum Bits {
  BIT0 = 0b00000001,
  BIT1 = 0b00000010,
  BIT2 = 0b00000100,
  BIT3 = 0b00001000,
  BIT4 = 0b00010000,
  BIT5 = 0b00100000,
  BIT6 = 0b01000000,
  BIT7 = 0b10000000 //standard bitwise operators
};

#endif /* ROBOTMAP_H_ */
