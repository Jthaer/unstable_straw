#include "defs.h"
#include "sender.h"


Sender::Sender(HardwareSerial* port)
{
   serial = port;
}


void Sender::send(Packet* message)
{
   serial->write(ControlCharacter::START);

   serial->write(message->data_length);
   serial->write(message->id);

   for(char i=0; i<message->data_length; i++) serial->write(message->data[i]);

   uint32_t crc = checker.crc32((const uint8_t*)message->data, message->data_length);

   // CRC not implemented
   serial->write((const char*)&crc, 4);

   serial->write(ControlCharacter::END);

}

