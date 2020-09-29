#include "ProducerConsumer.hpp"
#include <iostream>

using namespace std;

ProducerConsumer :: ProducerConsumer()
{
  queueFront = -1;
  queueEnd = -1;
}

bool ProducerConsumer :: isEmpty()
{
  if(queueEnd == -1 && queueFront == -1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool ProducerConsumer :: isFull()
{
  if((queueEnd == SIZE - 1 && queueFront == 0)|| (queueEnd == (queueFront -1) % (SIZE -1 )))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void ProducerConsumer :: enqueue(string item)
{
  if(!isFull())
    {
      if(queueEnd == SIZE - 1)
        {
            queueEnd = 0;
        }
        else
        {
          queueEnd++;
        }
        queue[queueEnd] = item;
        if(queueFront == -1)
          {
            queueFront = 0;
          }
  }
  else
    {
      cout << "Queue full, cannot add new item" << endl;
    }
}


void ProducerConsumer :: dequeue()
{
  if(isEmpty() == true)
  {
    cout << "Queue empty, cannot dequeue an item" << endl;
    return;
  }
  else if(queueEnd == queueFront)
  {
    queue[queueFront] = "";
    queueFront = -1;
    queueEnd = -1;
    return;
  }
  if(queueFront == SIZE - 1)
  {
    queue[queueFront] = "";
    queueFront = 0;
    return;
  }
  queue[queueFront] = " ";
  queueFront++;
}

int ProducerConsumer :: queueSize()
{
  if(isEmpty())
  {
  return 0;
  }
  else if(queueFront < queueEnd)
  {
  return queueEnd + 1 - queueFront;
  }
  else
  {
  return (SIZE + 1) - (queueFront - queueEnd);
  }
}

string ProducerConsumer :: peek()
{
  if(!isEmpty())
  {
  return queue[queueFront];}
  else
  {
    cout << "Queue empty, cannot peek\n" << endl;
    return "";
  }
}
