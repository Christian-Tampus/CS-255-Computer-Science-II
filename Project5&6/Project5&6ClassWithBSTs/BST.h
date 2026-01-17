/*
Student Name: Christian Tampus
File Name: BST.h
Description: BST Header File
Course Number: CS 255
Section Number: 02 (Tuesday/Thursday)
Due Date: 12/4
*/
/*
----------------------------------------------------------------------------------------------------
DEPENDENCIES
----------------------------------------------------------------------------------------------------
*/
#ifndef _BST_H
#define _BST_H
#include <iostream>
/*
----------------------------------------------------------------------------------------------------
NODE CLASS DECLERATION
----------------------------------------------------------------------------------------------------
*/
class Node {
private:
	/*
	----------------------------------------------------------------------------------------------------
	PRIVATE DATA MEMBERS
	----------------------------------------------------------------------------------------------------
	*/
	std::string Data;
	Node* LeftChild;
	Node* RightChild;
	friend class BST;
	Node(std::string NewData);
	~Node();
};
/*
----------------------------------------------------------------------------------------------------
BST CLASS DECLERATION
----------------------------------------------------------------------------------------------------
*/
class BST {
private:
	/*
	----------------------------------------------------------------------------------------------------
	PRIVATE DATA MEMBERS
	----------------------------------------------------------------------------------------------------
	*/
	Node* RootNode;
public:
	/*
	----------------------------------------------------------------------------------------------------
	PUBLIC DATA MEMBERS
	----------------------------------------------------------------------------------------------------
	*/
	BST();
	void DestructorDFS(Node* CurrentNode);
	~BST();
	bool Insert(std::string NewData);
	void PrintTraversal(char Order)const;
	void PrintTraversalDFS(Node* CurrentNode, char Order)const;
	int CountHeight(bool DisplayBST) const;
	int GetCountDFS(Node* CurrentNode)const;
	int GetCount()const;
	std::string GetMinMaxDFS(Node* CurrentNode, bool LeftChild, std::string ReturnString)const;
	std::string GetMin()const;
	std::string GetMax()const;
	std::string Search(std::string UserInputToSearch)const;
	std::string SearchDFS(Node* CurrentNode, std::string UserInputToSearch, std::string SearchResult)const;
};
#endif