#include "election.h"
election::election(date _date_) :_date(_date_), _citizenList(_date_)
{
	resArr = nullptr;
	resArrSize = 0;

}

election::~election()
{

}

int election::addVote(const char* id, int serialNumberOfParty)
{
	int partyFound;
	party& _party_ = getParty(serialNumberOfParty, &partyFound);

	if (partyFound == 0)
	{
		return (-3);
	}
	else
	{
		int citizenFound;
		citizen& _citizen_ = getCitizen(id, &citizenFound);
		if (citizenFound == 0)
		{
			return (-2);
		}
		else
		{
			int voteStatusOfCitizen = _citizen_.__vote();
			if (voteStatusOfCitizen == (-1))
			{
				return 0;
			}
			else if (voteStatusOfCitizen == 1)
			{
				return (-1);
			}
			else
			{
				addVoteToFederalParty(_party_);
				addVoteToDistrictParty(_party_, _citizen_.getDistrict());
			}
		}
	}
}

void election::addVoteToFederalParty(party& _party_)
{
	_party_.add1Vote();
}

void election::addVoteToDistrictParty(party& _party_, district& _district_)
{
	int temp;
	districtParty& _districtParty_ = _district_.findDistrictPartyBySerialNumber(_party_.getSerialNumber(), &temp);

	_districtParty_.add1VoteToDistrictParty();

	_district_.add1ToVoteCount();

}

citizen& election::getCitizen(const char* id, int* res)
{
	return _citizenList.searchCitizen(id, res);
}

void election::bulidResArr()
{
	resArrSize = _partyList.getPartyCounter();
	if (resArr)
	{
		delete resArr;
	}

	resArr = new result[resArrSize];

	partyNode* p = _partyList._head;

	for (int i = 0; i < resArrSize; i++, p = p->_next)
	{
		resArr[i]._serialNumberOfParty = p->_data->getSerialNumber();
	}
}

void election::disPlayResult()
{
	cout << "Election's date: " << _date << endl;

	cout << "District result:" << endl << "________" << endl;

	printDistrictResult();

	cout << "________________________________________________" << endl;

	cout << "parties result" << endl << "________" << endl;

	printPartiesResult();

}

int election::printPartiesResult()
{
	calculateFederalResult();

	for (int i = 0; i < resArrSize; i++)
	{
		printPartyResult(resArr[i]);
	}
	return 1;
}

int election::printPartyResult(result _result)
{
	printPartyResult(_result._serialNumberOfParty, _result._electors);
	return 1;
}

int election::printPartyResult(int serialNumberOfParty, int electors)
{
	int partyFound;

	party& _party = getParty(serialNumberOfParty, &partyFound);

	printPartyResult(_party, electors);

	return 1;
}

int election::printPartyResult(party& _party, int electors)
{
	cout << _party;

	cout << "electors: " << electors << endl;

	cout << "Federal Votes:   " << _party.__vote() << endl << endl;

	return 1;
}

int election::printDistrictResult(int serialNumberOfDistrict)
{
	int districtFound;

	district& _district = getDistrict(serialNumberOfDistrict, &districtFound);

	if (districtFound == 1)
	{
		printDistrictResult(_district);
	}
	return districtFound;
}

int election::printDistrictResult(district& _district)
{
	cout << "***************" << endl;
	cout << "Name: " << _district.getName() << endl;

	cout << "Representative: " << _district.howManyRepresentative() << endl;

	cout << "***************" << endl;

	printElectorsDividedOfDistrict(_district);

	cout << "********Representative List*******" << endl;


	printFinallyRepresentativeList(_district);

	printTurnOut(_district);

	cout << "***************" << endl << endl << endl;
	return 1;

}

