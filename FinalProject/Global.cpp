#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Global.h"

using namespace std;

vector <Person*> Persons;
cntContainer Counters;
int searchPersonID;

/*
Function: [bool] serach a person object by given ID
*/
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

/*
Function: [int] count number of leap years before the given date 
*/
int countLeapYears(Date d)
{
    int years = d.year;

    // Check if the current year needs to be considered for the count of leap years or not 
    if (d.month <= 2)
        years--;

    // An year is a leap year if it is a multiple of 4 or 400 and not a multiple of 100
    return (years / 4) - (years / 100) + (years / 400);
}

/*
Function: [int] returns number of days between two given dates.
*/
int getDatesDiff(Date dt1, Date dt2)
{
    // initialize count using years and day 
    const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long int dt1_days = dt1.year * 365 + dt1.day;

    // Add days for months in given date 
    for (int i = 0; i < dt1.month - 1; i++)
        dt1_days += monthDays[i];

    // Since every leap year is of 366 days, Add a day for every leap year  
    dt1_days += countLeapYears(dt1);

    // count total number of days before 'dt2'
    long int dt2_days = dt2.year * 365 + dt2.day;
    for (int i = 0; i < dt2.month - 1; i++)
        dt2_days += monthDays[i];
    dt2_days += countLeapYears(dt2);

    return (dt2_days - dt1_days);
}

/*
Function: [void] update system counters - decrease or increase
*/
void updateCounters(Person* p, bool flag)    // flag = 0 -> decrease counters, flag = 1 -> increase counters
{
    int itemType = p->get_itemType();

    if (flag)
        Counters.CountByCity[p->get_Address().city]++;
    else
        Counters.CountByCity[p->get_Address().city]--;

    if (itemType != 3)         // Sick
    {
        Sick* s = (Sick*)(p);
        if (flag)
            Counters.CountByArea[s->get_InfectionArea()]++;
        else
            Counters.CountByArea[s->get_InfectionArea()]--;
    }

    switch (itemType)
    {
        case 0:                // Hospitalized
        {
            Hospitalized* h = (Hospitalized*)(p);
            if (flag)
            {
                Counters.CountByHostital[h->get_Hospital()]++;
                Counters.CountByLevel[h->get_Level()]++;
                Counters.TotalHospitalized++;
                if (h->get_IsVentilated())
                    Counters.TotalVentilated++;
            }
            else
            {
                Counters.CountByHostital[h->get_Hospital()]--;
                Counters.CountByLevel[h->get_Level()]--;
                Counters.TotalHospitalized--;
                if (h->get_IsVentilated())
                    Counters.TotalVentilated--;
            }

            break;
        }

        case 1:                 // NonHospitalized
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

        case 2:                 // Recovered
        {
            if (flag)
                Counters.TotalRecovered++;
            else
                Counters.TotalRecovered--;

            break;
        }

        case 3:                 // Isolated
        {
            if (flag)
                Counters.TotalIsolated++;
            else
                Counters.TotalIsolated--;

            break;
        }

        default:
            break;
    }

    Counters.TotalSicks = Counters.TotalHospitalized + Counters.TotalNonHospitalized;
}
