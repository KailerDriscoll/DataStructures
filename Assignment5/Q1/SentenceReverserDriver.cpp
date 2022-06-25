#include <iostream>
#include <cmath>
#include <iomanip>
#include "SentenceReverser.hpp"

using namespace std;

int main()
{
	
  SentenceReverser stack;
  stack.push("datastructures");
  Word* stackTop = stack.peek();
  cout << "Top of the stack: " << stackTop->word<< endl;

  /*
  // stack to hold the elements
  SentenceReverser stack;  

  int numElement = 0; 
  string* inparr = new string[50];

  string word;
  cout << "Enter the sentences separated by '[' and ']' " << endl;

  while(true)
  {
    cout << "#> ";
    getline(cin, word);
    //  TODO
    //    1. Read input until you encounter a "end"
    //    2. store them in inparr
    
    if(word.compare("end")) {
      inparr[numElement] = word;
      numElement++;
    } else {
      cout << endl;
      if (numElement == 0) {cout << "No sentences: Nothing to evaluate" << endl;}
      else {stack.evaluate(inparr, numElement);}
      break;
    }
   }

  //  TODO - If the inparr is empty then print "No sentences: Nothing to evaluate"
  //           else call the evaluate function
  // 
  */

  return 0;
  
}
