#pragma once
#include "Person.h"
#include "Isolated.h"
#define NUM_OF_INFECTIONAREAS 16

const CString InfectionAreas[NUM_OF_INFECTIONAREAS] = { _T("Event"), _T("Synagogue"), _T("Work"), _T("Transport"), _T("Mall"), _T("Restaurent"), _T("Sea"), _T("Supermarket"), _T("School"),
					_T("Nursing_home"), _T("Clinic"), _T("Gym"), _T("Beauty_salon"), _T("Airplane"), _T("Hotel"), _T("Unknown") };

class Sick : public Person
{
public:
	Sick();
	Sick(bool gender, CString id, CString name, Address addr, Date birthday,
		Date positivetest, CString infectionarea, CString infectedby);
	Sick(const Sick& S);
	Sick(Isolated& I, Date positivetest, CString infectionarea, CString infectedby);
	~Sick();

	Date get_PositiveTest_date();
	CString get_InfectedBy();
	CString get_InfectionArea();

protected:
	Date PositiveTest;
	CString InfectedBy;
	CString InfectionArea;
	static int TotalSick;
};