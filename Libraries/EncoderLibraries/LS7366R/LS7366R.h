/*
LS7366R - Library for LS7366R IC Decoder .
Created by Anil Adiguzel / www.about.me/aniladiguzel , MAY 12, 2016.
Released into the public domain.
*/
//****** You do not have to use  SetStatusRegister,OperationFunction,SetMDR0Register,SetMDR1Register,ZeroSendRegister,SetOperation,InitLS7366R for reading Encoder
// All of these for Options. just i wrote these functions to understand how to set Registers. for reading encoder, just use ....... these functions


#include "Arduino.h"
#include <SPI.h>


class LS7366R
{

public:

	 enum  STRegister
	{
		//****************************STR(Status Register ) 8 bit*********************************

		//*************************************************
		//STR bits CY-BW-CMP-IDX-CEN-PLS-U/D-S               *
		//*************************************************
		S_BIT   = 0X00,
		//Select Byte Mode S bit as follows
		UD_BIT  = 0X01,
		//Select Byte Mode U/D bit as follows
		PLS_BIT = 0X02,
		//Select Byte Mode PLS bit as follows
		CEN_BIT = 0X04,
		//Select Byte Mode CEN bit as follows
		IDX_BIT = 0X10,
		//Select Byte Mode IDX bit as follows
		CMP_BIT = 0X20,
		//Select Byte Mode CMP bit as follows
		BW_BIT  = 0X40,
		//Select Byte Mode BW bit as follows
		CY_BIT  = 0X80,
		//Select Byte Mode CY bit as follows


		//****************************************************************************************	


	};




enum  IRregister
{
//************************IR (Instruction Register 0)  8 bit************************************ 

//*************************************************
//IR bits B7-B6-B5-B4-B3-B2-B1-B0               *
//*************************************************


//Clear Functions

CLR_MDR0 = 0x08, // 0 0 0 0 1 B2 B1 B0
CLR_MDR1 = 0x10, // 0 0 0 1 0 B2 B1 B0
CLR_DTR  = 0x18, // 0 0 0 1 1 B2 B1 B0
CLR_CNTR = 0x20, // 0 0 1 0 0 B2 B1 B0
CLR_OTR  = 0X28, // 0 0 1 0 1 B2 B1 B0
CLR_STR  = 0X30, // 0 0 1 1 0 B2 B1 B0

//Read Functions

RD_MDR0 = 0x48, // 0 1 0 0 1 B2 B1 B0
RD_MDR1 = 0x50, // 0 1 0 1 0 B2 B1 B0
RD_DTR  = 0x58, // 0 1 0 1 1 B2 B1 B0
RD_CNTR = 0x60, // 0 1 1 0 0 B2 B1 B0
RD_OTR  = 0X68, // 0 1 1 0 1 B2 B1 B0
RD_STR  = 0X70, // 0 1 1 1 0 B2 B1 B0

//Write Functions

WR_MDR0 = 0x88, // 1 0 0 0 1 B2 B1 B0
WR_MDR1 = 0x90, // 1 0 0 1 0 B2 B1 B0
WR_DTR  = 0x98, // 1 0 0 1 1 B2 B1 B0
WR_CNTR = 0xA0, // 1 0 1 0 0 B2 B1 B0
WR_OTR  = 0XA8, // 1 0 1 0 1 B2 B1 B0

//Load Functions

LD_CNTR = 0xE0, // 1 1 1 0 0 B2 B1 B0
LD_OTR  = 0XE8, // 1 1 1 0 1 B2 B1 B0
	

};





enum   MDR0Register
{
	//************************MDR0 (Mode Register 0)  8 bit************************************ 

	//*************************************************
	//MDR0 bits B7-B6-B5-B4-B3-B2-B1-B0               *
	//*************************************************


	//Select quadrature Mode B1:B0 bits as follows
	NON_QUAD = 0x00, // B7 B6 B5 B4 B3 B2 00
	X1_QUAD = 0x01, // B7 B6 B5 B4 B3 B2 01
	X2_QUAD = 0x02, // B7 B6 B5 B4 B3 B2 10
	X4_QUAD = 0x03, // B7 B6 B5 B4 B3 B2 11

