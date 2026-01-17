#ifndef _LL_H
#define _LL_H
#include <iostream>
using namespace std;
class Node {
private:
	int Data;
	Node* Next;
	int LL_ID;
	Node();
	Node(int NewNodeData);
	Node(int NewNodeData, Node* NodePtr);
	void SetLL_ID(int LL_ID);
	~Node();
	friend class LL;
	friend ostream& operator<<(ostream& OS, const Node& Node);
};
class LL {
private:
	Node* Head;
	int LL_ID;
public:
	LL();
	~LL();
	LL(const LL& LL_RIGHT);
	LL& operator=(const LL& LL_RIGHT);
	void Deallocate();
	void CopyData(const LL& LL_RIGHT);
	bool Insert(int InsertNodeData);
	bool Remove(int RemoveNodeData);
	void Print()const;
};
#endif