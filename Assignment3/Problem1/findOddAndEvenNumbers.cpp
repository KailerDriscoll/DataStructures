#include "findOddAndEvenNumbers.h"

void findOddAndEvenNumbers(int* numbers, int*& odd, int*& even, int length, int& numOdd, int& numEven) {
    numEven = 0;
    numOdd = 0;
    for (int i=0; i<length; i++) {
        if (numbers[i]%2 == 0) {
            numEven++;
        } else if (numbers[i]%2 == 1) {
            numOdd++;
        }
    }
    odd = new int[numOdd];
    even = new int[numEven];
    int oddcnt, evencnt = 0;

    for (int i=0; i<length; i++) {
        if (numbers[i]%2 == 0) {
            even[evencnt] = numbers[i];
            evencnt++;
        } else {
            odd[oddcnt] = numbers[i];
            oddcnt++;
        }
    }
}