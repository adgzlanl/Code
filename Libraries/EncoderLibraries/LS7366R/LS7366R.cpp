/*
LS7366R - Library for LS7366R IC Decoder .
Created by Anil Adiguzel / www.about.me/aniladiguzel , MAY 12, 2016.
Released into the public domain.
*/

#include "LS7366R.h"
#include "Arduino.h"




void LS7366R::SetStatusRegister(STRegister SelectStatusRegister) const

{
	SPI.transfer(SelectStatusRegister);
}


void LS7366R::OperationFunction(IRregister SelectOperation) const

{	
	SPI.transfer(SelectOperation);
}

void LS7366R::SetMDR0Register(MDR0Register SetMDR0bit) const

{	
	SPI.transfer(SetMDR0bit);
}

void LS7366R::SetMDR1Register(MDR1Register SetMDR1bit) const

{
	SPI.transfer(SetMDR1bit);
}
void LS7366R::ZeroSendRegister(ZeroSend SetZero) const
{
	SPI.transfer(SetZero);
	SPI.transfer(SetZero);
	SPI.transfer(SetZero);
	SPI.transfer(SetZero);
}


void LS7366R::SetOperation (int SlaveSelect,ZeroSend SetZero, SelecEnumOp OP, IRregister SetIR,STRegister SetSTR, MDR0Register SetMDR0, MDR1Register SetMDR1) const
{

	if (OP == SETMDR0)
	{
		digitalWrite(SlaveSelect, LOW);
		OperationFunction(SetIR);
		SetMDR0Register(SetMDR0);
		digitalWrite(SlaveSelect, HIGH);
	}


	else if (OP == SETMDR1)
	{
		digitalWrite(SlaveSelect, LOW);
		OperationFunction(SetIR);
		SetMDR1Register(SetMDR1);
		digitalWrite(SlaveSelect, HIGH);
	}


	else if (OP == SETSR)
	{
		digitalWrite(SlaveSelect, LOW);
		OperationFunction(SetIR);
		SetStatusRegister(SetSTR);
		digitalWrite(SlaveSelect, HIGH);
	}


	else if (OP == CLEARREG)
	{
		digitalWrite(SlaveSelect, LOW);
		OperationFunction(SetIR);
		ZeroSendRegister(SetZero);
		digitalWrite(SlaveSelect, HIGH);
	}
	else if (OP == SETIR)
	{
		digitalWrite(SlaveSelect, LOW);
		OperationFunction(SetIR);
		digitalWrite(SlaveSelect, HIGH);
	}


}
uint32_t LS7366R::ReadLS7366R(int SlaveSelect) const
{
	uint32_t count_value;
	uint32_t count_1, count_2, count_3, count_4;
		digitalWrite(SlaveSelect, LOW);
		SPI.transfer(0x60);
		count_1 = SPI.transfer(0x00);
		count_2 = SPI.transfer(0x00);
		count_3 = SPI.transfer(0x00);
		count_4 = SPI.transfer(0x00);
		digitalWrite(SlaveSelect, HIGH);

	count_value = (count_1 << 24) + (count_2 << 16) + (count_3 << 8) + (count_4);

	return count_value;
}
void LS7366R::InitLS7366R(int SelectSlave) const
{	
	SPI.begin();
	pinMode(SelectSlave, OUTPUT);
	digitalWrite(SelectSlave, HIGH);
	
}





