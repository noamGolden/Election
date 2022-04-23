#include "citizenList.h"
#include <string.h>

citizenList::citizenList(date& _date_) :_date(_date_)
{
	makeEmptyList();
}
citizenList::~citizenList()
{
	deleteList();
}

int citizenList::addCitizen(const char* name, const char* id, int birthYear, district& _district_, const char* distrcitName)
{
	int pepoleFound;
	searchCitizen(id, &pepoleFound);
	if (pepoleFound == 0)
	{

		citizen* newCitizen = new citizen(_district_, name, id, legalAge(birthYear), birthYear, distrcitName);
		addToList(newCitizen);
		return 1;
	}
	return  0;
}

bool citizenList::legalAge(int birthYear)
{
	//if ((_date._year - birthYear) < 18)
	//{
	//	return false;
	//}
	//else
	//{
		return true;
	//}
}

citizen& citizenList::searchCitizen(const char* _Id_, int* res)
{
	citizenNode* p;
	p = _head;

	while (p)
	{

		if (strcmp(p->_data->getId(), _Id_) == 0)
		{
			*res = 1;
			return *(p->_data);
		}
		p = p->_next;
	}
	*res = 0;
}

int citizenList::getCitizensCounter() const
{
	return citizensCounter;
}

int citizenList::saveCitizenCount(ofstream& f)const
{
	f.write(WRITE(&citizensCounter), sizeof(int));

	return 1;
}

////////List//////////////////start/////////////////////////////////////
void citizenList::addToList(citizen* citizen)
{
	citizenNode* newNode = new citizenNode(citizen);

	if (isEmpty())
	{
		_head = newNode;
	}
	else
	{
		_tail->_next = newNode;
	}
	_tail = newNode;
	citizensCounter++;
}
bool citizenList::isEmpty()
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
void citizenList::makeEmptyList()
{
	_head = nullptr;
	_tail = nullptr;
	citizensCounter = 0;
}
void citizenList::deleteList()
{
	citizenNode* temp;
	while (_head)
	{
		temp = _head;
		delete _head->_data;

		_head = _head->_next;
		delete temp;
	}
}
/////////list////////////////end/////////////