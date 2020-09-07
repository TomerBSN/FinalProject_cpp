#pragma once
#include "Sick.h"
#include "Isolated.h"
#define NUM_OF_HOSPITALS 12

const string Hospitals[NUM_OF_CITYS] = { "Ichilov", "Sheba", "Rambam", "Shaare Zedek", "Meir", "Hasharon", "Assaf Harofeh", "Kaplan",
				"Wolfson", "Poriya", "Barzilai", "Haemek" };

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
	bool get_Hospital();
	Date get_HospitalizationDate();

private:
	CString Level;
	bool IsVentilated;
	CString Hospital;
	Date Hospitalization;
	void setDate(Date date);
};