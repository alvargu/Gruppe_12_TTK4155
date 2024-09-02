//Procedures and functions used to initialise UART, transmit, and receive over UART.
#ifndef UART_DRIVER
#define UART_DRIVER

//Initialises UART communication.
//Takes in a given UBRR value. (UART baud rate)
void uart_init(unsigned int ubbr);

//Transmits one character over UART
//Takes in the character to transmit
void uart_transmit(unsigned char data);

//Recieves one character from UART
unsigned char uart_receive(void);
#endif
