/*
LS7366R - Library for LS7366R IC Decoder .
Created by Anil Adiguzel / www.about.me/aniladiguzel , MAY 12, 2016.
Released into the public domain.
*/

#include "LS7366R.h"





//****** You do not have to use  SetStatusRegister,OperationFunction,SetMDR0Register,SetMDR1Register,ZeroSendRegister,SetOperation,InitLS7366R for reading Encoder
// All of these for Options. just i wrote these functions to understand how to set Registers. for reading encoder, just use ....... these functions



// InitEncoder
LS7366R::LS7366R(int SelectSlave)
{
	SS = SelectSlave;
	pinMode(SS, OUTPUT);
	digitalWrite(SS, HIGH);
	SPI.begin();
	digitalWrite(SS, LOW);
	SPI.transfer(WR_MDR0);
	SPI.transfer(X4_QUAD);
	digitalWrite(SS, HIGH);

	digitalWrite(SS, LOW);
	SPI.transfer(WR_MDR1);
	SPI.transfer(FOUR_BYTE);
	digitalWrite(SS, HIGH);

};


LS7366R::LS7366R(int SelectSlave ,byte SetMDR0Bit, byte SetMDR1Bit)
{
	SS = SelectSlave;
	pinMode(SS, OUTPUT);
	digitalWrite(SS, HIGH);
	SPI.begin();
	digitalWrite(SS, LOW);
	SPI.transfer(WR_MDR0);
	SPI.transfer(SetMDR0Bit);
	digitalWrite(SS, HIGH);

	digitalWrite(SS, LOW);
	SPI.transfer(WR_MDR1);
	SPI.transfer(SetMDR1Bit);
	digitalWrite(SS, HIGH);

};

//Reset Encoder
void LS7366R::ResetEncoder() 
{
  digitalWrite(SS, LOW);
  SPI.transfer(WR_DTR);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  digitalWrite(SS, HIGH);

  digitalWrite(SS, LOW);
  SPI.transfer(LD_CNTR);
  digitalWrite(SS, HIGH);
}

// Read Encoder
uint32_t LS7366R::ReadEncoder() 
{
	uint32_t count_value;
	uint32_t count_1, count_2, count_3, count_4;
		digitalWrite(SS, LOW);
		SPI.transfer(RD_CNTR);
		count_1 = SPI.transfer(0x00);
		count_2 = SPI.transfer(0x00);
		count_3 = SPI.transfer(0x00);
		count_4 = SPI.transfer(0x00);
		digitalWrite(SS, HIGH);

	count_value = (count_1 << 24) + (count_2 << 16) + (count_3 << 8) + (count_4);

	return count_value;
}






