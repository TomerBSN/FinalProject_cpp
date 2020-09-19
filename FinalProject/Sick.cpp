#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Sick.h"
#include <string>

Sick::Sick()
{

}

Sick::Sick(bool gender, CString id, CString name, Address addr, Date birthday,
	Date positivetest, CString infectionarea, CString infectedby) : Person(gender, id, name, addr, birthday)
{
	this->PositiveTest = positivetest;
	this->InfectionArea = infectionarea;
	if (infectedby.GetLength())
		this->InfectedBy = infectedby;
}

Sick::Sick(const Sick& S): Sick(S.Gender, S.ID, S.Name, S.address, S.Birthday, S.PositiveTest, S.InfectionArea, S.InfectedBy)
{

}

Sick::Sick(Isolated& I, Date positivetest, CString infectionarea, CString infectedby) : Person(I)
{
	this->PositiveTest = positivetest;
	this->InfectionArea = infectionarea;
	if (infectedby.GetLength())
		this->InfectedBy = infectedby;
}

Sick::~Sick()
{

}

Date Sick::get_PositiveTest_date()
{
	return this->PositiveTest;
}

CString Sick::get_InfectedBy()
{
	return this->InfectedBy;
}

CString Sick::get_InfectionArea()
{
	return this->InfectionArea;
}

int Sick::get_itemType()
{
	return this->itemType;
}
