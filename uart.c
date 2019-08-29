#include "uart.h"
#include <avr/io.h>
#include <stdio.h>


void USART_Init( unsigned int ubrr ){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	fdevopen(USART_Transmit , USART_Receive);
}



unsigned char USART_Receive(void){
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) );
/* Get and return received data from buffer */
return UDR0;
}



void USART_Transmit( unsigned char data ){
 /*Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
UDR0 = data;
}


//void USART_Transmit( unsigned int data ){
/* Wait for empty transmit buffer */
//while ( !( UCSR0A & (1<<UDRE0)) );
/* Copy 9th bit to TXB8 *///UCSR0B &= ~(1<<TXB80);if ( data & 0x0100 )UCSR0B |= (1<<TXB80);/* Put 
//data into buffer, sends the data */
//UDR0 = data;
//}


