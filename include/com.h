#pragma once
#include "Arduino.h"
#include "reader.h"
#include "sender.h"


class Straw
{
   public:
      Straw(HardwareSerial* port);
      void frame_process();

   private:
      HardwareSerial* serial;
      Reader r;
      char params[MAX_FRAME_SIZE] = {0};
      char param_sizes[MAX_ARGUMENTS] = {0};
};


