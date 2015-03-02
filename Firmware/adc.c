#include "main.h"


void ADC_Config()
{
#ifdef _PIC16F1829_H_
    //Configure Fixed voltage reference
    FVRCONbits.FVREN    = 1;            //1 = Fixed Voltage Reference is enabled
    while(!FVRCONbits.FVRRDY);          //1 = Fixed Voltage Reference output is ready for use

    //FVRCONbits.TSEN     = 1;            //1 = Temperature indicator is enabled
    FVRCONbits.ADFVR    = 0b11;         //11 = ADC Fixed Voltage Reference Peripheral output is 4x (4.096V)


    ADCON1bits.ADNREF   = 0;            // VSS is negative reference for ADC
    ADCON1bits.ADPREF   = 0b11;         // 11 = VREF+ is connected to internal Fixed Voltage Reference (FVR) module(1)
    ADCON1bits.ADCS     = 0b110;        // 110 = FOSC/64 -> 2us
    ADCON1bits.ADFM     = 1;            // 10bit result is right aligned


    //Configure pins used for ADC
    PINVOLTAGE      = 0;
    TRISVOLTAGE     = INPUT;
    ANSELVOLTAGE    = ANALOG;

    PINVCC          = 0;
    TRISVCC         = INPUT;
    ANSELVCC        = ANALOG;

    PINCURRENT      = 0;
    TRISCURRENT     = INPUT;
    ANSELCURRENT    = ANALOG;

    PINDACVOLTAGE      = 0;
    TRISDACVOLTAGE     = INPUT;
    ANSELDACVOLTAGE    = ANALOG;



    ADCON0bits.ADON     = 1;            //1 = ADC is enabled

    _delay_ms(10);  //Give UART some time to stabilise (not necessary)

#else
#warning "ADCConfig() function is empty for this device"
#endif
}

uint16_t ADC_ReadChannel(uint8_t channel)
{
    ADCON0bits.ADON     = 0;
    uint16_t adcresult = 0;
    uint8_t res_high, res_low;
    
    ADCON0bits.CHS  = channel;
    ADCON0bits.ADON     = 1;
    _delay_ms(20);
    ADCON0bits.ADGO = 1;

    //If interrupt is used to read value on completed adc cycle, then don't execute this code
#ifndef ADCINTERRUPTDRIVEN
    while(ADCON0bits.ADGO);     //1 = A/D conversion cycle in progress. Setting this bit starts an A/D conversion cycle.
                                //This bit is automatically cleared by hardware when the A/D conversion has completed.
    res_high = ADRESH & 0x03;
    res_low  = ADRESL;
    
    adcresult   = ( (uint16_t)(res_high << 8) | res_low);
#endif

    ADCON0bits.ADON     = 0;
    return adcresult;
}


uint16_t ADCAverageChannel(uint8_t channel, uint8_t samples)
{
    uint16_t result = 0, temp=0;
    uint8_t count = 0;

    while(--samples) {
        temp = ADC_ReadChannel(channel);

        if(count == 0) { result = temp; }
        result = ((result + temp) / 2);
    }

    return result;
}

uint16_t ADC_MeasureVCC()
{
    uint16_t VCC_Val = 0;
    ADC_SetPVref(0);        //Set Vref to 2.048 so we can measure 3v3 and 5V VCC
    VCC_Val = ADC_ReadChannel(ADCVCCSENSE);
    VCC_Val = VCC_Val   * 2 * ADC_VCC_DIVIDER;  // *2 to get milivolts value and * ADC_VCC_DIVIDER to get the real mV value of VCC
    ADC_SetPVref(1);        //Set Vref back to 4.096

    return VCC_Val;
}



void ADC_SetPVref(uint8_t reference)
{
    //We are using FVR of our MCU as positive voltage reference
    //Since device will be powered ether from 5v or 3v3 we are using 2.048V as reference
    //Make sure that voltage divider is set to be LESS or equal to 2V
    ADCON1bits.ADPREF   = 0b11;     //11 = VREF+ is connected to internal Fixed Voltage Reference (FVR) module(1)
    FVRCONbits.FVREN    = 0;        //0 = Fixed Voltage Reference is disabled
    
    if(reference == 1) {
        FVRCONbits.ADFVR    = 0b11;     //11 = ADC Fixed Voltage Reference Peripheral output is 4x (4.096V)(2)
    }
    else {
        FVRCONbits.ADFVR    = 0b10;     //10 = ADC Fixed Voltage Reference Peripheral output is 2x (2.048V)(2)
    }

    FVRCONbits.FVREN    = 1;        //1 = Fixed Voltage Reference is enabled
    UART_Debug("Waiting for FVR to get ready\r\n");
    while(!FVRCONbits.FVRRDY);      //1 = Fixed Voltage Reference output is ready for use
    UART_Debug("FVR ready\r\n");
    
}