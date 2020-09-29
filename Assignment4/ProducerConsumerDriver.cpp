/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
using namespace std;

void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
	ProducerConsumer newItem;
	string choice;
	string num1;
	string num2;
	string itemchoice;
	while(choice != "3")
	{
		menu();
		getline(cin,choice);
		switch(stoi(choice)){
			case 1:
				cout << "Enter the number of items to be produced:" << endl;
				getline(cin, num1);
				for(int i =0; i < stoi(num1); i++){
					cout << "Item" << i +1 << ":" << endl;
					getline(cin, itemchoice);
					newItem.enqueue(itemchoice);
				}
				break;

				case 2:
					cout << "Enter the number of items to be consumed:" << endl;
					getline(cin, num2);
					for(int i =0; i < stoi(num2); i++){
						cout << "Consumed: " << newItem.peek() << endl;
						newItem.dequeue();
						if(newItem.isEmpty() == true){
							cout << "No more items to consume from queue" << endl;
							break;
						}
					}
					break;

				case 3:
					cout << "Number of items in the queue:" << newItem.queueSize() << endl;
					break;
		}
	}
	return 0;
}
