// Include libraries this sketch will use
#include  <Wire.h>
#include  <MCP4551.h>

// Instantiate objects used in this project
MCP4551 myMCP4551;

void setup() {
  Wire.begin();
  TWBR = 12;  // 400 kHz (maximum)

  myMCP4551.begin();
  
}

void loop() {
  uint8_t  i;
  
    myMCP4551.setWiper(i++);
}