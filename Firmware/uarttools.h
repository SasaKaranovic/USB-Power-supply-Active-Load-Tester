#ifndef UARTTOOLS_H
#define	UARTTOOLS_H

/**
 * @Description Send VCC value in mV as ASCII double over UART. 
 * @Input uint16_t Value of VCC in 1mV
 * @Output Sends ASCII value over UART
 * @Notice This function requires to read VCC value and pass it to this function because we have to change FVR
 * to sense if VCC is 5V or 3V
 */
void UART_SendVCC(uint16_t value);

/**
 * @Description Measure PSU Voltage, compensate for the resistor divider and send voltage over UART as ASCII double
 * @Output Sends ASCII voltage of Pover Supply Unit under test over UART
 */
void UART_Send_PSU_Voltage();


/**
 * @Description Measure PSU current draw, compensate for the resistor and send voltage over UART as ASCII double
 * @Output Sends ASCII current draw of Pover Supply Unit under test over UART
 */
void UART_Send_CurrentDraw();

/**
 * @Description Send uint16_t value as ASCII double over UART.
 * @Input uint16_t Value to be sent as ASCII double
 * @Output Sends ASCII value over UART
 * @Example Input: 2576 -> UART Output 25.76
 * @NOTE All values will be divided by 10 and last two digits will be used as .xx
 */
void UART_SendDouble(uint16_t value);

/**
 * @Description Send uint16_t value as ASCII integer over UART
 * @Input uint16_t Value to be sent as ASCII Integer
 * @Output Sends ASCII value over UART
 */
void UART_SendInteger(uint16_t value);

/**
 * @Description Read and send values of Voltage of Power Supply Under test and current current draw (I know, current current :) )
 * @Output Sends values over UART
 */
void UART_Send_PSU_VoltAmp();

/**
 * @Description Read and send voltage on + input of OpAmp
 * @Output Sends ASCII value over UART
 * @Note Depending on configuration (manual or auto) this value represents programming voltage of DAC or Potentiometer
 */
void UART_Send_OPAMP_Voltage();

/**
 * @Description Send ASCII newline characters to the UART (10dec and 13dec).
 */
void UART_NewLine();

/**
 * @Description Send *string over UART, used only in debugging mode. If you wan't always to
 * send data use UART_Write() function istead!
 * @Input const char *str
 * @Output void
 * @WARNING This function will NOT work if you don't uncomment #define _UART_DEBUG_ line
 */
void UART_Debug(const char *str);

/**
 * @Description Send *string over UART
 * @Input const char *str
 * @Output void
 */
void UART_Write(const char *str);

#endif	/* UARTTOOLS_H */

