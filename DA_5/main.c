/*
 * GccApplication1.c
 *
 * Created: 4/27/2021 7:13:37 PM
 * Author : brian
 */ 

#define F_CPU 16000000UL	//CPU clock speed
#define BAUD 9600			//9600 baud rate

#ifndef __SMALL_SPI_H__
#define __SMALL_SPI_H__
#include <avr/common.h>
void spi_master_init(void);
void spi_bulk_send(uint8_t *send_buffer, uint8_t count);
void spi_send(uint8_t send_data);
void spi_bulk_exchange(uint8_t *send_buffer, uint8_t *receive_buffer, uint8_t count);
uint8_t spi_exchange(uint8_t send_data);
#endif

#include <avr/common.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>
#include <stdio.h>
#include <util/delay.h>

#define DDR_SPI DDRB	//define SPI port
#define DD_MOSI DDB3	//MOSI pin3
#define DD_MISO DDB4	//MISO pin4
#define DD_SCK DDB5		//SCK pin5

char display[20];		//uart string display 
char X = 'X';
char Y = 'Y';
char Z = 'Z';
uint8_t who_am_i = 0;	//whoami value
//retrived data storage variables
uint16_t Xacc, Yacc, Zacc, Xgyr, Ygyr, Zgyr;

//SPI initialize
void spi_master_init(void)
{
	SPCR0 = (0 << SPIE) | (1 << SPE) | (0 << DORD) | (1 << MSTR) |
	(0 << CPOL) | (0 << CPHA) | (0 << SPR1) | (1 << SPR0);
}
//bulk send function
void spi_bulk_send(uint8_t *send_buffer, uint8_t count)
{
	while(count--)
	{
		SPDR0 = *send_buffer++;
		loop_until_bit_is_set(SPSR0, SPIF);
	}
}

//spi command function
void spi_send(uint8_t send_data)
{
	SPDR0 = send_data;
	while(!(SPSR0 & (1<<SPIF)));
}

//bulk send/receive function
void spi_bulk_exchange(uint8_t *send_buffer, uint8_t *receive_buffer, uint8_t count)
{
	while(count--)
	{
		SPDR0 = *send_buffer++;
		loop_until_bit_is_set(SPSR0, SPIF);
		*receive_buffer++ = SPDR0;
	}
}

//8-bit exchange function
uint8_t spi_exchange(uint8_t send_data)
{
	SPDR0 = send_data;
	while(!(SPSR0 & (1<<SPIF)));
	return SPDR0;
}

//UART initialize
void USART_init(void)
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

//terminal print function
void USART_tx_string(char *data)
{
	while((*data != '\0'))					//loop while string not empty
	{
		while(!(UCSR0A & (1 << UDRE0)));	//loop while data register not empty
		UDR0 = *data;						//save data to UDR0
		data++;								//increment data
	}
}
//who_am_i function
uint16_t who_am_i_func(void){
	uint16_t data;
	PORTB &= ~(1 << 2);					//spi enable
	spi_send(0x80);						//send who_am_i address
	data = spi_exchange(0x00);			//get who_am_i value
	PORTB |= (1 << 2);					//spi disable
	
	return data;
}
//get 16-bit data function
int get_data(uint16_t addressH, uint16_t addressL){
	int data;
	PORTB &= ~(1 << 2);			//spi enable
	spi_send(addressH);			//send address high
	data = spi_exchange(0x00);	//get data
	PORTB |= (1 << 2);			//spi disable
	PORTB &= ~(1 << 2);			//spi enable
	spi_send(addressL);			//send address low
	data = ((uint16_t)(8<<data)) | (uint16_t)(spi_exchange(0x00)); //combining L and H
	PORTB |= (1 << 2);			//spi disable
	
	return data;
}

int main(void)
{
	DDRB |= (1 << 2)|(1<<3)|(1<<5);		//set output ports
	DDRB &= ~(1<<4);					//set input
	USART_init();						//initialize UART
	USART_tx_string("Connection Established\r\n");	//confirm UART connection
	spi_master_init();					//spi master initialize
	PORTB &= ~(1 << 2);					//spi enable
	spi_send(0x06);						//address sensor clock
	spi_send(0x05);						//send sensor clock speed
	PORTB |= (1 << 2);					//toggle SPI enable
	
	//who_am_i
	who_am_i = who_am_i_func();
	//print who_am_i info
	sprintf(display, "%d", who_am_i);
	USART_tx_string("Slave address is: ");
	USART_tx_string(display);
	USART_tx_string("\r\n");
	while (1)
	{
		who_am_i = who_am_i_func(); //who_am_i check
		if (who_am_i == 234)		//if true, device connected
		USART_tx_string("ICM-20948 is still Connected\r\n");
		else						//if false, device not connected
		USART_tx_string("ICM-20948 is NOT Connected\r\n");
		//gyro X
		Xgyr = get_data(0xB3, 0xB4);
		//print gyro X info
		sprintf(display, "%d", Xgyr);
		USART_tx_string("Gyro X Value: ");
		USART_tx_string(display);
		USART_tx_string("\r\n");
		
		//gyro Y
		Ygyr = get_data(0xB5, 0xB6);
		//print gyro Y info
		sprintf(display, "%d", Ygyr);
		USART_tx_string("Gyro Y Value: ");
		USART_tx_string(display);
		USART_tx_string("\r\n");
		
		//gyro Z
		Zgyr = get_data(0xB7, 0xB8);
		//print gyro Z info
		sprintf(display, "%d", Zgyr);
		USART_tx_string("Gyro Z Value: ");
		USART_tx_string(display);
		USART_tx_string("\r\n");
		
		//accelerometer X
		Xacc = get_data(0xAD, 0xAE);
		//print accel X info
		sprintf(display, "%d", Xacc);
		USART_tx_string("Accelerometer X Value: ");
		USART_tx_string(display);
		USART_tx_string("\r\n");
		
		//accelerometer Y
		Yacc = get_data(0xAF, 0xB0);
		//print accel Y info
		sprintf(display, "%d", Yacc);
		USART_tx_string("Accelerometer Y Value: ");
		USART_tx_string(display);
		USART_tx_string("\r\n");
		
		//Accelerometer Z
		Zacc = get_data(0xB1, 0xB2);
		//print accel Z info
		sprintf(display, "%d", Zacc);
		USART_tx_string("Accelerometer Z Value: ");
		USART_tx_string(display);
		USART_tx_string("\r\n");
		USART_tx_string("\r\n");
		
		_delay_ms(500); //terminal delay
	}
}


