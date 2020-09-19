#pragma once
#include "Sick.h"
#include "Isolated.h"

class NonHospitalized : public Sick
{
public:
	NonHospitalized();
	NonHospitalized(bool gender, CString id, CString name, Address addr, Date birthday,
		Date positivetest, CString infectionarea, CString infectedby, Address whereisolated);
	NonHospitalized(Isolated& I, Date positivetest, CString infectionarea, CString infectedby,
		Address whereisolated);
	~NonHospitalized();

	Address get_WhereIsolated();
	void set_WhereIsolated(const Address addr);
	int get_itemType();

private:
	Address WhereIsolated;
	const int itemType = 1;
};