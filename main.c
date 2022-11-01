/*
 * Car_Project.c
 *
 * Created: 11/1/2022 12:29:44 PM
 * Author : jkulick
 */ 

//inclusions
#include <avr/io.h>

//Definitions

//Global Variables
volatile uint8_t EnableTracker; //(IR Speed Controller, Autonomous E brake, Adaptive Cruise, Backup/ Rear Collision Avoidance, BlindSpot Detection, Anti-Roller, Automatic Parallel Parking, empty)
volatile uint8_t ClearHolds; //(empty, Autonomous E brake, empty, Backup/ Rear Collision Avoidance, empty, empty, empty, empty)

//Function Prototypes
uint8_t Receiver_ModeReturn(uint8_t EnableTracker, uint8_t ModeReturn);

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
	
    }
}

uint8_t Receiver_ModeReturn(uint8_t EnableTracker, uint8_t ModeReturn)

