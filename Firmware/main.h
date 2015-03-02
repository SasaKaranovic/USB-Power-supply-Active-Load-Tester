#ifndef HEADER_H
#define	HEADER_H

#define INPUT   1
#define OUTPUT  0

#define DIGITAL 0
#define ANALOG  1

//Device Oscillator Frequency in Hz
#define _XTAL_FREQ  32000000

//Comment the line below to disable debugging mode!
#define _DEBUG_UART_    //Comment this line if you don't want the UART output

//The files we will be needing :)
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "adc.h"
#include "i2c.h"
#include "mcp4726.h"

#include "deviceconfig.h"
#include "ISRFunctions.h"
#include "uarttools.h"





//Fix ugly MPLab X __delay_ms() and __delay_us() error :)
#if 1 // to fix stupid IDE error issues with __delay_ms
#ifndef _delay_ms(x)
#define _delay_ms(x) __delay_ms(x)
#endif
#ifndef _delay_us(x)
#define _delay_us(x) __delay_us(x)
#endif
#endif

#endif	/* HEADER_H */

