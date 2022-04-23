#include "election.h"
electionRegular::electionRegular(date _date_) :election(_date_)
{
}

electionRegular::~electionRegular()
{
	delete resArr;
}

const districtList& electionRegular::getDistrictList() const
{
	return _districtList;
}

const citizenList& electionRegular::getCitizenList() const
{
	return _citizenList;
}

int electionRegular::printDistrictResult()
{

	districtNode* p;
	p = _districtList._head;


	while (p)
	{
		election::printDistrictResult(*(p->_data));
		p = p->_next;
	}
	return 1;
}

void electionRegular::calculateFederalResult()
{
	bulidResArr();
	districtNode* p = _districtList._head;


	while (p)
	{

		result* districtResult = p->_data->getResult();

		if (districtResult)
		{
			addToResArray(districtResult, p->_data->getDistrictType());
		}
		p = p->_next;
	}
	district::sortResultArray(resArr, resArrSize);

}

void electionRegular::addToResArray(result* districtResultArr, districtType _districtType_)
{
	if (_districtType_ == districtType::divided)
	{



		for (int i = 0; i < resArrSize; i++)
		{
			addToPartyRes(districtResultArr[i]);
		}
	}
	else
	{
		addToPartyRes(districtResultArr[0]);
	}

}

void electionRegular::addToPartyRes(result partyResult)
{
	int index = findPartyIndexInResultArrayBySerialNumber(partyResult._serialNumberOfParty);
	resArr[index].addElectors(partyResult._electors);
}

int electionRegular::printRepresentativeOfPartyInAllThedistricts(int serialNumberOfParty) const
{
	return _districtList.printRepresentativeOfSpecificPartyForAllTheDistricts(serialNumberOfParty);
}

int electionRegular::findPartyIndexInResultArrayBySerialNumber(int _serialNumber_)
{
	for (int i = 0; i < resArrSize; i++)
	{
		if ((resArr[i]._serialNumberOfParty) == _serialNumber_)
		{
			return i;
		}
	}
	return -1;
}

district& electionRegular::getDistrict(int serialNumberOfDistrict, int* res)
{
	return _districtList.findDistrict(serialNumberOfDistrict, res);
}

districtParty& electionRegular::getDistrictParty(int serialNumberOfDistrict, int serialNumberOfParty, int* res)
{
	return _districtList.findDistrictParty(serialNumberOfDistrict, serialNumberOfParty, res);
}

party& electionRegular::getParty(int serialNumberOfParty, int* res)
{
	return _partyList.getParty(serialNumberOfParty, res);

}

int electionRegular::addCitizen(const char* name, const char* id, int birthYear, int serialNumberOfDistrict)
{
	int districtFound;

	district& refToDistrict = getDistrict(serialNumberOfDistrict, &districtFound);


	if (districtFound == 0)
	{
		return -1;
	}
	else
	{
		refToDistrict.add1ToPopulationCount();
		return(_citizenList.addCitizen(name, id, birthYear, refToDistrict, refToDistrict.getName()));
	}
}

int electionRegular::addDistrict(const char* name, int numOfRepresentative, int type)
{

	int returnValue = _districtList.addDistrict(name, numOfRepresentative, type);

	return returnValue;
}

int electionRegular::addParty(const char* partyName, const char* idOfresidentalStumble)
{
	int residentalStumbeleFound;
	citizen& residentalStumble = _citizenList.searchCitizen(idOfresidentalStumble, &residentalStumbeleFound);

	if (residentalStumbeleFound == 0)
	{
		return (-2);
	}
	else if (residentalStumble.__representine())
	{
		return (-1);
	}
	else
	{
		party& newParty = _partyList.addParty(partyName, residentalStumble, residentalStumble.getName());

		addPartyToAllTheDistrictsPartyList(newParty);

		return newParty.getSerialNumber();
	}
}

