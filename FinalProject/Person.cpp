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
	setAddress(addr);
	setDate(birthday);
}

Person::Person(const Person& P) : Person(P.Gender, P.ID, P.Name, P.address, P.Birthday)
{

}

Person::~Person()
{

}

void Person::setAddress(Address addr)
{
	address.street = addr.street;
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

//string Person::getCityString(const int ID)
//{
//	string str[NUM_OF_CITYS] = { "TelAviv", "BatYam", "Holon", "RamatGan", "Givataim", "BneiBrak", "OrYehuda", "ZichronYaakov", "Ramla", "Lod", "KfarChabad", "PetahTikva", "RishonLezion", "Rehovot", "KfarSaba", "Raanana", "Herzliya", "HodHasharon", "RamatHasharon", "Jerusalem", "BeitShemesh", "Modiin", "ModiinIllit", "Elad", "Efrat", "BeitarIllit", "Ashkelon", "Ashdod", "Netivot", "KiryatGat", "BeerSheva", "Sderot", "Netanya", "Haifa", "Hedera", "Tveria","Acre", "NofHagalil", "MigdalHaemek", "KiryatShmona" };
//
//	if (ID < 0 || ID > 39) return "Error";
//	return str[ID];
//}

Date Person::get_Birthday()
{
	return Birthday;
}
