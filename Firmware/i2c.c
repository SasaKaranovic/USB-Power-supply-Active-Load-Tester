#include "main.h"

void I2C1_Setup()
{
    //Configure I2C Pins as Digital
    ANSELBbits.ANSB4    = DIGITAL;
    
    //Configure I2C pins as inputs
    TRIS_I2C_SCK    = INPUT;
    TRIS_I2C_SDA    = INPUT;

    //Configure MSSP for I2C mode
#ifdef _PIC16F1829_H_

    SSP1ADD = 0x4F;     //Calculate for ~100 KHz I2C Clock
    SSP1CON1bits.SSPEN  = 1;        //1 = Enables the serial port and configures the SDAx and SCLx pins as the source of the serial port pins(3)

    SSP1CON1bits.SSPM   = 0b1000;   //1000 = I2C Master mode, clock = FOSC / (4 * (SSPxADD+1))(4)

    SSP1STATbits.SMP    = 1;        //1 = Slew rate control disabled for standard speed mode (100 kHz and 1 MHz)
    SSP1STATbits.CKE    = 1;        //1 = Enable input logic so that thresholds are compliant with SMbus specification

    SSP1CON3bits.SDAHT  = 1;        //1 = Minimum of 300 ns hold time on SDAx after the falling edge of SCLx
    
    SSP1CON2bits.RCEN   = 0;        //1 = Enables Receive mode for I2C
    // SSPBUF 0x00;
    SSP1BUF = 0x00;

    

    // SSPMSK 0x00;
    SSP1MSK = 0x00;
#endif
    
}

void I2C1_WaitIdle()
{
    uint16_t watchdog = 15000;

    while( ( (!SSP1CON2bits.SEN) || (!SSP1STATbits.R_nW) || (!SSP1CON2bits.RSEN) || (!SSP1CON2bits.PEN) || (!SSP1CON2bits.ACKEN) ) && (watchdog !=0) ) {
        --watchdog;
    }
#ifdef _DEBUG_UART_
    UART_Debug("Error: I2C not idle!\r\n");
#endif

}

uint8_t I2C1_SendByte(uint8_t data)
{
    SSP1BUF = data;
    I2C1_WaitIdle();

    return (uint8_t)(!SSP1CON2bits.ACKSTAT);
}

uint8_t I2C1_ReadByte()
{
    SSP1CON2bits.RCEN = 1;
    while (SSP1CON2bits.RCEN == 1);
    return SSP1BUF;
}


/**
  Prototype:        uint8_t I2C1_ReadFrame(uint8_t i2c1SlaveAddress, uint8_t *i2c1ReadPointer, uint8_t i2c1FrameLength)
  Input:            i2c1SlaveAddress : Address of slave sending data.
                    *i2c1ReadPointer : Pointer to starting location in file register where data is written.
                    i2c1FrameLength : Number of bytes to receive.
  Output:           none
  Description:      This function is used to read from the I2C bus and store into the file register from
                    the starting location passed as an argument. This is a blocking function and will wait until
                    all the data is received.
  Usage:            I2C1_ReadFrame(i2c1SlaveAddress, (char *)i2c1ReadPointer, i2c1FrameLength);
*/
uint8_t I2C1_ReadFrame(uint8_t i2c1SlaveAddress, uint8_t *i2c1ReadPointer, uint8_t i2c1FrameLength)
{
    if(SSP1STATbits.S)
    {
        return I2C1_BUS_BUSY;
    }

    // initiate start condition
    SSP1CON2bits.SEN = 1;
    while (SSP1CON2bits.SEN)
    {
    }

    //check for bus collision
    if(PIR2bits.BCL1IF)
    {
        PIR2bits.BCL1IF = 0;
        return I2C1_BUS_COLLISION;
    }

    // send slave address with Read/Write bit set
    SSP1BUF = i2c1SlaveAddress | 0x01;
    while ((SSP1STATbits.BF || SSP1STATbits.R_nW) && !PIR2bits.BCL1IF);

    //check for bus collision
    if(PIR2bits.BCL1IF)
    {
        PIR2bits.BCL1IF = 0;
        return I2C1_BUS_COLLISION;
    }

    // check for acknowledgement status
    if (SSP1CON2bits.ACKSTAT)
    {
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN)
		{
		}
        return I2C1_ACK_NOT_RECEIVED;
    }


    while (i2c1FrameLength)
    {
        // receive byte of data
        SSP1CON2bits.RCEN = 1;
        while(SSP1CON2bits.RCEN)
	{
	}
        *i2c1ReadPointer++ = SSP1BUF;

        // set acknowledgement status
        if(i2c1FrameLength == 1)
        {
            SSP1CON2bits.ACKDT = 1;
        }
        else
        {
            SSP1CON2bits.ACKDT = 0;
        }
        // send acknowledgement
        SSP1CON2bits.ACKEN = 1;
        while (SSP1CON2bits.ACKEN)
	{
	}
        i2c1FrameLength--;

        //check for bus collision
        if (PIR2bits.BCL1IF)
        {
            PIR2bits.BCL1IF = 0;
            return I2C1_BUS_COLLISION;
        }

    }
    // initiate stop condition
    SSP1CON2bits.PEN = 1;
    while (SSP1CON2bits.PEN)
    {
    }

    //check for bus collision
    if (PIR2bits.BCL1IF)
    {
        PIR2bits.BCL1IF=0;
        return I2C1_BUS_COLLISION;
    }
    return I2C1_SUCCESS;
}

