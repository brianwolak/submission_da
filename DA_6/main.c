/*
 * GccApplication1.c
 *
 * Created: 4/22/2021 8:52:28 AM
 * Author : Brian
 */ 


#define F_CPU 16000000UL //CPU clock speed
#define BAUD 9600 //Baud rate is 9600
#include <avr/common.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>
#include <stdio.h>
#include <util/delay.h>
#include <inttypes.h>
#include <util/twi.h>
#define SCL_CLOCK 100000L
#define TW_STATUS_PB (TWSR0 & 0xF8)
char display[20], display2[20];
uint8_t who_am_i;				//device address
uint16_t Xacc, Yacc, Zacc, Xgyr, Ygyr, Zgyr;
float Xaccf, Yaccf, Zaccf, Xgyrf, Ygyrf, Zgyrf;

//UART initialize
void USART_init(void)
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}
//UART print function
void USART_tx_string(char *data){
	while((*data != '\0')){ //while the data string is not empty
		while(!(UCSR0A & (1 << UDRE0))); //while the data regsiter is not empty
		UDR0 = *data; //UDR0 register receives data
		data++; //next data value
	}
}

void i2c_init(void)
{/* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
	TWSR0 = 0; /* no prescaler */
	TWBR0 = ((F_CPU/SCL_CLOCK)-16)/2; /* must be > 10 for stable operation 12*/
}/* i2c_init */

unsigned char i2c_start(unsigned char address)
{
		uint8_t twst;
		// send START condition
		TWCR0 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		// wait until transmission completed
		while(!(TWCR0 & (1<<TWINT)));
		// check value of TWI Status Register. Mask prescaler bits.
		twst = TW_STATUS_PB & 0xF8;
		if ( (twst != TW_START) && (twst != TW_REP_START)) return 1;
		// send device address
		TWDR0 = address;
		TWCR0 = (1<<TWINT) | (1<<TWEN);
		// wail until transmission completed and ACK/NACK has been received
		while(!(TWCR0 & (1<<TWINT)));
		// check value of TWI Status Register. Mask prescaler bits.
		twst = TW_STATUS_PB & 0xF8;
		if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;
		return 0;
}/* i2c_start */
		
unsigned char i2c_rep_start(unsigned char address)
{
	return i2c_start( address );
}/* i2c_rep_start */

void i2c_stop(void)
{
	/* send stop condition */
	TWCR0 = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	// wait until stop condition is executed and bus released
	while(TWCR0 & (1<<TWSTO));
}/* i2c_stop */

unsigned char i2c_write( unsigned char data )
{
	uint8_t twst;
	// send data to the previously addressed device
	TWDR0 = data;
	TWCR0 = (1<<TWINT) | (1<<TWEN);
	// wait until transmission completed
	while(!(TWCR0 & (1<<TWINT)));
	// check value of TWI Status Register. Mask prescaler bits
	twst = TW_STATUS_PB & 0xF8;
	if( twst != TW_MT_DATA_ACK) return 1;
	return 0;
}//* i2c_write *

unsigned char i2c_readAck(void)
{
	TWCR0 = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR0 & (1<<TWINT)));
	return TWDR0;
}/* i2c_readAck */

unsigned char i2c_readNak(void)
{
	TWCR0 = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR0 & (1<<TWINT)));
	return TWDR0;
}/* i2c_readNak */

void i2c_start_wait(unsigned char address)
{
	uint8_t twst;
	while ( 1 )
	{
	// send START condition
	TWCR0 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait until transmission completed
	while(!(TWCR0 & (1<<TWINT)));
	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS_PB & 0xF8;
	if ( (twst != TW_START) && (twst != TW_REP_START)) continue;
	// send device address
	TWDR0 = address;
	TWCR0 = (1<<TWINT) | (1<<TWEN);
	// wail until transmission completed
	while(!(TWCR0 & (1<<TWINT)));
	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS_PB & 0xF8;
	if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) )
	{/* device busy, send stop condition to terminate write operation */
	TWCR0 = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	// wait until stop condition is executed and bus released
	while(TWCR0 & (1<<TWSTO));
	continue;
	}
	//if( twst != TW_MT_SLA_ACK) return 1;
	break;
}
}/* i2c_start_wait */

