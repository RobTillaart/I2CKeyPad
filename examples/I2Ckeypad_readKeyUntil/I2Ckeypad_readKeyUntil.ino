//
//    FILE: I2Ckeypad_readKeyUntil.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo reading until specific keyPress
//     URL: https://github.com/RobTillaart/I2CKeyPad
//

// PCF8574
//    pin p0-p3 rows
//    pin p4-p7 colums
// 4x4 or smaller keypad.


#include "Wire.h"
#include "I2CKeyPad.h"

const uint8_t KEYPAD_ADDRESS = 0x38;

I2CKeyPad keyPad(KEYPAD_ADDRESS);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  Wire.setClock(400000);
  if (keyPad.begin() == false)
  {
    Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
    while (1);
  }
}


void loop()
{
  char buf[20];
  int result = readKeyPad('#', buf, 20, 10000);
  if (result == 0)
  {
    Serial.print("SUCCESS: ");
    Serial.println(buf);
  }
  if (result == -1)
  {
    Serial.print("FAILURE: ");
    Serial.println(buf);
  }
  if (result == -2)
  {
    Serial.print("TIMEOUT: ");
    Serial.println(buf);
  }
  
}


//
// until  = end character
// buffer = buffer to fill
// length = length of buffer (incl '\0'
// timeout = timeout in milliseconds
// returns false if until character is not read.
//
int readKeyPad(char until, char * buffer, uint8_t length, uint16_t timeout)
{
  char keymap[19] = "123A456B789C*0#DNF";  // ... None  Fail }
  uint8_t bufferIndex = 0;
  uint32_t start = millis();

  // empty buffer
  buffer[bufferIndex] = 0;

  while (true)
  {
    // while no key is pressed wait
    while (keymap[keyPad.getKey()] == 'N')
    {
      yield();
      if (millis() - start > timeout) return -2;
    }

    // get the key pressed
    uint8_t raw = keyPad.getLastKey();

    // process key pressed
    uint8_t key = keymap[raw];

    // handle end conditions
    if ( key == until) return 0;
    if ( key == 'F') return -1;    // failed to read;
    if (bufferIndex == length) return false;

    // add key to buffer
    buffer[bufferIndex++] = key;
    buffer[bufferIndex] = 0;

    // while key is pressed wait
    while (keymap[keyPad.getKey()] == key)
    {
      yield();
      if (millis() - start > timeout) return -2;
    }
  }
}


// -- END OF FILE --
