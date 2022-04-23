#include "district.h"
#include <string.h>
district::district(const char* _name_, const int _serialNumber_, const int _representative_, districtType _type_) :
	_serialNumber(_serialNumber_), _representative(_representative_), _type(_type_)
{
	_name = new char[strlen(_name_) + 1];

	memcpy(_name, _name_, strlen(_name_) + 1);

	_populationCount = 0;
	_voteCount = 0;

	makeEmptyList();

	resArr = nullptr;
	resArrSize = 0;
}

district::district(ifstream& f, districtType _type_) :
	_name(nullptr), _serialNumber(-1), _representative(-1), _type(_type_)
{
	f.read(READ(this), sizeof(*this));

	_populationCount = 0;

	_voteCount = 0;

	makeEmptyList();

	resArr = nullptr;

	resArrSize = 0;
}

district::~district()
{
	delete resArr;

	delete _name;


	deleteList();
}

int district::saveDistrict(ofstream& f) const
{
	f.write(WRITE(this), sizeof(*this));

	return 1;
}

int district::getSerialNumber() const
{
	return _serialNumber;
}

int district::setVoteCount(int newVoteCount)
{
	_voteCount = newVoteCount;

	return 1;
}

int district::setPupaltionCount(int newCount)
{
	_populationCount = newCount;

	return 1;
}

const char* district::getName() const
{
	return _name;
}

int district::printRepresentativeList(int serialNumberOfParty) const
{
	int partyFound;
	districtParty& _party_ = findDistrictPartyBySerialNumber(serialNumberOfParty, &partyFound);
	if (partyFound == 1)
	{
		cout << "district:" << _name << endl;
		_party_.printRepresentativeList();
	}
	return partyFound;

}

void district::add1ToPopulationCount()
{
	_populationCount++;

}

void district::add1ToVoteCount()
{
	_voteCount++;
}

districtParty& district::findDistrictPartyBySerialNumber(int partySerialNumber, int* res) const
{
	districtPartyNode* p;
	p = _head;

	while (p)
	{
		const party& _party = p->_data->_getFederalParty();
		int tempSerialNumber;
		tempSerialNumber = _party.getSerialNumber();
		if (tempSerialNumber == partySerialNumber)
		{
			*res = 1;
			return *(p->_data);
		}
		p = p->_next;
	}
	*res = 0;
}

void district::addToDistrictPartyList(party& _federalParty_)
{

	districtParty* newDistrictParty = new districtParty(_federalParty_, *this);
	addToList(newDistrictParty);

}

void district::makeElectorsDivisionArray()
{
	if (resArr)
	{
		delete resArr;
	}
	if (_voteCount > 0)
	{
		float valueOfVote = calculateValueOfVote();

		resArrSize = partyCount;

		resArr = new result[resArrSize];

		int electorsGivenCount = 0;

		float* carry = new float[resArrSize];

		districtPartyNode* p = _head;


		for (int i = 0; i < resArrSize; i++, p = p->_next)
		{
			resArr[i]._serialNumberOfParty = p->_data->_getFederalParty().getSerialNumber();
			electorsGivenCount += calculateElectorsAndCarry(resArr[i], carry[i], (p->_data->__vote()) * valueOfVote);
		}

		dividedRemainingElectors(resArr, carry, resArrSize, _representative - electorsGivenCount);

		sortResultArray(resArr, resArrSize);
	}
}

int district::__voteCount() const
{
	return _voteCount;
}

int district::printFinnallyRepresentativeList()
{
	if (_voteCount > 0)
	{
		makeElectorsDivisionArray();

		for (int i = 0; i < resArrSize; i++)
		{
			printFinnallyRepresentativeList(resArr[i]._serialNumberOfParty, resArr[i]._electors);
		}
	}
	else
	{
		cout << "no vote for this district" << endl;
	}
	return 1;
}

int district::printFinnallyRepresentativeList(int serialNumberOfParty, int partyElectors) const
{
	int partyFound;

	districtParty& _party = findDistrictPartyBySerialNumber(serialNumberOfParty, &partyFound);

	if (partyFound == 1)
	{
		printFinnallyRepresentativeList(_party, partyElectors);
	}

	return 1;
}

