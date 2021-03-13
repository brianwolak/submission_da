/*
 * GccApplication1.c
 *
 * Created: 3/13/2021 11:58:00 AM
 * Author : brian
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#include <avr/io.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

int timer_count;				//counter looping value
volatile uint8_t tempread;		//temp read value from ADC
char display1[20];				//fahrenheit string
char display2[20];				//celsius string

void USART_initialize(void){
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);	//8-bit data transfer
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);	//enable RX & TX
}

void interrupt_set(void){
	TCCR1A = 0x00;
	TCCR1B = 0x0D;		//prescale 1024, CTC mode
	OCR1A = 0x030C;		//0.05s counter delay value
	TIMSK1 = 0x02;		//enable OCR1A interrupt flag
	sei();
}

void adc_set(void){
	//reference Vcc, ADC5 input, PINC.5
	ADMUX |= (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | (0<<MUX3) | (1<<MUX2) | (0<<MUX1) | (1<<MUX0);
	//enable ADC, 128 prescale
	ADCSRA = (1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

void USART_TX_string(char *data){
	while (*data != '\0'){				//while data DNE 0
		while (!(UCSR0A & (1<<UDRE0)));	//while UNDRE0 DNE 1
		UDR0 = *data;				//UDR0 gets data value
		data++;						//next data value
	}
}

void ADC_READ(void){
	ADCSRA |= (1<<ADSC);				//start transfer
	while((ADCSRA & (1<<ADIF)) == 0);	//wait for ADIF flag
	ADCSRA |= (1 << ADIF);			//clear ADIF flag
	tempread = ADC;					//store temp value
}

void USART_TX_FLOAT(char data){		//convert for serialplot output
	UDR0 = data;
}

int main(void)
{
	USART_initialize();					//call USART initialize function
	interrupt_set();					//call interrupt set function
	adc_set();							//call ADC setup function
	float tempc;						//celsius temp
	float tempf;						//fahrenheit temp
	//confirm connection in terminal
	USART_TX_string("Device is Connected..\r\n");
	while (1)
	{
		if (timer_count == 5){						//enter loop once 0.25s time is reached
			ADC_READ();								//call ADC read function
			tempc = ((tempread * 500.0) / 1024);	//adjust tempc from binary to decimal
			tempf = (tempc * 1.8) + 32;				//convert to farenheit
			sprintf(display1, "%.2f", tempf);		//convert tempf to string
			_delay_ms(10);							//10ms delay
			sprintf(display2, "%.2f", tempc);		//convert tempc to string
			_delay_ms(10);							//10ms delay
			
			//terminal print statements for both temp C & F
			USART_TX_string("Temp is: ");
			USART_TX_string(display1);
			USART_TX_string(" F or ");
			USART_TX_string(display2);
			USART_TX_string(" C");
			USART_TX_string("\n");
			//uncomment one TX_FLOAT line and comment TX_string lines above to output to SERIALPLOT
			//USART_TX_FLOAT(tempc);	
			//USART_TX_FLOAT(tempf);
			timer_count = 0;						//reset 0.05s per step counter
		}
	}
}

ISR(TIMER1_COMPA_vect){
	//increment .05s counter once TIM1 COMPA match is made
	timer_count++;
}
