#include "fifo_utils.h"

#define QUEUE_SIZE 600

static uint32_t fifo[QUEUE_SIZE];
static uint16_t rdAddr = 0;
static uint16_t wrAddr = 0;
static uint16_t entries = 0;

int writeFifo(uint32_t val){
	if(entries < QUEUE_SIZE){
		fifo[wrAddr] = val;
		wrAddr = (wrAddr+1)%QUEUE_SIZE;
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
		rdAddr = (rdAddr+1)%QUEUE_SIZE;
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
