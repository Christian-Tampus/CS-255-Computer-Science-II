#include <iostream>
#include "LinkedList.h"
using namespace std;
int main(){
	std::cout << "LINKED LIST 1!" << std::endl;
	LinkedList LinkedList1;
	LinkedList1.InsertAtTail(0);
	LinkedList1.InsertAtTail(0);
	LinkedList1.InsertAtTail(1);
	LinkedList1.InsertAtTail(0);
	LinkedList1.InsertAtTail(2);
	LinkedList1.InsertAtTail(3);
	LinkedList1.InsertAtTail(4);
	LinkedList1.InsertAtTail(0);
	LinkedList1.InsertAtTail(0);
	LinkedList1.InsertAtTail(5);
	LinkedList1.InsertAtTail(0);
	LinkedList1.InsertAtTail(0);
	LinkedList1.InsertAtTail(0);
	LinkedList1.DeleteNode(0);
	/*
	LinkedList1.InsertAtHead(0);
	LinkedList1.InsertAtHead(-1);
	LinkedList1.InsertAtHead(-2);
	LinkedList1.InsertAtHead(-3);
	LinkedList1.InsertAtTail(1);
	LinkedList1.InsertAtTail(2);
	LinkedList1.InsertAtTail(3);
	std::cout << "LINKED LIST 2!" << std::endl;
	LinkedList LinkedList2(1);
	LinkedList2.InsertAtTail(2);
	LinkedList2.InsertAtTail(3);
	LinkedList2.InsertAtHead(0);
	LinkedList2.InsertAtHead(-1);
	LinkedList2.InsertAtHead(-2);
	LinkedList2.InsertAtHead(-3);
	std::cout << "END LINKED LIST PROGRAM!" << std::endl;
	*/
	return 0;
};