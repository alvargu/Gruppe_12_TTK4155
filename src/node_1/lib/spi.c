#include "spi.h"

void
spi_master_init()
{
	//SPI IO Registers config
	//SS	- signal configured as an output (PB4)
	//MOSI	- signal configured as an output (PB5)
	//SCK	- signal configured as an output (PB7)
	DDRB = (1 << DDB4) | (1 << DDB5) | (1 << DDB7);

	//Enable and configure SPI as master with clock rate f_clk/16
	//Additionaly configures SPI to function in Mode 1,1
	SPCR = (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << CPHA)| (1 << SPR0);
	
	//Enable Global Interrupt
	sei();
}

void
spi_slave_init()
{
	//SPI Direction Register Config
	//Setup MISO as output everything else input
	DDRB = (1 << DDB6);
	
	//Enable SPI
	SPCR = (1 << SPE);
}

void
spi_transmit(char cTx)
{
    //Init transmit by setting SS line low
    PORTB &= ~(1 << PB4);

	//Start transmission by loading the char into transmit register
	SPDR = cTx;

	//Wait for transmit to finish
	while(!(SPSR & (1 << SPIF)))
	    ;

    //Sync Slave and Master by setting SS high
    PORTB |= (1 << PB4);
}

uint8_t
spi_rx()
{
    //Wait for SPI to finish transmitting data
	while(!(SPSR & (1 << SPIF)))
		;
	
    //Get and return the received data from SPDR register
	return SPDR;
}