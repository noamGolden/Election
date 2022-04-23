#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "partyList.h"
#include "citizenList.h"
#include "districtList.h"
#include "header.h"

class election {
private:
	citizenList _citizenList;
	date _date;
	partyList _partyList;
	result* resArr;
	int resArrSize;

	//res Array
	virtual void calculateFederalResult() = 0;

	void bulidResArr();
	//

	//getters

	//in case of the citizen didnt found *res=0
	//else the function return reference to the citizen and *res=1
	citizen& getCitizen(const char* id, int* res);

	//in case of the party didnt found *res=0
	//else the function return reference to the party and *res=1
	virtual party& getParty(int serialNumber, int* res) = 0;

	//in case of this is election without districts *res=-1
	//in case of the district didnt found *res=0
	//else the function return reference to the district and *res=1
	virtual district& getDistrict(int serialNumber, int* res) = 0;

	//in case of the election without districts the function return -2
		//in case of the district didnt found *res= -1
			//in case of the party didnt found  *res= 0
			//else the function return a reference to the district party and *res=1
	virtual districtParty& getDistrictParty(int serialNumberOfDistrict, int serialNumberOfParty, int* res) = 0;

	//in case of the party didnt found the function return 0
	virtual int printRepresentativeOfPartyInAllThedistricts(int serialNumberOfParty) const = 0;

	//in case of the district didnt found the function return 0
	//else the function return 1 and print the divided electors of the district
	int printElectorsDividedOfDistrict(int serialNumberOfDistrict);

	int printElectorsDividedOfDistrict(district& _district);

	int printElectorsDividedOfDividedDistrict(district& _district);

	int printElectorsDividedOfUniformDistrict(district& _district);

	int printTurnOut(district& _district);

	//in case of the district didnt found the function return 0
	//else the function return 1 and print the district result
	int printDistrictResult(int serialNumberOfDistrict);

	int printDistrictResult(district& _district);

	int printFinallyRepresentativeList(district& _district);

	int printPartyResult(result _result);

	int printPartyResult(int serialNumberOfParty, int electors);

	int printPartyResult(party& _party, int electors);

public:
	election(date _date_);//structure
	~election();//destrcture

	////////myfriends////////////////////////////////
	friend class electionRegular;
	friend class electionWithoutDistricts;
	friend class saveFile;
	////////////////////////////////////////////////

	void addVoteToFederalParty(party& _party_);

	//the function have to update the districts voters counter
	void addVoteToDistrictParty(party& _party_, district& _district_);

	virtual int printDistrictResult() = 0;

	int printPartiesResult();

	int getPartiesCounter() const;

	int getCitizensCounter() const;

	virtual bool regularElection() const = 0;

	void setTheSerialNumberCounterOfParties(const int newSerialNumber);//for file load

	//load///////
	int load(ifstream& f);

	int loadDate(ifstream& f);

	virtual int loadCounters(ifstream& f, int* districtsCount, int* partiesCount, int* citizensCount) = 0;

	virtual int loadDistrictList(ifstream& f, int districtCount) = 0;

	virtual int loadCitizensList(ifstream& f, int citizenCount) = 0;

	int loadPartyList(ifstream& f, int partyCounter);

	virtual int loadPartyDistrictList(ifstream& f, int partyCount) = 0;

	int loadPartyDistrictListHelper(ifstream& f, district& _district, int partyCounter);

	int loadRepresentativeList(ifstream& f, districtParty& newParty);

	virtual int loadSerialNumbers(ifstream& f) = 0;
	////////

	//save///////
	int save(ofstream& f)const;

	//in case of withoutdistricts the function save 0
	//in case of regularelection the function save 1
	int saveElectionType(ofstream& f)const;

	int saveDate(ofstream& f) const;

	virtual int saveCounters(ofstream& f) const = 0;

	virtual int saveDistrictList(ofstream& f) const = 0;

