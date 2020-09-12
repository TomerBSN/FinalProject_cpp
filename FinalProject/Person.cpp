#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Person.h"
#include <string>

Person::Person()
{

}

Person::Person(bool gender, CString id, CString name, Address addr, Date birthday)
{
	Gender = gender;
	Name = name;
	ID = id;
	address = addr;
	Birthday = birthday;
}

Person::Person(const Person& P) : Person(P.Gender, P.ID, P.Name, P.address, P.Birthday)
{

}

Person::~Person()
{

}

bool Person::get_Gender()
{
	return Gender;
}

CString Person::get_ID()
{
	return ID;
}

CString Person::get_Name()
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

void Person::set_Gender(const bool gender)
{
	Gender = gender;
}

void Person::set_ID(const CString id)
{
	ID = id;
}

void Person::set_Name(const CString name)
{
	Name = name;
}

void Person::set_Address(const Address addr)
{
	address = addr;
}

void Person::set_Birthday(const Date birthday)
{
	Birthday = birthday;
}

int Person::get_itemType()
{
	return this->itemType;
}

