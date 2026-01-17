/*
Student Name: Christian Tampus
File Name: TampusChristian_255_P6.cpp
Description: BST Source/Driver C++ File
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
#include <string>
#include <fstream>
#include <set>
#include <unordered_map>
#include <vector>
#include <iomanip>
/*
----------------------------------------------------------------------------------------------------
CONSTANTS
----------------------------------------------------------------------------------------------------
*/
const std::string TXT_SUFFIX = ".txt";
const std::string MAIN_MENU_ARRAY[10] = { "Operations Menu","[1] Load File Contents Into BST","[2] Print Traversals","[3] Print Stats","[4] Search","[5] Print Comparisons","[6] Display BST","[m] Print Menu","[x] Cancel","[q] Quit Program" };
const std::unordered_map<char, std::vector<std::string>> SUB_MENU_ARRAY = { {'2',{"Print Traversals Menu","[1] Print In-Order Traversal","[2] Print Pre-Order Traversal","[3] Print Post-Order Traversal","[x] Cancel"}},{'3',{"Print Stats Menu","[1] Print Tree Height","[2] Print Node Count","[3] Print Min Value","[4] Print Max Value","[x] Cancel"}} };
const std::unordered_map<char, std::set<char>> VALID_SUB_MENU_OPTIONS_MAP = { {'2',{'1','2','3','x'}},{'3',{'1','2','3','4','x'}} };
const std::set<char> VALID_SUB_MENU_OPTIONS = { '2','3' };
const std::set<char> VALID_MAIN_MENU_OPTIONS = { '1','2','3','4','5','6','m','x','q' };
const std::unordered_map<char, std::string> MAIN_MENU_MAP = { {'1',"Load File Contents Into BST"},{'2',"Print Traversals"},{'3',"Print Stats"},{'4',"Search"},{'5',"Print Comparisons"},{'6',"Display BST"},{'m',"Print Menu"},{'x',"Cancel"},{'q',"Quit Program"} };
struct BSTInfo {
	std::string FileName;
	std::string Height;
	std::string Count;
	//I Overloaded The [] Operator So That I Can Just Index It Instead Of Having To Use If/Else Statements Similar To Lua :)
	std::string& operator[](const std::string& IndexKey) {
		if (IndexKey.compare("FileName") == 0) {
			return FileName;
		}
		else if (IndexKey.compare("Height") == 0) {
			return Height;
		}
		else if (IndexKey.compare("Count") == 0) {
			return Count;
		};
	};
};
/*
----------------------------------------------------------------------------------------------------
FUNCTION PROTOTYPES
----------------------------------------------------------------------------------------------------
*/
void PrintMainMenu();
void GetUserInputForOperations();
char CheckUserInputForOperations(const std::set<char> InputMenuOptionsSet);
std::vector<std::string> LoadFile(std::string& FileName);
void PrintLine(int Iterations, std::vector<std::string> FileNamesVector, std::unordered_map<std::string, BSTInfo> BSTInfoMap, std::string DataType, bool IsHeader);
/*
----------------------------------------------------------------------------------------------------
MAIN/DRIVER FUNCTION
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: main();
Function Description: Calls PrintMainMenu() Then Calls GetUserInputForOperations()
Return Value: 0 (Integer)
Incoming Params: None
Outgoing Params: 0 (Integer)
*/
int main() {
	std::cout << "Class With BSTs" << std::endl;
	std::cout << "Developed By: Christian Tampus" << std::endl;
	PrintMainMenu();
	GetUserInputForOperations();
};
/*
----------------------------------------------------------------------------------------------------
FUNCTION DEFINITIONS
----------------------------------------------------------------------------------------------------
*/
/*
----------------------------------------------------------------------------------------------------
PRINT MAIN MENU
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: PrintMainMenu();
Function Description: Prints MAIN_MENU_ARRAY Contents
Return Value: Void
Incoming Params: None
Outgoing Params: None
*/
void PrintMainMenu() {
	for (int Index = 0; Index < sizeof(MAIN_MENU_ARRAY) / sizeof(MAIN_MENU_ARRAY[0]); Index++) {
		std::cout << MAIN_MENU_ARRAY[Index] << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
GET USER INPUT FOR OPERATIONS
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: GetUserInputForOperations();
Function Description: Gets User Input For Operations Then Executes Them
Return Value: Void
Incoming Params: None
Outgoing Params: None
*/
void GetUserInputForOperations() {
	std::string UserInputOperation;
	char CharUserInputMainMenuOperation = ' ';
	std::vector<std::string> FileNamesVector;
	std::unordered_map<std::string, BSTInfo> BSTInfoMap;
	BST* BST1 = new BST;
	do {
		CharUserInputMainMenuOperation = CheckUserInputForOperations(VALID_MAIN_MENU_OPTIONS);
		auto ValidSubMenuOptionsSetIterator = VALID_SUB_MENU_OPTIONS.find(CharUserInputMainMenuOperation);
		if (ValidSubMenuOptionsSetIterator != VALID_SUB_MENU_OPTIONS.end()) {
			for (int Index = 0; Index < SUB_MENU_ARRAY.at(CharUserInputMainMenuOperation).size(); Index++) {
				std::cout << SUB_MENU_ARRAY.at(CharUserInputMainMenuOperation)[Index] << std::endl;
			};
			char CharUserInputSubMenuOperation = CheckUserInputForOperations(VALID_SUB_MENU_OPTIONS_MAP.at(CharUserInputMainMenuOperation));
			if (CharUserInputSubMenuOperation != 'x') {
				if (CharUserInputMainMenuOperation == '2') {
					(*BST1).PrintTraversal(CharUserInputSubMenuOperation);
				}
				else if (CharUserInputMainMenuOperation == '3') {
					switch (CharUserInputSubMenuOperation) {
					case '1':
						std::cout << "[SYSTEM MESSAGE] Tree Height: " << (*BST1).CountHeight(false) << std::endl;
						break;
					case '2':
						std::cout << "[SYSTEM MESSAGE] Node Count: " << (*BST1).GetCount() << std::endl;
						break;
					case '3':
						std::cout << "[SYSTEM MESSAGE] Min Value: " << (*BST1).GetMin() << std::endl;
						break;
					case '4':
						std::cout << "[SYSTEM MESSAGE] Max Value: " << (*BST1).GetMax() << std::endl;
						break;
					};
				};
			}
			else {
				std::cout << "[SYSTEM MESSAGE] Cancelled Successfully!" << std::endl;
			};
		}
		else {
			if (CharUserInputMainMenuOperation == '1') {
				delete BST1;
				BST1 = nullptr;
				BST1 = new BST;
				std::string FileName;
				std::vector<std::string> FileContentsVector = LoadFile(FileName);
				for (int Index = 0; Index < FileContentsVector.size(); Index++) {
					(*BST1).Insert(FileContentsVector[Index]);
				};
				auto BSTInfoMapIterator = BSTInfoMap.find(FileName);
				if (BSTInfoMapIterator == BSTInfoMap.end()) {
					BSTInfoMap[FileName] = { FileName,std::to_string((*BST1).CountHeight(false)),std::to_string((*BST1).GetCount()) };
					FileNamesVector.push_back(FileName);
				};
			}
			else if (CharUserInputMainMenuOperation == '4') {
				std::string UserInputToSearch;
				std::cout << "[SYSTEM MESSAGE] Please Enter Node To Search: ";
				std::cin >> std::ws;
				std::getline(std::cin, UserInputToSearch);
				std::cout << "[SYSTEM MESSAGE] Search Result For '" << UserInputToSearch << "': " << (*BST1).Search(UserInputToSearch) << std::endl;
			}
			else if (CharUserInputMainMenuOperation == '5') {
				if (FileNamesVector.size() > 0) {
					PrintLine(FileNamesVector.size(), FileNamesVector, BSTInfoMap, "FileName", true);
					PrintLine(FileNamesVector.size(), FileNamesVector, BSTInfoMap, "Height", false);
					PrintLine(FileNamesVector.size(), FileNamesVector, BSTInfoMap, "Count", false);
				}
				else {
					std::cout << "[SYSTEM ERROR] No Files Have Been Loaded!" << std::endl;
				};
			}
			else if (CharUserInputMainMenuOperation == '6') {
				(*BST1).CountHeight(true);
			}
			else if (CharUserInputMainMenuOperation == 'm') {
				PrintMainMenu();
			}
			else {
				std::cout << "[SYSTEM MESSAGE] Cancelled Successfully!" << std::endl;
			};
		};
	} while (CharUserInputMainMenuOperation != 'q');
	std::cout << "[SYSTEM MESSAGE] Quitting Program..." << std::endl;
};
/*
----------------------------------------------------------------------------------------------------
CHECK USER INPUT FOR OPERATIONS
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: CheckUserInputForOperations();
Function Description: Gets User Input For An Operation & Validates The Input If It Is A Valid Operation Character
Return Value: Character
Incoming Params: InputMenuOptionsSet (Set)
Outgoing Params: CharUserInputOperation (Character)
*/
char CheckUserInputForOperations(const std::set<char> InputMenuOptionsSet) {
	std::string UserInputOperation;
	char CharUserInputOperation = ' ';
	bool ValidOperator = false;
	do {
		std::cout << "[SYSTEM MESSAGE] Please Enter Operation:";
		std::cin >> std::ws;
		std::getline(std::cin, UserInputOperation);
		if (UserInputOperation.size() != 1) {
			std::cout << "[SYSTEM ERROR] Invalid Input!" << std::endl;
		}
		else {
			CharUserInputOperation = std::tolower(UserInputOperation.at(0));
			//This Can Handle Different Sets (InputMenuOptionsSet) To Check If You Need To Check VALID_SUB_MENU_OPTIONS OR VALID_MAIN_MENU_OPTIONS
			auto ValidMenuOptionsSetIterator = InputMenuOptionsSet.find(CharUserInputOperation);
			if (ValidMenuOptionsSetIterator != InputMenuOptionsSet.end()) {
				ValidOperator = true;
			}
			else {
				std::cout << "[SYSTEM ERROR] Invalid Input!" << std::endl;
			};
		};
	} while (!ValidOperator);
	return CharUserInputOperation;
};
/*
----------------------------------------------------------------------------------------------------
LOAD FILE
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: LoadFile();
Function Description: Loads The User Input File Then Puts The Contents Into The FileContentsVector Then Returns It
Return Value: Character
Incoming Params: FileName (String)
Outgoing Params: FileName (String) ,FileContentsVector (Vector)
*/
std::vector<std::string> LoadFile(std::string& FileName) {
	std::vector<std::string> FileContentsVector;
	std::string UserInputFileName, Temp;
	std::ifstream InputFile;
	bool IsArraysFilled = false;
	do {
		std::cout << "Please Enter File To Read (Default: p6a.txt, Enter 'd' For Default W/O Quotes):";
		std::cin >> std::ws;
		std::getline(std::cin, UserInputFileName);
		if (UserInputFileName == "d") {
			UserInputFileName = "p6a.txt";
		}
		else if (UserInputFileName.size() <= TXT_SUFFIX.size() || UserInputFileName.size() > TXT_SUFFIX.size() && UserInputFileName.compare(UserInputFileName.size() - TXT_SUFFIX.size(), TXT_SUFFIX.size(), TXT_SUFFIX) != 0) {
			UserInputFileName += TXT_SUFFIX; //Can Handle If Input Was For Example: p6a So You Don't Have To Add The .txt Part
		};
		std::cout << "Input File Name You Entered: " + UserInputFileName << std::endl;
		InputFile.open(UserInputFileName);
		std::cout << (InputFile.fail() ? "File Name: " + UserInputFileName + " Does Not Exist!" : "File Name: " + UserInputFileName + " Successfully Opened!") << std::endl;
	} while (InputFile.fail() && !InputFile.is_open());
	while (!InputFile.eof()) {
		std::getline(InputFile, Temp);
		FileContentsVector.push_back(Temp);
	};
	FileName = UserInputFileName;
	return FileContentsVector;
};
/*
----------------------------------------------------------------------------------------------------
PRINT LINE
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: PrintLine();
Function Description: Loads The User Input File Then Puts The Contents Into The FileContentsVector Then Returns It
Return Value: Void
Incoming Params: Iterations (Integer), FileNamesVector (Vector), BSTInfoMap (Unordered Map), DataType (String), IsHeader (Boolean)
Outgoing Params: None
*/
void PrintLine(int Iterations, std::vector<std::string> FileNamesVector, std::unordered_map<std::string, BSTInfo> BSTInfoMap, std::string DataType, bool IsHeader) {
	if (IsHeader) {
		for (int Index = 0; Index <= Iterations; Index++) {
			std::cout << "--------------------";
		};
		std::cout << std::endl;
	};
	std::cout << std::left << std::setw(15) << DataType;
	for (int Index = 0; Index < Iterations; Index++) {
		std::cout << std::left << std::setw(5) << "|" << std::left << std::setw(15) << BSTInfoMap.at(FileNamesVector[Index])[DataType]; //<- LIKE LUA :)
	};
	std::cout << std::endl;
	for (int Index = 0; Index <= Iterations; Index++) {
		std::cout << "--------------------";
	};
	std::cout << std::endl;
};