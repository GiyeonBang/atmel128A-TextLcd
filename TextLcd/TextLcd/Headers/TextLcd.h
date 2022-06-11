#pragma once

#include "Board_02.h"

extern uint8_t read_data();
extern void write_data(uint8_t data);
extern void write_command(uint8_t data);


void gen_E_strobe()
{
	//Control_W |= 1 << E;
	PORTC |= 1 << E;
	
	volatile int i;
	for (i = 0; i < 10; i++)
		;
	
	//Control_W &= ~(1 << E);
	PORTC &= ~(1 << E);
}

void wait_busy()
{
	uint8_t is_busy;
	
	//Data = 0x00;
	//Control_W = (Control_W & ~(1 << RS))
	//	| 1 << RW;
	DDRC = 0x00;
	PORTA = (PORTA & ~(1 << RS))
		| 1 << RW;
	
	do
	{
		PORTA |= 1 << E;
		
		volatile int i;
		for (i = 0; i < 10; i++)
			;
		
		//is_busy = Data_R & 1 << Flag_busy;
		is_busy = PINA & 1 << PA7;
		
		//DDRA = 0x01;
		//PORTA = is_busy ? 0x01 : 0x00;
		
		//Control_W &= ~(1 << E);
		PORTD &= ~(1 << E);
	}
	while (is_busy);
}

void lcd_command(uint8_t data)
{
	wait_busy();
	
	//Data = 0xFF;
	//write_command(data);
	DDRA = 0xFF;
	PORTA = data;
	
	//Control_W &= ~(1 << RS | 1 << RW);
	PORTC &= ~(1 << RS || 1 << RW);
	
	gen_E_strobe();
}

void lcd_write(uint8_t data)
{
	wait_busy();
	
	//Data = 0xFF;
	//write_data(data);
	DDRA = 0xFF;
	PORTA = data;
	
	//Control_W = (Control_W | 1 << RS) & ~(1 << RW);
	PORTC = (PORTC | 1 << RS) & ~(1 << RW);
	
	gen_E_strobe();
}

void lcd_init()
{
	//Control |= 1 << RS
	//	| 1 << RW
	//	| 1 << E;
	DDRC |= 1 << RS
		| 1 << RW
		| 1 << E;
	
	//Control_W &= ~(1 << RS | 1 << RW | 1 << E);
	PORTC &= ~(1 << RS | 1 << RW | 1 << E);
	
	lcd_command(0x3C);
	lcd_command(0x02);
	lcd_command(0x01);
	lcd_command(0x06);
	lcd_command(0x0F);
}
