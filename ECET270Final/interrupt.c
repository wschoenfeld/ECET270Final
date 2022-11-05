#include "interrupt.h"

void init_interrupt(void)
{
	EICRA = 0x00;												//clear EICRA register
	EIMSK = 0x00;												//clear EIMSK register
	
	EICRA |= (1 << ISC00) | (1 << ISC01);						//set ISC0 bits to <rising edge trigger>
	EIMSK |= (1 << INT0);										//set INT0 bit to <enabled>
}

//runs when INTF0 is set
ISR(INT0_vect)
{
	_delay_ms(10); // delay is used so we can tell when two buttons are being pressed
	uint8_t mode_temp = 0;
	if(PINB == 0x02){	//If button A is on
		mode_temp = 1;
	}
	else if(PINB == 0x04){ //If button B is on
		mode_temp = 2;
	}
	else if(PINB == 0x08){ //If button C is on
		mode_temp = 3;
	} 
	else if(PINB == 0x10){ //If button D is on
		mode_temp = 4;
	}
	else if(PINB == 0x03){	//If button A and button B are on
		mode_temp = 5;
	}
	else if(PINB == 0x11){
		mode_temp = 6;
	}
	
	Receiver_ModeReturn(mode_temp);
}