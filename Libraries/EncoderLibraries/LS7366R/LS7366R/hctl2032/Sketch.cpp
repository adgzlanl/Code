/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include "LS7366R.h"
#include <SPI.h>
/*End of auto generated code by Atmel studio */
#define SSS 50

LS7366R enc1(SSS,X4_QUAD,FOUR_BYTE);
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio

void setup()
{
Serial.begin(9600);
  enc1.ResetEncoder();

}

void loop()
{

  uint32_t EncoderValue1=enc1.ReadEncoder();
  
  Serial.println(EncoderValue1);

}
