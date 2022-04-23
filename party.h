#pragma once
#include "header.h"
class citizen;
class party {
private:
	char* _name;
	const int _serialNumber;
	citizen& _residentialStumble;
	char* _residentalStumbleName;
	int _vote;
public:
	party(int _serialnumber_, citizen& _residentialStumble_, const char* _name_, const char* residentalStumbleName);//structure
	party(ifstream& f, citizen& _citizen, int _serialNumber_);//structure for load file
	~party();//destructure

	void add1Vote();

	int getSerialNumber() const;

	char* getCandidateOfPrimerMinisterName() const;

	citizen& getCandidateOfPrimerMinister();

	const char* getName() const;

	int __vote() const;

	friend ostream& operator<<(ostream& os, const party& _party)
	{
		os << "Name :" << _party._name << endl;
		os << "Serial Number :" << _party._serialNumber << endl;
		os << "Candidate for Prime Minister :" << _party._residentalStumbleName << endl;

		return os;
	}

	//save

	//the function save:
	//the appearance
	//the party name size
	//the party name string
	//the stumble name size
	//the stumble name string
	int saveParty(ofstream& f)const;
};