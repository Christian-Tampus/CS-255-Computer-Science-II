#include "LL.h"
/*
----------------------------------------------------------------------------------------------------
NODE CONSTRUCTORS
----------------------------------------------------------------------------------------------------
*/
Node::Node() :Next(nullptr) {};
Node::Node(int NewNodeData) :Data(NewNodeData), Next(nullptr) {};
Node::Node(int NewNodeData, Node* NodePtr) :Data(NewNodeData), Next(NodePtr) {};
/*
----------------------------------------------------------------------------------------------------
NODE DESTRUCTOR
----------------------------------------------------------------------------------------------------
*/
Node::~Node() {
	this->Next = nullptr;
	std::cout << "[SYSTEM MESSAGE] Node Destructor Called! Node Data Removed: " << this->Data << " From Linked List LL_ID: " << this->LL_ID << std::endl;
};
/*
----------------------------------------------------------------------------------------------------
NODE SET LL ID
----------------------------------------------------------------------------------------------------
*/
void Node::SetLL_ID(int LL_ID) {
	this->LL_ID = LL_ID;
};
/*
----------------------------------------------------------------------------------------------------
LL CONSTRUCTOR
----------------------------------------------------------------------------------------------------
*/
LL::LL() :Head(nullptr) {
	this->LL_ID = std::rand() * 1000;
};
/*
----------------------------------------------------------------------------------------------------
LL DEALLOCATE
----------------------------------------------------------------------------------------------------
*/
void LL::Deallocate() {
	Node* CurrentNodePointer = this->Head;
	while (CurrentNodePointer != nullptr) {
		Node* NextNodePointer = CurrentNodePointer->Next;
		delete CurrentNodePointer;
		CurrentNodePointer = NextNodePointer;
	};
	this->Head = nullptr;
};
/*
----------------------------------------------------------------------------------------------------
LL DESTRUCTOR
----------------------------------------------------------------------------------------------------
*/
LL::~LL() {
	this->Deallocate();
	std::cout << "[SYSTEM MESSAGE] Linked List Destructor Called! LL_ID: " << this->LL_ID << std::endl;
};
/*
----------------------------------------------------------------------------------------------------
LL COPYDATA
----------------------------------------------------------------------------------------------------
*/
void LL::CopyData(const LL& LL_RIGHT) {
	if (!this->LL_ID) {
		this->LL_ID = std::rand() * 1000;
	};
	this->Head = nullptr;
	Node* CurrentNodePointer = this->Head;
	Node* LL_RIGHT_CurrentNodePointer = LL_RIGHT.Head;
	while (LL_RIGHT_CurrentNodePointer != nullptr) {
		if (CurrentNodePointer == nullptr) {
			this->Head = new Node(LL_RIGHT_CurrentNodePointer->Data, nullptr);
			this->Head->SetLL_ID(this->LL_ID);
			CurrentNodePointer = this->Head;
		}
		else {
			CurrentNodePointer->Next = new Node(LL_RIGHT_CurrentNodePointer->Data, nullptr);
			CurrentNodePointer->Next->SetLL_ID(this->LL_ID);
			CurrentNodePointer = CurrentNodePointer->Next;
		};
		LL_RIGHT_CurrentNodePointer = LL_RIGHT_CurrentNodePointer->Next;
	};
};
/*
----------------------------------------------------------------------------------------------------
LL COPY CONSTRUCTOR
----------------------------------------------------------------------------------------------------
*/
LL::LL(const LL& LL_RIGHT) {
	this->CopyData(LL_RIGHT);
	std::cout << "[SYSTEM MESSAGE] Copied Linked List!" << std::endl;
};
/*
----------------------------------------------------------------------------------------------------
LL ASSIGNMENT OPERATOR
----------------------------------------------------------------------------------------------------
*/
LL& LL::operator=(const LL& LL_RIGHT) {
	if (this != &LL_RIGHT) {
		this->Deallocate();
		this->CopyData(LL_RIGHT);
	};
	std::cout << "[SYSTEM MESSAGE] Assignment Operator Linked List!" << std::endl;
	return (*this);
};
/*
----------------------------------------------------------------------------------------------------
EXTRACTION OPERATOR OVERLOAD
----------------------------------------------------------------------------------------------------
*/
ostream& operator<<(ostream& OS, const Node& Node) {
	std::string NextNodeString = "NULL POINTER";
	if (Node.Next) {
		NextNodeString = "EXIST";
	};
	OS << "Node Data: " << Node.Data << " Node Next: " << NextNodeString;
	return OS;
};
/*
----------------------------------------------------------------------------------------------------
LL INSERT
----------------------------------------------------------------------------------------------------
*/
bool LL::Insert(int InsertNodeData) {
	Node* InsertionPointer = nullptr;
	if (this->Head == nullptr || InsertNodeData < this->Head->Data) {
		this->Head = new Node(InsertNodeData, this->Head);
		this->Head->SetLL_ID(this->LL_ID);
		InsertionPointer = this->Head;
		std::cout << "[SYSTEM MESSAGE] Inserted New Node Data: (" << InsertNodeData << ") At Or Before Head!" << std::endl;
	}
	else {
		bool IsDuplicate = false;
		Node* PreviousNodePointer = this->Head;
		Node* CurrentNodePointer = this->Head;
		while (CurrentNodePointer != nullptr) {
			if (PreviousNodePointer->Data < InsertNodeData && InsertNodeData < CurrentNodePointer->Data) {
				PreviousNodePointer->Next = new Node(InsertNodeData, CurrentNodePointer);
				PreviousNodePointer->Next->SetLL_ID(this->LL_ID);
				InsertionPointer = PreviousNodePointer->Next;
				std::cout << "[SYSTEM MESSAGE] Inserted New Node Data: (" << InsertNodeData << ") In Betweeen Nodes: (" << PreviousNodePointer->Data << ")->(" << InsertNodeData << ")->(" << CurrentNodePointer->Data << ")!" << std::endl;
				break;
			}
			else if (PreviousNodePointer->Data == InsertNodeData || CurrentNodePointer->Data == InsertNodeData) {
				std::cout << "[SYSTEM ERROR] Attempted To Insert: (" << InsertNodeData << ") To Linked List When It Already Exists!" << std::endl;
				IsDuplicate = true;
				break;
			};
			PreviousNodePointer = CurrentNodePointer;
			CurrentNodePointer = CurrentNodePointer->Next;
		};
		if (InsertionPointer == nullptr && !IsDuplicate) {
			PreviousNodePointer->Next = new Node(InsertNodeData, nullptr);
			PreviousNodePointer->Next->SetLL_ID(this->LL_ID);
			InsertionPointer = PreviousNodePointer->Next;
			std::cout << "[SYSTEM MESSAGE] Inserted New Node Data: (" << InsertNodeData << ")->(NULLPTR) After Tail!" << std::endl;
		};
	};
	return InsertionPointer != nullptr;
};
/*
----------------------------------------------------------------------------------------------------
LL REMOVE
----------------------------------------------------------------------------------------------------
*/
bool LL::Remove(int RemoveNodeData) {
	bool RemovalSuccess = false;
	if (this->Head == nullptr) {
		std::cout << "[SYSTEM ERROR] Attempted To Remove: " << RemoveNodeData << " When Linked List Is Empty!" << std::endl;
	}
	else if (this->Head != nullptr && this->Head->Data == RemoveNodeData) {
		Node* TempNodePointer = this->Head->Next;
		delete this->Head;
		this->Head = nullptr;
		this->Head = TempNodePointer;
		std::cout << "[SYSTEM MESSAGE] Remove: " << RemoveNodeData << " From Linked List Head!" << std::endl;
	}
	else {
		Node* PreviousNodePointer = this->Head;
		Node* CurrentNodePointer = this->Head;
		while (CurrentNodePointer != nullptr) {
			if (CurrentNodePointer->Data == RemoveNodeData) {
				PreviousNodePointer->Next = nullptr;
				PreviousNodePointer->Next = CurrentNodePointer->Next;
				delete CurrentNodePointer;
				CurrentNodePointer = nullptr;
				RemovalSuccess = true;
				std::cout << "[SYSTEM MESSAGE] Remove: " << RemoveNodeData << " From Linked List!" << std::endl;
				break;
			};
			PreviousNodePointer = CurrentNodePointer;
			CurrentNodePointer = CurrentNodePointer->Next;
		};
		if (!RemovalSuccess) {
			std::cout << "[SYSTEM ERROR] Attempted To Remove: " << RemoveNodeData << " When It Does Not Exist In The Linked List!" << std::endl;
		};
	};
	return RemovalSuccess;
};
/*
----------------------------------------------------------------------------------------------------
LL PRINT
----------------------------------------------------------------------------------------------------
*/
void LL::Print()const {
	std::cout << "[SYSTEM MESSAGE] Linked List: ";
	Node* CurrentNodePointer = this->Head;
	if (CurrentNodePointer == nullptr) {
		std::cout << "(HEAD)->(NULLPTR) Size: 0";
	}
	else {
		int LinkedListSize = 0;
		while (CurrentNodePointer != nullptr) {
			std::cout << "(" << CurrentNodePointer->Data << ")->";
			CurrentNodePointer = CurrentNodePointer->Next;
			LinkedListSize++;
		};
		std::cout << "(NULLPTR) Size: " << LinkedListSize;
	};
	std::cout << " LL_ID: " << this->LL_ID << std::endl;
};