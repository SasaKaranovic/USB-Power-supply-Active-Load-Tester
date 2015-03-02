#ifndef I2C_H
#define	I2C_H


#define TRIS_I2C_SCK    TRISBbits.TRISB6
#define TRIS_I2C_SDA    TRISBbits.TRISB4

enum
{
    I2C1_ACK_NOT_RECEIVED,
    I2C1_SUCCESS,
    I2C1_BUS_COLLISION,
    I2C1_BUS_BUSY
}I2C1_STATE;


void I2C1_Setup();
uint8_t I2C1_SendByte(uint8_t data);
uint8_t I2C1_ReadByte();
void I2C1_WaitIdle();
uint8_t I2C1_WriteByte(uint8_t i2c1SlaveAddress, uint8_t i2c1Data);
uint8_t I2C1_WriteFrame(uint8_t i2c1SlaveAddress, uint8_t *i2c1WritePointer, uint8_t i2c1FrameLength);
uint8_t I2C1_ReadFrame(uint8_t i2c1SlaveAddress, uint8_t *i2c1ReadPointer, uint8_t i2c1FrameLength);


#endif	/* I2C_H */

