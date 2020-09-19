#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "NonHospitalized.h"

NonHospitalized::NonHospitalized()
{

}

NonHospitalized::NonHospitalized(bool gender, CString id, CString name, Address addr, Date birthday,
	Date positivetest, CString infectionarea, CString infectedby, Address whereisolated) : Sick(gender,
		id, name, addr, birthday, positivetest, infectionarea, infectedby)

{
	this->WhereIsolated = whereisolated;
}

NonHospitalized::NonHospitalized(Isolated& I, Date positivetest, CString infectionarea,
	CString infectedby, Address whereisolated) : Sick(I, positivetest, infectionarea, infectedby)
{
	this->WhereIsolated = whereisolated;
}

NonHospitalized::~NonHospitalized()
{

}

Address NonHospitalized::get_WhereIsolated()
{
	return this->WhereIsolated;
}

void NonHospitalized::set_WhereIsolated(const Address addr)
{
	this->WhereIsolated = addr;
}

int NonHospitalized::get_itemType()
{
	return this->itemType;
}
