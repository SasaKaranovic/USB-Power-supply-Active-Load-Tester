/*
 *  Project     : Programmable Active Dummy Load
 *  Code Version: 0.6 (see change log for more information and what's changed)
 *  Compile with: Microchip XC8 v1.31 or up (free compiler)
 *  Hardware    : - PIC16F1829
 *                - MCP4726   (12bit DAC)
 *                - MCP6002   (2x Rail-to-Rail OP-Amp)
 *                - Logic Level N-MOSFET (IRLxx in TO-220 case)
 *                - USB-to-UART converter (FTDI, CH340 or any other)
 *
 *  Description : As the title implies, this is the source code of the programmable active load
 *  unit. Latest source code, design files, schematic, Bill of Material, HOW-TO and lot's of other
 *  useful information about this project can be found on:
 *  My Homepage: http://sasakaranovic.com/projects/usb-pal-tester/
 *  GitHub     : https://github.com/coldkeyboard/USB-PAL-Tester
 *
 * 
 *  Nice feature is that this unit is completely programmable via USB, so you can write little
 *  Python, C, C++, .NET app that will do series of tests on your Power Supply that you want to
 *  check and log that data or plot it on the graphs to see the Power Supply characteristics.
 *
 *  Device configuration and readings are done over the serial communication or UART.
 *  With commands like S:3000 the MCU will set-up DAC to set 3000mV or 3.000V on its output.
 *  DAC Output is connected to + Op Amp which is driving the N-MOSFET that acts like dummy load.
 *  Drain of mosfet is connected to Power Supply + that we want to test/stress. Source of the
 *  MOSFET is connected to the ground via small sensing resistor, 1ohm/1% or better. So having
 *  that in mind, and how OP-amps and MOSFETS work, our dummy load will try to draw 3Amps from
 *  the power supply under test. This little unit will send values like how much Amps are we
 *  drawing from the Power Supply under test, what voltage is across Power Supply under test,
 *  what is the output of the DAC (set current) and etc.
 *
 *  All of the files provided (including but not limited to schematics, source-code, drawings and etc.)
 *  are provided "as-is" without any guarantee and you are using them on your own risk.
 *
 *  All of the files provided are completely open-source. You can do whatever you want with them.
 *
 * I would really appreciate if you would share your designs, modifications, opinions, suggestions
 *  and etc. with me/others so we can all share and collaborate on this project.
 *
 * Also if you like this project or want to show your support, please consider donating (your time,
 *  opinion, review, code modifications, suggestions, request, beer, coffee or anything else you want). :)
 *
 */

#include "main.h"

//Value to send to DAC (VCC/DAC_RESOLUTION * SET_VOLTAGE)
uint16_t DAC_Target_Voltage = 0;

uint16_t ADC_val_VCC            = 0;
uint16_t ADC_val_PSUVCC         = 0;
uint16_t ADC_val_Current        = 0;

//UART ISR values
uint8_t ISR_RX_TEMP;        //Read to this temp variable
uint8_t ISR_RX_BUFF[10];    //Buffer to store RX characters
uint8_t ISR_RX_COUNT = 0;   //Counter for UART RX characters
uint8_t ISR_RX_STATE = 0;   //State of the current UART recieve process
uint8_t ISR_RX_MODE  = 0;   //Are we receiving command to set DAC (S:) or other parameters (C:)

//Configuration
uint8_t CONF_CONTINUOS_SEND         = 0;    //1 -> Send VCC, Current and Voltage Values continuously
uint8_t CONF_CONTINUOS_DELAY        = 10;    //Delay in (this_value)*100ms
uint8_t CONF_CONTINUOS_DELAY_TMP    = 10;    //Temp value used for creating dynamic delay
uint8_t ONDEMAND_PENDING            = 0;

void main()
{
    Device_SetUp();
    Device_Initialize();

    //Measure VCC to make sure our FVR can work properly
    ADC_val_VCC = ADC_MeasureVCC();

    UART_SendVCC(ADC_val_VCC);
    UART_Send_PSU_VoltAmp();
    UART_Send_OPAMP_Voltage();


    while(1)
    {
        if(CONF_CONTINUOS_SEND == 1)      //Continous mode enabled
        {
            UART_Send_PSU_VoltAmp();     //Send PSU Voltage and Current(amps) draw

            CONF_CONTINUOS_DELAY_TMP = CONF_CONTINUOS_DELAY;
            while(--CONF_CONTINUOS_DELAY_TMP) { _delay_ms(100); }
        }
        else if(ONDEMAND_PENDING == 1)
        {
            UART_Send_PSU_VoltAmp();     //Send PSU Voltage and Current(amps) draw
            UART_Send_OPAMP_Voltage();
            ONDEMAND_PENDING = 0 ;
        }

    }
}


//Interrupt Handling
void interrupt ISRRoutine(void)
{
    //USART RX Interrupt
    if (PIE1bits.RCIE && PIR1bits.RCIF) {
        PIE1bits.RCIE  = 0;    //Disable receive interrupts
        PIR1bits.RCIF  = 0;

        ISR_RX_TEMP = RCREG;

        #ifdef _DEBUG_UART_
        //putch(RCREG);   //Loopback sent character
        #endif

        LEDACTIVITY     = 1;
        

        //Check if we are receiving SET command for DAC
        if(ISR_RX_STATE == 0)
        {
            if(ISR_RX_TEMP == 'S')          { ISR_RX_MODE = 1; ISR_RX_STATE    = 1; }
            else if (ISR_RX_TEMP == 'C')    { ISR_RX_MODE = 2; ISR_RX_STATE    = 1; }
            ISR_RX_COUNT    = 0;
        }
        //2nd character must be : to indicate we are receiving S: or C: command
        else if (ISR_RX_STATE == 1 && ISR_RX_TEMP == ':') { ISR_RX_STATE = 2; }
        //followed by 4 ASCII characters
        else if (ISR_RX_STATE == 2 && ISR_RX_COUNT < 4)
        {
     
            ISR_RX_BUFF[ISR_RX_COUNT] = ISR_RX_TEMP;
            ++ISR_RX_COUNT;
            if(ISR_RX_COUNT == 4) { ISR_RX_STATE = 3; }
        }

        if (ISR_RX_STATE == 3)
        {    //Receiving complete. All 4 characters are in ISR_RX_BUFF
            
            if(ISR_RX_MODE == 1) { ISR_SetDAC(ISR_RX_BUFF); }   //Set DAC command received
            else if ( ISR_RX_MODE == 2) { ISR_Command_Mode(ISR_RX_BUFF); }    //Control command is received

            ISR_RX_STATE    = 0;
            ISR_RX_MODE     = 0;
        }

        LEDACTIVITY = 0;

        PIE1bits.RCIE  = 1;    //Enable receive interrupts
        return;
    }
}