#pragma once
#include <iostream>
#include <cstring>
#include "election.h"
#include "Str.h"

using namespace std;

void printMenu();
void printStartMenu();
void printElectionTypeMenu();
void navigatorRegular(int choice, electionRegular& election);
void navigatorSimple(int choice, electionWithoutDistricts& election);
void electionMenuRegular(electionRegular& election);
void electionMenuSimple(electionWithoutDistricts& election);
void enter();
bool checkDate(int day, int month, int year);
const char* saveElection(election& election, Str fileName);
const int loadElection(election& election, Str fileName);
int getElectionType(ifstream& f);