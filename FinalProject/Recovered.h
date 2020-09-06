#pragma once
#include "Sick.h"
#include "Hospitalized.h"
#include "NonHospitalized.h"

class Recovered : public Sick
{
public:
	Recovered();
	Recovered(bool gender, CString id, CString name, Address Address, Date birthday,
		Date positivetest, InfectionAreas infectionarea, CString infectedby, Date recovery);
	Recovered(Hospitalized& H, Date recovery);
	Recovered(NonHospitalized& NH, Date recovery);
	~Recovered();

	Date get_RecoeryDate();

private:
	Date Recovery;
	void setDate(Date date);
};