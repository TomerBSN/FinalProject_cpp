#include "stdafx.h"
#include "Hospitalized.h"
#include <string>

Hospitalized::Hospitalized()
{

}

Hospitalized::Hospitalized(bool gender, CString id, CString name, Address addr, Date birthday,
	Date positivetest, CString infectionarea, CString infectedby,
	CString level, bool isventilated, CString hospital, Date hospitalization) : Sick(gender,
		id, name, addr, birthday, positivetest, infectionarea, infectedby)

{
	Level = level;
	IsVentilated = isventilated;
	Hospital = hospital;
	Hospitalization = hospitalization;
	itemType = 0;
}

Hospitalized::Hospitalized(Isolated& I, Date positivetest, CString infectionarea,
	CString infectedby, CString level, bool isventilated, CString hospital,
	Date hospitalization) : Sick(I, positivetest, infectionarea, infectedby)
{
	Level = level;
	IsVentilated = isventilated;
	Hospital = hospital;
	Hospitalization = hospitalization;
	itemType = 0;
}

Hospitalized::~Hospitalized()
{

}

CString Hospitalized::get_Level()
{
	return this->Level;
}

bool Hospitalized::get_IsVentilated()
{
	return this->IsVentilated;
}

CString Hospitalized::get_Hospital()
{
	return this->Hospital;
}

Date Hospitalized::get_HospitalizationDate()
{
	return this->Hospitalization;
}
