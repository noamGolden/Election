#include "menu.h"
#include <typeinfo>

void printStartMenu()
{
	cout << "Please choose from the following options:" << endl;
	cout << "1. Create a new election campaign." << endl <<
		"2. Upload existing election campaign." << endl <<
		"3. Exit." << endl;
}

void printMenu() 
{
	cout << "Please choose from the following options: " << endl;
	cout << "1. Add a District." << endl <<
		"2. Add a Citizen." << endl <<
		"3. Add a Party." << endl <<
		"4. Add a Citizen as a Representative." << endl <<
		"5. Display all Districts." << endl <<
		"6. Display all Citizens." << endl <<
		"7. Display All Parties." << endl <<
		"8. Make a Vote." << endl <<
		"9. Display Elections results." << endl <<
		"10. Exit" << endl <<
		"11. Save Campaign." << endl <<
		"12. Load Campaign." << endl;
}

void electionMenuRegular(electionRegular& election)
{
	int choice;
	do {
		system("cls");
		printMenu();
		cin >> choice;
		system("cls");
		navigatorRegular(choice, election);
	} while (choice != 10);
	exit(0);
}

void electionMenuSimple(electionWithoutDistricts& election)
{
	int choice;
	do {
		system("cls");
		printMenu();
		cin >> choice;
		system("cls");
		navigatorSimple(choice, election);
	} while (choice != 10);
	exit(0);
}

void enter()
{
	cout << "\n\nclick ENTER to continue" << endl;
	char enter = '\0';
	cin.get();

	while (enter != '\n')
	{
		enter = cin.get();
	}
	system("CLS");
}

void printElectionTypeMenu()
{
	cout << "Please choose the election type:" << endl;
	cout << "1. Regular election campaign (with districts)." << endl <<
		"2. Simple election campaign (without districts)." << endl;
}

bool checkDate(int day, int month, int year)
{
	if (((day < 1) || (day > 31)) || ((month < 1) || (month > 12)) || ((year < 1900) || (year > 2100)))
		return false;
	return true;
}

