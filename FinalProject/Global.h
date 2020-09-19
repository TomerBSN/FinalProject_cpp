#pragma once
#include "Person.h"
#include "Hospitalized.h"
#include "NonHospitalized.h"
#include "Recovered.h"
#include "Isolated.h"
#include <vector>
#include <map>

using namespace std;

typedef struct cntContainer
{
	map<CString, int> CountByCity;
	map<CString, int> CountByLevel;
	map<CString, int> CountByArea;
	map<CString, int> CountByHostital;
	int TotalHospitalized;
	int TotalNonHospitalized;
	int TotalSicks;
	int TotalRecovered;
	int TotalIsolated;
} cntContainer;

extern cntContainer Counters;
extern vector <Person*> Persons;
extern int searchPersonID;

bool searchPersonByID(CString ID);
int getDifference(Date dt1, Date dt2);
void updateCounters(Person* p, bool flag);