int electionRegular::addRepresentative(const char* idOfRepresentative, int serialNumberOfParty, int serialNumberOfDistrict)
{
	int districtPartyFound;
	districtParty& _districtParty_ = getDistrictParty(serialNumberOfDistrict, serialNumberOfParty, &districtPartyFound);


	if (districtPartyFound == (-1))
	{
		return (-3);
	}
	else if (districtPartyFound == (0))
	{
		return (-2);
	}
	else
	{
		int representativeFound;
		citizen& _newRepresentative_ = _citizenList.searchCitizen(idOfRepresentative, &representativeFound);

		if (representativeFound == 0)
		{
			return (-1);
		}
		else if (_newRepresentative_.__representine())
		{
			return (0);
		}
		else
		{
			_districtParty_.addRepresentative(_newRepresentative_);
			return 1;
		}
	}

}

void electionRegular::addPartyToAllTheDistrictsPartyList(party& newParty)
{
	_districtList.addPartyToAllDistrictsParties(newParty);
}

void electionRegular::setTheSerialNumberCounterOfDistricts(int newSerialNumber)
{
	_districtList.setTheSerialNumberCounter(newSerialNumber);
}

int electionRegular::loadCitizensList(ifstream& f, int citizensCount)
{
	for (int i = 0; i < citizensCount; i++)
	{

		int serialNumberOfDistrict;

		f.read(READ(&serialNumberOfDistrict), sizeof(int));
		//

		int birthYear;

		f.read(READ(&birthYear), sizeof(int));

		//

		bool _upTo18_;

		f.read(READ(&_upTo18_), sizeof(bool));

		//



		//
		int districtFound;
		district& _district = getDistrict(serialNumberOfDistrict, &districtFound);

		if (districtFound == 1)
		{
			const char* districtName = _district.getName();

			citizen* newCitizen = new citizen(f, _district, districtName, birthYear, _upTo18_);

			_citizenList.addToList(newCitizen);
		}
	}
	return 1;
}

bool electionRegular::regularElection()const
{
	return true;
}

int electionRegular::loadDistrictList(ifstream& f, int districtCount)
{
	_districtList.load(f, districtCount);

	return 1;
}

int electionRegular::loadCounters(ifstream& f, int* districtsCount, int* partiesCount, int* citizensCount)
{
	f.read(READ(districtsCount), sizeof(int));

	f.read(READ(partiesCount), sizeof(int));

	f.read(READ(citizensCount), sizeof(int));

	return 1;
}

int electionRegular::saveCounters(ofstream& f)const
{
	_districtList.saveDistrictsCounter(f);

	_partyList.savePartiesCounter(f);

	_citizenList.saveCitizenCount(f);

	return 1;
}

int electionRegular::saveDistrictList(ofstream& f)const
{
	_districtList.saveDistrictList(f);

	return 1;

}

int electionRegular::loadPartyDistrictList(ifstream& f, int partyCount)
{

	districtNode* p = _districtList._head;
	while (p)
	{
		int garbage;
		f.read(READ(&garbage), sizeof(int));

		loadPartyDistrictListHelper(f, *(p->_data), partyCount);

		p = p->_next;

	}

	return 1;
}

int electionRegular::savePartiesDistrictList(ofstream& f) const
{
	districtNode* p = _districtList._head;

	while (p)
	{
		int districtSerialNumber = p->_data->getSerialNumber();

		f.write(WRITE(&districtSerialNumber), sizeof(int));

		savePartiesDistrictListHelper(f, p->_data);

		p = p->_next;
	}

	return 1;
}

int electionRegular::SaveSerialNumbers(ofstream& f) const
{
	_districtList.saveSerialNumber(f);

	_partyList.saveTheSerialNumber(f);

	return 1;
}

int electionRegular::loadSerialNumbers(ifstream& f)
{
	_districtList.loadSerialNumber(f);

	_partyList.loadSerialNumber(f);

	return 1;
}