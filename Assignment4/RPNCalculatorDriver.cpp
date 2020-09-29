/****************************************************************/
/*                  RPN Calculator Driver File                  */
/****************************************************************/
/*      TODO: Implement driver as described in the writeup      */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>
#include <iomanip> 
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

int main()
{
  // TODO - Declare a stack to hold the operands

  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;
  RPNCalculator rpnCalc;
  string sym;
  float number = 0.0;
  bool check = true;
  while(check ==true)
  {
    cout << "#> ";
    getline(cin, sym);
    if(isNumber(sym) == true && sym != "=" && sym != "+" && sym != "*")
    {
      number = stof(sym);
      rpnCalc.push(number);
    }
    else if(sym == "+" || sym == "*")
    {
      rpnCalc.compute(sym);
    }
    else if(sym == "=")
    {
      check = false;
      if(rpnCalc.isEmpty() == true)
      {
        cout << "No operands: Nothing to evaluate" << endl;
        return 0;
      }
      else
      {
        Operand *newTemp;
        newTemp = rpnCalc.getStackHead();
        if(newTemp -> next != NULL)
        {
          cout << "Invalid expression" << endl;
          return 0;
        }
        cout << setprecision(4) << newTemp -> number << endl;
      }
    }
  }
    return 0;
}
