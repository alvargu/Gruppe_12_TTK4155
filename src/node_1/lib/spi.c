#include "spi.h"

void
spi_init()
{
    //TODO:
    //SPI Registers config
    DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK);

    //Enable and configure SPI as master with clock rate f_clk/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void
spi_transmit(char cTx)
{
    //Start Transmision
    SPDR = cTx;

    //Wait for transmit to finish
    while(!(SPSR & (1 << SPIF)))
        ;
}