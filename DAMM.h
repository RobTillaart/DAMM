#pragma once
//
//    FILE: DAMM.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-00-00
// VERSION: 0.1.0
// PURPOSE: Arduino library for calculating DAMM checksum.
//     URL: https://github.com/RobTillaart/DAMM
//     URL: https://en.wikipedia.org/wiki/Damm_algorithm
//


#include "Arduino.h"


#define DAMM_LIB_VERSION         (F("0.1.0"))

class DAMM
{
public:
  DAMM()
  {
    _value = 0;
    _count = 0;
  }


  //////////////////////////////////////////////////////////////
  //
  //  NORMAL INTERFACE
  //
  bool isValid(const char * buffer)
  {
    return isValid((char*)buffer);
  }

  bool isValid(char * buffer)
  {
    _value = 0;
    int len = strlen(buffer);
    for (int i = 0; i < len; i++)
    {
      add(buffer[i] - '0');
    }
    return (_value == 0);
  }

  char generateChecksum(const char * buffer)
  {
    return generateChecksum((char *) buffer);
  }

  char generateChecksum(char * buffer)
  {
    _value = 0;
    uint32_t len = strlen(buffer);
    for (uint32_t i = 0; i < len; i++)
    {
      add(buffer[i] - '0');
    }
    return (_value + '0');
  }


  //////////////////////////////////////////////////////////////
  //
  //  STREAM INTERFACE
  //
  char reset()
  {
    int val = _value;
    _value = 0;
    _count = 0;
    return val + '0';
  }

  //  for digits
  char add(int x)
  {
    _count++;
    _value = DAMM[_value][x];
    return _value + '0';
  }

  //  for digits as char '0'..'9'
  char add(char c)
  {
    _count++;
    _value = DAMM[_value][c - '0'];
    return _value + '0';
  }

  uint32_t count()
  {
    return _count;
  }


protected:
  int       _value = 0;
  uint32_t  _count = 0;

  //  DAMM matrix.
  //  PROGMEM ?
  //  2 digits in 1 byte?
  uint8_t DAMM[10][10] =
  {
    {0, 3, 1, 7, 5, 9, 8, 6, 4, 2},
    {7, 0, 9, 2, 1, 5, 4, 8, 6, 3},
    {4, 2, 0, 6, 8, 7, 1, 3, 5, 9},
    {1, 7, 5, 0, 9, 8, 3, 4, 2, 6},
    {6, 1, 2, 3, 0, 4, 5, 9, 7, 8},
    {3, 6, 7, 4, 2, 0, 9, 5, 8, 1},
    {5, 8, 6, 9, 7, 2, 0, 1, 3, 4},
    {8, 9, 4, 5, 3, 6, 2, 0, 1, 7},
    {9, 4, 3, 8, 6, 1, 7, 2, 0, 5},
    {2, 5, 8, 1, 4, 3, 6, 7, 9, 0}
  };

};


//  -- END OF FILE --

