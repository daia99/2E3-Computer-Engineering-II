#include "List.h"
#include "Node.h"
#include <string>
#include <iostream>

using namespace std;

StudentLinkedList::StudentLinkedList() {
	headP = NULL;
	tailP = NULL;
	numStudents = 0;
}

StudentLinkedList::~StudentLinkedList() {
    StudentNode *next;
    StudentNode *curr = headP;
	
    while (curr != NULL) {
		next = curr->getNext();
		delete curr;
		curr = next;
	}
}

void StudentLinkedList::printAllStudents() {
	StudentNode* curr;
	curr = headP;
	while (curr != NULL) {
		cout << "Name: " << curr->getName() << endl;
		cout << "Student ID: " << curr->getID() << endl;
		cout << "Final Grade: " << curr->getGrade() << endl;
		cout << endl;
		curr = curr->getNext();
	}
}

int StudentLinkedList::addSize() {
	return (numStudents++);
}

StudentNode* StudentLinkedList::findByName(string _name) {
	StudentNode* curr;
	curr = headP;
	while (curr != NULL && curr->getName() != _name) {
		curr = curr->getNext();
	}
	return curr;
}

StudentNode* StudentLinkedList::findByID(int _id) {
	StudentNode* curr;
	curr = headP;
	while (curr != NULL && curr->getID() != _id) {
		curr = curr->getNext();
	}
	return curr;
}

void StudentLinkedList::addStudent() {
	addSize();
    StudentNode *temp = new StudentNode(numStudents);

    if (headP == NULL) {
		headP = temp;
		tailP = temp;
    }
    else {	
		tailP->setNext(temp);
		tailP = temp;
	}	  
}

void StudentLinkedList::insertAfter(StudentNode* p, StudentNode* newP) {
	if (p == tailP) {
		p->setNext(newP);
		tailP = newP;
	}
	else {
		newP->setNext(p->getNext());
		p->setNext(newP);
	}
}

void StudentLinkedList::sortByName(int a) {
	bool notSorted = true;
	StudentNode* p = headP;
    StudentNode* next = p->getNext(); //after p
    StudentNode* temp = 0; //behind p except if swapping head node with next node
	if (a == 1) { //sort from Z to A
		while (notSorted) {
			if ((next != tailP) && (p->getName() < next->getName())) {
				if (p == headP) {
					headP = next;
                    temp = next->getNext();
                    p->setNext(temp);
                    next->setNext(p);
                    next = temp;
                    temp = headP; //set before p for next iteration
				}
                else {
                    temp->setNext(next);
                    p->setNext(next->getNext());
                    next->setNext(p);
                    
                    //move all pointers forward once (p already moved forward)
                    temp = next;
                    next = p->getNext();
                }
			}
			else {
				if (next == tailP) {
                    if (p->getName() < next->getName()) {
                        tailP = p;
                        temp->setNext(next);
                        p->setNext(NULL);
                        next->setNext(p);
                    }
                    //reset pointers
					p = headP;
                    next = p->getNext();
                    temp = 0;
					while (1) { //checks to see if list is sorted fully
						if (p->getName() >= next->getName()) {
                            p = next;
                            next = next->getNext();
							if (next == NULL) {
								notSorted = false;
								break;
							}
						}
						else { //do sorting again from start of list
                            p = headP;
                            next = p->getNext();
							break;
						}
					}
				}
				else {
                    temp = p;
					p = next;
                    next = next->getNext();
				}
			}
		}
	}
	else if (a == 2) {
		while (notSorted) {
            if ((next != tailP) && (p->getName() > next->getName())) {
                if (p == headP) {
                    headP = next;
                    temp = next->getNext();
                    p->setNext(temp);
                    next->setNext(p);
                    next = temp;
                    temp = headP; //set before p for next iteration
                }
                else {
                    temp->setNext(next);
                    p->setNext(next->getNext());
                    next->setNext(p);
                    
                    //move all pointers forward once (p already moved forward)
                    temp = next;
                    next = p->getNext();
                }
            }
            else {
                if (next == tailP) {
                    if (p->getName() > next->getName()) {
                        tailP = p;
                        temp->setNext(next);
                        p->setNext(NULL);
                        next->setNext(p);
                    }
                    //reset pointers
                    p = headP;
                    next = p->getNext();
                    temp = 0;
                    while (1) { //checks to see if list is sorted fully
                        if (p->getName() <= next->getName()) {
                            p = next;
                            next = next->getNext();
                            if (next == NULL) {
                                notSorted = false;
                                break;
                            }
                        }
                        else { //do sorting again from start of list
                            p = headP;
                            next = p->getNext();
                            break;
                        }
                    }
                }
                else {
                    temp = p;
                    p = next;
                    next = next->getNext();
                }
            }

		}
	}
	else {
		cout << "Invalid command, not sorted." << endl;
	}
}

void StudentLinkedList::removeByName(string _name) {
	StudentNode* p = headP;
	StudentNode* temp = 0;
	int command;
	while (p != NULL) {
		if (p->getName() == _name) {
			cout << "Student with ID: " << p->getID() << " found, to remove, type '1', else, type any other character: ";
			cin >> command;
			if (command == 1) {
				if (p == headP) {
					p = p->getNext();
					delete headP;
					headP = p;
                    temp = p;
                    p = p->getNext();
				}
				else if (p == tailP) {
                    tailP = temp;
                    temp->setNext(NULL);
                    delete p;
                    p = NULL;
                    cout << "End of list reached, no more to remove";
                }
                else {
                    temp->setNext(p->getNext());
                    delete p;
                    p = temp->getNext();
                }
			}
            else {
                temp = p;
                p = p->getNext();
                if (p == NULL) {
                    cout << "End of list reached, no more to remove";
                }
            }
        }
        else {
            temp = p;
            p = p->getNext();
            if (p == NULL) {
                cout << "End of list reached, no more to remove";
            }
        }
    }
}


void StudentLinkedList::removeByNameAndID(string _name, int _id) {
	StudentNode* p = headP;
	StudentNode* temp = 0;
	while (p != NULL) {
		if (p->getName() == _name && p->getID() == _id) {
            if (p == headP) {
                p = p->getNext();
                delete headP;
                headP = p;
                temp = p;
                p = p->getNext();
            }
            else if (p == tailP) {
                tailP = temp;
                temp->setNext(NULL);
                delete p;
                p = NULL;
                cout << "End of list reached, no more to remove";
            }
            else {
                temp->setNext(p->getNext());
                delete p;
                p = temp->getNext();
            }
        }
        else {
            temp = p;
            p = p->getNext();
            if (p == NULL) {
                cout << "End of list reached, no more to remove";
            }
        }
    }
}
