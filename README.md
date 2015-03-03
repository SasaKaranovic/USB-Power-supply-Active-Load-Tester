# USB Power supply Active Load Tester

USB Power supply Active Load Tester or short PAL Tester is unit designed for testing the quality of the power supplies.
Idea was to create low-cost precise device for simultaneous measurement of Voltage and Current draw from the device under test. This is one of my weekend projects that I have decided to release to the public. If you are interested in my other projects you can check them out on [my homepage].

### Device Features:
- Open Source and Open Hardware
- Modular design, easy to understand and change/adapt to your needs
- Uses widely available and off-the shelf components
- Components Bill of Material is below 10$
- Integrated USB-to-Serial converter for easier interface with the device
- API for communicating with PC
- Recording Voltage vs Amps data and graphing the results
- Easy to use

### Example graph outputs from Application
![](https://raw.githubusercontent.com/coldkeyboard/USB-PAL-Tester/master/Desktop%20Application/C%23%20App%20Sample%20Plot%201%20-%205V%201A%20Power%20Adapter.png)
![](https://raw.githubusercontent.com/coldkeyboard/USB-PAL-Tester/master/Desktop%20Application/C%23%20App%20Sample%20Plot%202%20-%205V%201A%20Power%20Adapter.png)


### Basic capabilities:
- PSU under test max voltage 55V
- Current Load of 5A (or more by lowering current sense resistor value)
- Current and Voltage accuracy below 5%


### Component list and estimated price:
- 1x - PIC16F1829 [1.6$]
- 1x - MCP6002 Rail-to-Rail OpAmp [0.69$]
- 1x - MCP4726 12bit DAC [0.96$]
- 1x - IRF L3705 Logic Level N-MOSFET [0.5$]
- 1x - CH340T USB-to-Serial converter [0.99$]
- 10x - Current sense 1 ohm 1% 1/2W resistor
- miscellaneous (resistors and capacitors)

Total components cost should be way under 10$.


### How to build your own PAL Tester:
 If you are going to use photo etching or toner transfer method to make DIY board, there are bottom layer printouts in the Hardware folder that are ready for you to print and create a board via your favourite PCB manufacturing technique.

Once you have finished with developing, cleaning and drilling the board, in Hardware folder you have a file "Component-placement.png" which shows how and where to position components.

If you want to make changes or review the design, Schematic files (in .pdf) and Altium project files are available for download in Hardware folder. Open the design files in Altium or convert them to your favourite CAD and edit them.


### Device operation for laymans:
Microcontroller, trough Digital-to-Analog converter (DAC) sets the voltage on positive input of the Op amp. Then output of the Op amp drives the N-MOSFET that allows current to flow. Negative input of Op amp is connected to the sensing resistor (Rs) that is between source of the N-MOSFET and GND. Voltage over Rs (and thus voltage on negative input of Op Amp) is proportional to the current flowing trough the resistor. For 1 Ohm resistor, V=1 ohm x Current draw. Since Op Amp * "tries to equalize positive and negative inputs" *, if the voltage on positive input is 1V, to equalize positive and negative inputs, voltage on negative input (that is connected to Rs) must also be 1V, therefore Op Amp drives N-MOSFET to open and allow the current flow but only enough to make 1V on negative side. Calculating the current draw from the above mentioned formula, we see that the current draw will be 1A.

### Development

Want to contribute? Great!

Currently there is a C# .NET application written for interfacing with the device. It works but it's very rough and very basic. If you are interested in writing an application in Python, C++, C or any other language, please do. I would greatly appreciate that. Also if you need help or more information, feel free to contact me over Skype, Email, IRC or whatever way you like. :)

Also if you think you can help in any other way, please do. Any kind of help is greatly appreciated.

Special thanks to
----
- Your name here :)

Contact me
----
[Sasa Karanovic Home] - Follow me [@Twitter] - [Facebook] - [Skype] - [EMail] *remove ".nospam" :)


License and Disclaimer
----
You are using this software and hardware at your own risk.

**Open Source, Open Hardware. Do WHATEVER your want :)**

[Sasa Karanovic Home]:http://sasakaranovic.com
[my homepage]:http://sasakaranovic.com
[@Twitter]:http://twitter.com/iSaleK
[Facebook]:https://www.facebook.com/SasaKaranovic
[Skype]:skype:coldkeyboard
[EMail]:mailto:sale@mrdnise.nospam.com
