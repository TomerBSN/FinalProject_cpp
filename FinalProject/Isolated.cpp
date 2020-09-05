#include "stdafx.h"
#include "Isolated.h"
#include <string>

Isolated::Isolated()
{

}

Isolated::Isolated(bool gender, const char* id, const char* name, Address addr, Date birthday,
	Address whereisolated, Date Isolation, const char* exposedto="") : Person(gender, id, name, addr, birthday)
{
	setAddress(whereisolated);
	setDate(Isolation);
	if (strlen(exposedto))
		strcpy(ExposedTo, exposedto);
}

Isolated::~Isolated()
{

}

void Isolated::setAddress(Address addr)
{
	strcpy(WhereIsolated.street, addr.street);
	WhereIsolated.city = addr.city;
}

void Isolated::setDate(Date date)
{
	Isolation.day = date.day;
	Isolation.month = date.month;
	Isolation.year = date.year;
}
