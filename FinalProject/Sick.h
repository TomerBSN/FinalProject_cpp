#pragma once
#include "Person.h"
#include "Isolated.h"

enum InfectionAreas{Event, Synagogue, Work, Transport, Mall, Restaurent, Sea, Supermarket, School,
					Nursing_homes, Clinic, Gym, Beauty_salon, Airplane, Hotel, Unknown};

class Sick : public Person
{
public:
	Sick();
	Sick(bool gender, const char* id, const char* name, Address addr, Date birthday,
		Date positivetest, InfectionAreas infectionarea, const char* infectedby);
	Sick(Sick& S);
	Sick(Isolated& I, Date positivetest, InfectionAreas infectionarea, const char* infectedby);
	~Sick();

	Date get_PositiveTest_date();
	char* get_InfectedBy();
	InfectionAreas get_InfectionArea();

protected:
	Date PositiveTest;
	char InfectedBy[MAX_ID];
	InfectionAreas InfectionArea;
	static int TotalSick;
	void setDate(Date date);

};