#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Global.h"

using namespace std;

vector <Person*> Persons;
cntContainer Counters;
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

    // Check if the current year needs to be considered for the count of leap years or not 
    if (d.month <= 2)
        years--;

    // An year is a leap year if it is a multiple of 4 / 400 and not a multiple of 100
    return years / 4 - years / 100 + years / 400;
}

// This function returns number of days between two given dates
int getDifference(Date dt1, Date dt2)
{
    // initialize count using years and day 
    const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long int n1 = dt1.year * 365 + dt1.day;

    // Add days for months in given date 
    for (int i = 0; i < dt1.month - 1; i++)
        n1 += monthDays[i];

    // Since every leap year is of 366 days, Add a day for every leap year  
    n1 += countLeapYears(dt1);

    // count total number of days before 'dt2'
    long int n2 = dt2.year * 365 + dt2.day;
    for (int i = 0; i < dt2.month - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    return (n2 - n1);
}

void updateCounters(Person* p, bool flag)    // flag = 0 -> decrease counters, flag = 1 -> increase counters
{
    int itemType = p->get_itemType();

    if (flag)
        Counters.CountByCity[p->get_Address().city]++;
    else
        Counters.CountByCity[p->get_Address().city]--;

    if (itemType != 3)
    {
        Sick* s = (Sick*)(p);
        if (flag)
            Counters.CountByArea[s->get_InfectionArea()]--;
        else
            Counters.CountByArea[s->get_InfectionArea()]--;
    }

    switch (itemType)
    {
        case 0:
        {
            Hospitalized* h = (Hospitalized*)(p);
            if (flag)
            {
                Counters.CountByHostital[h->get_Hospital()]++;
                Counters.CountByLevel[h->get_Level()]++;
                Counters.TotalHospitalized++;
            }
            else
            {
                Counters.CountByHostital[h->get_Hospital()]--;
                Counters.CountByLevel[h->get_Level()]--;
                Counters.TotalHospitalized--;
            }

            break;
        }

        case 1:
        {
            if (flag)
            {
                Counters.CountByLevel[_T("Easy")]++;
                Counters.TotalNonHospitalized++;
            }
            else
            {
                Counters.CountByLevel[_T("Easy")]--;
                Counters.TotalNonHospitalized--;
            }

            break;
        }

        case 2:
        {
            if (flag)
                Counters.TotalRecovered++;
            else
                Counters.TotalRecovered--;

            break;
        }

        case 3:
        {
            if (flag)
                Counters.TotalIsolated++;
            else
                Counters.TotalIsolated--;

            break;
        }

    }

    Counters.TotalSicks = Counters.TotalHospitalized + Counters.TotalNonHospitalized;
}
