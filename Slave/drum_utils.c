#include "drum_utils.h"
#include <stdint.h>

// Code based off ThatOneTeam's code from last year
static uint8_t hitLeft = 0x0;
void hitDrum(){
	if (hitLeft)
        {
                LEFT_PORT |= LEFT_H;
                LEFT_PORT &= ~LEFT_R;
                RIGHT_PORT &= ~RIGHT_H;
                RIGHT_PORT |= RIGHT_R;
		R_ON();
        }
        else
        {
                RIGHT_PORT |= RIGHT_H;
                RIGHT_PORT &= ~RIGHT_R;
                LEFT_PORT &= ~LEFT_H;
                LEFT_PORT |= LEFT_R;
                R_OFF();
        }
        hitLeft = !hitLeft;
}

void unhitDrum(){
        //retract strike
        if (hitLeft)
        {
                LEFT_PORT &= ~LEFT_H;
                LEFT_PORT |= LEFT_R;
        }
        else
        {
                RIGHT_PORT &= ~RIGHT_H;
                RIGHT_PORT |= RIGHT_R;
        }

        hitLeft = !hitLeft;
	R_OFF();
	Y_OFF();
}
