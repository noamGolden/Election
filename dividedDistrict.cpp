#include "district.h"

dividedDistrict::dividedDistrict(const char* _name_, const int _serialNumber_, const int _representative_) :
	district(_name_, _serialNumber_, _representative_, districtType::divided)
{

}

dividedDistrict::dividedDistrict(ifstream& f) :district(f, districtType::divided)
{
	int nameSize;

	f.read(READ(&nameSize), sizeof(int));

	f.read(READ(_name), nameSize * sizeof(char));

}

result* dividedDistrict::getResult()
{
	makeElectorsDivisionArray();
	return resArr;
}

int dividedDistrict::save(ofstream& f)const
{

	f.write(WRITE(&_type), sizeof(districtType));

	saveDistrict(f);

	int nameLength = strlen(_name);

	int nameSize = nameLength + 1;

	f.write(WRITE(&nameSize), sizeof(int));

	f.write(WRITE(_name), nameSize * sizeof(char));

	return 1;

}