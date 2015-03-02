#ifndef DEVICECONFIG_H
#define	DEVICECONFIG_H

//Configuration bits for PIC16F1829
#ifdef _16F1829
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF       // PLL Enable (4x PLL disable)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)



//Activity (LED Anode) PIN
#define TRISACTIVITY    TRISBbits.TRISB7
#define ANSELACTIVITY   ANSELBbits.ANSB7
#define LEDACTIVITY     LATBbits.LATB7


/*
 *
 *          ADC PINS
 *
 */

//DAC Output (trough voltage divider) voltage Sensing
//RA2 - PIN17 - AN2
#define TRISDACVOLTAGE     TRISAbits.TRISA2
#define ANSELDACVOLTAGE    ANSELAbits.ANSA2
#define PINDACVOLTAGE      LATAbits.LATA2
#define ADCDACVOLTAGESENSE 0b00010


//Power Supply Under Test Voltage Sensing
//RC1 - PIN15 - AN5
#define TRISVOLTAGE         TRISCbits.TRISC1
#define ANSELVOLTAGE        ANSELCbits.ANSC1
#define PINVOLTAGE          LATCbits.LATC1
#define ADCPSUVOLTAGESENSE  0b00101


//Current Draw Sensing
//RC2 - PIN14 - AN6
#define TRISCURRENT     TRISCbits.TRISC2
#define ANSELCURRENT    ANSELCbits.ANSC2
#define PINCURRENT      LATCbits.LATC2
#define ADCCURRENTSENSE 0b00110


//MCU VCC rail voltage (trough voltage divider) Sensing
//RC0 - PIN16 - AN4
#define TRISVCC         TRISCbits.TRISC0
#define ANSELVCC        ANSELCbits.ANSC0
#define PINVCC          LATCbits.LATC0
#define ADCVCCSENSE     0b00100



#define EnableInterrupts()  (INTCONbits.GIE = 1)
#define DisableInterrupts() (INTCONbits.GIE = 0)




#endif

void Device_SetUp();
void Device_Initialize();
void Device_SetUpInterrupts();
void UART_Setup(uint16_t baudrate);
void putch(uint8_t data);


#endif	/* DEVICECONFIG_H */

