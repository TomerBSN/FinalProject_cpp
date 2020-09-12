#pragma once
#include "Person.h"

class Isolated : public Person
{
public:
	Isolated();
	Isolated(bool gender, CString id, CString name, Address addr, Date birthday,
		Address whereisolated, Date isolation, CString exposedto);
	~Isolated();
	
	Address get_WhereIsolated();
	Date get_Isolation_date();
	CString get_ExposedTo();

private:
	Address WhereIsolated;
	Date Isolation;
	CString ExposedTo;
};