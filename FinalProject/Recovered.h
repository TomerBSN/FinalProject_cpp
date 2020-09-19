#pragma once
#include "Sick.h"
#include "Hospitalized.h"
#include "NonHospitalized.h"

class Recovered : public Sick
{
public:
	Recovered();
	Recovered(bool gender, CString id, CString name, Address Address, Date birthday,
		Date positivetest, CString infectionarea, CString infectedby, Date recovery);
	Recovered(Hospitalized& H, Date recovery);
	Recovered(NonHospitalized& NH, Date recovery);
	~Recovered();

	Date get_RecoveryDate();
	int get_itemType();

private:
	Date Recovery;
	const int itemType = 2;
};