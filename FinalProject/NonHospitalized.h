#pragma once
#include "Sick.h"
#include "Isolated.h"

class NonHospitalized : public Sick
{
public:
	NonHospitalized();
	NonHospitalized(bool gender, CString id, CString name, Address addr, Date birthday,
		Date positivetest, InfectionAreas infectionarea, CString infectedby, Address whereisolated);
	NonHospitalized(Isolated& I, Date positivetest, InfectionAreas infectionarea, CString infectedby,
		Address whereisolated);
	~NonHospitalized();

	Address get_WhereIsolated();

private:
	Address WhereIsolated;
	void setAddress(Address addr);
};