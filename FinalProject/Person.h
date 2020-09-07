#pragma once
#include <string>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_ID 10
#define MAX_STR 25
#define NUM_OF_CITYS 40
// TODO: think about replacing char array in string class
using namespace std;

typedef struct date {
	int day;
	int month;
	int year;
}Date;

enum Citys {TelAviv, BatYam, Holon, RamatGan, Givataim, BneiBrak, OrYehuda, ZichronYaakov, Ramla, Lod,
			KfarChabad, PetahTikva, RishonLezion, Rehovot, KfarSaba, Raanana, Herzliya, HodHasharon,
			RamatHasharon, Jerusalem, BeitShemesh, Modiin, ModiinIllit, Elad, Efrat, BeitarIllit,
			Ashkelon, Ashdod, Netivot, KiryatGat, BeerSheva, Sderot, Netanya, Haifa, Hedera, Tveria,
			Acre, NofHagalil, MigdalHaemek, KiryatShmona};

typedef struct address {
	CString street;
	Citys city;
}Address;

class Person
{
public:
	Person();
	Person(bool gender, CString id, CString name, Address addr, Date birthday);
	Person(Person& P);
	virtual ~Person();
	bool get_Gender();
	CString get_ID();
	CString get_Name();
	Address get_Address();
	//string getCityString(const int ID);//To be removed if needed
	Date get_Birthday();

protected:
	bool Gender;           // False -> Female, True -> Male
	CString ID;
	CString Name;
	Address address;
	Date Birthday;
	//string cityName;
	virtual void setAddress(Address addr);
	virtual void setDate(Date date);
};
