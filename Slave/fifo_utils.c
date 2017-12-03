#include "fifo_utils.h"

static uint32_t fifo[256];
static uint8_t rdAddr = 0;
static uint8_t wrAddr = 0;
static uint8_t entries = 0;

int writeFifo(uint32_t val){
	if(entries < 256){
		fifo[wrAddr] = val;
		wrAddr++;
		entries++;
	}else{
		//printf("ERROR: fifo full.");
		return 1;
	}
	return 0;
}

int readFifo(uint32_t *val){
	if(entries > 0){
		*val = fifo[rdAddr];
		rdAddr++;
		entries--;
	}else{
		//printf("ERROR: fifo empty.");
		return 1;
	}
	return 0;
}

int peekFifo(uint32_t *val){
	if(entries > 0){
		*val = fifo[rdAddr];
	}else{
		//printf("ERROR: fifo empty.");
		return 1;
	}
	return 0;
}

int clearFifo(){
	entries = 0;
	rdAddr = 0;
	wrAddr = 0;
	return 0;
}
