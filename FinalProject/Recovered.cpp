#include "stdafx.h"
#include "Recovered.h"
#include <string>

Recovered::Recovered()
{

}

Recovered::Recovered(bool gender, CString id, CString name, Address addr, Date birthday,
	Date positivetest, CString infectionarea, CString infectedby, Date recovery) : Sick(gender,
		id, name, addr, birthday, positivetest, infectionarea, infectedby)

{
	setDate(recovery);
	itemType = 2;
}

Recovered::Recovered(Hospitalized& H, Date recovery) : Sick(H)
{
	setDate(recovery);
	itemType = 2;
}

Recovered::Recovered(NonHospitalized& NH, Date recovery) : Sick(NH)
{
	setDate(recovery);
	itemType = 2;
}

Recovered::~Recovered()
{

}

Date Recovered::get_RecoveryDate()
{
	return this->Recovery;
}

void Recovered::setDate(Date date)
{
	Recovery.day = date.day;
	Recovery.month = date.month;
	Recovery.year = date.year;
}
