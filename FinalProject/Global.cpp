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

int countLeapYears(Date d)
{
    int years = d.year;

    // Check if the current year needs to be considered 
    // for the count of leap years or not 
    if (d.month <= 2)
        years--;

    // An year is a leap year if it is a multiple of 4, 
    // multiple of 400 and not a multiple of 100. 
    return years / 4 - years / 100 + years / 400;
}

// This function returns number of days between two given dates
int getDifference(Date dt1, Date dt2)
{
    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1' 

    // initialize count using years and day 
    const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long int n1 = dt1.year * 365 + dt1.day;

    // Add days for months in given date 
    for (int i = 0; i < dt1.month - 1; i++)
        n1 += monthDays[i];

    // Since every leap year is of 366 days, 
    // Add a day for every leap year 
    n1 += countLeapYears(dt1);

    // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2' 

    long int n2 = dt2.year * 365 + dt2.day;
    for (int i = 0; i < dt2.month - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    return (n2 - n1);
}