int district::printFinnallyRepresentativeList(districtParty& _party, int partyElectors) const
{
	int enoughRepresentive;
	cout << "Party Name:" << _party._getFederalParty().getName() << endl;

	_party.printLimitedRepresentativeList(partyElectors, &enoughRepresentive);

	cout << "Number Of Votes  :  " << getDistrictPartyNumOfVotes(_party) << endl;

	cout << "percent Of Votes  :  " << getDistrictPartyPercentageOfVotes(_party) << "%" << endl;

	cout << '.' << endl << '.' << endl;
	if (enoughRepresentive == 0)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int district::howManyRepresentative() const
{
	return _representative;
}

void district::dividedRemainingElectors(result* resultArr, float* carryArr, int sizeOfArrays, int remainingElectors)
{
	while (remainingElectors > 0)
	{
		int indexToAdd = findMax(carryArr, sizeOfArrays);

		carryArr[indexToAdd] = 0;

		resultArr[indexToAdd].addElectors(1);

		remainingElectors--;
	}
}

int district::calculateElectorsAndCarry(result& temp, float& carry, float votes)
{
	int BottomWholeValue = Truncate(votes);

	temp.addElectors(BottomWholeValue);

	carry = votes - BottomWholeValue;

	return BottomWholeValue;
}

float district::calculateValueOfVote()
{
	float numOfElectos = _representative;

	float numOfVotes = _voteCount;

	return numOfElectos / numOfVotes;
}

districtType district::getDistrictType() const
{
	return _type;
}

float district::getDistrictPartyPercentageOfVotes(int serialNumberOfParty) const
{
	int partyFound;
	const districtParty& _party_ = findDistrictPartyBySerialNumber(serialNumberOfParty, &partyFound);
	if (partyFound == 0)
	{
		return -1;
	}
	else
	{
		return getDistrictPartyPercentageOfVotes(_party_);
	}
}

float district::getDistrictPartyPercentageOfVotes(const districtParty& _party_) const
{
	float districtPartyNumOfVotes = getDistrictPartyNumOfVotes(_party_);

	float numOfVotesInTheDistrict = _voteCount;

	float res = districtPartyNumOfVotes / numOfVotesInTheDistrict;

	return res * 100;
}

int district::getDistrictPartyNumOfVotes(int serialNumberOfParty) const
{
	int partyFound;
	const districtParty& _party_ = findDistrictPartyBySerialNumber(serialNumberOfParty, &partyFound);
	if (partyFound == 0)
	{
		return -1;
	}
	else
	{
		return getDistrictPartyNumOfVotes(_party_);
	}
}

int district::getDistrictPartyNumOfVotes(const districtParty& _party_) const
{

	return _party_.__vote();

}

float district::getTurnOutInTheDistrict() const
{
	float numOfVotes = _voteCount;

	float numOfPepole = _populationCount;

	float res = numOfVotes / numOfPepole;

	return res * 100;

}

int district::getNumberOfRepresentative()const
{
	return _representative;
}

int district::getpopulationCount()const
{
	return _populationCount;
}

int district::getVoteCount()const
{
	return _voteCount;
}

void district::printDistrictType() const
{
	if (_type == districtType::divided)
	{
		cout << "divided";
	}
	else
	{
		cout << "uniform";
	}
}


///list/////////start
void district::addToList(districtParty* newDistrictParty)
{
	districtPartyNode* newNode = new districtPartyNode(newDistrictParty);


	if (isEmpty())
	{
		_head = newNode;
	}
	else
	{
		_tail->_next = newNode;
	}
	_tail = newNode;
	partyCount++;
}
bool district::isEmpty()
{
	if (_head)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void district::makeEmptyList()
{
	_head = nullptr;
	_tail = nullptr;
	partyCount = 0;
}
void district::deleteList()
{
	districtPartyNode* temp;
	while (_head)
	{
		temp = _head;
		delete _head->_data;

		_head = _head->_next;
		delete temp;
	}
	partyCount = 0;
}
/////////list////////////////end/////////////
