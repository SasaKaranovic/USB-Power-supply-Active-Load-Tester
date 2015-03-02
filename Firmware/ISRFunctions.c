#include "main.h"

extern uint16_t ADC_val_VCC;
extern uint16_t DAC_Target_Voltage;
extern uint8_t CONF_CONTINUOS_SEND;
extern uint8_t CONF_CONTINUOS_DELAY;
extern uint8_t CONF_CONTINUOS_DELAY_TMP;
extern uint8_t ONDEMAND_PENDING;

void ISR_SetDAC(uint8_t *ISR_RX_BUFF)
{
    //Convert ASCII numbers to hex integers
    ISR_RX_BUFF[0]  -=48;
    ISR_RX_BUFF[1]  -=48;
    ISR_RX_BUFF[2]  -=48;
    ISR_RX_BUFF[3]  -=48;

    //Sanity check
    if(ISR_RX_BUFF[0] > 9) { ISR_RX_BUFF[0] = 0; UART_Debug("Char0 is NaN\r\n"); }
    if(ISR_RX_BUFF[1] > 9) { ISR_RX_BUFF[1] = 0; UART_Debug("Char1 is NaN\r\n"); }
    if(ISR_RX_BUFF[2] > 9) { ISR_RX_BUFF[2] = 0; UART_Debug("Char2 is NaN\r\n"); }
    if(ISR_RX_BUFF[3] > 9) { ISR_RX_BUFF[3] = 0; UART_Debug("Char3 is NaN\r\n"); }


    DAC_Target_Voltage = ISR_RX_BUFF[0] * 1000;
    DAC_Target_Voltage = DAC_Target_Voltage + ISR_RX_BUFF[1] * 100;
    DAC_Target_Voltage = DAC_Target_Voltage + ISR_RX_BUFF[2] * 10;
    DAC_Target_Voltage = DAC_Target_Voltage + ISR_RX_BUFF[3];

    if(DAC_Target_Voltage >= ADC_val_VCC) { UART_Debug("W: ADC set voltage excedes device VCC rail!\r\n"); }

    mcp4726_SetVoltage(DAC_Target_Voltage, ADC_val_VCC);
    UART_Send_PSU_VoltAmp();
}



void ISR_Command_Mode(uint8_t *ISR_RX_BUFF)
{
    switch(ISR_RX_BUFF[0]) {
        case 'M': //Set the device mode of operation
            if(ISR_RX_BUFF[3] == '0') {
                CONF_CONTINUOS_SEND = 0;
            }
            else if(ISR_RX_BUFF[3] == '1') {
                CONF_CONTINUOS_SEND = 1;
            }
            else {
               CONF_CONTINUOS_SEND = 0;
               UART_Debug("Invalid Mode!\r\n");
            }
            break;
        case 'O':  //Initiate On Demand read
            ONDEMAND_PENDING = 1;
            break;
        case 'D':  //Set the delay of the continous mode
            ISR_RX_BUFF[1] = (ISR_RX_BUFF[1] >= 48 && ISR_RX_BUFF[1] <= 57) ? ISR_RX_BUFF[1] : 0;
            ISR_RX_BUFF[2] = (ISR_RX_BUFF[2] >= 48 && ISR_RX_BUFF[2] <= 57) ? ISR_RX_BUFF[2] : 0;
            ISR_RX_BUFF[3] = (ISR_RX_BUFF[3] >= 48 && ISR_RX_BUFF[3] <= 57) ? ISR_RX_BUFF[3] : 5;
            CONF_CONTINUOS_DELAY    = ISR_RX_BUFF[1] *100;
            CONF_CONTINUOS_DELAY    += ISR_RX_BUFF[2] *10;
            CONF_CONTINUOS_DELAY    += ISR_RX_BUFF[3];
            CONF_CONTINUOS_DELAY_TMP = 1;   //Reset the current delay
            break;

        default:
            break;
    }
}