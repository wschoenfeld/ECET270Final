/*
 * Car_Project.c
 *
 * Created: 11/1/2022 12:29:44 PM
 * Author : jkulick
 */ 

//Hardware for 2560 and 328
//								ATMEGA 2560		ATMEGA 328		Pins (2560)		Pins (328)
//Keyfob Data Lines	1-4			PORTB 0..3		PORTB 0..3		D53..50			14..17
//Interrupt 0					PORTD0			PORTD2			D21				4

//Definitions
#define F_CPU 16000000UL

//inclusions
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "interrupt.h"
#include "ir_speed_ctrl.h"
#include "Debugger.h"

//Global Variables
//volatile uint8_t EnableTracker; //(IR Speed Controller, Autonomous E brake, Adaptive Cruise, Backup/ Rear Collision Avoidance, BlindSpot Detection, Anti-Roller, Automatic Parallel Parking, empty)
//volatile uint8_t ClearHolds; //(empty, Autonomous E brake, empty, Backup/ Rear Collision Avoidance, empty, empty, empty, empty)

//Function Prototypes
uint8_t Receiver_ModeReturn(uint8_t RecieverInput,uint8_t EnableTracker,uint8_t ClearHolds); //Reciever Input is D1..D4. Exclude VT (interrupt pin)
void init_ports(void);

int main(void)
{
	init_ports();
	init_interrupt();
	initDebug();
	init_timer1_freq();
	init_mode8_pwm();
	uint8_t EnableTracker; //(IR Speed Controller, Autonomous E brake, Adaptive Cruise, Backup/ Rear Collision Avoidance, BlindSpot Detection, Anti-Roller, Automatic Parallel Parking, empty)
	uint8_t ClearHolds; //(empty, Autonomous E brake, empty, Backup/ Rear Collision Avoidance, empty, empty, empty, empty)
	uint8_t temp = PINL;
    /* Replace with your application code */
    while (1) 
    {
		
				EnableTracker,ClearHolds = Receiver_ModeReturn(temp,EnableTracker,ClearHolds);
		_delay_ms(100);
		//PORTC = EnableTracker; //set PORTC to EnableTracker so we can tell what is on and what isn't
    }
}
void init_ports(void){
	DDRL = 0x00;	//set PORTB to inputs from Receiver
	PORTL = 0xFF;	//turn pullup resistors on
	DDRC = 0xFF;	//set PORTC to outputs so we can test EnableTracker on LEDs
	PORTC = 0x00;	// turn them off to start
	DDRA = 0x00; // Port A as input from switches & push-buttons.
	PORTA = 0xFF; // Activate all pull-up resistors.
}

uint8_t Receiver_ModeReturn(uint8_t RecieverInput,uint8_t EnableTracker,uint8_t ClearHolds)
{
	//PORTC = 0;
	PORTC = RecieverInput;
	
// 	switch (RecieverInput)
//     {
// 		
//     case 1 : //IR Speed Controller
// 					
//                 EnableTracker ^= 1 << 7; //Toggle IR Speed enable bit
//                 break;
// 	case 2 : //Autonomous E Brake
// 			if (ClearHolds & (1 << 6)) //If Autonomous E Brake was activated clear it
// 				ClearHolds ^= 1 << 6; //Clear hold
// 			else //if break wasn't engaged
// 				EnableTracker ^= 1 << 6; //Toggle Autonomous E Brake enable bit
// 			break;
// 	case 3 : //Adaptive Cruise
// 			EnableTracker ^= 1 << 5; //Toggle Adaptive Cruise enable bit
// 			break;
// 	case 4 : //Backup/ Rear Collision Avoidance
// 			if (ClearHolds & (1 << 4)) //If Backup/ Rear Collision Avoidance was activated clear it
// 				ClearHolds ^= 1 << 4; //Clear hold
// 			else //if Backup/ Rear Collision Avoidance wasn't engaged
// 				EnableTracker ^= 1 << 4; //Toggle Backup/ Rear Collision Avoidance enable bit
// 			break;
// 	case 5 : //BlindSpot Detection
// 			EnableTracker ^= 1 << 3; //Toggle BlindSpot Detection enable bit
// 			break;
// 	case 6 : //Anti-Roller
// 			EnableTracker ^= 1 << 2; //Toggle Anti-Roller enable bit
// 			break;
// 	case 7 : //Automatic Parallel Parking
// 			EnableTracker ^= 1 << 1; //Toggle Automatic Parallel Parking enable bit
// 			break;
//     }
 	return(EnableTracker,ClearHolds);
}
