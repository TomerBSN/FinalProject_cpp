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
	setDate(hospitalization);
}

Hospitalized::Hospitalized(Isolated& I, Date positivetest, CString infectionarea,
	CString infectedby, CString level, bool isventilated, CString hospital,
	Date hospitalization) : Sick(I, positivetest, infectionarea, infectedby)
{
	Level = level;
	IsVentilated = isventilated;
	Hospital = hospital;
	setDate(hospitalization);
}

Hospitalized::~Hospitalized()
{

}

void Hospitalized::setDate(Date date)
{
	Hospitalization.day = date.day;
	Hospitalization.month = date.month;
	Hospitalization.year = date.year;
}
