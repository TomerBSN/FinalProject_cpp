#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Isolated.h"
#include <string>

Isolated::Isolated()
{

}

Isolated::Isolated(bool gender, CString id, CString name, Address addr, Date birthday,
	Address whereisolated, Date Isolation, CString exposedto) : Person(gender, id, name, addr, birthday)
{
	setAddress(whereisolated);
	setDate(Isolation);
	if (exposedto.GetLength())
		ExposedTo = exposedto;
}

Isolated::~Isolated()
{

}

void Isolated::setAddress(Address addr)
{
	WhereIsolated.street = addr.street;
	WhereIsolated.city = addr.city;
}

void Isolated::setDate(Date date)
{
	Isolation.day = date.day;
	Isolation.month = date.month;
	Isolation.year = date.year;
}
