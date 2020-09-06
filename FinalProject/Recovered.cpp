#include "stdafx.h"
#include "Recovered.h"
#include <string>

Recovered::Recovered()
{

}

Recovered::Recovered(bool gender, CString id, CString name, Address addr, Date birthday,
	Date positivetest, InfectionAreas infectionarea, CString infectedby, Date recovery) : Sick(gender,
		id, name, addr, birthday, positivetest, infectionarea, infectedby)

{
	setDate(recovery);
}

Recovered::Recovered(Hospitalized& H, Date recovery) : Sick(H)
{
	setDate(recovery);
}

Recovered::Recovered(NonHospitalized& NH, Date recovery) : Sick(NH)
{
	setDate(recovery);
}

Recovered::~Recovered()
{

}

void Recovered::setDate(Date date)
{
	Recovery.day = date.day;
	Recovery.month = date.month;
	Recovery.year = date.year;
}
