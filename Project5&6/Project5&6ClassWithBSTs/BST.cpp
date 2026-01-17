/*
Student Name: Christian Tampus
File Name: BST.cpp
Description: BST C++ File
Course Number: CS 255
Section Number: 02 (Tuesday/Thursday)
Due Date: 12/4
*/
/*
----------------------------------------------------------------------------------------------------
DEPENDENCIES
----------------------------------------------------------------------------------------------------
*/
#include "BST.h";
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
/*
----------------------------------------------------------------------------------------------------
CONSTANTS
----------------------------------------------------------------------------------------------------
*/
const std::unordered_map<char, std::string> TRAVERSAL_ORDER_MAP = { {'1',"In-Order Traversal"},{'2',"Pre-Order Traversal"},{'3',"Post-Order Traversal"} };
/*
----------------------------------------------------------------------------------------------------
NODE CONSTRUCTOR
----------------------------------------------------------------------------------------------------
*/
/*
Constructor Name: Node::Node(std::string NewData);
Constructor Description: 1 Parameter Node Constructor, Sets Data To NewData Then Sets Left & Right Child Pointers To Nullptr
Return Value: None
Incoming Params: NewData (String)
Outgoing Params: None
*/
Node::Node(std::string NewData) :Data(NewData), LeftChild(nullptr), RightChild(nullptr) {};
/*
----------------------------------------------------------------------------------------------------
NODE DESTRUCTOR
----------------------------------------------------------------------------------------------------
*/
/*
Destructor Name: Node::~Node();
Destructor Description: Resets Data To An Empty String Then Sets Left & Right Child Pointers To Nullptr
Return Value: None
Incoming Params: None
Outgoing Params: None
*/
Node::~Node() {
	this->Data = "";
	this->LeftChild = nullptr;
	this->RightChild = nullptr;
};
/*
----------------------------------------------------------------------------------------------------
BST CONSTRUCTOR
----------------------------------------------------------------------------------------------------
*/
/*
Constructor Name: BST::BST();
Constructor Description: 0 Parameter BST Constructor, Sets RootNode To Nullptr
Return Value: None
Incoming Params: None
Outgoing Params: None
*/
BST::BST() :RootNode(nullptr) {};
/*
----------------------------------------------------------------------------------------------------
DESTRUCTOR DFS
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: void BST::DestructorDFS(Node* CurrentNode);
Method Description: Does A Post Order Traversal Then Deallocates The CurrentNode
Return Value: Void
Incoming Params: CurrentNode (Node Pointer)
Outgoing Params: None
*/
void BST::DestructorDFS(Node* CurrentNode) {
	if (CurrentNode != nullptr) {
		this->DestructorDFS(CurrentNode->LeftChild);
		this->DestructorDFS(CurrentNode->RightChild);
		delete CurrentNode;
	};
};
/*
----------------------------------------------------------------------------------------------------
BST DESTRUCTOR
----------------------------------------------------------------------------------------------------
*/
/*
Destructor Name: BST::~BST();
Destructor Description: Calls DestructorDFS Then Resets RootNode To Nullptr
Return Value: None
Incoming Params: None
Outgoing Params: None
*/
BST::~BST() {
	this->DestructorDFS(this->RootNode);
	this->RootNode = nullptr;
};
/*
----------------------------------------------------------------------------------------------------
INSERT
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: bool BST::Insert(std::string NewData);
Method Description: Inserts A New Node Into The BST, If It Already Exist Will Prevent Insertion, Uses A While Loop Method Instead Of DFS To Accomplish This
Return Value: Boolean
Incoming Params: NewData (String)
Outgoing Params: true/false (Boolean)
*/
bool BST::Insert(std::string NewData) {
	if (NewData.size() == 0) {
		return false;
	};
	Node* ParentNode = this->RootNode;
	Node* CurrentNode = this->RootNode;
	bool LeftDirection = true;
	if (CurrentNode == nullptr) {
		this->RootNode = new Node(NewData);
	}
	else {
		//I Used A While Loop Instead Of DFS :)
		while (CurrentNode != nullptr) {
			if (CurrentNode->Data.compare(NewData) == 0) {
				return false;
			};
			ParentNode = CurrentNode;
			LeftDirection = (CurrentNode->Data > NewData);
			CurrentNode = (CurrentNode->Data > NewData) ? CurrentNode->LeftChild : CurrentNode->RightChild;
		};
		if (LeftDirection) {
			ParentNode->LeftChild = new Node(NewData);
		}
		else {
			ParentNode->RightChild = new Node(NewData);
		};
	};
	return true;
};
/*
----------------------------------------------------------------------------------------------------
PRINT TRAVERSAL DFS
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: void BST::PrintTraversalDFS(Node* CurrentNode, char Order)const;
Method Description: Uses DFS Algorithm And Checks If Order Is Equivalent To Print It In The Desired Traversal Method
Return Value: Void
Incoming Params: CurrentNode (Node Pointer), Order (Character)
Outgoing Params: None
*/
void BST::PrintTraversalDFS(Node* CurrentNode, char Order)const {
	if (CurrentNode != nullptr) {
		//Can Handle All 3 Types Of Traversals
		if (Order == '2') {
			std::cout << CurrentNode->Data << ",";
		};
		this->PrintTraversalDFS(CurrentNode->LeftChild, Order);
		if (Order == '1') {
			std::cout << CurrentNode->Data << ",";
		};
		this->PrintTraversalDFS(CurrentNode->RightChild, Order);
		if (Order == '3') {
			std::cout << CurrentNode->Data << ",";
		};
	};
};
/*
----------------------------------------------------------------------------------------------------
PRINT TRAVERSAL
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: void BST::PrintTraversal(char Order)const;
Method Description: If BST Is Not Empty, Will Call The PrintTraversalDFS Method To Print All Nodes In BST According To The Order Input
Return Value: Void
Incoming Params: Order (Character)
Outgoing Params: None
*/
void BST::PrintTraversal(char Order)const {
	if (this->RootNode != nullptr) {
		std::cout << "[SYSTEM MESSAGE] " << TRAVERSAL_ORDER_MAP.at(Order) << ": <";
		this->PrintTraversalDFS(this->RootNode, Order);
		std::cout << ">" << std::endl;
	}
	else {
		std::cout << "[SYSTEM MESSAGE] BST Is Empty!" << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
COUNT HEIGHT
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: int BST::CountHeight(bool DisplayBST)const;
Method Description: Uses A BFS Algorithm To Count The Height Of The BST, If DisplayBST Is True, Will Print Out The Nodes On Each Level Of The BST
Return Value: MaxHeight (Integer)
Incoming Params: DisplayBST (Boolean)
Outgoing Params: MaxHeight (Integer)
*/
int BST::CountHeight(bool DisplayBST)const {
	if (this->RootNode == nullptr) {
		if (DisplayBST) {
			std::cout << "[LEVEL 0]: (Empty BST)" << std::endl;
		};
		return 0;
	};
	//Breath First Search Algorithm (BFS) :)
	int MaxHeight = 0;
	int CurrentLevel = 0;
	std::vector<Node*> QueueVector = { this->RootNode };
	std::vector<int> LevelVector = { 0 };
	//This Only Works If The DisplayBST Input Is True, Used For Operation [6] Display BST
	if (DisplayBST) {
		std::cout << "[LEVEL 0]: ";
	};
	while (QueueVector.size() > 0) {
		Node* CurrentNode = QueueVector[0];
		int CurrentLevelVector = LevelVector[0];
		QueueVector.erase(QueueVector.begin());
		LevelVector.erase(LevelVector.begin());
		//This Only Works If The DisplayBST Input Is True, Used For Operation [6] Display BST
		if (DisplayBST) {
			if (CurrentLevel < CurrentLevelVector) {
				std::cout << std::endl;
				std::cout << "[LEVEL " << CurrentLevelVector << "]: ";
				CurrentLevel = CurrentLevelVector;
			};
			std::cout << "(Node: " << CurrentNode->Data << "; Left Child: ";
			if (CurrentNode->LeftChild != nullptr) {
				std::cout << CurrentNode->LeftChild->Data;
			}
			else {
				std::cout << "NULLPTR";
			}
			std::cout << "; Right Child: ";
			if (CurrentNode->RightChild != nullptr) {
				std::cout << CurrentNode->RightChild->Data;
			}
			else {
				std::cout << "NULLPTR";
			}
			std::cout << ")";
		};
		if (CurrentNode->LeftChild != nullptr || CurrentNode->RightChild != nullptr) {
			MaxHeight = MaxHeight < CurrentLevelVector + 1 ? CurrentLevelVector + 1 : MaxHeight;
			if (CurrentNode->LeftChild != nullptr) {
				QueueVector.push_back(CurrentNode->LeftChild);
				LevelVector.push_back(CurrentLevelVector + 1);
			};
			if (CurrentNode->RightChild != nullptr) {
				QueueVector.push_back(CurrentNode->RightChild);
				LevelVector.push_back(CurrentLevelVector + 1);
			};
		};
	};
	//This Only Works If The DisplayBST Input Is True, Used For Operation [6] Display BST
	if (DisplayBST) {
		std::cout << std::endl;
	};
	return MaxHeight;
};
/*
----------------------------------------------------------------------------------------------------
GET COUNT DFS
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: int BST::GetCountDFS(Node* CurrentNode)const;
Method Description: Uses DFS Algorithm To Count The Number Of Nodes In A BST
Return Value: Integer
Incoming Params: CurrentNode (Node Pointer)
Outgoing Params: 0/1 + LeftChildNodeCount + RightChildNodeCount (Integer)
*/
int BST::GetCountDFS(Node* CurrentNode)const {
	if (CurrentNode != nullptr) {
		int LeftChildNodeCount = this->GetCountDFS(CurrentNode->LeftChild);
		int RightChildNodeCount = this->GetCountDFS(CurrentNode->RightChild);
		return 1 + LeftChildNodeCount + RightChildNodeCount;
	}
	else {
		return 0;
	};
}
/*
----------------------------------------------------------------------------------------------------
GET COUNT
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: int BST::GetCount()const;
Method Description: Calls GetCountDFS With The RootNode As Input Then Returns The Result
Return Value: Integer
Incoming Params: None
Outgoing Params: this->GetCountDFS(this->RootNode) (Integer)
*/
int BST::GetCount()const {
	return this->GetCountDFS(this->RootNode);
};
/*
----------------------------------------------------------------------------------------------------
GET MIN MAX DFS
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: std::string BST::GetMinMaxDFS(Node* CurrentNode, bool LeftChild, std::string ReturnString)const;
Method Description: Gets The Minimum Or Maximum Value In A BST Based On If LeftChild Is True Or False
Return Value: String
Incoming Params: CurrentNode (Node Pointer), LeftChild (Boolean), ReturnString (String)
Outgoing Params: ReturnString (String)
*/
std::string BST::GetMinMaxDFS(Node* CurrentNode, bool LeftChild, std::string ReturnString)const {
	if (CurrentNode != nullptr) {
		//This Can Handle Min Or Max Values
		if (LeftChild) {
			return this->GetMinMaxDFS(CurrentNode->LeftChild, LeftChild, CurrentNode->Data);
		}
		else {
			return this->GetMinMaxDFS(CurrentNode->RightChild, LeftChild, CurrentNode->Data);
		};
	}
	else {
		return ReturnString;
	};
};
/*
----------------------------------------------------------------------------------------------------
GET MIN
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: std::string BST::GetMin()const;
Method Description: Calls GetMinMaxDFS With LeftChild As True Then Returns The Result
Return Value: String
Incoming Params: None
Outgoing Params: this->GetMinMaxDFS(this->RootNode, true, "(Empty BST)") (String)
*/
std::string BST::GetMin()const {
	return this->GetMinMaxDFS(this->RootNode, true, "(Empty BST)");
};
/*
----------------------------------------------------------------------------------------------------
GET MAX
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: std::string BST::GetMax()const;
Method Description: Calls GetMinMaxDFS With LeftChild As False Then Returns The Result
Return Value: String
Incoming Params: None
Outgoing Params: this->GetMinMaxDFS(this->RootNode, false, "(Empty BST)") (String)
*/
std::string BST::GetMax()const {
	return this->GetMinMaxDFS(this->RootNode, false, "(Empty BST)");
};
/*
----------------------------------------------------------------------------------------------------
SEARCH
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: std::string BST::Search(std::string UserInputToSearch)const;
Method Description: If Root Not Is Not A NullPtr, Calls SearchDFS To Find If UserInputToSearch Is In BST
Return Value: String
Incoming Params: None
Outgoing Params: this->SearchDFS(this->RootNode, UserInputToSearch, "Node Not Found!") (String)
*/
std::string BST::Search(std::string UserInputToSearch)const {
	if (this->RootNode == nullptr) {
		return "(Empty BST)";
	};
	return this->SearchDFS(this->RootNode, UserInputToSearch, "Node Not Found!");
};
/*
----------------------------------------------------------------------------------------------------
SEARCH DFS
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: std::string BST::SearchDFS(Node* CurrentNode, std::string UserInputToSearch, std::string SearchResult)const;
Method Description: Uses DFS Algorithm To Search If Is Inside UserInputToSearch Node Is Inside The BST By Comparing If It Is Greater Than Or Less Than Current Node To Move Towards The Approrpiate Direction, If It Is Equivalent, Prints The Node, LeftChild & RightChild Values
Return Value: String
Incoming Params: CurrentNode (Node Pointer), UserInputToSearch (String), SearchResult (String)
Outgoing Params: SearchResult (String)
*/
std::string BST::SearchDFS(Node* CurrentNode, std::string UserInputToSearch, std::string SearchResult)const {
	if (CurrentNode != nullptr) {
		if (CurrentNode->Data.compare(UserInputToSearch) == 0) {
			std::string LeftChild = "NULLPTR";
			std::string RightChild = "NULLPTR";
			if (CurrentNode->LeftChild != nullptr) {
				LeftChild = CurrentNode->LeftChild->Data;
			};
			if (CurrentNode->RightChild != nullptr) {
				RightChild = CurrentNode->RightChild->Data;
			};
			return "(Node: " + CurrentNode->Data + "; LeftChild: " + LeftChild + "; RightChild: " + RightChild + ")";
		}
		else if (CurrentNode->Data > UserInputToSearch) {
			return SearchDFS(CurrentNode->LeftChild, UserInputToSearch, SearchResult);
		}
		else if (CurrentNode->Data < UserInputToSearch) {
			return SearchDFS(CurrentNode->RightChild, UserInputToSearch, SearchResult);
		};
	}
	else {
		return SearchResult;
	};
};