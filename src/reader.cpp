#include "defs.h"
#include "reader.h"



Reader::Reader(HardwareSerial* port)
{
   serial = port;
}


void Reader::read()
{
   while(serial->available() and !frame_ready)
   {
      incomingChar = (char) serial->read();
/*      Serial.print(char_counter);*/
/*      Serial.print(" r ");*/
/*      Serial.println(incomingChar, HEX);*/

      if(!char_counter && incomingChar == ControlCharacter::START)
      {
         ++char_counter;
      }
      else if (char_counter == 1)
      {
         buff.data_length = incomingChar;
         ++char_counter;
      }
      else if (char_counter == 2)
      {
         buff.id = incomingChar;
         ++char_counter;
      }
      else if (char_counter > 2 && char_counter < buff.data_length + 3)
      {
         buff.data[char_counter-3] = incomingChar;
         ++char_counter;
      }
      else if (char_counter >= buff.data_length + 3 && char_counter < buff.data_length + 4 + 3)
      {
         buff.crc[char_counter-3-buff.data_length] = incomingChar;
         ++char_counter;
      }
      else if(char_counter == buff.data_length + 7 && incomingChar == ControlCharacter::END)
      {
         frame_ready = check_crc();
         char_counter = 0;
      }

      else
      {
         char_counter = 0;
         ++discard_counter;
      }
   }
}


void Reader::next_frame()
{
   frame_ready = false;
}

bool Reader::check_crc()
{
   uint32_t res;
   res = checker.crc32((const uint8_t *) buff.data, buff.data_length);
/*   Serial.println(res, DEC);*/
/*   Serial.println(*((uint32_t*)buff.crc), DEC);*/
   if (res == *((uint32_t*)buff.crc))
   {
      ++success_counter;
      return true;
   }
   else
   {
      ++discard_counter;
      return false;
   }
}
