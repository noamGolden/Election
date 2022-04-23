#include "districtList.h"

static int serialNumber = -1;

districtList::districtList()
{
	makeEmptyList();

	districtCount = 0;
}

districtList::~districtList()
{
	deleteList();
}

void districtList::addPartyToAllDistrictsParties(party& _federalParty_)
{
	districtNode* p;

	p = _head;
	while (p)
	{
		p->_data->addToDistrictPartyList(_federalParty_);

		p = p->_next;
	}
}

districtParty& districtList::findDistrictParty(int serialNumberOfDistrict, int serialNumberOfParty, int* res)
{
	int found;
	district& foundDis = findDistrict(serialNumberOfDistrict, &found);
	if (found == 0)
	{
		*res = -1;
	}
	else
	{
		return(foundDis.findDistrictPartyBySerialNumber(serialNumberOfParty, res));
	}
};

district& districtList::findDistrict(int serialNumber, int* res)
{
	districtNode* p;
	p = _head;

	while (p)
	{

		if (p->_data->getSerialNumber() == serialNumber)
		{
			*res = 1;
			return *(p->_data);
		}
		p = p->_next;
	}
	*res = 0;
}

int districtList::addDistrict(const char* name, const int numOfRepresntative, int type)
{
	serialNumber++;

	district* newDistrict;

	if (type == 1)
	{
		newDistrict = new uniformDistrict(name, serialNumber, numOfRepresntative);
	}
	else
	{
		newDistrict = new dividedDistrict(name, serialNumber, numOfRepresntative);
	}
	addToList(newDistrict);
	return serialNumber;
}

int districtList::printRepresentativeOfSpecificPartyForAllTheDistricts(int serialNumberOfParty) const
{
	districtNode* p = _head;

	while (p)
	{
		int partyFound = p->_data->printRepresentativeList(serialNumberOfParty);
		cout << endl;
		if (partyFound == 0)
		{
			return 0;
		}
		p = p->_next;
	}
	cout << endl;
	return 1;
}


////load/////////////////////

int districtList::load(ifstream& f, int districtCount)
{
	for (int i = 0; i < districtCount; i++)
	{
		districtType type;
		district* newDistrict;

		f.read(READ(&type), sizeof(int));

		if (type == districtType::uniform)
		{

			newDistrict = new uniformDistrict(f);



		}
		else
		{

			newDistrict = new dividedDistrict(f);



		}
		addToList(newDistrict);
	}

	return 1;
}

int districtList::loadSerialNumber(ifstream& f)
{
	f.read(READ(&serialNumber), sizeof(int));

	return 1;
}
/////////////////////////////

////save/////////////////////
void districtList::saveDistrictList(ofstream& f)const
{
	districtNode* p = _head;

	while (p)
	{
		p->_data->save(f);

		p = p->_next;
	}


}

void districtList::setTheSerialNumberCounter(const int newSerialNumber)
{
	serialNumber = newSerialNumber;
}

void districtList::saveDistrictsCounter(ofstream& f) const
{

	f.write(WRITE(&districtCount), sizeof(int));
}

int districtList::saveSerialNumber(ofstream& f) const
{

	f.write(WRITE(&serialNumber), sizeof(int));

	return 1;
}

////////////////////////////////

////////List//////////////////start/////////////////////////////////////
void districtList::addToList(district* _district_)
{
	districtNode* newNode = new districtNode(_district_);
	if (isEmpty())
	{
		_head = newNode;
	}
	else
	{
		_tail->_next = newNode;
	}
	_tail = newNode;
	districtCount++;
}
bool districtList::isEmpty()
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
void districtList::makeEmptyList()
{
	_head = nullptr;
	_tail = nullptr;
}
void districtList::deleteList()
{
	districtNode* temp;
	while (_head)
	{
		temp = _head;

		delete _head->_data;

		_head = _head->_next;

		delete temp;
	}
}
/////////list////////////////end/////////////