	int savePartyList(ofstream& f) const;

	int saveCitizensList(ofstream& f)const;

	virtual int savePartiesDistrictList(ofstream& f)const = 0;

	int savePartiesDistrictListHelper(ofstream& f, const district* _district)const;

	int saveRepresentativeList(ofstream& f, districtParty* _districtParty)const;

	virtual int SaveSerialNumbers(ofstream& f) const = 0;



	////////////////////////////menu////////////////////////

		//1//
		 //
		 //in case of uniform district type =1
		 //in case of divided district type =2
		 //
		 //in case of election with districts the function return the serial number of the district
		//in case of election without districts the function return -1
	virtual int addDistrict(const char* name, int numOfRepresentative, int type) = 0;

	///2//
	/// 
	/// //in case of the district serial number didnt exist the function return -1
	//in case of the id alredy exist the function return 0
	//in case of the id dont exist the function add the citizen to the list and reuturn 1
	//
	//in case of election without districts the function ignore the serial number of district
	virtual int addCitizen(const char* name, const char* id, int birthYeaar, int serialNumberOfDistrict) = 0;

	//3//
	//
	////in case of the the if od resedental stumble didnt exist the function return -2
	//in case of the residential Stumble already representative the function return -1
	//in case of the party succesfuly added the fuinction return the serial number of the new party
	virtual int addParty(const char* partyName, const char* idOfresidentalStumble) = 0;

	//4//
	//
	//in case of the district didnt found the fucntion return -3
	//in case of the party didnt found the function return -2
	//in case of the id didnt exist the function return -1
	//in case of the person alredy representative the function return 0
	//else the function return 1 and add him to representative list of the district
	//
	//in case of party without districts the function ignore the serial number of district
	virtual int addRepresentative(const char* idOfRepresentative, int serialNumberOfParty, int serialNumberOfDistrict) = 0;



	//7//
	//
	void displayAllParties() const;

	////8//
	//
	//in case of the party didnt found the function return -3
	//in case of the person didnt found the function return= -2
	//in case of the person found but already voted the function return -1
	//in case of the person found but too young the function return 0
	//else the function add the vote and the function return 1
	int addVote(const char* id, int serialNumberOfParty);

	//9
	//
	void disPlayResult();

};



class electionRegular
	:public election
{
private:


	//res Array//////

	//if the party found the function return the party index
	//else the function return -1
	int findPartyIndexInResultArrayBySerialNumber(int serialNumber);

	void  calculateFederalResult();

	void addToResArray(result* districtResultArr, districtType type);

	void addToPartyRes(result partyResult);

	//////////////////////////////////

	//in case of the district didnt found *res=0
	//else the function return reference to the district and *res=1
	district& getDistrict(int serialNumberOfDistrict, int* res);

	//in case of the district didnt found *res= -1
	//in case of the party didnt found  *res= 0
	//else the function return a reference to the district party and *res=1
	districtParty& getDistrictParty(int serialNumberOfDistrict, int serialNumberOfParty, int* res);

	//in case of the party didnt found *res=0
	//else the function return reference to the party and *res=1
	party& getParty(int serialNumber, int* res);

	void addPartyToAllTheDistrictsPartyList(party& newParty);

	//in case of the party didnt found the function return 0
	int printRepresentativeOfPartyInAllThedistricts(int serialNumberOfParty) const;
public:
	electionRegular(date _Date_);//structure
	~electionRegular();// destructure

	districtList _districtList;
	int printDistrictResult();

	const citizenList& getCitizenList() const;
	//in case of uniform district type =1
   //in case of divided district type =2
   //
   //the function return the serial number of the district
	int addDistrict(const char* name, int numOfRepresentative, int type);

	//in case of the district serial number didnt exist the function return -1
	//in case of the id alredy exist the function return 0
	//in case of the id didnt exist the function add the citizen to the list and reuturn 1
	int addCitizen(const char* name, const char* id, int birthYeaar, int serialNumberOfDistrict);

	////in case of the the if od resedental stumble didnt exist the function return -2
	//in case of the residential Stumble already representative the function return -1
	//in case of the party succesfuly added the fuinction return the serial number of the new party
	int addParty(const char* partyName, const char* idOfresidentalStumble);

	//in case of the district didnt found the fucntion return -3
	//in case of the party didnt found the function return -2
	//in case of the id didnt exist the function return -1
	//in case of the person alredy representative the function return 0
	//else the function return 1 and add him to representative list of the district
	int addRepresentative(const char* idOfRepresentative, int serialNumberOfParty, int serialNumberOfDistrict);

	const districtList& getDistrictList() const;

	void setTheSerialNumberCounterOfDistricts(const int newSerialNumber);//for file load

	bool regularElection() const;

	//save///////
	int saveCounters(ofstream& f) const;

	int saveDistrictList(ofstream& f) const;

	int savePartiesDistrictList(ofstream& f)const;

	int SaveSerialNumbers(ofstream& f) const;
	////////////



	//load///////
	int loadCounters(ifstream& f, int* districtsCount, int* partiesCount, int* citizensCount);

	int loadDistrictList(ifstream& f, int districtCount);

	int loadCitizensList(ifstream& f, int citizenCount);

	int loadPartyDistrictList(ifstream& f, int partyCount);

	int loadSerialNumbers(ifstream& f);
	/////////////
};



