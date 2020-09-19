#pragma once
#include "Person.h"
#include "Hospitalized.h"
#include "NonHospitalized.h"
#include "Recovered.h"
#include "Isolated.h"
#include <vector>
#include <map>

using namespace std;

extern map<CString, int> CountByCity;
extern map<CString, int> CountByLevel;
extern map<CString, int> CountByArea;
extern map<CString, int> CountByHostital;
extern int TotalHospitalized;
extern int TotalNonHospitalized;
extern int TotalRecovered;
extern int TotalIsolated;

extern vector <Person*> Persons;
extern int searchPersonID;

bool searchPersonByID(CString ID);
int getDifference(Date dt1, Date dt2);
void decreaseCounters(int index);