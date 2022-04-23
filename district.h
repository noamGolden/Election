#pragma once
#include "districtParty.h"
#include "party.h"
#include <string.h>

struct districtPartyNode {
	districtParty* _data;
	districtPartyNode* _next;

	districtPartyNode(districtParty* _data_, districtPartyNode* _next_ = nullptr)
	{
		_data = _data_;
		_next = _next_;
	}
};

struct result {
	int _serialNumberOfParty;
	int _electors;

	result()
	{
		_serialNumberOfParty = -1;
		_electors = 0;
	}
	void addElectors(int electors)
	{
		_electors += electors;
	}

};

enum class districtType
{
	uniform = 1,
	divided = 2
};

class district {
private:
	char* _name;
	const int _serialNumber;
	const int _representative;
	int _populationCount;
	int _voteCount;
	const districtType _type;
	result* resArr;
	int resArrSize;

	//list///
	districtPartyNode* _head;
	districtPartyNode* _tail;
	int partyCount;
	void addToList(districtParty* _district_);
	void makeEmptyList();
	bool isEmpty();
	void deleteList();
	////////

	//calculate///
	void makeElectorsDivisionArray();

	void dividedRemainingElectors(result* resultArr, float* carryArr, int sizeOfArrays, int remainingElectors);

	int calculateElectorsAndCarry(result& temp, float& carry, float votes);

	//the function return how many electors given
	float calculateValueOfVote();
	/////////////
public:
	district(const char* _name_, const int _serialNumber_, const int _representative_, districtType type);//structure
	district(ifstream& f, districtType _type_);//strcture for load file
	~district();//destructure


	//my freinds//////
	friend class dividedDistrict;
	friend class uniformDistrict;
	friend class election;
	friend class electionWithoutDistricts;
	////////////////

	int __voteCount()const;

	int setVoteCount(int newVoteCount);//only for file load and dictators

	int setPupaltionCount(int newCount);//only for file load

	virtual result* getResult() = 0;

	int getSerialNumber() const;

	const char* getName() const;

	districtType getDistrictType() const;

	//in case of the party didnt found the function return -1
	float getDistrictPartyPercentageOfVotes(int serialNumberOfParty) const;

	float getDistrictPartyPercentageOfVotes(const districtParty& _party_) const;

	//in case of the party didnt found the function return -1
	int getDistrictPartyNumOfVotes(int serialNumberOfParty) const;

	//in case of the party didnt found the function return 0
	//else the function return 1 and print the representative list
	int printRepresentativeList(int serialNumberOfParty) const;

	int getDistrictPartyNumOfVotes(const districtParty& _party_) const;

	float getTurnOutInTheDistrict() const;

	int getNumberOfRepresentative()const;

	int getpopulationCount()const;

	int getVoteCount()const;

	//in case of serialNumber didnt found *res=0;
	//else *res=1;
	districtParty& findDistrictPartyBySerialNumber(int serialNumber, int* res) const;

	void addToDistrictPartyList(party& _federalParty_);

	void add1ToPopulationCount();

	void add1ToVoteCount();

	int howManyRepresentative() const;

	int printFinnallyRepresentativeList();

	//in case of not enogh representative the function return -1
	//in case of the district parrty didnt found the function return 0
	//else the fuicntion return 1 and print finally representive list of the districtParty
	//the function print else the number and percent votes of the party
	int printFinnallyRepresentativeList(int serialNumberOfParty, int partysElectors) const;

	// in case of not enogh representative the function return -1
		//else the fuicntion return 1 and print finally representive list of the districtParty
	int printFinnallyRepresentativeList(districtParty& _party, int partysElectors) const;

	void printDistrictType() const;

	static void sortResultArray(result* arr, int arrSize)
	{
		for (int i = 0; i < arrSize; i++)
		{
			for (int j = i; j < arrSize; j++)
			{
				if ((arr[i]._electors) < (arr[j]._electors))
				{
					result temp;
					temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
	}

	friend ostream& operator<<(ostream& os, const district& _district)
	{
		os << "Name :" << _district._name << endl;
		os << "Serial Number :" << _district._serialNumber << endl;
		os << "Representative:" << _district._representative << endl;
		os << "district type :";
		_district.printDistrictType();
		os << endl;
		return os;
	}
	//the function save:
	//the appearance
	//the name length with the '\0'
	//the name string
	int saveDistrict(ofstream& f) const;

	virtual int save(ofstream& f)const = 0;



};


class dividedDistrict : public district
{
private:

public:
	dividedDistrict(const char* _name_, const int _serialNumber_, const int _representative_);//strcture
	dividedDistrict(ifstream& f);//strcture for load file

	//my friend//
	friend class electionWithoutDistricts;
	//

	result* getResult();

	int save(ofstream& f) const;

};



class uniformDistrict : public district
{
private:

public:


	uniformDistrict(const char* _name_, const int _serialNumber_, const int _representative_);//structure

	uniformDistrict(ifstream& f);//structure for load file

	result* getResult();

	int save(ofstream& f) const;
};


