#pragma once
#include <string>

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


const CString Citys[NUM_OF_CITYS] = { _T("Tel Aviv"), _T("Bat Yam"), _T("Holon"), _T("Ramat Gan"), _T("Givataim"), _T("Bnei Brak"), _T("Or Yehuda"), _T("Zichron Yaakov"), _T("Ramla"), _T("Lod"),
			_T("Kfar Chabad"), _T("Petah Tikva"), _T("Rishon Lezion"), _T("Rehovot"), _T("Kfar Saba"), _T("Raanana"), _T("Herzliya"), _T("Hod Hasharon"),
			_T("Ramat Hasharon"), _T("Jerusalem"), _T("Beit Shemesh"), _T("Modiin"), _T("Modiin Illit"), _T("Elad"), _T("Efrat"), _T("Beitar Illit"),
			_T("Ashkelon"), _T("Ashdod"), _T("Netivot"), _T("Kiryat Gat"), _T("Beer Sheva"), _T("Sderot"), _T("Netanya"), _T("Haifa"), _T("Hedera"), _T("Tveria"),
			_T("Acre"), _T("Nof Hagalil"), _T("Migdal Haemek"), _T("Kiryat Shmona") };

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
	void set_Gender(const bool gender);
	void set_ID(const CString id);
	void set_Name(const CString name);
	void set_Address(const Address addr);
	void set_Birthday(const Date birthday);


protected:
	bool Gender;           // False -> Female, True -> Male
	CString ID;
	CString Name;
	Address address;
	Date Birthday;
	int itemType = -1;
};
