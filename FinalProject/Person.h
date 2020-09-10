#pragma once
#include <string>
#include <map>

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
	//string getCityString(const int ID);//To be removed if needed
	Date get_Birthday();
	int get_itemType();

protected:
	bool Gender;           // False -> Female, True -> Male
	CString ID;
	CString Name;
	Address address;
	Date Birthday;
	int itemType = -1;
	//string cityName;
	virtual void setAddress(Address addr);
	virtual void setDate(Date date);
};
