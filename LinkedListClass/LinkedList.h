#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <iostream>
class Node{
	public:
		int NodeValue;
		Node* NextNode;
		Node(int NewNodeValue);
};
class LinkedList{
	private:
		Node* HeadNode;
	public:
		LinkedList();
		LinkedList(int NewHeadNodeValue);
		void InsertAtTail(int NewNodeValue);
		void InsertAtHead(int NewNodeValue);
		void DeleteNode(int NodeValueToDelete);
		void DisplayNodes(std::string Method)const;
		//IMPLEMENT INSERT NODE AT A POSITION
		//IMPLEMENT DELETE NODE AT A POSITION
		//IMPLEMENT CHECK FOR CYCLES
		//IMPLEMENT REVERSE THE LINKED LIST
};
#endif