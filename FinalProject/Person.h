#pragma once
#define MAX_ID 10
#define MAX_STR 25

// TODO: think about replacing char array in string class

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
	char street[MAX_STR];
	Citys city;
}Address;

class Person
{
public:
	Person();
	Person(bool gender, const char* id, const char* name, Address addr, Date birthday);
	Person(Person& P);
	virtual ~Person();
	bool get_Gender();
	char* get_ID();
	char* get_Name();
	Address get_Address();
	Date get_Birthday();

protected:
	bool Gender;           // False -> male, True -> female
	char ID[MAX_ID];
	char Name[MAX_STR];
	Address address;
	Date Birthday;
	virtual void setAddress(Address addr);
	virtual void setDate(Date date);
};
