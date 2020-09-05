#pragma once
#include "Sick.h"
#include "Isolated.h"

enum SicknessLVL {Easy, Medium, Difficult};
enum Hospitals {Ichilov, Sheba, Rambam, Shaare_Zedek, Meir, Hasharon, Assaf_Harofeh, Kaplan,
				Wolfson, Poriya, Barzilai, Haemek};

class Hospitalized : public Sick
{
public:
	Hospitalized();
	Hospitalized(bool gender, const char* id, const char* name, Address addr, Date birthday,
				 Date positivetest, InfectionAreas infectionarea, const char* infectedby,
				 SicknessLVL level, bool isventilated, Hospitals hospital, Date hospitalization);
	Hospitalized(Isolated& I, Date positivetest, InfectionAreas infectionarea, const char* infectedby,
		SicknessLVL level, bool isventilated, Hospitals hospital, Date hospitalization);
	~Hospitalized();

	SicknessLVL get_Level();
	bool get_IsVentilated();
	bool get_Hospital();
	Date get_HospitalizationDate();

private:
	SicknessLVL Level;
	bool IsVentilated;
	Hospitals Hospital;
	Date Hospitalization;
	void setDate(Date date);
};