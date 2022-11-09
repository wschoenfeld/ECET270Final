/*
 * interrupt.h
 *
 * Created: 11/5/2022 6:00:04 PM
 *  Author: wills
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

//Definitions
#define F_CPU 16000000UL

void init_interrupt(void);



#endif /* INTERRUPT_H_ */