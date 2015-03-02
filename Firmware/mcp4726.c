#include "main.h"

/**
 * Prototype:   uint8_t mcp4726_SetValue(uint16_t value)
 * Input:       value  : 12bit DAC value (0-4095)
 * Output:      result : I2C1 Status code
 */
uint8_t mcp4726_SetValue(uint16_t value)
{
    if(value > 4095) {
        UART_Debug("DAC Value out of range!\r\n");
        return 0;
    }

    uint8_t WriteArray[3];

    WriteArray[0] = 0x40;   //MCP command: Write Volatile Memory (datasheet page 51)

    value = (value << 4);   //12-bit data is left-aligned
    WriteArray[1] = (value >> 8);
    WriteArray[2] = (value & 0xFF);

    uint8_t result = 0;
    result = I2C1_WriteFrame(MCP4726_I2C_ADDRESS, WriteArray, 3);

#ifdef _DEBUG_UART_
    switch(result) {
        case I2C1_SUCCESS:
            UART_Debug("I2C-Write-Done\r\n");
            break;
        case I2C1_BUS_BUSY:
            UART_Debug("I2C-Write-Bus busy\r\n");
            break;
        case I2C1_BUS_COLLISION:
            UART_Debug("I2C-Write-bus collision\r\n");
            break;
        case I2C1_ACK_NOT_RECEIVED:
            UART_Debug("I2C-Write-noACK\r\n");
            break;

    }
#endif
    
    return result;
}


uint8_t mcp4726_SetVoltage(uint16_t value, uint16_t VCC_VAL)
{
//    UARTNewLine();
//    UARTNewLine();
//    UARTSendInteger(value);
//
//    UARTNewLine();
//    UARTSendInteger(VCC_VAL);
//    UARTNewLine();
    
    value = (int)(value / (double)((double)VCC_VAL / (double)4096));    //It's messy but it seems to work -_-
//    UARTSendInteger(value);
//    UARTNewLine();

    if(value >0) { value -= 1; }
    if(value > 4096) { value = 4095; }

    return mcp4726_SetValue(value);
}

