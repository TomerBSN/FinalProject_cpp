#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "NonHospitalized.h"
#include <string>

NonHospitalized::NonHospitalized()
{

}

NonHospitalized::NonHospitalized(bool gender, const char* id, const char* name, Address addr, Date birthday,
	Date positivetest, InfectionAreas infectionarea, const char* infectedby, Address whereisolated) : Sick(gender,
		id, name, addr, birthday, positivetest, infectionarea, infectedby)

{
	setAddress(whereisolated);
}

NonHospitalized::NonHospitalized(Isolated& I, Date positivetest, InfectionAreas infectionarea,
	const char* infectedby, Address whereisolated) : Sick(I, positivetest, infectionarea, infectedby)
{
	setAddress(whereisolated);
}


NonHospitalized::~NonHospitalized()
{

}

void NonHospitalized::setAddress(Address addr)
{
	strcpy(WhereIsolated.street, addr.street);
	WhereIsolated.city = addr.city;
}
