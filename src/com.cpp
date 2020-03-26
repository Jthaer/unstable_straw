#include "Arduino.h"
#include "com.h"
#include <stdio.h>
#include <string.h>


Straw::Straw(HardwareSerial* port): r(port)
{
   serial = port;
}



//
// void test()
// {
//    char str[] = "- This, a smaple string.";
//    char* pch;
//    printf("Splitting string \"%s\" into tokens:\n", str);
//    pch = strtok(str," ,.-");
//    while (pch!=NULL)
//    {
//       printf("%s\n", pch);
//       pch = strtok(NULL, " ,.-");
//    }
//
// }
