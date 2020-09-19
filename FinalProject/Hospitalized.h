#pragma once
#include "Sick.h"
#include "Isolated.h"

#define NUM_OF_HOSPITALS 12
#define NUM_OF_LEVELS 3

const CString Hospitals[NUM_OF_HOSPITALS] = { _T("Ichilov"), _T("Sheba"), _T("Rambam"), _T("Shaare Zedek"), _T("Meir"), _T("Hasharon"), _T("Assaf Harofeh"), _T("Kaplan"),
				_T("Wolfson"), _T("Poriya"), _T("Barzilai"), _T("Haemek") };
const CString SicknessLVL[NUM_OF_LEVELS] = { _T("Easy"), _T("Medium"), _T("Critical") };


class Hospitalized : public Sick
{
public:
	Hospitalized();
	Hospitalized(bool gender, CString id, CString name, Address addr, Date birthday,
		Date positivetest, CString infectionarea, CString infectedby,
		CString level, bool isventilated, CString hospital, Date hospitalization);
	Hospitalized(Isolated& I, Date positivetest, CString infectionarea, CString infectedby,
		CString level, bool isventilated, CString hospital, Date hospitalization);
	~Hospitalized();

	CString get_Level();
	bool get_IsVentilated();
	CString get_Hospital();
	Date get_HospitalizationDate();
	int get_itemType();

private:
	CString Level;
	bool IsVentilated;
	CString Hospital;
	Date Hospitalization;
	const int itemType = 0;
};