#include "stdafx.h"
#include "Person.h"

Person::Person()
{
	ID[0] = 'a';
	ID[1] = '\0';
	gender = false;
}

Person::~Person()
{
	delete[] ID;
}
