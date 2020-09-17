#pragma once
#include "Person.h"
#include <vector>

using namespace std;

extern vector <Person*> Persons;
extern map<CString, int> CountByCity;
extern map<CString, int> CountByLevel;
extern map<CString, int> CountByArea;
extern map<CString, int> CountByHostital;
extern int TotalHospitalized;
extern int TotalNonHospitalized;
extern int TotalRecovered;
extern int TotalIsolated;
extern int searchPersonID;