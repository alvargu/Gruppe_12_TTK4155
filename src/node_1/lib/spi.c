#include "spi.h"

void
spi_master_init()
{
	//SPI IO Registers config
	DDRB = (1 << DDB5) | (1 << DDB7);

	//Enable and configure SPI as master with clock rate f_clk/16
	//Additionaly configures SPI to function in Mode 1,1
    //! Consider if it is supposed to function with an interrupt
	SPCR = /*(1 << SPIE) |*/ (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << CPHA)| (1 << SPR0);
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
	//Start Transmision by loading the char into transmit register
	SPDR = cTx;

	//Wait for transmit to finish
	while(!(SPSR & (1 << SPIF)))
	;
}


uint8_t
spi_rx()
{
    //Wait for SPI to finish reciving data
	while(!(SPSR & (1 << SPIF)))
		;
	
    //Get and return the recived data from SPDR register
	return SPDR;
}