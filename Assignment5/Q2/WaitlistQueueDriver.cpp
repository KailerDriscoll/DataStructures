
#include <iostream>
#include <string>
#include "WaitlistQueue.hpp"

using namespace std;

int main(int argc, char* argv[]) 
{
    cout << boolalpha;  // this displays boolean values as true and false

/*
    WaitlistQueue q(5);

    q.enqueue("buff_24");
    cout << q.peek() << endl;

    q.enqueue("buff_25");
    q.enqueue("buff_26");
    q.printInfo();

    q.dequeue();
    q.dequeue();
    q.printInfo();
*/
    // Another sample run below:
    /*
    WaitlistQueue q(5);

    q.enqueue("buff_24");
    q.enqueue("buff_25");
    q.enqueue("buff_26");
    q.printInfo();

    q.dequeue();
    q.dequeue();
    q.printInfo();

    q.dequeue();
    q.printInfo();
*/

    WaitlistQueue q(stoi(argv[1]));
    cout << "Initial queue capacity = " << argv[1] << endl;

    string word;
    while(true)
    {
        cout << "#> ";
        cin >> word;

        if (!word.compare("quit")) {
            q.printInfo();
            cout << "Contents of the queue:" << endl;
            while (!q.isEmpty()) {
                cout << q.peek() << " ";
                q.dequeue();
            }
            cout << endl;
            break;
        } else if (!word.compare("enqueue")) {
            cin >> word;
            q.enqueue(word);
        } else if (!word.compare("dequeue")) {
            q.dequeue();
        } else if (!word.compare("peek")) {
            cout << q.peek() << endl;
        } else if (!word.compare("resize")) {
            cin >> word;
            cout << "Resizing from " << q.capacity() << " to " << word << endl;
            q.resize(stoi(word));
        }
        q.printInfo();
    }

    return 0;
}