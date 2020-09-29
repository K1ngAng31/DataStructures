#include "RPNCalculator.hpp"
#include <iostream>

using namespace std;

RPNCalculator::RPNCalculator()
{
  stackHead = NULL;
}

RPNCalculator::~RPNCalculator()
{
  while(stackHead != NULL)
  {
    Operand *tempO = stackHead;
    stackHead = stackHead -> next;
    delete tempO;
  }
}

bool RPNCalculator::isEmpty()
{
  if(stackHead == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void RPNCalculator::push(float number)
{
  if(!isEmpty())
  {
    Operand *tempNode = new Operand;
    tempNode -> number = number;
    tempNode ->next = stackHead;
    stackHead = tempNode;
  }
  else
  {
    Operand *tempNode = new Operand;
    tempNode -> number = number;
    stackHead = tempNode;
    stackHead -> next = NULL;
  }
}

void RPNCalculator::pop()
{
  if(stackHead == NULL)
  {
    cout << "Stack empty, cannot pop an item" << endl;
    return;
  }
  else
  {
    Operand *timetoPop = stackHead;
    stackHead = stackHead -> next;
    delete timetoPop;
  }

}

Operand* RPNCalculator::peek()
{
  if(stackHead == NULL)
  {
    cout << "Stack empty, cannot peak" << endl;
    return NULL;
  }
  else
  {
    if(!isEmpty())
    {
      return stackHead;
    }
  }

}

bool RPNCalculator::compute(string symbol)
{
  Operand *number1;
  Operand *number2;
  float input1 = 0.0;
  float input2 = 0.0;
  float result = 0.0;
if(symbol == "*")
  {
      if(!isEmpty())
      {
        number1 = peek();
        input1 = number1 -> number;
        pop();
        if(!isEmpty())
        {
          number2 = peek();
          input2 = number2 -> number;
          pop();
          result = input1 * input2;
          push(result);
          return true;
        }
        else
        {
          cout << "err: not enough operands" << endl;
          push(input1);
          return false;
        }
      }
      else
      {
        cout << "err: not enough operands" << endl;
        return false;
      }
    }
    if(symbol == "+")
      {
        if(!isEmpty())
        {
          number1 = peek();
          input1 = number1 -> number;
          pop();
          if(!isEmpty())
          {
            number2 = peek();
            input2 = number2 -> number;
            pop();
            result = input1 + input2;
            push(result);
            return true;
          }
          else
          {
            cout << "err: not enough operands" << endl;
            push(input1);
            return false;
          }
        }
        else
        {
          cout << "err: not enough operands" << endl;
          return false;
        }
      }
  else
    {
      cout << "err: invalid operation" << endl;
      return false;
    }
}
