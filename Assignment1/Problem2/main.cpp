#include <iostream>
#include <fstream>
#include <string>
#include "student.h"

using namespace std;


int main(int argc, char* argv[]) {
    if (argc!=5) {
        cout << "Correct usage : ./main [INPUT.csv] [OUTPUT.csv] [LOW_BOUND] [UP_BOUND]" << endl;
        return -1;
        }
    studentData students[10];
    string name;
    string line;

    int length = 0;

    ifstream input (argv[1]);
    ofstream output (argv[2]);

    while (getline(input, name, ',')) {

        getline(input, line, ',');
        int homework = stoi (line);
        getline(input, line, ',');
        int recitation = stoi (line);
        getline(input, line, ',');
        int quiz = stoi (line);
        getline(input, line);
        int exam = stoi (line);
        addStudentData(students, name, homework, recitation, quiz, exam, length);
        length++;
        if (length>=10) {break;}
    }
    printList(students, length);
    for (int j=0; j<10; j++) {
        char letterGrade = calcLetter(students[j].average);
        if (letterGrade <= *argv[3] && letterGrade >= *argv[4]) {
            output << students[j].studentName << ',' << students[j].average << ',' << letterGrade << endl;
        }
    }
    input.close();
    return 0;
}