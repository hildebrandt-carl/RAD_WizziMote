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
  #define EN_0 BIT3
  #define EN_1 BIT3
  #define VREF BIT2
#elif MY_ID == CYMBAL
  #define LEFT_PORT P1OUT
  #define RIGHT_PORT P1OUT
  #define LEFT_H BIT0
  #define LEFT_R BIT1
  #define RIGHT_H LEFT_H
  #define RIGHT_R LEFT_R
  #define EN_0 BIT3
  #define EN_1 BIT3
  #define VREF BIT2
#elif MY_ID == SNARE
  #define LEFT_PORT P1OUT
  #define RIGHT_PORT P1OUT
  #define LEFT_H BIT0
  #define LEFT_R BIT1
  #define RIGHT_H BIT3
  #define RIGHT_R BIT2
  #define EN_0 BIT4
  #define EN_1 BIT3
  #define VREF BIT5
#elif MY_ID == LOTOM
  #define LEFT_PORT P1OUT
  #define RIGHT_PORT P1OUT
  #define LEFT_H BIT0
  #define LEFT_R BIT1
  #define RIGHT_H BIT2
  #define RIGHT_R BIT3
  #define EN_0 BIT4
  #define EN_1 BIT4
  #define VREF BIT3
#elif MY_ID == HITOM
  #define LEFT_PORT P1OUT
  #define RIGHT_PORT P1OUT
  #define LEFT_H BIT0
  #define LEFT_R BIT1
  #define RIGHT_H BIT2
  #define RIGHT_R BIT3
  #define EN_0 BIT4
  #define EN_1 BIT4
  #define VREF BIT3
#elif MY_ID == FLTOM
  #define LEFT_PORT P1OUT
  #define RIGHT_PORT P2OUT
  #define LEFT_H BIT1
  #define LEFT_R BIT2
  #define RIGHT_H BIT4
  #define RIGHT_R BIT7
  #define EN_0 BIT0
  #define EN_1 BIT5
  #define VREF BIT3
#elif MY_ID == HIHAT
  #define LEFT_PORT P1OUT
  #define RIGHT_PORT P2OUT
  #define LEFT_H BIT0
  #define LEFT_R BIT1
  #define RIGHT_H BIT4
  #define RIGHT_R BIT5
  #define EN_0 BIT3
  #define EN_1 BIT3
  #define VREF BIT2
#else
#error "Not a valid ID number"
#endif

void hitDrum();
void unhitDrum();


