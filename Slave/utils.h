#include <stdint.h>

uint8_t getPROGRESS();
void setPROGRESS(uint8_t);
void clearPROGRESS();

void kickWatchdog();

void statusLog(char*);
void debugLog(char*);
