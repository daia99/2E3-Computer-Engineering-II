#include "List.h"
#include "Node.h"
#include <string>
#include <iostream>

using namespace std;

StudentNode::StudentNode(int numStudents){
	ID = numStudents;
	setName();
	setGrade();
	nextS = NULL;
}

StudentNode::StudentNode(int _ID, string _firstName, double _finalGrade){
	ID = _ID;
	firstName = _firstName;
	finalGrade = _finalGrade;
	nextS = NULL;
}

double StudentNode::getGrade() {
	return finalGrade;
}

string StudentNode::getName() {
	return firstName;
}

void StudentNode::setGrade() {
	cout << "Enter student final grade: ";
	cin >> finalGrade;
}

void StudentNode::setName() {
	cout << "Enter student first name: ";
	cin >> firstName;
}

int StudentNode::getID() {
	return ID;
}

StudentNode* StudentNode::getNext() {
	return nextS;
}

void StudentNode::setNext(StudentNode* _next) {
	nextS = _next;
}