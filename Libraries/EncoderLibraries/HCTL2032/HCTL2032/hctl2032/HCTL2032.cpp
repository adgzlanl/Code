/*
HCTL2032 - Library for HCTL2032 IC Decoder .
Created by Anil Adiguzel / www.about.me/aniladiguzel , MAY 12, 2016.
Released into the public domain.
*/


#include "HCTL2032.h"
#include "Arduino.h"

void HCTL2032::EncoderQuadrature(QuadrateX QuadX) const

{
	switch QuadX
	
	case 1
	
		digitalWrite(encoderPinEn1, HIGH);
		digitalWrite(encoderPinEn2, HIGH);
		
		break:
		
		case 2
		
		digitalWrite(encoderPinEn1, LOW);
		digitalWrite(encoderPinEn2, HIGH);
		
		break:
		
		case 3:
				
		digitalWrite(encoderPinEn1, HIGH);
		digitalWrite(encoderPinEn2, LOW);
				
		break
}

void HCTL2032::EncoderInit() const
{
	pinMode(encoderPinXY, OUTPUT);
	pinMode(encoderPinOE, OUTPUT);
	pinMode(encoderPinSEL1, OUTPUT);
	pinMode(encoderPinSEL2, OUTPUT);
	pinMode(encoderPinRSTX, OUTPUT);
	pinMode(encoderPinRSTY, OUTPUT);
	pinMode(encoderPinD0, INPUT);
	pinMode(encoderPinD1, INPUT);
	pinMode(encoderPinD2, INPUT);
	pinMode(encoderPinD3, INPUT);
	pinMode(encoderPinD4, INPUT);
	pinMode(encoderPinD5, INPUT);
	pinMode(encoderPinD6, INPUT);
	pinMode(encoderPinD7, INPUT);

	pinMode(encoderPinEn1, OUTPUT);
	pinMode(encoderPinEn2, OUTPUT);



	EncoderQuadrature(x4);
	
	digitalWrite(encoderPinOE, HIGH);

	EncoderReset();
}

byte HCTL2032::ReadByte() const
{
	byte SumByte = (digitalRead(encoderPinD7) << 7) +
	(digitalRead(encoderPinD6) << 6) +
	(digitalRead(encoderPinD5) << 5) +
	(digitalRead(encoderPinD4) << 4) +
	(digitalRead(encoderPinD3) << 3) +
	(digitalRead(encoderPinD2) << 2) +
	(digitalRead(encoderPinD1) << 1) +
	digitalRead(encoderPinD0);

	return SumByte ;
}

void HCTL2032::EncoderReset() const
{
	digitalWrite(encoderPinRSTX, LOW);
	delayMicroseconds(20);
	digitalWrite(encoderPinRSTX, HIGH);
	delayMicroseconds(20);
	digitalWrite(encoderPinRSTY, LOW);
	delayMicroseconds(20);
	digitalWrite(encoderPinRSTY, HIGH);
}

int32_t HCTL2032::EncoderRead(SelectChannel EncoderChannel) const
{
	int32_t count;
	byte busByte;
	if (EncoderChannel == ChannelX)
	{
		digitalWrite(encoderPinXY, LOW);
		delayMicroseconds(20);
	}
	else
	{
		digitalWrite(encoderPinXY, HIGH);
		delayMicroseconds(20);
	}

	
	digitalWrite(encoderPinOE, LOW);

	digitalWrite(encoderPinSEL1, LOW);
	digitalWrite(encoderPinSEL2, HIGH);
	busByte = ReadByte();
	count = busByte;
	count <<= 8;

	digitalWrite(encoderPinSEL1, HIGH);
	digitalWrite(encoderPinSEL2, HIGH);
	busByte = ReadByte();
	count += busByte;
	count <<= 8;

	digitalWrite(encoderPinSEL1, LOW);
	digitalWrite(encoderPinSEL2, LOW);
	busByte = ReadByte();
	count += busByte;
	count <<= 8;

	digitalWrite(encoderPinSEL1, HIGH);
	digitalWrite(encoderPinSEL2, LOW);
	busByte = ReadByte();
	count += busByte;


	digitalWrite(encoderPinOE, HIGH);

	return count;
}
