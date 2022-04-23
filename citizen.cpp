#include "citizen.h"
#include <string>

citizen::citizen(district& _district_, const char* _name_, const char* _id_, bool upTo18, int _birthYear_, const char* _districtName_) :
	_district(_district_), _upTo18(upTo18), _vote(false), _representive(false), _birthYear(_birthYear_)
{

	name = new char[strlen(_name_) + 1];

	memcpy(name, _name_, strlen(_name_) + 1);


	//
	id = new char[strlen(_id_) + 1];

	memcpy(id, _id_, strlen(_id_) + 1);


	//
	districtName = new char[strlen(_districtName_) + 1];

	memcpy(districtName, _districtName_, strlen(_districtName_) + 1);

}

citizen::citizen(ifstream& f, district& _district_, const char* _districtName_, int _birthYear_, bool _upTo18_) :_upTo18(_upTo18_), _vote(0), _representive(0), _birthYear(_birthYear_), _district(_district_)
{
	districtName = new char[strlen(_districtName_) + 1];

	memcpy(districtName, _districtName_, strlen(_districtName_) + 1);

	//
	int nameSize;

	f.read(READ(&nameSize), sizeof(int));

	name = new char[nameSize];

	f.read(READ(name), nameSize * sizeof(char));


	//
	int idSize;

	f.read(READ(&idSize), sizeof(int));

	id = new char[idSize];

	f.read(READ(id), idSize * sizeof(char));

	//
	f.read(READ(&_representive), sizeof(bool));


}

citizen::~citizen()
{
	delete[]name;
	delete[]id;
	delete[]districtName;
}

int citizen::__vote()
{
	if (!_upTo18)
	{
		return -1;
	}
	else if (_vote)
	{
		return 1;
	}
	else
	{
		_vote = true;
		return 0;
	}
}

bool citizen::__representine()
{
	if (_representive)
	{
		return true;
	}
	else
	{
		_representive = true;
		return false;
	}
}

const char* citizen::getId() const
{
	return id;
}

const char* citizen::getName() const
{
	return name;
}

district& citizen::getDistrict() const
{
	return _district;
}

int citizen::saveId(ofstream& f) const
{
	int idLength = strlen(id);

	int idSize = idLength + 1;

	f.write(WRITE(&idSize), sizeof(int));

	f.write(WRITE(id), idSize * sizeof(char));

	return 1;
}

int citizen::saveCitizen(ofstream& f) const
{
	//
	f.write(WRITE(&_birthYear), sizeof(int));


	//
	f.write(WRITE(&_upTo18), sizeof(bool));

	//
	int nameLength = strlen(name);

	int nameSize = nameLength + 1;

	f.write(WRITE(&nameSize), sizeof(int));

	f.write(WRITE(name), nameSize * sizeof(char));


	//
	int idLength = strlen(id);

	int idSize = idLength + 1;

	f.write(WRITE(&idSize), sizeof(int));

	f.write(WRITE(id), idSize * sizeof(char));


	//
	f.write(WRITE(&_representive), sizeof(bool));

	return 1;
}
