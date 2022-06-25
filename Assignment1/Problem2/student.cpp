#include <iostream>
#include "student.h"

using namespace std;

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length) {
    studentData student;
    student.studentName = studentName;
    student.homework = homework;
    student.recitation = recitation;
    student.quiz = quiz;
    student.exam = exam;
    student.average = (double) (homework + recitation + quiz + exam) / 4;
    students[length] = student;
}

char calcLetter (double avg) {
    if (avg >= 90) {return 'A';}
    else if (avg >= 80) {return 'B';}
    else if (avg >= 70) {return 'C';}
    else if (avg >= 60) {return 'D';}
    else {return 'F';}
}

void printList(const studentData students[], int length) {
    for (int i=0; i<length; i++) {
        cout << students[i].studentName << " earned " << students[i].average << " which is a(n) " << calcLetter(students[i].average) << endl;
    }
}