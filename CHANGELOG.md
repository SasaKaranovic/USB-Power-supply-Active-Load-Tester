# Change Log
All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [0.6.1] - 2015-03-01
### Added
- Added examples of Line, SpLine and Point charts to /Desktop Application/ folder.

### Changed
- Desktop Application now has options to clear graph, change graph type and save graph (was available from the beginning but was hidden under chart double-click and by default saved at c:\).
- Desktop Application should now display proper values for X-axis

## [0.6] - 2015-03-01
### Added
- C# Source files and compiled application written in C# to interface with the device
- Command List.pdf - Contains commands list, explanations and example input and UART output.
- Command [C:M00x] to chose between continuous sending of Voltage and Current draw readings
 and on demand. x means 1=Continuous, 0=On Demand
- Command [C:Dxxx] to set delay in continuous mode. xxx is delay of xxx*100ms. [eg. 005 -> 500ms delay]
- Reading of device VCC rail via resistor divider and using that data to further
self-calibrate the device.
- Using VCC_voltage/4096 as DAC quant instead of 5V/4096 making the device more precise
and immune to the VCC rail noise/fluctuation.
- Added function to issue self recalibrate command.
- ACTIVITY LED to notify user when changes have been received/applied and as a general
indication of activity.
- MCU POWER LED for indication if device is powered up
- PSU under test VOLTAGE PRESENT LED indicating that MCU is measuring voltage above 1V
between + and - leads of the PSU under test.

### Changed
- \r\n moved from the start of the string to the end of the string.
- UART Receiver Interrupt handling routine (aka RX ISR) has become too big so I've moved it
to separate file called ISRFunctions.h and ISRFunctions.c This should improve code readability
and also simplify the process of adding support for new commands.
ISR is still big but at this moment it "has to be". At least it should be easy to follow.
- UART Set/Read API made more coherent. Using S:xxxx for SET voltage and C:xxxx for configuring
and communicating with the device.
- Command and function names have been renamed to further reflect what peripheral/device
they belong to and set to easier to read format. (still a lot of work to do here...)

## [0.5] - 2015-02-01
### Added
- General "human readable" API to set/read data from the device. Hopefully making
use of this device with other software easier and more pleasant. :)

### Fixed
- Issues where after disconnecting UART or re-powering the device, last programmed
target current draw will remain and be immediately set as new target causing unwanted
stress or overload on the PSU under test
- Overflowing the DAC/VCC value will result in no status change instead of resetting to 0A draw.
Also an error message will be sent over UART notifying the user.

## [0.4] - 2015-01-21
### Added
- Code to support DAC I2C communication.
- Code to support UART setting target current draw from the PSU under test.

### Changed
- Modified schematic to house potentiometer with MCP4726 (12bit DAC) to enable users to set
target current draw via UART or set manual mode.


## [0.3] - 2015-01-18
### Changed
- Switched to using 5V rail for MCU.
- Switched to using MCP4002 (rail-to-rail) OP-Amp instead of LM324.
- Miscellaneous (minor) changes to voltage dividers and sensing resistor.

## [0.2] - 2015-01-17
### Changed
- Changed function descriptions and names to be more coherent.

### Added
- Reading voltage from potentiometer (besides PSU VCC and voltage on sensing resistor).
- Functions to send VCC, Resistor Voltage and PSU Voltage over UART in more convenient form.

## [0.1] - 2015-01-15
### Added
- Initial build.

