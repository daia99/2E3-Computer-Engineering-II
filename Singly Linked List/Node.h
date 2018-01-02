#pragma once
#include <string>

using namespace std;

class StudentNode 
{
private:
	int ID; 
	string firstName; 
	double finalGrade; 
	StudentNode* nextS;
public:
	StudentNode(int numStudents);
	StudentNode(int _ID, string _firstName, double _finalGrade);
	double getGrade();
	string getName();
	void setGrade();
	void setName();
	int getID();
	StudentNode* getNext();
	void setNext(StudentNode* _next);
};