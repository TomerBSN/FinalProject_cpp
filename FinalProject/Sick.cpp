#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Sick.h"
#include <string>

Sick::Sick()
{

}

Sick::Sick(bool gender, CString id, CString name, Address addr, Date birthday,
	Date positivetest, InfectionAreas infectionarea, CString infectedby) : Person(gender, id, name, addr, birthday)
{
	setDate(positivetest);
	InfectionArea = infectionarea;
	if (infectedby.GetLength())
		InfectedBy = infectedby;
}

Sick::Sick(Sick& S)
{
	Sick(S.Gender, S.ID, S.Name, S.address, S.Birthday, S.PositiveTest, S.InfectionArea, S.InfectedBy);
}

Sick::Sick(Isolated& I, Date positivetest, InfectionAreas infectionarea, CString infectedby) : Person(I)
{
	setDate(positivetest);
	InfectionArea = infectionarea;
	if (infectedby.GetLength())
		InfectedBy = infectedby;
}

Sick::~Sick()
{

}

void Sick::setDate(Date date)
{
	PositiveTest.day = date.day;
	PositiveTest.month = date.month;
	PositiveTest.year = date.year;
}

Date Sick::get_PositiveTest_date()
{
	return PositiveTest;
}

CString Sick::get_InfectedBy()
{
	return InfectedBy;
}

InfectionAreas Sick::get_InfectionArea()
{
	return InfectionArea;
}
