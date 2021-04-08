/*
 * GccApplication1.c
 *
 * Created: 4/6/2021 2:14:45 PM
 * Author : Brian
 */ 

#define F_CPU 16000000UL							/* Define CPU Frequency 16MHz */
#include <avr/io.h>									/* Include AVR std. library file */
#include <util/delay.h>								/* Include Delay header file */

volatile unsigned int pot;		//temporary read value from ADC

//ADC initialize, PC0 input
void adc_init(void){
	ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (0 << MUX3) | (0 << MUX2) |
	(0 << MUX1) | (0 << MUX0);
	ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIF) | (0 << ADIE) | (1
	<< ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}
//read ADC value
void read_adc(void){
	ADCSRA |= (1 << ADSC);
	while((ADCSRA & (1 << ADIF))==0);		//wait for ADIF flag
	ADCSRA |= (1 << ADIF);					//reset ADIF flag
	pot = ADC;								//read value
	OCR1A = 50 + pot / 2;					//set pot value to OCR1A with 
}
//timer1 setup function
void t1_setup(void){
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
	ICR1=4999;											//fPWM=50Hz (Period = 20ms Standard)
}

int main(void)
{
	t1_setup();			//timer1 intialize
	adc_init();			//initialize ADC
	
	DDRB |= (1<<PINB1);   //PWM output on PB1

	while(1)
	{
		read_adc();		//continous read ADC
		
	}
}

