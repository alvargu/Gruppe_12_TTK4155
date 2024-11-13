#include "ir_driver.h"

volatile uint16_t adc_data		= 0;
volatile uint16_t old_adc_data	= 2000;

//Interrupt Service Routine code implementation
//Waits for data ready interrupt and then saves measured ADC data from ADC_LCDR register
void
ADC_Handler(void)
{
	if(ADC -> ADC_ISR & ADC_ISR_DRDY)
	{
		adc_data = ADC -> ADC_LCDR;
	}
}

//Initializes both ADC and other dependent peripherals for measurement
void
adc_init()
{
	NVIC_EnableIRQ(ADC_IRQn);										//Enable interrupt for ADC
	__enable_irq();													//Enable Interrupts
	
	PMC  -> PMC_PCER1	|= PMC_PCER1_PID37;							//Enable Peripheral in PMC
	
	PIOA -> PIO_PDR		|= PIO_PA16;								//Change Control over pin to peripheral
	PIOA -> PIO_ABSR	|= PIO_PA16;								//Change peripheral to peripheral B (ADC)
	
	ADC	 -> ADC_MR		|= ADC_MR_FREERUN_ON						//Configure ADC in freerun mode
						|  ADC_MR_PRESCAL(0b01100011);				//Running ADC at 420kHz
	ADC  -> ADC_CHER	|= ADC_CHER_CH7;							//Enable ADC Channel 7
	ADC  -> ADC_IER		|= ADC_IER_DRDY;							//Interrupt when data ready
	
	ADC  -> ADC_CR		|= ADC_CR_START;							//Start ADC
}

//Function return last measured ADC data
uint16_t
get_adc_val()
{
	return adc_data;
}

//Function to check is there has been a goal
//Goal i sdetected by measuring a falling edge on ADC data
uint8_t
is_goal()
{
	uint8_t return_val;
	if ((adc_data < 2000) && (old_adc_data >= 2000))
	{
		return_val = 1;
	}
	else
	{
		return_val = 0;
	}
	
	old_adc_data = adc_data;
	
	return return_val;
}
