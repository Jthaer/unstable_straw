#pragma once
#include "defs.h"
#include "FastCRC.h"


class Sender
{

   public:
      Sender(HardwareSerial* port);
      void send(Packet* message);

   private:
      HardwareSerial* serial;
      FastCRC32 checker;

};


// beg length id data     crc      end
// 0    1     2  3..2+n   3+n..6+n 7+n

