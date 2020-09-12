#pragma once
#include "Person.h"
#include "Isolated.h"
#define NUM_OF_INFECTIONAREAS 16

const string InfectionAreas[NUM_OF_INFECTIONAREAS] = { "Event", "Synagogue", "Work", "Transport", "Mall", "Restaurent", "Sea", "Supermarket", "School",
					"Nursing_home", "Clinic", "Gym", "Beauty_salon", "Airplane", "Hotel", "Unknown" };

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