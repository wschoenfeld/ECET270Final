#include "interrupt.h"

void init_interrupt(void)
{
	EICRA = 0x00;												//clear EICRA register
	EIMSK = 0x00;												//clear EIMSK register
	
	EICRA |= (1 << ISC00) | (1 << ISC01);						//set ISC0 bits to <rising edge trigger>
	EICRA |= (1 << ISC10) | (1 << ISC11);						//set ISC1 bits to <rising edge trigger>
	EIMSK |= (1 << INT0);										//set INT0 bit to <enabled>
	EIMSK |= (1 << INT1);										//set INT1 bit to <enabled>
}

//runs when INTF0 is set
ISR(INT0_vect)
{
	if (mode < 2)
	{
		mode++;
	}
	else
	{
		mode = 0;
	}
}