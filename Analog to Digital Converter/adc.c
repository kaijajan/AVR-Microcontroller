#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"

char buffer[7];

void adc_init(){
	
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
	
}

int adc_read(){
	
	ADCSRA |= (1<<ADSC);
	
	while(ADCSRA & (1<<ADSC));
	
	return ADC;	
}

int main(void){
	
	lcd_init(LCD_DISP_ON);
	adc_init();
	
	lcd_puts("ADC Val: ");
	
    while(1){
	
		int adc = adc_read();
		int volt = adc * (12000/614);
		itoa(volt,buffer,10);
		lcd_gotoxy(9,0);
		lcd_puts(buffer);
		lcd_puts("     ");
		
		_delay_ms(100);
    }
}