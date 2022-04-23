#include "party.h"

party::party(int _serialnumber_, citizen& _residentialStumble_, const char* _name_, const char* _residentalStumbleName_) :
	_serialNumber(_serialnumber_), _residentialStumble(_residentialStumble_)
{
	_name = new char[strlen(_name_) + 1];

	memcpy(_name, _name_, strlen(_name_) + 1);

	//
	_residentalStumbleName = new char[strlen(_residentalStumbleName_) + 1];

	memcpy(_residentalStumbleName, _residentalStumbleName_, strlen(_residentalStumbleName_) + 1);

	_vote = 0;
}

party::party(ifstream& f, citizen& _citizen_, int _serialNumber_) :_serialNumber(_serialNumber_), _residentialStumble(_citizen_)
{
	int _nameSize;

	f.read(READ(&_nameSize), sizeof(int));

	_name = new char[_nameSize];

	f.read(READ(_name), _nameSize * sizeof(char));

	//

	int _residentalStumbleNameSize;

	f.read(READ(&_residentalStumbleNameSize), sizeof(int));

	_residentalStumbleName = new char[_residentalStumbleNameSize];

	f.read(READ(_residentalStumbleName), _residentalStumbleNameSize * sizeof(char));

	//

	f.read(READ(&_vote), sizeof(int));


}

party::~party()
{
	delete _name;
}

void party::add1Vote()
{
	_vote++;
}

int party::getSerialNumber() const
{
	return _serialNumber;
}

int party::__vote() const
{
	return _vote;
}

const char* party::getName() const
{
	return _name;
}

char* party::getCandidateOfPrimerMinisterName() const
{
	return _residentalStumbleName;
}

int party::saveParty(ofstream& f) const
{

	f.write(WRITE(&_serialNumber), sizeof(int));

	//
	int nameLength = strlen(_name);

	int nameSize = nameLength + 1;

	f.write(WRITE(&nameSize), sizeof(int));

	f.write(WRITE(_name), nameSize * sizeof(char));


	//
	int residentalStumbleNameLength = strlen(_residentalStumbleName);

	int residentalStumbleNameSize = residentalStumbleNameLength + 1;

	f.write(WRITE(&residentalStumbleNameSize), sizeof(int));

	f.write(WRITE(_residentalStumbleName), residentalStumbleNameSize * sizeof(char));

	//
	f.write(WRITE(&_vote), sizeof(int));

	return 1;
}

citizen& party::getCandidateOfPrimerMinister()
{
	return _residentialStumble;
}