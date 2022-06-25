#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct wordRecord {
    string word;
    int count;
};

wordRecord* arrayDouble(wordRecord* oldArray, int &capacity) {
    int newCapacity = capacity*2;

    wordRecord *newArray = new wordRecord[newCapacity];
    for (int i=0; i<capacity; i++) {
        newArray[i].word = oldArray[i].word;
        newArray[i].count = oldArray[i].count;
    }
    delete[] oldArray;
    oldArray = nullptr;
    capacity = newCapacity;
    return newArray;
}

void getCommonWords (const string commonWordFileName, string *commonWords) {
    ifstream list;
    string temp;
    list.open(commonWordFileName.c_str());
    
    if (list.is_open()) {
        for(int p=0; p<50; p++) {
            getline(list, temp);
            commonWords[p] = temp;
        }
    } else {
        cout << "Failed to open " << commonWordFileName << endl;
    }
}

bool isCommonWord(string word, string *commonWords) {
    for(int p=0; p<50; p++) {
        if (!word.compare(commonWords[p])) {
            return true;
        }
    }
    return false;
}

int getTotalNumberUncommonWords (wordRecord *distinctWords, int length) {
    int count=0;
    for (int i=0; i<length; i++) {
        count += distinctWords[i].count;
    }
    return count;
}

void sortArray (wordRecord *distinctWords, int length) {
    wordRecord tempWord;
    /*
    for (int i=0; i<length; i++) {
        if (distinctWords[i+1].count >= distinctWords[i].count) {
            for (int j=i; j>=0; j--) {
                if (distinctWords[j+1].count > distinctWords[j].count) {
                    tempWord = distinctWords[j];
                    distinctWords[j] = distinctWords[j+1];
                    distinctWords[j+1] = tempWord;
                }
            }
        }
    }
    */
    for (int i=0; i<length; i++) {
        if (distinctWords[i+1].count >= distinctWords[i].count) {
            for (int j=i; j>=0; j--) {
                if (distinctWords[j+1].count == distinctWords[j].count) {
                    if (distinctWords[j+1].word < distinctWords[j].word) {
                        tempWord = distinctWords[j];
                        distinctWords[j] = distinctWords[j+1];
                        distinctWords[j+1] = tempWord;
                    }
                }
                if (distinctWords[j+1].count > distinctWords[j].count) {
                    tempWord = distinctWords[j];
                    distinctWords[j] = distinctWords[j+1];
                    distinctWords[j+1] = tempWord;
                }
            }
        }
    }
}

void printNFromM (wordRecord *distinctWords, int M, int N, int totalNumWords) {
    cout << fixed << setprecision(5);
    for (int i=M; i<M+N; i++) {
        cout << (float)distinctWords[i].count/totalNumWords << " - " << distinctWords[i].word << endl;
    }
}

int main (int argc, char* argv[]) {
    if (argc !=5) {
        cout << "Usage ./Assignment2 <inputfilename> <commonWordsfilename> <M> <N>" << endl;
        return -1;
    }

    string input_file = argv[1];
    string commonWordFile = argv[2];
    int index = stoi(argv[3]);
    int num_words = stoi(argv[4]);

    // Common Words
    
    string *commonWords = new string[50];
    getCommonWords(commonWordFile, commonWords);

    // Input Words
    ifstream input;
    input.open(input_file.c_str());

    string word;
    int numElements = 0;
    int capacity = 100;
    int timesDoubled = 0;
    bool overlap=0;
    wordRecord *arrayPtr = new wordRecord[capacity];

    if (input.is_open()) {
        while (input >> word) {
            if (numElements == capacity) {
                arrayPtr = arrayDouble(arrayPtr, capacity);
                timesDoubled++;
            }
            if (isCommonWord(word, commonWords)) {overlap=true;} 

            for (int n=0; n<numElements; n++) {
                if (!word.compare(arrayPtr[n].word)) {
                    arrayPtr[n].count++;
                    overlap=true;
                }
            }
            //cout << word << endl;
            if (!overlap) {
                arrayPtr[numElements].word = word;
                arrayPtr[numElements].count = 1;
                numElements++;
            }
            overlap=false;
            
        }
    }
    input.close();
    
    sortArray(arrayPtr, numElements);
    cout << "Array doubled: " << timesDoubled << endl;
    cout << "Distinct uncommon words: " << numElements << endl;
    cout << "Total uncommon words: " << getTotalNumberUncommonWords(arrayPtr, numElements) << endl;
    cout << "Probability of next " << num_words << " words from rank " << index << endl;
    cout << "---------------------------------------" << endl;
    printNFromM(arrayPtr, index, num_words, getTotalNumberUncommonWords(arrayPtr, numElements));
    delete[] arrayPtr;
    arrayPtr = nullptr;
    return 0;
}