void navigatorRegular(int choice, electionRegular& election)
{
	if (choice == 1)
	{
		int type = 0;
		Str districtName;
		int numOfRep;
		int numDistrict;
		while ((type != 1) && (type != 2))
		{
			system("cls");
			cout << "Please choose type of district:\n1. Uniform district.\n2. Devided district." << endl;
			cin >> type;
		}
		system("cls");
		cout << "Enter district name: ";
		cin.ignore();
		cin >> districtName;
		cout << "\nEnter number of representative: ";
		cin >> numOfRep;
		numDistrict = election.addDistrict(districtName.str, numOfRep, type);
		system("cls");
		cout << "District " << districtName.str << "'s number is: " << numDistrict;
		enter();
	}
	if(choice == 2)
	{
		int allGood = 2;
		Str citiName;
		Str id;
		int year;
		int numDistrict;
		cout << "Please enter a name: ";
		if((allGood!=0)&&(allGood!=-1)) cin.ignore();
		cin >> citiName;
		cout << "Enter an ID: ";
		cin >> id;
		cout << "Enter birth year: ";
		cin >> year;
		cout << "Choose a district for " << citiName << " (number of district): ";
		cin >> numDistrict;
		allGood = election.addCitizen(citiName.str, id.str, year, numDistrict);
		system("cls");
		if(allGood != 1) //citizen id already exist or district don't exist.
		{
			if (allGood == -1) cout << "District serial number don't exist.\nCitizen wasn't create, please try again.";
			if (allGood == 0) cout << "ID already exist.\nCitizen wasn't create, please try again.";
			enter();
		}
		if(allGood == 1) 
		{ 
			cout << "Citizen " << citiName << " was added.";
			enter();
		}
	}
	if (choice == 3)
	{
		int allGood = -1;
		Str partyName;
		Str idOfCanidate;
		cout << "Please enter party's name: ";
		cin.ignore();
		cin >> partyName;
		cout << "Enter canidate's ID: ";
		cin >> idOfCanidate;
		allGood = election.addParty(partyName.str, idOfCanidate.str);
		system("cls");
		if (allGood == -2) cout << "Citizen dosen't exist.\nPlease try again.";
		else if (allGood == -1) cout << "Citizen already is a canidate.\nPlease try again.";
		else cout << "The Party " << partyName.str << "'s serial number is: " << allGood;
		enter();
	}
	if (choice == 4)
	{
		int allGood = 2;
		Str idOfRep;
		int numOfParty, numOfDis;
		cout << "Please enter citizen's ID for being representative: ";
		if (allGood>1) cin.ignore();
		cin >> idOfRep;
		cout << "Enter the serial's party number: ";
		cin >> numOfParty;
		cout << "Enter the serial's district number: ";
		cin >> numOfDis;
		allGood = election.addRepresentative(idOfRep.str, numOfParty, numOfDis);
		system("cls");
		if (allGood == -3) cout << "District was not found.\nPlease try again.";
		else if (allGood == -2) cout << "Party was not found.\nPlease try again.";
		else if (allGood == -1) cout << "ID was not found.\nPlease try again.";
		else if (allGood == 0) cout << "Citizen is already a representative.\nPlease try again.";
		else cout << "The citizen was add as a representative.";
		enter();
	}
	if (choice == 5)
	{
		cout << election.getDistrictList() << endl;
		enter();
	}
	if (choice == 6)
	{
		cout << election.getCitizenList() << endl;
		enter();
	}
	if (choice == 7)
	{
		election.displayAllParties();
		enter();
	}
	if (choice == 8)
	{
		int allGood = -1;
		Str id;
		int numOfParty;
		cout << "Vote:\nPlease enter the citizen's ID: ";
		cin.ignore();
		cin >> id;
		cout << "Enter the serial number of the party that the vote will go to: ";
		cin >> numOfParty;
		allGood = election.addVote(id.str, numOfParty);
		system("cls");
		if (allGood == -3) cout << "Party was not found.\nPlease try again.";
		else if (allGood == -2) cout << "Citizen was not found.\nPlease try again.";
		else if (allGood == -1) cout << "Citizen already voted.\nPlease try again.";
		else if (allGood == 0) cout << "Citizen is too young for voting.\nPlease try again.";
		else cout << "The citizen's vote added.";
		enter();
	}
	if (choice == 9)
	{
		election.disPlayResult();
		enter();
	}
	if (choice == 10)
	{
		cout << "Thank you, goodbye" << endl;
		enter();
	}
	if (choice == 11)
	{
		Str saveFile;
		cout << "Enter file's name: ";
		cin.ignore();
		cin >> saveFile;
		saveElection(election, saveFile);
		system("cls");
		cout << "The file " << saveFile << " is saved.";
		enter();
	}
	if (choice == 12)
	{
		Str fileName;
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
	if(choice > 12)
	{
		cout << "Wrong input!\nPlease enter a number between 1 - 12";
		enter();
	}
}

void navigatorSimple(int choice, electionWithoutDistricts& election)
{
	if (choice == 1)
	{
		cout << "Can not create districts in Simple Election campaign, only in Regular Election campaign.";
		enter();
	}
	if (choice == 2)
	{
		int allGood = 2;
		Str citiName;
		Str id;
		int year;
		cout << "Please enter a name: ";
		if ((allGood != 0) && (allGood != -1)) cin.ignore();
		cin >> citiName;
		cout << "Enter an ID: ";
		cin >> id;
		cout << "Enter birth year: ";
		cin >> year;
		allGood = election.addCitizen(citiName.str, id.str, year,0);
		system("cls");
		if (allGood == 0) //citizen id already exist or district don't exist.
		{
			cout << "ID already exist.\nCitizen wasn't create, please try again.";
			enter();
		}
		if (allGood == 1)
		{
			cout << "Citizen " << citiName << " was added.";
			enter();
		}
	}
	if (choice == 3)
	{
		int allGood = -1;
		Str partyName;
		Str idOfCanidate;
		cout << "Please enter party's name: ";
		cin.ignore();
		cin >> partyName;
		cout << "Enter canidate's ID: ";
		cin >> idOfCanidate;
		allGood = election.addParty(partyName.str, idOfCanidate.str);
		system("cls");
		if (allGood == -2) cout << "Citizen dosen't exist.\nPlease try again.";
		else if (allGood == -1) cout << "Citizen already is a canidate.\nPlease try again.";
		else cout << "The Party " << partyName.str << "'s serial number is: " << allGood;
		enter();
	}
	if (choice == 4)
	{
		int allGood = 2;
		Str idOfRep;
		int numOfParty;
		cout << "Please enter citizen's ID for being representative: ";
		if (allGood > 1) cin.ignore();
		cin >> idOfRep;
		cout << "Enter the serial's party number: ";
		cin >> numOfParty;
		allGood = election.addRepresentative(idOfRep.str, numOfParty, 0);
		system("cls");
		if (allGood == -2) cout << "Party was not found.\nPlease try again.";
		else if (allGood == -1) cout << "ID was not found.\nPlease try again.";
		else if (allGood == 0) cout << "Citizen is already a representative.\nPlease try again.";
		else cout << "The citizen was add as a representative.";
		enter();
	}
	if (choice == 5)
	{
		cout << "Option available only for Regular Election campaign." << endl;
		enter();
	}
	if (choice == 6)
	{
		cout << election.getCitizenList() << endl;
		enter();
	}
	if (choice == 7)
	{
		election.displayAllParties();
		enter();
	}
	if (choice == 8)
	{
		int allGood = -1;
		Str id;
		int numOfParty;
		cout << "Vote:\nPlease enter the citizen's ID: ";
		cin.ignore();
		cin >> id;
		cout << "Enter the serial number of the party that the vote will go to: ";
		cin >> numOfParty;
		allGood = election.addVote(id.str, numOfParty);
		system("cls");
		if (allGood == -3) cout << "Party was not found.\nPlease try again.";
		else if (allGood == -2) cout << "Citizen was not found.\nPlease try again.";
		else if (allGood == -1) cout << "Citizen already voted.\nPlease try again.";
		else if (allGood == 0) cout << "Citizen is too young for voting.\nPlease try again.";
		else cout << "The citizen's vote added.";
		enter();
	}
	if (choice == 9)
	{
		election.disPlayResult();
		enter();
	}
	if (choice == 10)
	{
		cout << "Thank you, goodbye" << endl;
		enter();
	}
	if (choice == 11)
	{
		Str saveFile;
		cout << "Enter file's name: ";
		cin.ignore();
		cin >> saveFile;
		saveElection(election, saveFile);
		system("cls");
		cout << "The file " << saveFile << " is saved.";
		enter();
	}
	if (choice == 12)
	{
		Str fileName;
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
	if (choice > 12)
	{
		cout << "Wrong input!\nPlease enter a number between 1 - 12";
		enter();
	}
}

int getElectionType(ifstream& f)
{
	int res;

	f.read(READ(&res), sizeof(int));

	return res;
}

const char* saveElection(election& election, Str fileName)
{
	ofstream outPut(fileName.str, ios::binary | ios::trunc);
	if (!outPut)
	{
		cout << "Error with" << fileName << endl;
		exit(-1);
	}
	else
	{
		election.save(outPut);
		outPut.close();
	}
	return fileName.str;
}

const int loadElection(election& election, Str fileName)
{
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
			election.load(inPut);
		}
		else
		{
			election.load(inPut);
		}

		inPut.close();
		return electionType;
	}
}

