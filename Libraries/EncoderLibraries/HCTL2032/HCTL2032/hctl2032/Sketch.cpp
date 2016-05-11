/*Begining of Auto generated code by Atmel studio */

#include "HCTL2032.h"
#include "arduino.h"
/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio
HCTL2032 ReadEncoder;

void setup()
{
  Serial.begin(9600);

  ReadEncoder.EncoderInit();

}

void loop()
{

  int32_t Encoder1value=ReadEncoder.EncoderRead(HCTL2032::ChannelX);
  int32_t Encoder2value=ReadEncoder.EncoderRead(HCTL2032::ChannelY);
  Serial.print(Encoder1value);
  Serial.print("-");
  Serial.print(Encoder2value);
  Serial.println();

}