class electionWithoutDistricts
	:public election
{
private:

	dividedDistrict* _country;

	//res Array
	virtual void calculateFederalResult();
	//

	//return *res=-1 
	district& getDistrict(int serialNumber, int* res);

	//in case of the party didnt found *res=0
	//else the function return reference to the party and *res=1
	party& getParty(int serialNumber, int* res);

	void addPartyToCountryDistrictPartyList(party& party);

	//in case of the party didnt found the function return 0
	int printRepresentativeOfPartyInAllThedistricts(int serialNumberOfParty) const;


public:
	electionWithoutDistricts(date _Date_, int numOfRepresentative);//structure

	int printDistrictResult();

	//no districts in this kind of election and the function always return -1
	int addDistrict(const char* name, int numOfRepresentative, int type);

	//in case of the id alredy exist the function return 0
	//in case of the id dont exist the function add the citizen to the list and reuturn 1
	//
	//the function ignore the serial number of district
	int addCitizen(const char* name, const char* id, int birthYeaar, int serialNumberOfDistrict);

	////in case of the the if od resedental stumble didnt exist the function return -2
	//in case of the residential Stumble already representative the function return -1
	//in case of the party succesfuly added the fuinction return the serial number of the new party
	int addParty(const char* partyName, const char* idOfresidentalStumble);

	//in case of the party didnt found the function return -2
	//in case of the id didnt exist the function return -1
	//in case of the person alredy representative the function return 0
	//else the function return 1 and add him to representative list of the district
	//
	//the function ignore the serial number of district
	int addRepresentative(const char* idOfRepresentative, int serialNumberOfParty, int serialNumberOfDistrict);

	districtParty& getDistrictParty(int serialNumberOfDistrict, int serialNumberOfParty, int* res);

	bool regularElection() const;

	//save/////////
	int saveCounters(ofstream& f) const;

	int saveDistrictList(ofstream& f) const;

	int savePartiesDistrictList(ofstream& f)const;

	int SaveSerialNumbers(ofstream& f) const;
	//////////////

	//load///////
	int loadCounters(ifstream& f, int* districtsCount, int* partiesCount, int* citizensCount);

	int loadDistrictList(ifstream& f, int districtCount);

	int loadCitizensList(ifstream& f, int citizenCount);

	int loadPartyDistrictList(ifstream& f, int partyCount);

	int loadSerialNumbers(ifstream& f);

	const citizenList& getCitizenList() const;
	//////////////
};



