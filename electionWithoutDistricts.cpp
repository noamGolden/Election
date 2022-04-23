#include "election.h"

electionWithoutDistricts::electionWithoutDistricts(date _date_, int _numOfRepresentative_) :election(_date_)
, _country(new dividedDistrict("Country", -10, _numOfRepresentative_))
{

}

int electionWithoutDistricts::printRepresentativeOfPartyInAllThedistricts(int serialNumberOfParty) const
{
	return(_country->printRepresentativeList(serialNumberOfParty));
}

district& electionWithoutDistricts::getDistrict(int serialNumberOfDistrict, int* res)
{
	*res = (-1);
	return *_country;
}

int electionWithoutDistricts::addDistrict(const char* name, int numOfRepresentative, int type)
{
	return -1;
}

party& electionWithoutDistricts::getParty(int serialNumberOfParty, int* res)
{

	return _partyList.getParty(serialNumberOfParty, res);
}

void electionWithoutDistricts::calculateFederalResult()
{
	bulidResArr();
	resArr = _country->getResult();
}

int electionWithoutDistricts::addCitizen(const char* name, const char* id, int birthYear, int serialNumberOfDistrict)
{
	_country->add1ToPopulationCount();

	return(_citizenList.addCitizen(name, id, birthYear, *_country, "country"));
}

int electionWithoutDistricts::addParty(const char* partyName, const char* idOfresidentalStumble)
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
		addPartyToCountryDistrictPartyList(newParty);
		return newParty.getSerialNumber();
	}
}

void electionWithoutDistricts::addPartyToCountryDistrictPartyList(party& newParty)
{
	_country->addToDistrictPartyList(newParty);
}

int electionWithoutDistricts::addRepresentative(const char* idOfRepresentative, int serialNumberOfParty, int serialNumberOfDistrict)
{
	int partyFound;
	districtParty& _party_ = _country->findDistrictPartyBySerialNumber(serialNumberOfParty, &partyFound);

	if (partyFound == 0)
	{
		return (-2);
	}
	else
	{

		int representativeFound;
		citizen& _newRepresentative_ = getCitizen(idOfRepresentative, &representativeFound);

		if (representativeFound == 0)
		{
			return (-1);
		}
		else
		{
			if (_newRepresentative_.__representine())
			{
				return 0;
			}
			else
			{
				_party_.addRepresentative(_newRepresentative_);
			}
		}
	}
}

int electionWithoutDistricts::printDistrictResult()
{
	election::printDistrictResult(*_country);
	return 0;
}

districtParty& electionWithoutDistricts::getDistrictParty(int serialNumberOfDistrict, int serialNumberOfParty, int* res)
{
	return (_country->findDistrictPartyBySerialNumber(serialNumberOfParty, res));

}

bool electionWithoutDistricts::regularElection()const
{
	return false;
}


////////////////////load//////////////////////
int electionWithoutDistricts::loadCitizensList(ifstream& f, int citizensCount)
{
	for (int i = 0; i < citizensCount; i++)
	{

		int garbage;
		f.read(READ(&garbage), sizeof(int));

		//
		int birthYear;
		f.read(READ(&birthYear), sizeof(int));

		//
		bool upTo18;
		f.read(READ(&upTo18), sizeof(bool));

		//

		citizen* newCitizen = new citizen(f, *_country, "country", birthYear, upTo18);

		_citizenList.addToList(newCitizen);
	}

	return 1;
}

int electionWithoutDistricts::loadPartyDistrictList(ifstream& f, int partyCount)
{
	loadPartyDistrictListHelper(f, *_country, partyCount);

	return 1;
}

int electionWithoutDistricts::loadSerialNumbers(ifstream& f)
{

	_partyList.loadSerialNumber(f);

	return 1;
}
////////////////////////////////////////////

//////////////////save//////////////////////
int electionWithoutDistricts::saveCounters(ofstream& f)const
{

	_partyList.savePartiesCounter(f);

	_citizenList.saveCitizenCount(f);

	return 1;
}

int electionWithoutDistricts::loadDistrictList(ifstream& f, int districtCount)//maybe will make a proble
{
	int _serialNumber;

	int _representative;

	int _populationCount;

	int _voteCount;

	f.read(READ(&_serialNumber), sizeof(int));

	f.read(READ(&_representative), sizeof(int));

	f.read(READ(&_populationCount), sizeof(int));

	f.read(READ(&_voteCount), sizeof(int));

	_country = new dividedDistrict("country", _serialNumber, _representative);

	_country->setVoteCount(_voteCount);

	_country->setPupaltionCount(_populationCount);

	return 1;
}

int electionWithoutDistricts::loadCounters(ifstream& f, int* districtsCount, int* partiesCount, int* citizensCount)
{
	*districtsCount = 1;

	f.read(READ(partiesCount), sizeof(int));

	f.read(READ(citizensCount), sizeof(int));

	return 1;
}

int electionWithoutDistricts::saveDistrictList(ofstream& f)const
{


	int _serialNumber = _country->getSerialNumber();

	int _representative = _country->getNumberOfRepresentative();

	int _populationCount = _country->getpopulationCount();

	int _voteCount = _country->getVoteCount();

	f.write(WRITE(&_serialNumber), sizeof(int));

	f.write(WRITE(&_representative), sizeof(int));

	f.write(WRITE(&_populationCount), sizeof(int));

	f.write(WRITE(&_voteCount), sizeof(int));

	return 1;
}

int electionWithoutDistricts::savePartiesDistrictList(ofstream& f) const
{
	savePartiesDistrictListHelper(f, _country);

	return 1;
}

int electionWithoutDistricts::SaveSerialNumbers(ofstream& f)const
{
	_partyList.saveTheSerialNumber(f);

	return 1;
}

const citizenList& electionWithoutDistricts::getCitizenList() const
{
	return _citizenList;
}
//////////////////////////////////////////////////////////