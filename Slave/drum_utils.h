#include "header.h"

//xxxx_H is the bit that should be 1 to hit the drum
//xxxx_R is the bit that should be 1 to retract from the drum
//LEFT and RIGHT are the same for crash cymbal and bass drum (they only have 1 stick) 

#if MY_ID == BASS
  #define LEFT_PORT P1OUT
  #define RIGHT_PORT P1OUT
  #define LEFT_H BIT1
  #define LEFT_R BIT0
  #define RIGHT_H LEFT_H
  #define RIGHT_R LEFT_R
#elif MY_ID == CYMBAL
  #define LEFT_PORT P1OUT
  #define RIGHT_PORT P1OUT
  #define LEFT_H BIT1
  #define LEFT_R BIT0
  #define RIGHT_H LEFT_H
  #define RIGHT_R LEFT_R
#else
  #define LEFT_PORT P1OUT
  #define RIGHT_PORT P1OUT
  #define LEFT_H BIT1
  #define LEFT_R BIT0
  #define RIGHT_H BIT3
  #define RIGHT_R BIT2
#endif

void hitDrum();
void unhitDrum();

