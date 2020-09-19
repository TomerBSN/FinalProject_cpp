#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Person.h"
#include <string>

Person::Person()
{
	Birthday.day = 1;
	Birthday.month = 1;
	Birthday.year = 1;
}

Person::Person(bool gender, CString id, CString name, Address addr, Date birthday)
{
	this->Gender = gender;
	this->Name = name;
	this->ID = id;
	this->address = addr;
	this->Birthday = birthday;
}

Person::Person(const Person& P) : Person(P.Gender, P.ID, P.Name, P.address, P.Birthday)
{

}

Person::~Person()
{

}

bool Person::get_Gender()
{
	return this->Gender;
}

CString Person::get_ID()
{
	return this->ID;
}

CString Person::get_Name()
{
	return this->Name;
}

Address Person::get_Address()
{
	return this->address;
}

Date Person::get_Birthday()
{
	return this->Birthday;
}

void Person::set_Gender(const bool gender)
{
	this->Gender = gender;
}

void Person::set_ID(const CString id)
{
	this->ID = id;
}

void Person::set_Name(const CString name)
{
	this->Name = name;
}

void Person::set_Address(const Address addr)
{
	this->address = addr;
}

void Person::set_Birthday(const Date birthday)
{
	this->Birthday = birthday;
}

int Person::get_itemType()
{
	return this->itemType;
}
