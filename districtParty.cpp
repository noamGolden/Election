#include "districtParty.h"
#include <string.h>

districtParty::districtParty(party& _federalParty_, district& _district_) :
	_federalParty(_federalParty_), _district(_district_)
{
	_vote = 0;
	makeEmptyList();

}

districtParty::~districtParty()
{
	//deleteList();
}

void districtParty::add1VoteToDistrictParty()
{
	_vote++;
}

int districtParty::__vote() const
{
	return _vote;
}

const party& districtParty::_getFederalParty() const
{
	return _federalParty;
}

void districtParty::addRepresentative(citizen& newRepresentative)
{
	addToList(newRepresentative);
}

void districtParty::printLimitedRepresentativeList(int n, int* res)
{
	int size;
	representativeNode* p = _head;
	bool stop = false;

	if (n > representativeCount)
	{
		size = representativeCount;
		*res = 0;
	}
	else
	{
		size = n;
		*res = 1;
	}

	for (int i = 1; i <= size; i++, p = p->_next)
	{
		cout << i << "." << p->_data.getName() << endl;
	}

}

void districtParty::copyNameToArray(citizen& _citizen_, char* name)
{
	int resStrLength;
	int resStrSize;

	resStrLength = strlen(_citizen_.getName());
	resStrSize = resStrLength + 1;

	name = new char[resStrSize];
	memcpy(name, _citizen_.getName(), resStrSize);
}

int districtParty::getRepresentativeCount() const
{
	return representativeCount;

}

void districtParty::setVote(const int num)
{
	_vote = num;
}

int districtParty::setRepresentativeCount(int newCount)
{
	representativeCount = newCount;

	return newCount;
}

void districtParty::printRepresentativeList() const
{
	int count = 1;
	representativeNode* p = _head;

	if (!p)
	{
		cout << "no representative" << endl;
	}
	else
	{
		while (p)
		{
			cout << count << ". " << p->_data.getName() << endl;

			count++;
			p = p->_next;
		}

	}

}

int districtParty::saveDistrictParty(ofstream& f) const
{
	f.write(WRITE(&_vote), sizeof(int));

	f.write(WRITE(&representativeCount), sizeof(int));

	return 1;
}

////////List//////////////////start/////////////////////////////////////
void districtParty::addToList(citizen& _newRepresentative_)
{

	representativeNode* newNode = new representativeNode(_newRepresentative_);
	if (isEmpty())
	{
		_head = newNode;
	}
	else
	{
		_tail->_next = newNode;
	}
	_tail = newNode;
	representativeCount++;


}
void districtParty::printList()//FOR DEBUGGING
{
	representativeNode* p;

	p = _head;
	int count = 0;
	cout << endl;
	while (p)
	{
		count++;
		cout << count << " . " << p->_data;

		p = p->_next;
	}
	cout << endl;
}
bool districtParty::isEmpty()
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
void districtParty::makeEmptyList()
{
	_head = nullptr;
	_tail = nullptr;
	representativeCount = 0;
}
void districtParty::deleteList()
{
	representativeNode* temp;


	while (_head)
	{

		temp = _head;

		_head = _head->_next;

		delete temp;

	}
}
/////////list////////////////end/////////////