#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Isolated.h"

Isolated::Isolated()
{

}

Isolated::Isolated(bool gender, CString id, CString name, Address addr, Date birthday,
	Address whereisolated, Date isolation, CString exposedto) : Person(gender, id, name, addr, birthday)
{
	this->WhereIsolated = whereisolated;
	this->Isolation = isolation;
	if (exposedto.GetLength())
		this->ExposedTo = exposedto;
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

int Isolated::get_itemType()
{
	return this->itemType;
}
