#pragma once
#include "citizen.h"
struct citizenNode {
	citizen* _data;
	citizenNode* _next;
	citizenNode(citizen* _data_, citizenNode* _next_ = nullptr)
	{
		_data = _data_;
		_next = _next_;
	}
};
class citizenList {
private:
	citizenNode* _head;
	citizenNode* _tail;
	date& _date;

	//List//
	int citizensCounter;
	void addToList(citizen* _citizen);
	void makeEmptyList();
	bool isEmpty();
	void deleteList();
	///////////////////

	bool legalAge(int birthYear);
public:
	citizenList(date& _date_);//structure
	~citizenList();//destructure

//my friend//
	friend class election;
	friend class electionRegular;
	friend class electionWithoutDistricts;
	//

	//in case of citizen didnt found res =0
	//in case of citizen found res=1 and the function return the reference to the citizen
	citizen& searchCitizen(const char* id, int* res);

	int getCitizensCounter() const;

	//in case of the id alredy exist the function return 0
   //in case of the id dont exist the function add the citizen to the list and reuturn 1
	int addCitizen(const char* name, const char* id, int birthYeaar, district& _district_, const char* districtName);

	int saveCitizenCount(ofstream& f)const;

	friend ostream& operator<<(ostream& os, const citizenList& lst)
	{
		cout << "citizenList" << endl;
		cout << "_____________" << endl;
		printList(lst._head);
		return os;
	}
};
