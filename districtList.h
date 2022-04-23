#pragma once
#include "district.h"



struct districtNode {
	district* _data;
	districtNode* _next;

	districtNode(district* _data_, districtNode* _next_ = nullptr)
	{
		_data = _data_;
		_next = _next_;
	}
};



class	districtList {
private:
	districtNode* _head;
	districtNode* _tail;

	//List//
	int districtCount;
	void addToList(district* _district);
	void makeEmptyList();
	bool isEmpty();
	void deleteList();
	///////////////////

public:
	districtList();
	~districtList();

	//my freind////
	friend class electionRegular;
	friend class electionWithoutDistricts;
	//////////////

	//in case of the district didnt found *res= -1
	//in case of the party didnt found  *res= 0
	//else the function return a reference to the district party and *res=1
	districtParty& findDistrictParty(int serialNumberOfDistrict, int serialNumberOfParty, int* res);

	//in case of the district didnt found *res=0
		//else the function return referense to the person tand *res=1
	district& findDistrict(int serialNumber, int* res);

	//in case of uniform district type =1
	//in case of divided district type =2
	//the function return the serial Number
	int addDistrict(const char* name, const int numOfRepresntative, int type);

	void addPartyToAllDistrictsParties(party& _federalParty_);

	//in case of the party didnt found the function return 0
	//else the function return 1 and print all the representative list of the party
	int printRepresentativeOfSpecificPartyForAllTheDistricts(int serialNumberOfParty) const;

	void setTheSerialNumberCounter(const int newSerialNumber);//for file load


	//save/////
	int saveSerialNumber(ofstream& f) const;//for file save

	void saveDistrictsCounter(ofstream& f) const;

	void saveDistrictList(ofstream& f) const;
	///////////

	//load//////
	int load(ifstream& f, int districtCount);

	int loadSerialNumber(ifstream& f);
	///////////


	friend ostream& operator<<(ostream& os, const districtList& _lst)
	{
		cout << "districts list" << endl;
		cout << "_____________" << endl;
		printList(_lst._head);
		return os;
	}
};
