#include "WaitlistQueue.hpp"

using namespace std;

// COMPLETE THE FUNCTIONS BELOW

WaitlistQueue::WaitlistQueue(int qSize)
{
    qFront = -1;
    qEnd = -1;
    qCapacity = qSize;
    queue = new string[qSize];
}

WaitlistQueue::~WaitlistQueue()
{
    while (!isEmpty()) {
        dequeue();
    }
}

void WaitlistQueue::enqueue(std::string value)
{
    if (!isFull()) {
        if (isEmpty()) {qFront ++;}

        if (qEnd == qCapacity-1) {
            queue[0] = value;
            qEnd = 0;
        } else {
            queue[qEnd+1] = value;
            qEnd++;
        }
    } else {
        cout << "Waitlist is full. Cannot enqueue." << endl;
    }
}

void WaitlistQueue::dequeue()
{
    if (!isEmpty()) {
        queue[qFront] = "";
        if (qFront == qEnd) { //One element in queue
            qFront = -1;
            qEnd = -1;
        } else if (qFront == qCapacity-1) { // end of queue
            qFront = 0;
        } else {
            qFront++;
        }
    } else {
        cout << "Wailist is empty. Cannot dequeue." << endl;
    }
}

std::string WaitlistQueue::peek()
{
    if (!isEmpty()) {return queue[qFront];}
    else {return "<EMPTY QUEUE>";}
}

void WaitlistQueue::resize(int newSize)
{
    string* newQueue = new string[newSize];
    int i;
    int cnt=0;
    for (i=0; i<min(size(), newSize); i++) {
        if (i+qFront < qCapacity) {
            newQueue[i] = queue[i+qFront];
        } else {
            newQueue[i] = queue[cnt];
            cnt++;
        }
    }
    qFront = 0;
    qEnd = i-1;
    qCapacity = newSize;
    queue = newQueue;
}

int WaitlistQueue::size()
{
    if (qFront == -1 || qEnd == -1) {
        return 0;
    } else if (qFront <= qEnd) {
        return qEnd - qFront + 1;
    } else if (qFront-qEnd == 1) {
        if (!queue[qEnd].compare("") && !queue[qFront].compare("")) {return 0;}
        else {return qCapacity;}
    } else {
        return qCapacity-qFront + qEnd + 1;
    }
}

int WaitlistQueue::capacity()
{
    return qCapacity;
}

bool WaitlistQueue::isEmpty()
{
    if (size() == 0 || qFront==-1) {return true;}
    else {return false;}
}

bool WaitlistQueue::isFull()
{
    if (size() == qCapacity) {return true;}
    else {return false;}
}