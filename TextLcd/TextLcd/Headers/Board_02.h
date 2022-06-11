#pragma once

#include <avr/io.h>
#include <stdint.h>

#define V0 PF0
	
#define RS PC0
#define RW PC1
#define E PC3

#define Flag_busy PA7

#define Control DDRC
#define Control_R PINC
#define Control_W PORTC
#define Data DDRA
#define Data_R PINA
#define Data_W PORTA

inline uint8_t reverse_bit(uint8_t data, uint32_t length = 1)
{
	 return ((data << length) & 0xff) | ((data >> (8 - length)) & 0xff);
}

inline uint8_t read_data()
{
	return Data_R;
	//return reverse_bit(Data_R);
}

inline void write_data(uint8_t data)
{
	Data_W = data;
	//Data_W = reverse_bit(data);	
}

inline void write_command(uint8_t data)
{
	Data_W = data;
	//Data_W = reverse_bit(data);
}
