#pragma once
#include "Person.h"

class Isolated : public Person
{
public:
	Isolated();
	Isolated(bool gender, const char* id, const char* name, Address addr, Date birthday,
		Address whereisolated, Date Isolation, const char* exposedto);
	~Isolated();
	
	Address get_WhereIsolated();
	Date get_Isolation_date();
	char* get_ExposedTo();

private:
	Address WhereIsolated;
	Date Isolation;
	char ExposedTo[MAX_ID];
	void setAddress(Address addr);
	void setDate(Date date);
};