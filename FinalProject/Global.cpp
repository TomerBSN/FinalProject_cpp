#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Global.h"


using namespace std;
vector <Person*> Persons;
map<CString, int> CountByCity;
map<CString, int> CountByLevel;
map<CString, int> CountByArea;
map<CString, int> CountByHostital;
int TotalHospitalized;
int TotalNonHospitalized;
int TotalRecovered;
int TotalIsolated;
int searchPersonID;

bool searchPersonByID(CString ID)
{
	bool found = false;
	int i;
	vector<Person*>::iterator ptr;
	ptr = Persons.begin();
	for (i = 0, ptr = Persons.begin(); ptr != Persons.end(); ptr++, i++)
	{
		if ((*ptr)->get_ID() == ID)
		{
			found = true;
			searchPersonID = i;
			break;
		}
	}

	return found;
}
