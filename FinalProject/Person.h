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
