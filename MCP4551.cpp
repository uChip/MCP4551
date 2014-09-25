/**************************************************************************/
/*! 
    @file     MCP455X.cpp
    @author   C. Schnarel
	@license  BSD (see license.txt)
	
	This is a library for the Microchip Digital Potentiometer series.

	@section  HISTORY

    2013-Dec-24  - First release, C. Schnarel
*/
/**************************************************************************/

#include "MCP4551.h"

/** Default constructor, uses default I2C address.
 * @see MCP4551_DEFAULT_ADDRESS
 */
MCP4551::MCP4551() {
    devAddr = MCP4551_DEFAULT_ADDRESS;
}

/** Specific address constructor.
 * @param address I2C address
 * @see MCP4551_DEFAULT_ADDRESS
 * @see MCP4551_ADDRESS_A0_GND
 * @see MCP4551_ADDRESS_A0_VCC
 */
MCP4551::MCP4551(uint8_t address) {
    devAddr = address;
}

/** Power on and prepare for general usage.
 * This device is ready to use automatically upon power-up. It defaults to
 * TCON all functions enabled, WIPER at MID scale. The begin() function sets
 * these same values since a reset did not necessarily restart the device.
 */
void MCP4551::begin() {
  //setTCON(MCP4551_TCON_ALL_EN);	// enable all functions
  setWiper(MCP4551_WIPER_MID);	// set to mid scale
}

/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return True if connection is valid, false otherwise
 */
bool MCP4551::testConnection() {
    Wire.beginTransmission(devAddr);
    return (Wire.endTransmission() == 0);
}

/** Set Wiper value
 * valid range is 0x000 = B to 0x100 = A
 * setting wiper in the range 0x101 to 0x3FF will lock wiper at A w/ inc & dec disabled
 */
bool MCP4551::setWiper(uint16_t value) {
  Wire.beginTransmission(devAddr);
  uint8_t temp = ((value >> 8 & 0x01) | MCP4551_CMD_WRITE);
  Wire.write(temp);
  temp = (value & 0xFF);
  Wire.write(temp);
  return (Wire.endTransmission() == 0);
}
 
/** Increment Wiper value (one step closer to A)
 * will not increment past 0x100
 */
bool MCP4551::incWiper() {
  Wire.beginTransmission(devAddr);
  Wire.write(MCP4551_CMD_INC);
  return (Wire.endTransmission() == 0);
}
 
/** Decrement Wiper value (one step closer to B)
 * will not decrement past 0x000
 */
bool MCP4551::decWiper() {
  Wire.beginTransmission(devAddr);
  Wire.write(MCP4551_CMD_DEC);
  return (Wire.endTransmission() == 0);
}
 
/** Read Wiper value
 */
int16_t MCP4551::getWiper() {
  Wire.beginTransmission(devAddr);
  Wire.write(MCP4551_CMD_READ);
  if(Wire.endTransmission() == 0) {
    if(Wire.requestFrom(devAddr, (uint8_t) 2) == 2) {
      buffer = Wire.read();
      buffer <<= 8;
      buffer |= Wire.read();
      return buffer;
    }
    else return -1;
  }
  else return -1;
}

