#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream input ("students.csv");
    string line;
    for (int i=0; i<10; i++) {
        getline(input, line, ',');
        cout << line << endl;
    }
}