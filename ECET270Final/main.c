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

//Function Prototypes
uint8_t Receiver_ModeReturn(uint8_t RecieverInput,uint8_t EnableTracker); //Receiver Input is D1..D4. Exclude VT (interrupt pin)
void init_ports(void);

int main(void)
{
	init_ports();
	init_interrupt();
	initDebug();
	init_timer1_freq();
	init_mode8_pwm();
	uint8_t EnableTracker = 0; //(IR Speed Controller, Autonomous E brake, Adaptive Cruise, Backup/ Rear Collision Avoidance, BlindSpot Detection, Anti-Roller, Automatic Parallel Parking, empty)
    while (1) 
    {
		if(PINL != 0)
		{
			_delay_ms(20);
			uint8_t temp = PINL; //Set temp to PINL
			EnableTracker = Receiver_ModeReturn(temp,EnableTracker);
		}
		PORTC = EnableTracker;
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

uint8_t Receiver_ModeReturn(uint8_t RecieverInput,uint8_t EnableTracker)
{
	_delay_ms(750);
 	switch (RecieverInput)
     {
 		
		case 1 : //IR Speed Controller	
				EnableTracker = EnableTracker^ 0x40; //Toggle IR Speed enable bit
				break;
 		case 2 : //Autonomous E Brake
 				EnableTracker = EnableTracker^ 0x20; //Toggle Autonomous E Brake enable bit
 				break;
 		case 3 : //Adaptive Cruise
 				EnableTracker = EnableTracker^ 0x10; //Toggle Adaptive Cruise enable bit
 				break;
 		case 4 : //Backup/ Rear Collision Avoidance
 				EnableTracker = EnableTracker^ 0x08; //Toggle Backup/ Rear Collision Avoidance enable bit
 				break;
 		case 5 : //BlindSpot Detection
 				EnableTracker = EnableTracker^ 0x04; //Toggle BlindSpot Detection enable bit
 				break;
 		case 6 : //Anti-Roller
 				EnableTracker = EnableTracker^ 0x02; //Toggle Anti-Roller enable bit
 				break;
 		case 8 : //Automatic Parallel Parking
 				EnableTracker = EnableTracker^ 0x01; //Toggle Automatic Parallel Parking enable bit
 				break;
     }
 	return(EnableTracker); //Return the TempArray
}
