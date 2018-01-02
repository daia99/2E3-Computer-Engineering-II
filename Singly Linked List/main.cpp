#include "List.h"
#include "Node.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    StudentNode* s0 = new StudentNode(100, "John", 45);
    cout << "Final Grade: " << s0->getGrade() << endl;
    delete s0;
    
    StudentLinkedList sll0;
    
    for (int i = 0; i < 5; i++) {
        sll0.addStudent();
    }
    sll0.printAllStudents();
    
    string name;
    cout << "Find student by name: ";
    cin >> name;
    StudentNode *s1 = sll0.findByName(name);
    if (s1 == NULL)
        cout << "Student not found" << endl;
    else {
        cout << "ID: " << s1->getID() << endl;
        cout << "Final grade: " << s1->getGrade() << endl;
    }
    
    int id;
    cout << "Find student by ID: ";
    cin >> id;
    StudentNode *s2 = sll0.findByID(id);
    if (s2 == NULL)
        cout << "Student not found" << endl;
    else {
        cout << "Name: " << s2->getName() << endl;
        cout << "Final grade: " << s2->getGrade() << endl << endl;
    }
    
    cout << "Inserting Pat" << endl;
    StudentNode* sNew1 = new StudentNode(100, "Pat", 50); //inserting new student at tail test
    StudentNode* sP1 = sll0.findByID(5);
    sll0.insertAfter(sP1, sNew1);
    sll0.printAllStudents();
    
    cout << "Inserting Liam" << endl;
    StudentNode* sNew2 = new StudentNode(200, "Liam", 51); //inserting new student at other
    StudentNode* sP2 = sll0.findByID(2);
    sll0.insertAfter(sP2, sNew2);
    sll0.printAllStudents();
    
    cout << "Sorting" << endl;
    sll0.sortByName(1);
    sll0.printAllStudents();
    
    cout << "Sorting" << endl;
    sll0.sortByName(2);
    sll0.printAllStudents();
    
    cout << "Removing Pat(s)" << endl;
    sll0.removeByName("Pat");
    sll0.printAllStudents();
    
    cout << "Removing Liam, ID 200" << endl;
    sll0.removeByNameAndID("Liam", 200);
    sll0.printAllStudents();
    
    return 0;
}
