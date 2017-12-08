#include "header.h"
#include "utils.h"
#include <stdio.h>

// Timer variables
volatile uint8_t timeToSync = 0; 	// set in interrupt handler when it is time to synchronize wizzimotes
volatile uint8_t ackTimerUp = 0; 	// set in interrupt handler when ACK timer expires TODO(low priority)
volatile uint8_t gotUartMessage = 0; 	// set in interrupt handler when new UART message has arrived

// Other variables
static volatile uint32_t virtualClock = 0;
volatile uint8_t uartMessage[6]; 	// set in interrupt handler
static uint8_t sentSchdlMsg[6];		// used to make sure SCHDL messages get ACKs TODO(low priority)
static char debugStr[50];

PROCESS(main_process, "Main Task");
AUTOSTART_PROCESSES(&main_process);

PROCESS_THREAD(main_process, ev, data)
{
	PROCESS_BEGIN();	
	
	// Sets up the watchdog timer to use ACLK input and an interval of 16s TODO: shorter interval?
	WDTCTL = WDTPW + WDTSSEL0 + WDTHOLD + WDTIS1 + WDTIS0;
	WDTCTL = (WDTCTL_L&~(WDTHOLD))+ WDTPW; 	// Start the watchdog

	// Turn off LEDs and init as outputs
	G_OFF(); G_OUT();
	R_OFF(); R_OUT();
	Y_OFF(); Y_OUT();

	// Begin status logging
	statusLog("Starting up the system RAD_TEAM");

	// Set up virtual clock timer
	TA1CTL = TASSEL0 + TAIE + MC0; // ACLK @ 32 kHz
	TA1CCR0 = 0x0400; // top value = 1024 -> interrupt at 64 Hz
	TA1CCTL0 = CCIE;
	static uint32_t sentTime;

	// Start receiving over radio
	static uint8_t msg[10] = "";
	static uint8_t oldMsgCnt = -1;
	static uint8_t newMsgCnt = -1;
	rf1a_start_rx();
	
	//TODO: set up UART
	

	// Set up the ack timer to a given interval..? but don't run it yet...
	//TODO(low priority)

	while(1)
	{
		kickWatchdog(); //TODO

		// Process received wizzimote messages
		getReceivedMessage(msg, &newMsgCnt);
		if(newMsgCnt != oldMsgCnt)
		{
			Y_T();
			oldMsgCnt = newMsgCnt;
			if(msg[0] == (CLKREQ | ACK))
			{
				uint8_t destID = msg[1];
				// calculate difference
				uint32_t slaveTime = *((uint32_t*)(&msg[2]));
				uint32_t diff = ((sentTime + virtualClock) / 2) - slaveTime;
				// setup SETCLK msg
				char returnMsg[6];
				returnMsg[0] = SETCLK;
				*((uint32_t*)(&returnMsg[2])) = diff;
				// send SETCLK msg
				unicast_send(returnMsg,6, destID);
				// debug info
				sprintf(debugStr,"Sent update message %d, %d, %d", 
					returnMsg[0], returnMsg[1], (*((uint32_t*)(&returnMsg[2]))) );
				debugLog(debugStr);
			}
			else if(msg[0] == (ACK))
			{
				//sentSchdlMsg TODO(low priority)
			}
		}

		//GENERATE MESSAGES FOR TESTING
		static int cnt = 500;
		static int newCnt = 500;
		while(virtualClock % 16 == 0 && virtualClock < 200){ 
			gotUartMessage = 1; 
			*((uint32_t*)(&uartMessage[2])) = cnt;
			newCnt = cnt+4;
		}
		while(virtualClock % 16 == 8 && virtualClock < 200){ 
			gotUartMessage = 1; 
			*((uint32_t*)(&uartMessage[2])) = cnt;
			newCnt = cnt+12;
		}
		cnt = newCnt;
		uartMessage[0] = SCHDL;
		uartMessage[1] = SNARE;
		
		// Process received UART messages
		if(gotUartMessage)
		{	
			G_T();
			gotUartMessage = 0;
			// Set clock message
			if(uartMessage[0] == SETCLK)
			{
				//TODO: disable interrupts
				virtualClock = *((uint32_t*)(&uartMessage[2]));
				//timeToSync = 1; // sync now since clock changed?
			}
			// Schedule message
			else if(uartMessage[0] == SCHDL)
			{
				//store into sentSchdlMsg TODO(low priority)
				//int i=0;
				//for(i=0; i<6; i++){ sentSchdlMsg[i] = uartMessage[i]; }
				//start ack timer...
				broadcast_send(uartMessage, 6);
				// debug info
				sprintf(debugStr,"Sent schedule message %d, %d, %d", 
					uartMessage[0], uartMessage[1], (*((uint32_t*)(&uartMessage[2]))) );
				debugLog(debugStr);
			}
			// Play now message
			else if(uartMessage[0] == 0x0)
			{
				broadcast_send(uartMessage, 6);	
				// debug info
				sprintf(debugStr,"Sent hit now message %d, %d, %d", 
					uartMessage[0], uartMessage[1], *((uint32_t*)(&uartMessage[2])));
				debugLog(debugStr);
			}
		}

		// Synchronize wizzimotes
		if(timeToSync)
		{
			timeToSync = 0;
			uint8_t msg[6];
			msg[0] = CLKREQ;
			broadcast_send(msg, 6);
			sentTime = virtualClock; //TODO: disable interrupts
			// debug info
			sprintf(debugStr,"Sent sync message %d, %d, %d", 
				msg[0], msg[1], (*((uint32_t*)(&msg[2]))) );	
			debugLog(debugStr);
		}
	} //end while loop
	PROCESS_END();
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1A0ISR(void)
{
	virtualClock++;
	if(virtualClock % 64 == 0)
	{ 
		timeToSync = 1;
	}
	sprintf(debugStr,"In the interrupt, clock is %d", virtualClock);
	//debugLog(debugStr);
}
