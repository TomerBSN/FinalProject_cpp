#pragma once
#include <string>
#include <map>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_ID 10
#define MAX_STR 25
#define NUM_OF_CITYS 40

using namespace std;

typedef struct date {
	int day;
	int month;
	int year;
}Date;

const string Citys[NUM_OF_CITYS] = { "Tel Aviv", "Bat Yam", "Holon", "Ramat Gan", "Givataim", "Bnei Brak", "Or Yehuda", "Zichron Yaakov", "Ramla", "Lod",
			"Kfar Chabad", "Petah Tikva", "Rishon Lezion", "Rehovot", "Kfar Saba", "Raanana", "Herzliya", "Hod Hasharon",
			"Ramat Hasharon", "Jerusalem", "Beit Shemesh", "Modiin", "Modiin Illit", "Elad", "Efrat", "Beitar Illit",
			"Ashkelon", "Ashdod", "Netivot", "Kiryat Gat", "Beer Sheva", "Sderot", "Netanya", "Haifa", "Hedera", "Tveria",
			"Acre", "Nof Hagalil", "Migdal Haemek", "Kiryat Shmona" };

typedef struct address {
	CString street;
	CString city;
}Address;

class Person
{
public:
	Person();
	Person(bool gender, CString id, CString name, Address addr, Date birthday);
	Person(const Person& P);
	virtual ~Person();
	bool get_Gender();
	CString get_ID();
	CString get_Name();
	Address get_Address();
	Date get_Birthday();
	int get_itemType();

	//Functions that are pure abstract in a sense.

	//Gets the sickness level; Hospitalized type;
	virtual CString get_Level() { return NULL; };
	//Gets if the person is Ventilated; Hospitalized type;
	virtual bool get_IsVentilated() { return false; };
	//Gets the hospital name; Hospitalized type;
	virtual CString get_Hospital() { return NULL; };
	//Gets the date they entered the hospital; Hospitalized type;
	virtual Date get_HospitalizationDate() { Date d; d.day = 1; d.month = 1; d.year = 1; return d; };
	//Gets the address of where they are isolated; Non-Hospitalized type & Isolated type;
	virtual Address get_WhereIsolated() { Address ad; return ad; };
	//Gets the date of when they recovered from sickness; Recovered type;
	virtual Date get_RecoveryDate() { Date d; d.day = 1; d.month = 1; d.year = 1; return d; };
	//Gets the date of when they entered isolation; Isolated type;
	virtual Date get_Isolation_date() { Date d; d.day = 1; d.month = 1; d.year = 1; return d; };
	//Gets the ID of who that was sick who exposed them to the illness; Isolated type;
	virtual CString get_ExposedTo() { return NULL; };
	//Gets the date of the Positive Covid test; Sick type;
	virtual Date get_PositiveTest_date() { Date d; d.day = 1; d.month = 1; d.year = 1; return d; };
	//Gets the ID of who infected them actually; Sick type;
	virtual CString get_InfectedBy() { return NULL; };
	//Gets the type of area they were in last that caused this positive test state; Sick type;
	virtual CString get_InfectionArea() { return NULL; };

protected:
	bool Gender;           // False -> Female, True -> Male
	CString ID;
	CString Name;
	Address address;
	Date Birthday;
	int itemType = -1;
	virtual void setAddress(Address addr);
	virtual void setDate(Date date);
};
