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
void Receiver_ModeReturn(uint8_t RecieverInput); //Reciever Input is D1..D4. Exclude VT (interrupt pin)

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
	
    }
}

void Receiver_ModeReturn(uint8_t RecieverInput)
{
	switch (RecieverInput)
    {
        case 1 : //IR Speed Controller
					
                EnableTracker ^= 1 << 7; //Toggle IR Speed enable bit
                break;
	case 2 : //Autonomous E Brake
			if (ClearHolds & (1 << 6)) //If Autonomous E Brake was activated clear it
				ClearHolds ^= 1 << 6; //Clear hold
			else //if break wasn't engaged
				EnableTracker ^= 1 << 6; //Toggle Autonomous E Brake enable bit
			break;
	case 3 : //Adaptive Cruise
			EnableTracker ^= 1 << 5; //Toggle Adaptive Cruise enable bit
			break;
	case 4 : //Backup/ Rear Collision Avoidance
			if (ClearHolds & (1 << 4)) //If Backup/ Rear Collision Avoidance was activated clear it
				ClearHolds ^= 1 << 4; //Clear hold
			else //if Backup/ Rear Collision Avoidance wasn't engaged
				EnableTracker ^= 1 << 4; //Toggle Backup/ Rear Collision Avoidance enable bit
			break;
	case 5 : //BlindSpot Detection
			EnableTracker ^= 1 << 3; //Toggle BlindSpot Detection enable bit
			break;
	case 6 : //Anti-Roller
			EnableTracker ^= 1 << 2; //Toggle Anti-Roller enable bit
			break;
	case 7 : //Automatic Parallel Parking
			EnableTracker ^= 1 << 1; //Toggle Automatic Parallel Parking enable bit
			break;
    }
}
