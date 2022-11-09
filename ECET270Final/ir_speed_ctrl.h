/*
Filename: "ir_speed_ctrl.h"
Version: 1

Created: 11/7/22
Author: Tobi Yoo

Operations: Header file for "ir_speed_ctlr.c" file.
*/

// Global Declarations & Libraries
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

// Function Prototypes
void init_timer1_freq(void);
void init_mode8_pwm(void);
uint16_t ir_freq_read(void);
void ir_ctrl_pwm(uint16_t);