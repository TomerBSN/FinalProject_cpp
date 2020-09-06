#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "NonHospitalized.h"
#include <string>

NonHospitalized::NonHospitalized()
{

}

NonHospitalized::NonHospitalized(bool gender, CString id, CString name, Address addr, Date birthday,
	Date positivetest, InfectionAreas infectionarea, CString infectedby, Address whereisolated) : Sick(gender,
		id, name, addr, birthday, positivetest, infectionarea, infectedby)

{
	setAddress(whereisolated);
}

NonHospitalized::NonHospitalized(Isolated& I, Date positivetest, InfectionAreas infectionarea,
	CString infectedby, Address whereisolated) : Sick(I, positivetest, infectionarea, infectedby)
{
	setAddress(whereisolated);
}


NonHospitalized::~NonHospitalized()
{

}

void NonHospitalized::setAddress(Address addr)
{
	WhereIsolated.street = addr.street;
	WhereIsolated.city = addr.city;
}
