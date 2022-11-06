/*
Filename: "ir_speed_ctrl.c"
Version: 1

Created: 11/7/22
Author: Tobi Yoo

Operations: Function library for IR speed block. Read frequency value from PORTD pin 7, output PWM to PORTE pin 3.

Hardware Connections:
Atmega2560			Hardware
PORTD.7		<---	IR Sensor
PORTE.3		--->	Electronic Speed Controller
*/

// Global Declarations & Libraries
#include <avr/io.h>
#include "ir_speed_ctrl.h"

/*
Function: init_timer1_freq
Input Parameters: None
Output Data Type: Void
Task: Initializes timer 1 & PORTD pin 7 for frequency measurement.
*/
void init_timer1_freq(void)
{
	DDRD = DDRD & 0x7F; // Set PORTD PIN7 as input of IR signal.
	PORTD = PORTD | 0x80; // Turn on PORTD PIN7 pull-up resistor.
	
	TCCR1A = 0; // Normal timer operation, non-PWM mode.
	TCNT1 = 0; // Pre-set timer counter to 0.
	OCR1A = 0xFFFF; // Set output compare at max (We don't need it).
}

/*
Function: init_mode8_pwm
Input Parameters: None
Output Data Type: Void
Task: Initializes timer 3 PWM mode 8 and the port it outputs to (PORTE.3).
*/
void init_mode8_pwm(void)
{
	DDRE = DDRE | 0x08; // Set PORTE PIN3 as output of PWM.
	PORTE = PORTE & 0xF7; // PIN3 initially 0.

	ICR3 = 0x4E20; // Set top for frequency of 50 Hz.
	OCR3A = 0; // Output nothing for now.
	TCNT3 = 0; // Preset timer counter to 0.
	TCCR3A = 0xC0; // WGM Mode 8, set on compare match up-counting & clear on down-counting.
	TCCR3B = 0x12; // WGM Mode 8, pre-scaler as CLK / 8.
}

/*
Function: ir_freq_read
Input Parameters: None
Output Data Type: Unsigned 16-Bit Integer
Task: Read from PORTD.7 then calculates and returns the frequency.
*/
uint16_t ir_freq_read(void)
{
	// Local Variable Declarations
	uint16_t tickCount;
	float freqIR;
	
	if(PINA & 0x01) // If signal is already HIGH...
	{
		while(PINA & 0x01) // Wait until it goes LOW.
		{
		}
	}
	while(!(PINA & 0x01)) // Wait until signal goes HIGH (capture rising edge).
	{
	}
	
	TCCR1B = 0x04; // Start timer with pre-scaler as CLK/256 at rising edge.
	
	while(PINA & 0x01) // Wait until signal goes back LOW.
	{
	}
	while(!(PINA & 0x01)) // Wait until signal goes back HIGH (capture rising edge).
	{
	}
	
	TCCR1B = 0; // Stop counting at next rising edge.
	tickCount = TCNT1L; // Document from L register first.
	tickCount = tickCount | (TCNT1H << 8); // Document the rest of TCNT1 register.
	TCNT1 = 0; // Reset timer counter to 0.
	freqIR = 1 / (tickCount * .000016); // Calculate frequency from tick number.
	return(freqIR); // Return frequency.
}

/*
Function: ir_ctrl_pwm
Input Parameters: Unsigned 16-Bit Integer
Output Data Type: Void
Task: Takes frequency and outputs PWM accordingly.
*/
void ir_ctrl_pwm(uint16_t frequency)
{
	if((frequency > 4) && (frequency < 6)) // If frequency is 5 Hz.
	{
		OCR3A = 0x61D; // Output 1.565 ms pulse width.
	}
	else if((frequency > 9) && (frequency < 11)) // If frequency is 10 Hz.
	{
		OCR3A = 0x640; // Output 1.6 ms pulse width.
	}
	else if((frequency > 14) && (frequency < 16)) // If frequency is 15 Hz.
	{
		OCR3A = 0x68B; // Output 1.675 ms pulse width.
	}
	else if((frequency > 19) && (frequency < 21)) // If frequency is 20 Hz.
	{
		OCR3A = 0x6BD; // Output 1.725 ms pulse width.
	}
	else
	{
		OCR3A = 0; // No PWM if the frequency doesn't match the range.
	}
}