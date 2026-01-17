#include "LinkedList.h"
#include <string>
Node::Node(int NewNodeValue):NodeValue(NewNodeValue),NextNode(nullptr){};
LinkedList::LinkedList():HeadNode(nullptr){
	this->DisplayNodes("Constructor! Linked List: ");
};
LinkedList::LinkedList(int NewHeadNodeValue){
	Node* NewHeadNode = new Node(NewHeadNodeValue);
	this->HeadNode = NewHeadNode;
	this->DisplayNodes("Constructor! Value: ("+std::to_string(NewHeadNodeValue)+") Linked List: ");
};
void LinkedList::InsertAtTail(int NewNodeValue){
	if (this->HeadNode == nullptr){
		Node* NewTailNode = new Node(NewNodeValue);
		this->HeadNode = NewTailNode;
	}else{
		Node* CurrentNode = this->HeadNode;
		while(CurrentNode->NextNode != nullptr){
			CurrentNode = CurrentNode->NextNode;
		};
		Node* NewTailNode = new Node(NewNodeValue);
		CurrentNode->NextNode = NewTailNode;
	};
	this->DisplayNodes("Insert At Tail! Value: ("+std::to_string(NewNodeValue)+") Linked List: ");
};
void LinkedList::InsertAtHead(int NewNodeValue){
	Node* NewHeadNode = new Node(NewNodeValue);
	NewHeadNode->NextNode = this->HeadNode;
	this->HeadNode = NewHeadNode;
	this->DisplayNodes("Insert At Head! Value: ("+std::to_string(NewNodeValue)+") Linked List: ");
};
void LinkedList::DeleteNode(int NodeValueToDelete){
	if (this->HeadNode != nullptr){
		Node* PreviousNode = new Node(0);
		Node* CurrentNode = this->HeadNode;
		PreviousNode->NextNode = CurrentNode;
		while(CurrentNode != nullptr){
			if (CurrentNode->NodeValue == NodeValueToDelete){
				if (CurrentNode == this->HeadNode){
					this->HeadNode = CurrentNode->NextNode;
				};
				Node* NodeToDelete = CurrentNode;
				PreviousNode->NextNode = CurrentNode->NextNode;
				CurrentNode = CurrentNode->NextNode;
				delete NodeToDelete;
				this->DisplayNodes("Delete Node! Value: ("+std::to_string(NodeValueToDelete)+") Linked List: ");
			}else{
				CurrentNode = CurrentNode->NextNode;
				PreviousNode = PreviousNode->NextNode;
			};
		};
	};
	this->DisplayNodes("[FINAL] Delete Node! Value: ("+std::to_string(NodeValueToDelete)+") Linked List: ");
};
void LinkedList::DisplayNodes(std::string Method)const{
	std::cout << Method;
	Node* CurrentNode = this->HeadNode;
	while (CurrentNode != nullptr){
		std::cout << "(" <<  CurrentNode->NodeValue << ")" << (CurrentNode->NextNode != nullptr ? "->" : "->(NULL)."); 
		CurrentNode = CurrentNode->NextNode;	
	};
	std::cout << std::endl;
};
//Item To Delete = 0
//EMPTY
//           H
//      D
// P         N
//           C    N
//(T)->(0)->(0)->(1)->(0)->(2)->(3)->(0)


//Item To Delete = 0
//EMPTY
//      H
//                     
//                P         N
//                          C    N
//(T)->(1)->(2)->(3)-