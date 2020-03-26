#include "com.h"
#include "Arduino.h"
#include "sender.h"

Packet one;
Packet two;
Packet* prptr;

bool ledstate;

uint32_t leR = millis();
uint32_t leS = millis();
uint32_t leprdc = millis();
Reader r(&Serial2);
Sender s(&Serial3);

void setup()
{
   Serial.begin(96000);
   Serial2.begin(2000000);
   Serial3.begin(2000000);
   pinMode(13, OUTPUT);
   delay(500);

   one.data[0] = 5;
   one.data_length = 1;
   one.id = CommandID::HELLO;

   two.data_length = 4;
   two.data[0] = 0;
   two.data[1] = 1;
   two.data[2] = 0;
   two.data[3] = 1;
   two.id = CommandID::HELLO;
}

void loop()
{

   if (leS < millis() + 1)
   {
      leS = millis();
      s.send(&one);
   }

   if (r.frame_ready)
   {
      leR = millis();
      prptr = &r.buff;
      r.next_frame();
//      Serial.println("Received");
//      Serial.println(leR);
//      Serial.println(r.buff.id, HEX);
//      Serial.println(r.buff.data_length, DEC);
//      r.buff.data[21] = '\0';
//      Serial.println(r.buff.data);
//      Serial.println(r.buff.crc);
//      r.buff.crc[3] = '\0';
//      ledstate = !ledstate;
   }

   if (leprdc + 5000 < millis() )
   {
      leprdc = millis();
      Serial.print(r.discard_counter, DEC);
      Serial.print(" / ");
      Serial.println(r.success_counter, DEC);
   }

   r.read();
   r.read();
//   digitalWrite(13, ledstate);

}