//who_am_i function
uint16_t who_am_i_func(void){
	uint16_t data;
	i2c_start_wait(0xD0); //open write communication with 20948
	i2c_write(0x00); //select register address
	i2c_start_wait(0xD1); //open communication again
	data = i2c_readNak(); //read data value
	i2c_stop(); //stop transmission
	
	return data;
}
//get 16-bit data function
int get_data(uint16_t addressL, uint16_t addressH){
	uint16_t data;
	i2c_start_wait(0xD0);		//start communication with sensor
	i2c_write(addressH);		//send high register address
	i2c_start_wait(0xD1);		//open communication
	data = i2c_readNak();		//read high register
	i2c_stop();					//stop transmission
	i2c_start_wait(0xD0);		//open write
	i2c_write(addressL);		//send low address
	i2c_start_wait(0xD1);		//open communication
	data = (8 << data) | i2c_readNak();		//read values
	i2c_stop();					//stop transmission
	
	return data;
}


int main(void)
{
		int device;							//device read address
		USART_init();						//function call
		i2c_init();							//initialize i2c
		USART_tx_string("Connection Established!\r\n"); //UART connection confirm		i2c_start_wait(0xD0);				//open communication with sensor
		i2c_write(0x06);					//select register 6
		i2c_write(0x00);					//write value to the register location
		i2c_stop();							//stop i2c
		
		//who_am_i
		who_am_i = who_am_i_func();
		//print who_am_i info
		sprintf(display, "%d", who_am_i);
		USART_tx_string("i2c device address is: ");
		USART_tx_string(display);
		USART_tx_string("\r\n");
		device = who_am_i;

				while (1){
					who_am_i = who_am_i_func(); //who_am_i check
					if (who_am_i == device)		//if true, device connected
					USART_tx_string("ICM-20948 is still Connected\r\n");
					else						//if false, device not connected
					USART_tx_string("ICM-20948 is NOT Connected\r\n");

					//gyro X
					Xgyr = get_data(0x33, 0x34);
					Xgyrf = Xgyr / 131.0;	//scale with sensitivity factor
					//print gyro X info
					sprintf(display, "%.2f", Xgyrf);
					USART_tx_string("Gyro X Value: ");
					USART_tx_string(display);
					USART_tx_string("\r\n");
					
					//gyro Y
					Ygyr = get_data(0x35, 0x36);
					Ygyrf = Ygyr / 131.0;	//scale with sensitivity factor
					//print gyro Y info
					sprintf(display, "%.2f", Ygyrf);
					USART_tx_string("Gyro Y Value: ");
					USART_tx_string(display);
					USART_tx_string("\r\n");
					
					//gyro Z
					Zgyr = get_data(0x37, 0x38);
					Zgyrf = Zgyr / 131.0;	//scale with sensitivity factor
					//print gyro Z info
					sprintf(display, "%.2f", Zgyrf);
					USART_tx_string("Gyro Z Value: ");
					USART_tx_string(display);
					USART_tx_string("\r\n");
					
					//accelerometer X
					Xacc = get_data(0x2D, 0x2E);
					Xaccf = Xacc / 16384.0;	//scale with sensitivity factor
					//print accel X info
					sprintf(display, "%.2f", Xaccf);
					USART_tx_string("Accelerometer X Value: ");
					USART_tx_string(display);
					USART_tx_string("\r\n");
					
					//accelerometer Y
					Yacc = get_data(0x2F, 0x30);
					Yaccf = Yacc / 16384.0; //scale with sensitivity factor
					//print accel Y info
					sprintf(display, "%.2f", Yaccf);
					USART_tx_string("Accelerometer Y Value: ");
					USART_tx_string(display);
					USART_tx_string("\r\n");
					
					//Accelerometer Z
					Zacc = get_data(0x31, 0x32);
					Zaccf = Zacc / 16384.0;	//scale with sensitivity factor
					//print accel Z info
					sprintf(display, "%.2f", Zaccf);
					USART_tx_string("Accelerometer Z Value: ");
					USART_tx_string(display);
					USART_tx_string("\r\n");
					USART_tx_string("\r\n");
					
					_delay_ms(500); //terminal delay

			}
}

