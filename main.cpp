#include "menu.h"

using namespace std;

void main()
{
	int choice;
	bool isRegularElection;
	Str fileName;
	int numOfRepresentative;

	cout << "Welcome!" << endl;
	printStartMenu();
	cin >> choice;

	while ((choice < 1) || (choice > 3))
	{
		system("cls");
		cout << "Worng input, Please try again.";
		enter();
		printStartMenu();
		cin >> choice;
	}

	system("cls");

	if (choice == 2)
	{
		cout << "Please enter the file's name: ";
		cin.ignore();
		cin >> fileName;
		date date(1, 1, 2021);		
		ifstream inPut(fileName.str, ios::binary);
		if (!inPut)
		{
			cout << "Error with " << fileName << endl;
			exit(-1);
		}
		else
		{
			int electionType = getElectionType(inPut);
			//in case of regular election getElectionType return 1
			//in case of election without district getElectionType return 0

			if (electionType == 1)
			{
				electionRegular _election(date);
				_election.load(inPut);
				electionMenuRegular(_election);
			}
			else
			{
				electionWithoutDistricts _election(date, -1);
				_election.load(inPut);
				electionMenuSimple(_election);
			}
			inPut.close();
		}
	}

	else if (choice ==3 )
	{
		cout << "Thank you and goodbye!" << endl;
		exit(0);
	}
	
	else
	{
		int day, month, year;
		cout << "Please enter the date for the Elections (day, month and year): ";
		cin >> day >> month >> year;
		date date(day, month, year);
		system("cls");
		printElectionTypeMenu();
		cin >> choice;
		while ((choice != 1) && (choice != 2))
		{
			system("cls");
			cout << "Worng input, Please try again.";
			enter();
			printElectionTypeMenu();
			cin >> choice;
		}
		if (choice == 1) isRegularElection = true;
		else isRegularElection = false; /*choice == 2*/
		system("cls");

		if (isRegularElection)
		{
			electionRegular election1(date);
			electionMenuRegular(election1);
		}
		else
		{
			cout << "Please choose the amount of representative: ";
			cin >> numOfRepresentative;
			system("cls");
			electionWithoutDistricts election2(date, numOfRepresentative);
			electionMenuSimple(election2);
		}
	}
}