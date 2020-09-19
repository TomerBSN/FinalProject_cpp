#include "stdafx.h"
#include "Recovered.h"

Recovered::Recovered()
{

}

Recovered::Recovered(bool gender, CString id, CString name, Address addr, Date birthday,
	Date positivetest, CString infectionarea, CString infectedby, Date recovery) : Sick(gender,
		id, name, addr, birthday, positivetest, infectionarea, infectedby)

{
	Recovery = recovery;
}

Recovered::Recovered(Hospitalized& H, Date recovery) : Sick(H)
{
	Recovery = recovery;
}

Recovered::Recovered(NonHospitalized& NH, Date recovery) : Sick(NH)
{
	Recovery = recovery;
}

Recovered::~Recovered()
{

}

Date Recovered::get_RecoveryDate()
{
	return this->Recovery;
}

int Recovered::get_itemType()
{
	return this->itemType;
}
