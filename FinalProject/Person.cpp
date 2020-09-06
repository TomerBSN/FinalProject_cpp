#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Person.h"
#include <string>

Person::Person()
{

}

Person::Person(bool gender, const char* id, const char* name, Address addr, Date birthday)
{
	Gender = gender;
	strcpy(Name, name);
	strcpy(ID, id);
	setAddress(addr);
	setDate(birthday);
}

Person::Person(Person& P)
{
	Person(P.Gender, P.ID, P.Name, P.address, P.Birthday);
}

Person::~Person()
{

}

void Person::setAddress(Address addr)
{
	strcpy(address.street, addr.street);
	address.city = addr.city;
}

void Person::setDate(Date date)
{
	Birthday.day = date.day;
	Birthday.month = date.month;
	Birthday.year = date.year;
}

bool Person::get_Gender()
{
	return Gender;
}

char* Person::get_ID()
{
	return ID;
}

char* Person::get_Name()
{
	return Name;
}

Address Person::get_Address()
{
	return address;
}

Date Person::get_Birthday()
{
	return Birthday;
}
