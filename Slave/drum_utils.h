#include "header.h"

//minimum number of seconds between hitting and retracting drum
#define COOLDOWN 0.1
#define HIT 2
#define READY 3

//single stick instruments
#if MY_ID == BASS
  #define SINGLE_STICK
#elif MY_ID == HIHAT
  #define SINGLE_STICK
#else
  #define DOUBLE_STICK
#endif

//xxxx_H is the bit that should be 1 to hit the drum
//xxxx_R is the bit that should be 1 to retract from the drum
#ifdef DOUBLE_STICK
  #define LEFT_PORT P1OUT
  #define RIGHT_PORT P1OUT
  #define LEFT_H BIT1
  #define LEFT_R BIT0
  #define RIGHT_H BIT3
  #define RIGHT_R BIT2
#else
  #define LEFT_PORT P1OUT
  #define RIGHT_PORT P1OUT
  #define LEFT_H BIT1
  #define LEFT_R BIT0
  #define RIGHT_H LEFT_H
  #define RIGHT_R LEFT_R
  // stick status
  #define RETRACTED 4
#endif

void hitDrum();