	// Select Count Mode  B3:B2 bits as follows
	FREE_RUN = 0x00,  // B7 B6 B5 B4 00 B1 B0
	SINGLE_CYCLE = 0x04,  // B7 B6 B5 B4 01 B1 B0
	RANGE_LIMIT = 0x08,  // B7 B6 B5 B4 10 B1 B0
	MOD_N_CNT = 0x0C,  // B7 B6 B5 B4 11 B1 B0

	//Select  Index Mode B5:B4 bits as follows
	DISABLE_IDX = 0x00,	  // B7 B6 00 B3 B2 B1 B0
	LOAD_CNTR = 0x10,   // B7 B6 01 B3 B2 B1 B0
	RST_CNTR = 0x20,   // B7 B6 10 B3 B2 B1 B0
	LOAD_OTR = 0x30,	  // B7 B6 11 B3 B2 B1 B0	

	//Select Sync Mode B6 bit as follows
	ASYN_IDX    = 0x00,  // B7 0 B5 B4 B3 B2 B1 B0
	SYN_IDX     = 0x40 , // B7 1 B5 B4 B3 B2 B1 B0

	//Select Filter Clock Division Mode B7 as follows
	CLK_DIV_1   = 0x00 , // 0 B6 B5 B4 B3 B2 B1 B0
	CLK_DIV_2   = 0x80,  // 1 B6 B5 B4 B3 B2 B1 B0

	//****************************************************************************************

};

	enum  MDR1Register
	{
		//****************************MDR1(Mode Register 1) 8 bit*********************************

		//*************************************************
		//MDR1 bits B7-B6-B5-B4-B3-B2-B1-B0               *
		//*************************************************

		//Select Byte Mode B1:B0 bits as follows
		FOUR_BYTE = 0x00,      // B7 B6 B5 B4 B3 B2 00
		THREE_BYTE = 0x01,     // B7 B6 B5 B4 B3 B2 01
		TWO_BYTE = 0x02,       // B7 B6 B5 B4 B3 B2 10
		ONE_BYTE = 0x03,       // B7 B6 B5 B4 B3 B2 11

		// Select Enable Count Mode B2 bit as follows
		ENABLE_CNT = 0x00,     // B7 B6 B5 B4 B3 0 B1 B0
		DISABLE_CNT = 0x04,    // B7 B6 B5 B4 B3 1 B1 B0

		//  B3 bit not used

		// Select FLAG INDEX Mode B4 bit as follows
		FLAG_IDX = 0x10,	   // B7 B6 B5 1 B3 B2 B1 B0

		// Select FLAG COMPARE Mode B5 bit as follows
		FLAG_CMP = 0x20,       // B7 B6 1 B4 B3 B2 B1 B0

		// Select FLAG BORROW Mode B6 bit as follows
		FLAG_BW = 0x40,        // B7 1 B5 B4 B3 B2 B1 B0

		// Select FLAG CARRY-OVER Mode B7 bit as follows
		FLAG_CY = 0x80,	      // 1 B6 B5 B4 B3 B2 B1 B0

	//****************************************************************************************

		
};

	enum ZeroSend
	{
		SEND_ZERO=0x00
	};


	enum SelecEnumOp
	{
		SETMDR0,
		SETMDR1,
		SETSR,
		CLEARREG,
		SETIR
	};

	void SetOperation(int SlaveSelect, ZeroSend SetZero, SelecEnumOp OP, IRregister SetIR, STRegister SetSTR, MDR0Register SetMDR0, MDR1Register SetMDR1) const;
	void InitLS7366R(int SelectSlave) const;
	uint32_t ReadEncoder(int SlaveSelect) const;
	void ResetEncoder(int SelectSlave) const;
	void InitEncoder(int SelectSlave,MDR0Register SetMDR0,MDR1Register SetMDR1) const;

	private:
	void OperationFunction(IRregister SelectOperation) const;
	void SetMDR0Register(MDR0Register SetMDR0bit) const;
	void SetMDR1Register(MDR1Register SetMDR1bit) const;
	void SetStatusRegister(STRegister SelectStatusRegister) const;
	void ZeroSendRegister(ZeroSend SetZero) const;

	







};
