#include "addToArrayAsc.h"

int addToArrayAsc(float sortedArray[], int numElements, float newValue) {
    
    for (int i=numElements; i>=0; i--) {
        if (newValue > sortedArray[i-1] | i == 0) {
            for (int j=numElements-1; j>i-1; j--) {
                sortedArray[j+1] = sortedArray[j];
            }
            sortedArray[i] = newValue;
            break;
        }
    
    }
    return numElements;
}
int addToArrayAsc(float sortedArray[], int numElements, float newValue) {
    
    for (int i=numElements; i>=0; i--) {
        if (newValue > sortedArray[i-1] | i == 0) {
            for (int j=numElements-1; j>i-1; j--) {
                sortedArray[j+1] = sortedArray[j];
            }
            sortedArray[i] = newValue;
            break;
        }
    
    }
    return numElements;
}