#include <iostream>
#include "SentenceReverser.hpp"

using namespace std;

SentenceReverser::SentenceReverser()
{
    stackHead = nullptr;
}

SentenceReverser::~SentenceReverser()
{
    while (stackHead) {
        pop();
    }
}

bool SentenceReverser::isEmpty()
{
	if (stackHead==nullptr) {return true;}
    else {return false;}
}

void SentenceReverser::push(string word)
{
    Word *newNode = new Word;
    newNode->next = stackHead;
    newNode->word = word;
    stackHead = newNode;
    /*
    if (stackHead) {
        Word *node = stackHead;
        while (node->next) {
            node = node->next;
        }
        node->next = newNode;
    } else {
        stackHead = newNode;
    }
    */
}

string SentenceReverser::pop()
{
    if (isEmpty()) {
        cout << "Stack empty, cannot pop a word." << endl;
        return "";
    }

    string word;
    Word *tempWord = stackHead;
    stackHead = stackHead->next;
    word = tempWord->word;
    delete tempWord;
    return word;

    /*
    
    if (stackHead->next == nullptr) {
        word = stackHead->word;
        delete stackHead;
        stackHead = nullptr;
        return word;
    }

    Word* node = stackHead;
    while (node->next->next) {
        node = node->next;
    }
    word = node->next->word;
    delete(node->next);
    node->next = nullptr;
    return word;
    */

}

Word* SentenceReverser::peek()
{
    if (stackHead) {
        // /*
        // Word *node = stackHead;
        // while (node->next) {
        //     node = node->next;
        // }
        // return node;
        // */
        return stackHead;
    } else {
        cout << "Stack empty, cannot peek." << endl;
        return nullptr;
    } 
    
}

void SentenceReverser::evaluate(string* s, int size)
{
    /*TODO: 1. Scan the array s from start
            2. Check for opening and closing brackets.
            3. Push each element on the stack till you encounter a "]"
            4. Then keep popping (& processing) from the stack till you get a "[".
            5. Handle the boundery cases as required.
            6. Read the writeup for more details. Another example is in Appendix 2.
    */
   int cnt = 0;
    for (int i=0; i<size; i++) {
        if (s[i][0] == ']') {
            while (peek()->word[0] != '[') {
                cout << pop() << " ";
                cnt++;
            }
        }
        push(s[i]);
        if (s[i][0] == ']') {
            pop();pop();
            cout << "- " << cnt << endl;
            cnt=0;
        }
    }
    if (!isEmpty()) {cout << "err: Invalid String" <<endl;}
}