/**
  Prototype:        uint8_t I2C1_WriteFrame(uint8_t i2c1SlaveAddress, uint8_t *i2c1WritePointer, uint8_t i2c1FrameLength)
  Input:            i2c1SlaveAddress : Address of slave receiving data.
		    *i2c1WritePointer : Pointer to starting location in file register from where data is read.
                    i2c1FrameLength : Number of bytes to send.
  Output:           none
  Description:      This function is used to write into the I2C bus. This is a blocking function and will wait until
                    all the data is send.
  Usage:            I2C1_WriteFrame(i2c1SlaveAddress, (char *)i2c1WritePointer, i2c1FrameLength);
*/
uint8_t I2C1_WriteFrame(uint8_t i2c1SlaveAddress, uint8_t *i2c1WritePointer, uint8_t i2c1FrameLength)
{
   if (SSP1STATbits.S)
   {
      return I2C1_BUS_BUSY;
   }

    // initiate start condition
    SSP1CON2bits.SEN = 1;
    while (SSP1CON2bits.SEN)
    {
    }

    //check for bus collision
    if (PIR2bits.BCL1IF)
    {
        PIR2bits.BCL1IF = 0;
        return I2C1_BUS_COLLISION;
    }

    //write address into the buffer
    SSP1BUF = i2c1SlaveAddress;
    while (SSP1STATbits.BF || SSP1STATbits.R_nW)
    {
    }

    //Check for acknowledgement status
    if (SSP1CON2bits.ACKSTAT )
    {
        SSP1CON2bits.PEN = 1;
        while (SSP1CON2bits.PEN)
	{
	}
        return I2C1_ACK_NOT_RECEIVED;
    }

    while (i2c1FrameLength)
    {
        //write byte into the buffer
        SSP1BUF = *i2c1WritePointer++;
        while (SSP1STATbits.BF || SSP1STATbits.R_nW)
	{
	}

        //Check for acknowledgement status
        if ( SSP1CON2bits.ACKSTAT )
        {
            SSP1CON2bits.PEN = 1;
            while (SSP1CON2bits.PEN)
            {
            }
            return I2C1_ACK_NOT_RECEIVED;
        }

        // check for bus collision
        if (PIR2bits.BCL1IF)
        {
            PIR2bits.BCL1IF = 0;
            return I2C1_BUS_COLLISION;
        }
        i2c1FrameLength-- ;
    }

    //initiate stop condition
    SSP1CON2bits.PEN = 1;
    while (SSP1CON2bits.PEN)
    {
    }

    //check for bus collision
    if(PIR2bits.BCL1IF)
    {
        PIR2bits.BCL1IF = 0;
        return I2C1_BUS_COLLISION;
    }
    return I2C1_SUCCESS;
}

/**
  Prototype:        uint8_t I2C1_WriteByte(uint8_t i2c1SlaveAddress, uint8_t i2c1Data)
  Input:            i2c1SlaveAddress : Address of slave receiving data.
		    i2c1Data : data to be send.
  Output:           none
  Description:      This function is used to write into the I2C bus. This is a blocking function and will wait until
                    the data byte is send.
  Usage:            I2C1_WriteByte(i2c1SlaveAddress, i2c1Data);
*/
uint8_t I2C1_WriteByte(uint8_t i2c1SlaveAddress, uint8_t i2c1Data)
{
   if (SSP1STATbits.S)
   {
       return I2C1_BUS_BUSY;
   }

    // initiate start condition
    SSP1CON2bits.SEN = 1;
    while (SSP1CON2bits.SEN)
    {
    }

    //check for bus collision
    if (PIR2bits.BCL1IF)
    {
        PIR2bits.BCL1IF = 0;
        return I2C1_BUS_COLLISION;
    }

    //write address into the buffer
    SSP1BUF = i2c1SlaveAddress;
    while (SSP1STATbits.BF || SSP1STATbits.R_nW)
    {
    }

    //Check for acknowledgement status
    if (SSP1CON2bits.ACKSTAT )
    {
        SSP1CON2bits.PEN = 1;
        while (SSP1CON2bits.PEN)
	{
	}
        return I2C1_ACK_NOT_RECEIVED;
    }

    //write byte into the buffer
    SSP1BUF = i2c1Data;
    while (SSP1STATbits.BF || SSP1STATbits.R_nW)
    {
    }

    //Check for acknowledgement status
    if ( SSP1CON2bits.ACKSTAT )
    {
        SSP1CON2bits.PEN = 1;
        while (SSP1CON2bits.PEN)
	{
	}
        return I2C1_ACK_NOT_RECEIVED;
    }

    // check for bus collision
    if (PIR2bits.BCL1IF)
    {
        PIR2bits.BCL1IF = 0;
        return I2C1_BUS_COLLISION;
    }

    //initiate stop condition
    SSP1CON2bits.PEN = 1;
    while (SSP1CON2bits.PEN)
    {
    }

    //check for bus collision
    if(PIR2bits.BCL1IF)
    {
        PIR2bits.BCL1IF = 0;
        return I2C1_BUS_COLLISION;
    }
    return I2C1_SUCCESS;
}
