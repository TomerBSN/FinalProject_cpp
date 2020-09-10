#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "NonHospitalized.h"
#include <string>

NonHospitalized::NonHospitalized()
{

}

NonHospitalized::NonHospitalized(bool gender, CString id, CString name, Address addr, Date birthday,
	Date positivetest, CString infectionarea, CString infectedby, Address whereisolated) : Sick(gender,
		id, name, addr, birthday, positivetest, infectionarea, infectedby)

{
	setAddress(whereisolated);
	itemType = 1;
}

NonHospitalized::NonHospitalized(Isolated& I, Date positivetest, CString infectionarea,
	CString infectedby, Address whereisolated) : Sick(I, positivetest, infectionarea, infectedby)
{
	setAddress(whereisolated);
	itemType = 1;
}


NonHospitalized::~NonHospitalized()
{

}

Address NonHospitalized::get_WhereIsolated()
{
	return this->WhereIsolated;
}

void NonHospitalized::setAddress(Address addr)
{
	WhereIsolated.street = addr.street;
	WhereIsolated.city = addr.city;
}
