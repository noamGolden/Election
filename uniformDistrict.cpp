#include "district.h"
uniformDistrict::uniformDistrict(const char* _name_, const int _serialNumber_, const int _representative_) :
	district(_name_, _serialNumber_, _representative_, districtType::uniform)
{

}

uniformDistrict::uniformDistrict(ifstream& f) :district(f, districtType::uniform)
{


	int nameSize;

	f.read(READ(&nameSize), sizeof(int));

	_name = new char[nameSize];

	f.read(READ(_name), nameSize * sizeof(char));
}

int uniformDistrict::save(ofstream& f)const
{

	f.write(WRITE(&_type), sizeof(districtType));

	saveDistrict(f);

	int nameLength = strlen(_name);

	int nameSize = nameLength + 1;

	f.write(WRITE(&nameSize), sizeof(int));

	f.write(WRITE(_name), nameSize * sizeof(char));


	return 1;

}

result* uniformDistrict::getResult()
{
	makeElectorsDivisionArray();
	resArr[0]._electors = _representative;
	return resArr;
}