int election::printTurnOut(district& _district)
{
	if (_district.__voteCount() > 0)
	{
		cout << "turn out of the district : " << _district.getTurnOutInTheDistrict() << "%" << endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

int election::printFinallyRepresentativeList(district& _district)
{
	_district.printFinnallyRepresentativeList();

	return 1;
}

int election::printElectorsDividedOfDistrict(int serialNumberOfDistrict)
{
	int districtFound;

	district& _district = getDistrict(serialNumberOfDistrict, &districtFound);

	if (districtFound == 1)
	{
		printElectorsDividedOfDistrict(_district);
	}

	return districtFound;
}

int election::printElectorsDividedOfDistrict(district& _district)
{
	resArrSize = _partyList.partyCount;

	if (_district.getDistrictType() == districtType::divided)
	{
		printElectorsDividedOfDividedDistrict(_district);
	}
	else
	{
		printElectorsDividedOfUniformDistrict(_district);
	}

	return 1;
}

int election::printElectorsDividedOfDividedDistrict(district& _district)
{
	result* districtResult = _district.getResult();
	if (districtResult)
	{
		bool stop = false;

		for (int i = 0; (i < resArrSize) && (!stop); i++)
		{
			int partyFound;//have to be always 1

			cout << "candiate for primer minister :" << getParty(districtResult[i]._serialNumberOfParty, &partyFound).getCandidateOfPrimerMinisterName() << endl;
			cout << "electors:" << districtResult[i]._electors << endl << endl;

			if ((districtResult[i + 1]._electors) == 0)
			{
				stop = true;
			}
		}
		return 1;
	}
}

int election::printElectorsDividedOfUniformDistrict(district& _district)
{
	result* districtResult = _district.getResult();

	if (districtResult)
	{

		int partyFound;//have to be 1

		cout << "candiate for primer minister :" << getParty(districtResult[0]._serialNumberOfParty, &partyFound).getCandidateOfPrimerMinisterName() << endl;
		cout << "electors:" << districtResult[0]._electors << endl << endl;

		return 1;
	}
}

int election::getCitizensCounter() const
{
	return _citizenList.getCitizensCounter();
}

int election::getPartiesCounter()const
{
	return _partyList.getPartyCounter();
}

void election::displayAllParties() const
{
	partyNode* p = _partyList._head;

	while (p)
	{
		cout << *(p->_data) << endl;
		printRepresentativeOfPartyInAllThedistricts(p->_data->getSerialNumber());

		p = p->_next;
	}
}

void election::setTheSerialNumberCounterOfParties(int newSerialNumber)
{
	_partyList.setTheSerialNumberCounter(newSerialNumber);
}

////////////////////////Load//////////////////////////
int election::load(ifstream& f)
{
	loadDate(f);

	int districtsCount;

	int partiesCount;

	int citizensCount;

	loadCounters(f, &districtsCount, &partiesCount, &citizensCount);

	loadDistrictList(f, districtsCount);

	loadCitizensList(f, citizensCount);

	loadPartyList(f, partiesCount);

	loadPartyDistrictList(f, partiesCount);

	loadSerialNumbers(f);


	return 1;
}

int election::loadDate(ifstream& f)
{
	f.read(READ(&_date), sizeof(date));

	return 1;
}

int election::loadPartyList(ifstream& f, int partyCounter)
{
	for (int i = 0; i < partyCounter; i++)
	{
		int idSize;

		f.read(READ(&idSize), sizeof(int));
		//
		char* id = new char[idSize];

		f.read(READ(id), idSize * sizeof(char));

		int citizenFound;

		citizen& _candidate = getCitizen(id, &citizenFound);
		//
		int serialNumber;

		f.read(READ(&serialNumber), sizeof(int));
		//
		party* newParty = new party(f, _candidate, serialNumber);

		_partyList.addToList(newParty);
		//
		delete[]id;
	}
	return 1;
}


//////////////////////////////////////////////////////

///////////////////////save///////////////////////////
int election::save(ofstream& f)const
{
	saveElectionType(f);

	saveDate(f);

	saveCounters(f);

	saveDistrictList(f);

	saveCitizensList(f);

	savePartyList(f);

	savePartiesDistrictList(f);

	SaveSerialNumbers(f);


	return 1;
}

int election::saveElectionType(ofstream& f)const
{
	int electionType;

	if (regularElection())
	{
		electionType = 1;
	}

	else
	{
		electionType = 0;
	}

	f.write(WRITE(&electionType), sizeof(int));

	return 1;
}

int election::saveDate(ofstream& f)const
{

	f.write(WRITE(&_date), sizeof(date));

	return 1;
}

int election::savePartyList(ofstream& f)const
{
	partyNode* p = _partyList._head;

	while (p)
	{
		p->_data->getCandidateOfPrimerMinister().saveId(f);

		p->_data->saveParty(f);

		p = p->_next;
	}

	return 1;
}

int election::saveCitizensList(ofstream& f) const
{
	citizenNode* p = _citizenList._head;

	while (p)
	{
		int serialNumberOfDistrict = p->_data->getDistrict().getSerialNumber();

		f.write(WRITE(&serialNumberOfDistrict), sizeof(int));

		p->_data->saveCitizen(f);

		p = p->_next;
	}

	return 1;
}

int election::loadPartyDistrictListHelper(ifstream& f, district& _district, int partyCounter)
{
	for (int i = 0; i < partyCounter; i++)
	{
		int partySerialNumber;

		f.read(READ(&partySerialNumber), sizeof(int));

		int partyFound;
		party& federalParty = getParty(partySerialNumber, &partyFound);

		districtParty* newDistrictParty = new districtParty(federalParty, _district);

		_district.addToList(newDistrictParty);
		//
		int vote;
		f.read(READ(&vote), sizeof(int));

		newDistrictParty->setVote(vote);
		//
		int represntativeCount;

		f.read(READ(&represntativeCount), sizeof(int));

		newDistrictParty->setRepresentativeCount(represntativeCount);

		//

		loadRepresentativeList(f, *newDistrictParty);
	}
	return 1;
}

int election::savePartiesDistrictListHelper(ofstream& f, const district* _district) const
{
	districtPartyNode* p = _district->_head;

	while (p)
	{
		int partySerialNumber = p->_data->_getFederalParty().getSerialNumber();

		f.write(WRITE(&partySerialNumber), sizeof(int));

		p->_data->saveDistrictParty(f);

		saveRepresentativeList(f, p->_data);

		p = p->_next;
	}

	return 1;
}

int election::loadRepresentativeList(ifstream& f, districtParty& newParty)
{
	int representativeCount = newParty.getRepresentativeCount();

	for (int i = 0; i < representativeCount; i++)
	{
		int idSize;

		f.read(READ(&idSize), sizeof(int));

		char* id = new char[idSize]; /////

		f.read(READ(id), idSize * sizeof(char));

		int citizenFound;
		citizen& newRepresentative = getCitizen(id, &citizenFound);


		newParty.addRepresentative(newRepresentative);
	}
	return 1;
}

int election::saveRepresentativeList(ofstream& f, districtParty* _districtParty)const
{
	representativeNode* p = _districtParty->_head;

	while (p)
	{
		p->_data.saveId(f);

		p = p->_next;
	}

	return 1;
}

//////////////////////////////////////////////////////