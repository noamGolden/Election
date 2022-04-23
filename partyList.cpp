#include "partyList.h"
static int _serialNumber = -1;

partyList::partyList()
{
	makeEmptyList();
}

partyList::~partyList()
{
	deleteList();
}

int partyList::getPartyCounter() const
{
	return partyCount;
}

party& partyList::getParty(int _serialNumber_, int* res)
{
	partyNode* p = _head;

	while (p)
	{
		if (p->_data->getSerialNumber() == _serialNumber_)
		{
			*res = 1;
			return *(p->_data);
		}
		p = p->_next;
	}
	*res = 0;
}

party& partyList::addParty(const char* _name_, citizen& _residentialStumble_, const char* _residentalStumbleName_)
{
	_serialNumber++;
	party* newParty = new party(_serialNumber, _residentialStumble_, _name_, _residentalStumbleName_);
	addToList(newParty);
	return *newParty;
}



int partyList::saveTheSerialNumber(ofstream& f) const
{
	f.write(WRITE(&_serialNumber), sizeof(int));
	return 1;

}

int partyList::loadSerialNumber(ifstream& f)
{
	f.read(READ(&_serialNumber), sizeof(int));

	return 1;
}


int partyList::savePartiesCounter(ofstream& f) const
{
	f.write(WRITE(&partyCount), sizeof(int));

	return 1;
}

void partyList::setTheSerialNumberCounter(const int newSerialNumber)
{
	_serialNumber = newSerialNumber;
}


////////List//////////////////start/////////////////////////////////////
void partyList::addToList(party* _party_)
{
	partyNode* newNode = new partyNode(_party_);
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
bool partyList::isEmpty()
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
void partyList::makeEmptyList()
{
	_head = nullptr;
	_tail = nullptr;
	partyCount = 0;
}
void partyList::deleteList()
{
	partyNode* temp;
	while (_head)
	{
		temp = _head;
		delete _head->_data;

		_head = _head->_next;
		delete temp;
	}
}
/////////list////////////////end/////////////