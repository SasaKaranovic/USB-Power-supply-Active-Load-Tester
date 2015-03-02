#ifndef ISRFUNCTIONS_H
#define	ISRFUNCTIONS_H

/**
 * @Description ISR Set DAC output voltage routine. Should be ONLY used in RX ISR
 * when appropriate command is received
 * @Input uint8_t *ISR_RX_BUFF - Pointer to the ISR RX Buffer array
 */
void ISR_SetDAC(uint8_t *ISR_RX_BUFF);



/**
 * @Description ISR Set DAC output voltage routine. Should be ONLY used in RX ISR
 * when appropriate command is received
 * @Input uint8_t *ISR_RX_BUFF - Pointer to the ISR RX Buffer array
 */
void ISR_Command_Mode(uint8_t *ISR_RX_BUFF);

#endif	/* ISRFUNCTIONS_H */

