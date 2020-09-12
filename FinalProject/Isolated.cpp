#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Isolated.h"
#include <string>

Isolated::Isolated()
{
	itemType = 3;
}

Isolated::Isolated(bool gender, CString id, CString name, Address addr, Date birthday,
	Address whereisolated, Date isolation, CString exposedto) : Person(gender, id, name, addr, birthday)
{
	WhereIsolated = whereisolated;
	Isolation = isolation;
	if (exposedto.GetLength())
		ExposedTo = exposedto;
	itemType = 3;
}

Isolated::~Isolated()
{

}

Address Isolated::get_WhereIsolated()
{
	return this->WhereIsolated;
}

Date Isolated::get_Isolation_date()
{
	return this->Isolation;
}

CString Isolated::get_ExposedTo()
{
	return this->ExposedTo;
}
