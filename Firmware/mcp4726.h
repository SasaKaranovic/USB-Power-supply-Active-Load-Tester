#ifndef MCP4726_H
#define	MCP4726_H

#define MCP4726_I2C_ADDRESS      0xC0

uint8_t mcp4726_SetValue(uint16_t value);
uint8_t mcp4726_SetVoltage(uint16_t value, uint16_t VCC_VAL);

#endif	/* MCP4726_H */

