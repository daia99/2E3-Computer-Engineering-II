#pragma once
#include "Node.h"
#include <string>

using namespace std;

class StudentLinkedList
{
private:
	StudentNode* headP;
	StudentNode* tailP;
	int numStudents;

public:
	StudentLinkedList();
	~StudentLinkedList();
	void printAllStudents();
	int addSize();
	StudentNode* findByName(string _name);
	StudentNode* findByID(int _id);
	void addStudent();
	void insertAfter(StudentNode* p, StudentNode* newP);
	void sortByName(int a);
	void removeByName(string _name);
	void removeByNameAndID(string _name, int _id);
};