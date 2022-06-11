#define F_CPU 16000000

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../Headers/TextLcd.h"


bool g_flag = true;

void fn1();
ISR(INT0_vect);

#define LCD
//#define BUTTON

int main()
{

	// LCD
#ifdef LCD	
	lcd_init();
	
	const char* strings[] = {
		"ATmega128A",
		"MicroController"
	};

	int row = 2;
	int col = 16;
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			if (strings[r][c] != '\0')
			{
				lcd_write(strings[r][c]);
			}
			else
			{
				if (row == 0)
					lcd_command(0xc0);
				break;
			}
		}
	}
	
	while (true);
	return 0;
#endif
	
	// Button
#ifdef BUTTON
	EIMSK = 0x0F;
	EICRA = 0b10101010;
	EIFR = 0xFF;
	
	SREG = 0x80;
	
	DDRA = 0xFF;
	PORTA = 0x00;
	
	DDRD = 0x00;
	PORTD = 0x00;
	
	//
	
	sei();
	while (true)
	{
		PORTA = ~PORTA;
		_delay_ms(2000);
	}
	return 0;
	
#endif
}

ISR(INT0_vect)
{	
	for (int i = 0; i < 10; i++)
	{
		PORTA = ~PORTA;
		_delay_ms(800);
	}
	
	EIFR = 0x00;
}

ISR(INT1_vect)
{	
	for (int i = 0; i < 20; i++)
	{
		PORTA = ~PORTA;
		_delay_ms(600);
	}
	
	EIFR = 0x00;
}

ISR(INT2_vect)
{	
	for (int i = 0; i < 30; i++)
	{
		PORTA = ~PORTA;
		_delay_ms(400);
	}
	
	EIFR = 0x00;
}

ISR(INT3_vect)
{	
	for (int i = 0; i < 40; i++)
	{
		PORTA = ~PORTA;
		_delay_ms(200);
	}
	
	EIFR = 0x00;
}
