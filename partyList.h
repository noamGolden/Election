#pragma once
#include "party.h"
class districtList;
class dividedDistrict;


struct partyNode {
	party* _data;
	partyNode* _next;
	partyNode(party* _data_, partyNode* _next_ = nullptr)
	{
		_data = _data_;
		_next = _next_;
	}
};



class partyList
{
private:
	//List//
	partyNode* _head;
	partyNode* _tail;
	int partyCount;
	void addToList(party* _party_);
	void makeEmptyList();
	bool isEmpty();
	void deleteList();
	///////////////////
public:
	partyList();//strcture
	~partyList();//destructure

	//my friend////
	friend class election;
	//////////////

	//in case of the party didnt found *res=0
	//else *res=1
	party& getParty(int serialNumber, int* res);

	int getPartyCounter() const;

	party& addParty(const char* name, citizen& _residentialStumble, const char* _residentalStumbleName_);

	void setTheSerialNumberCounter(const int newSerialNumber);//for file load

	int saveTheSerialNumber(ofstream& f) const;//for file save

	int savePartiesCounter(ofstream& f) const;//for file save

	int loadSerialNumber(ifstream& f);
};