#include <iostream>
#include <fstream>
#include "addToArrayAsc.h"
#include <string>

using namespace std;

int printArray(float a[], int n) {
    cout << a[0];
    for (int k=1; k<n+1; k++) {
        cout << "," << a[k];
    }
    cout << endl;
    return 0;
}


int main (int argc, char const* argv[]) {
    float array[100];
    int num = 0;
    float value;
    string line;

    if (argc==2) {

        ifstream iFile (argv[1]);

        if (iFile.is_open()) {
            
            while (getline(iFile, line)) {
                value = stof(line);
                addToArrayAsc(array, num, value);
                printArray(array, num);
                num++;
            }
        } else {
            cout << "Failed to open the file." << endl;
        }
        iFile.close();
    } else {
        cout << "Incorrect number of Arguments" << endl;
    }
    return 0;
}