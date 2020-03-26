#pragma once
#include "defs.h"
#include "FastCRC.h"

class Reader
{

   public:
      Reader(HardwareSerial* port);
      void read();
      void next_frame();

   public:
      HardwareSerial* serial;
      bool check_crc();
      FastCRC32 checker;
      bool frame_ready = false;
// TODO Getter
   public:
      char incomingChar = 0x00U;
      uint8_t char_counter = 0;
      Packet buff;
      uint32_t discard_counter = 0;
      uint32_t success_counter = 0;

};


// beg length id data     crc      end
// 0    1     2  3..2+n   3+n..6+n 7+n
