#ifndef SPI_H
#define SPI_H

void	spi_master_init();		//Init function of SPI as master
void	spi_slave_init();		//Init function of SPI as slave
void	spi_tx(char);			//Transmit char over SPI
uint8_t spi_rx();				//Read char over SPI							

#endif;