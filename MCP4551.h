/**************************************************************************/
/*! 
    @file     MCP455X.h
    @author   C. Schnarel
	@license  BSD (see license.txt)
	
	This is a library for the Microchip Digital Potentiometer series.

	@section  HISTORY

    2013-Dec-24  - First release, C. Schnarel
*/
/**************************************************************************/

#ifndef _MCP4551_H_
#define _MCP4551_H_

#ifdef ARDUINO
    #if ARDUINO < 100
        #include "WProgram.h"
    #else
        #include "Arduino.h"
    #endif
#else
    #include "ArduinoWrapper.h"
#endif

#include <Wire.h>

// I2C Address of device
#define MCP4551_DEFAULT_ADDRESS	0x2E	// A0 is connected to GND
#define MCP4551_ADDRESS_A0_VCC	0x2F	// A0 is connected to VCC
#define MCP4551_ADDRESS_A0_GND	0x2E	// A0 is connected to GND

// Command definitions (sent to WIPER register)
#define MCP4551_CMD_WRITE	0x00
#define MCP4551_CMD_INC		0x04
#define MCP4551_CMD_DEC		0x08
#define MCP4551_CMD_READ	0x0C

// Control bit definitions (sent to TCON register)
#define MCP4551_TCON_GC_EN	0x100
#define MCP4551_TCON_R0_EN	0x008
#define MCP4551_TCON_A_EN	0x004
#define MCP4551_TCON_W_EN	0x002
#define MCP4551_TCON_B_EN	0x001
#define MCP4551_TCON_ALL_EN	0x1FF

// Register addresses
#define MCP4551_RA_WIPER	0x00
#define MCP4551_RA_TCON		0x40


// Common WIPER values
#define MCP4551_WIPER_MID	0x080
#define MCP4551_WIPER_A		0x100
#define MCP4551_WIPER_B		0x000

class MCP4551 {
    public:
        MCP4551();
        MCP4551(uint8_t address);
        
        void begin(void);
        bool testConnection(void);

	// Write the Wiper register
	bool setWiper(uint16_t value);  // returns true if no errors
        
	// Increments the Wiper register
	bool incWiper(void);  // increments the wiper register - stops at 0x100

	// Decrements the Wiper register
	bool decWiper(void);  // decrements the wiper register - stops at 0x000

     // Read the Wiper register
     int16_t getWiper(void);  // returns -1 if errors

    private:
        uint8_t devAddr;
        uint16_t buffer;
};

#endif /* _MCP4551_H_ */
