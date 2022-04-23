#pragma once
#include "header.h"

class district;

class citizen {
private:
	char* name;
	char* id;
	district& _district;
	char* districtName;
	bool _vote;
	bool _representive;
	const int _birthYear;
	const bool  _upTo18;

public:
	citizen(district& _district_, const char* Name, const char* id, bool upTo18, const int _birthYear_, const char* districtName);//structure
	citizen(ifstream& f, district& _district_, const char* _districtName_, int _birthYear_, bool _upTo18_);//structure for load files only
	~citizen();

	//my friend///
	friend class electionRegular;
	friend class electionWithoutDistrict;
	////


	//in case the person already representine the function return 1
	//else the function return 0 and update the person to be representative
	bool __representine();

	//in case of the person to young for vote the function return -1
//in case of the person already voted the function return 1
//else the function return 0 and update the person voted to true
	int __vote();

	const char* getId() const;

	const char* getName() const;

	district& getDistrict() const;

	friend ostream& operator<<(ostream& os, const citizen& _citizen)
	{
		os << "Name :" << _citizen.name << endl;
		os << "Id :" << _citizen.id << endl;
		os << "Birth Year :" << _citizen._birthYear << endl;
		os << "District Name :" << _citizen.districtName << endl;

		return os;
	}

	//save

	//the function save:
	//the length of the id with \0
	//the string of the id
	int saveId(ofstream& f)const;

	//the function save:
	//the apperance
	//the length of the name with '\0'
	//the name string
	//the length of the id with '\0'
	//the id string
	//the length of the district name with '\0'
	//the district name string
	int saveCitizen(ofstream& f) const;
};