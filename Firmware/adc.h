#ifndef ADC_H
#define	ADC_H

#define ADC_VCC_DIVIDER 4   //This is the reciproc value of your voltage divider (ex. Write value of VCC/VOUT)

#define PVREF_2048  0
#define PVREF_4096  1


void ADC_Config();
uint16_t ADC_ReadChannel(uint8_t channel);
uint16_t ADC_AverageChannel(uint8_t channel, uint8_t samples);

/**
 * @Description: Measure VCC and return value that is equal to VCC in mV
 * @return  : uint16_t value. Each value is 1mV
 * @NOTE    : Please edit VCC_DIVIDER value in adc.h file to reflect value of your voltage divider!
 */
uint16_t ADC_MeasureVCC();

/**
 * Set Positive Voltage reference
 * @param reference
 * @Input 1 = 4.096V as positive voltage reference
 * @Input 0 = 2.048V as positive voltage reference
 */
void ADC_SetPVref(uint8_t reference);

#endif	/* ADC_H */

