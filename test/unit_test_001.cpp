//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-27
// PURPOSE: unit tests for the I2CKeyPad library
//          https://github.com/RobTillaart/I2CKeyPad
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>

#define assertEqualFloat(arg1, arg2, arg3)  assertOp("assertEqualFloat", "expected", fabs(arg1 - arg2), compareLessOrEqual, "<=", "actual", arg3)
#define assertEqualINF(arg)  assertOp("assertEqualINF", "expected", INFINITY, compareEqual, "==", "actual", arg)
#define assertEqualNAN(arg)  assertOp("assertEqualNAN", "expected", true, compareEqual, "==", "actual", isnan(arg))


#include "Arduino.h"
#include "I2CKeyPad.h"


unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/

unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", I2C_KEYPAD_LIB_VERSION);

  const uint8_t KEYPAD_ADDRESS = 0x38;
  I2CKeyPad keyPad;

  assertTrue(keyPad.begin(KEYPAD_ADDRESS));
  assertEqual(I2C_KEYPAD_NOKEY, keypad.getLastKey());
  assertTrue(keyPad.isConnected());
}


unittest(test_read)
{
  fprintf(stderr, "VERSION: %s\n", I2C_KEYPAD_LIB_VERSION);

  const uint8_t KEYPAD_ADDRESS = 0x38;
  I2CKeyPad keyPad;

  assertTrue(keyPad.isConnected());
  assertTrue(keyPad.begin(KEYPAD_ADDRESS));

  assertEqual(I2C_KEYPAD_NOKEY, keypad.getKey());
  assertFalse(keypad.isPressed());
}

unittest_main()

// --------
