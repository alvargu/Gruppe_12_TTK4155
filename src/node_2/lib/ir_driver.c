#include "ir_driver.h"

void
ADC_Handler(void)
{
	if(ADC -> ADC_ISR & ADC_ISR_DRDY)
	{
		adc_data = ADC -> ADC_LCDR;
	}
}

void
adc_init()
{
	NVIC_EnableIRQ(ADC_IRQn);												//Enable interrupt for ADC
	__enable_irq();															    //Enable Interrupts
	
	PMC -> PMC_PCER1	|= PMC_PCER1_PID37;						//Enable Peripheral in PMC
	
	PIOA -> PIO_PDR		|= PIO_PA16;									//Change Control over pin to peripheral
	PIOA -> PIO_ABSR	|= PIO_PA16;									//Change peripheral to peripheral B (ADC)
	
	ADC -> ADC_MR		|= ADC_MR_FREERUN_ON						//Configure ADC in freerun mode
						      |  ADC_MR_PRESCAL(0b01100011);	//Running ADC at 420kHz
	ADC -> ADC_CHER		|= ADC_CHER_CH7;							//Enable ADC Channel 7
	ADC -> ADC_IER		|= ADC_IER_DRDY;							//Interrupt when data ready
	
	ADC -> ADC_CR		|= ADC_CR_START;								//Start ADC
}
