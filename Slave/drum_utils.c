#include "drum_utils.h"
#include <stdint.h>

// Code based off ThatOneTeam's code from last year
void hitDrum(int hit){
	R_T(); // toggle Red LED

	// two stick instruments
	#ifdef DOUBLE_STICK
		static uint8_t hitLeft = 0x0;
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
	// single stick instruments
	#else
		//hit
		if(hit)
		{
			LEFT_PORT |= LEFT_H;
	        	LEFT_PORT &= ~LEFT_R;
		}
		//retract
		else
		{
			LEFT_PORT &= ~LEFT_H;
	        	LEFT_PORT |= LEFT_R;
		}
	#endif
}
