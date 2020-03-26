#pragma once
#include "Arduino.h"

#define MAX_FRAME_SIZE 255
#define MAX_ARGUMENTS 32

namespace ControlCharacter
{
   enum{
      START = 0x01U,
      END = 0x00U,
      ARG_SEP = 0x1FU,
      ESC = 0x10,

   };
}

namespace CommandID
{
   enum{
      HELLO = 0x81U,
   };
}

struct Packet
{
   char id = 0;
   char data[MAX_ARGUMENTS*6] = {0};
   char data_length = 0;
   char crc[4] = {0};
};
