#pragma once
#include "header.h"
#include "citizen.h"
class party;
class district;



struct representativeNode
{
	citizen& _data;
	representativeNode* _next;
	representativeNode(citizen& _data_, representativeNode* _next_ = nullptr) :_data(_data_), _next(_next_)
	{
	}
};



class districtParty {
private:
	const district& _district;
	const party& _federalParty;
	int _vote;

	//list///////
	representativeNode* _head;
	representativeNode* _tail;
	int representativeCount;
	void addToList(citizen& _newRepresentative_);
	void makeEmptyList();
	bool isEmpty();
	void deleteList();
	void printList();
	////////////////

		//the function make memory allocation for the name string and copy the citizen name to ptr
	void copyNameToArray(citizen& citizen, char* ptr);

public:
	districtParty(party& _federalParty_, district& _district_);//structure

	~districtParty();//destructure

	//my friend///
	friend class election;
	/////////

	const party& _getFederalParty() const;

	void add1VoteToDistrictParty();

	int getRepresentativeCount() const;//only for save file

	void setVote(const int num);//only for loadFile

	int setRepresentativeCount(int newCount);





	int __vote() const;

	//the function get ammount of representative to print
	//in case of now enough representative the fuinction return 0
	//else the function return 1
	void printLimitedRepresentativeList(int n, int* res);

	//the function assume that the citizen is legal representative
	void addRepresentative(citizen& newRepresentative);

	void printRepresentativeList() const;

	int saveDistrictParty(ofstream& f) const;
};
