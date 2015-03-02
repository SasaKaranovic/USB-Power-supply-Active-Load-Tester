#include "main.h"


void UART_SendVCC(uint16_t value)
{
    UART_Write("VCC:");
    UART_SendDouble(value);
    UART_Write("V\r\n");
}

void UART_Send_PSU_Voltage()
{
    uint16_t ADC_Value = 0;
    ADC_Value = ADC_ReadChannel(ADCPSUVOLTAGESENSE);
    ADC_Value = ADC_Value * 40;     //Compensate for the 1/10 voltage divider + *4mV ADC quant
    UART_Write("PSV:");
    UART_SendDouble(ADC_Value);
    UART_Write("V\r\n");
}

void UART_Send_CurrentDraw()
{
    uint16_t ADC_Value = 0;
    ADC_Value = ADC_ReadChannel(ADCCURRENTSENSE);
    //ADC_Value = ADC_Value *10;      //Compensate for the sensing resistor value [only if diferent from 1ohm (eg. for 0.1ohm)]
    ADC_Value = ADC_Value << 2;     //Compensate for 4mV minimum quant ( << 2 is equal to multiply by 4)

    UART_Write("PSI:");
    UART_SendDouble(ADC_Value);
    UART_Write("A\r\n");
}

void UART_Send_PSU_VoltAmp()
{
    UART_Send_PSU_Voltage();
    UART_Send_CurrentDraw();
}


void UART_Send_OPAMP_Voltage()
{
    uint16_t ADC_Value;
    ADC_Value = ADC_ReadChannel(ADCDACVOLTAGESENSE);
    ADC_Value = ADC_Value << 2;     //Multiply by 2 (each quant is 4mV)
    UART_Write("OPA:");
    UART_SendDouble(ADC_Value);
    UART_Write("V\r\n");
}

void UART_SendDouble(uint16_t value)
{
    value = value / 10;     //Last 2 digits will be used as decimal point
    
    uint8_t temp10000, temp1000, temp100, temp10, temp1;

    temp1       = value     % 10;
    temp10      = value     / 10        % 10;
    temp100     = value     / 100       % 10;
    temp1000    = value     / 1000      % 10;
    temp10000   = value     / 10000     % 10;

    
    if(temp10000)
    {
        putch(48 + temp10000);
    }
    if(temp1000)
    {
        putch(48 + temp1000);
    }
    putch(48 + temp100);

    putch('.');
    putch(48 + temp10);
    putch(48 + temp1);
}

void UART_SendInteger(uint16_t value)
{
    uint8_t temp10000, temp1000, temp100, temp10, temp1;

    temp1       = value     % 10;
    temp10      = value     / 10        % 10;
    temp100     = value     / 100       % 10;
    temp1000    = value     / 1000      % 10;
    temp10000   = value     / 10000     % 10;


    if(temp10000) {  putch(48 + temp10000); }
    if(temp1000) {  putch(48 + temp1000); }
    putch(48 + temp100);
    putch(48 + temp10);
    putch(48 + temp1);
}

void UART_NewLine()
{
    putch(10);
    putch(13);
}




void UART_Debug(const char *str) {
#ifdef _DEBUG_UART_
    puts(str);
#endif
}

void UART_Write(const char *str) {
    while(*str) {
        putch(*str);
        *str++;
    }
}