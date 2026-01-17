/*
Student Name: Christian Tampus
File Name: Driver.cpp
Description: Poly Source/Driver C++ File
Course Number: CS 255
Section Number: 02 (Tuesday/Thursday)
Due Date: 11/19
*/
/*
----------------------------------------------------------------------------------------------------
DEPENDENCIES
----------------------------------------------------------------------------------------------------
*/
#include "Poly.h"
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <fstream>
using namespace std;
/*
----------------------------------------------------------------------------------------------------
CONSTANTS
----------------------------------------------------------------------------------------------------
*/
const std::string MENU_ARRAY[21] = {"Operations Menu","[+] Insert (For Polynomial 1 Only)","[-] Remove (For Polynomial 1 Only)","[?] Search (For Polynomial 1 Only)","[p] Test Print Routine (Both Polynomial 1 & 2)","[v] Test Print Reverse Routine (Both Polynomial 1 & 2)","[c] Test Input From Console (For Polynomial 2 Only)","[f] Test Input From File (For Polynomial 2 Only)","[r] Test Reset (Both Polynomial 1 & 2)","[e] Test Evaluation (For Polynomial 1 Only)","[d] Test Derivative (For Polynomial 1 Only)","[1] Test Poly Copy Constructor (For Polynomial 3)","[2] Test Destructor (For Polynomial 4)","[3] Test Assignment Operator (For Polynomial 5)","[4] Test Addition (For Polynomial 6)","[5] Test Subtraction (For Polynomial 7)","[6] Test Addition Assignment (For Polynomial 1)","[7] Test Derivative (For Polynomial 2 Only)","[m] Print Menu","[q] Quit","[x] Cancel"};
const std::set<char> VALID_OPERATIONS_SET = { '+','-','?','p','v','c','f','r','e','d','1','2','3','4','5','6','7','m','q','x' };
const std::unordered_map<char, std::string> OPERATIONS_MAP = { {'+',"Insert (For Polynomial 1 Only)"},{'-',"Remove (For Polynomial 1 Only)"},{'?',"Search (For Polynomial 1 Only)"},{'p',"Test Print Routine (Both Polynomial 1 & 2)"},{'v',"Test Print Reverse Routine (Both Polynomial 1 & 2)"},{'c',"Test Input From Console (For Polynomial 2 Only)"},{'f',"Test Input From File (For Polynomial 2 Only)"},{'r',"Test Reset (Both Polynomial 1 & 2)"},{'e',"Test Evaluation (For Polynomial 1 Only)"},{'d',"Test Derivative (For Polynomial 1 Only)"},{'1',"Test Poly Copy Constructor (For Polynomial 3)"},{'2',"Test Destructor (For Polynomial 4)"},{'3',"Test Assignment Operator (For Polynomial 5)"},{'4',"Test Addition (For Polynomial 6)"},{'5',"Test Subtraction (For Polynomial 7)"},{'6',"Test Addition Assignment (For Polynomial 1)"},{'7',"Test Derivative (For Polynomial 2 Only)"},{'m',"Print Menu"},{'q',"Quit"},{'x',"Cancel"} };
/*
----------------------------------------------------------------------------------------------------
FUNCTION PROTOTYPES
----------------------------------------------------------------------------------------------------
*/
void PrintMenu();
void GetUserInputForOperations();
std::string GetUserInput(std::string InputType, std::string OutputMessage);
void TryCatch(bool& ValidUserInput, std::string INVALID_ARGUMENT_ERROR_MESSAGE, std::string OUT_OF_RANGE_ERROR_MESSAGE, std::string InputType, std::string UserInput);
/*
----------------------------------------------------------------------------------------------------
MAIN/DRIVER FUNCTION
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: main();
Function Description: Calls PrintMenu() Then Calls GetUserInputForOperations()
Return Value: 0 (Integer)
Incoming Params: None
Outgoing Params: 0 (Integer)
*/
int main() {
	std::cout << "[Project 3 & 4] Class With LinkedList As Polynomials" << std::endl;
	std::cout << "Developed By: Christian Tampus" << std::endl;
	PrintMenu();
	GetUserInputForOperations();
	std::cout << "[SYSTEM MESSAGE] Program Terminated..." << std::endl;
	return 0;
};
/*
----------------------------------------------------------------------------------------------------
FUNCTION DEFINITIONS
----------------------------------------------------------------------------------------------------
*/
/*
----------------------------------------------------------------------------------------------------
PRINT MENU
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: PrintMenu();
Function Description: Prints All Menu Options In MENU_ARRAY
Return Value: Void
Incoming Params: None
Outgoing Params: None
*/
void PrintMenu() {
	for (int Index = 0; Index < sizeof(MENU_ARRAY) / sizeof(MENU_ARRAY[0]); Index++) {
		std::cout << MENU_ARRAY[Index] << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
GET USER INPUT FOR OPERATIONS
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: GetUserInputForOperations();
Function Description: Gets User Input To Execute The Given Operation
Return Value: Void
Incoming Params: None
Outgoing Params: None
*/
void GetUserInputForOperations() {
	std::string UserInputOperation;
	char CharUserInputOperation = ' ';
	Poly Polynomial1;
	Poly Polynomial2;
	do {
		std::cout << "[SYSTEM MESSAGE] Please Enter Operation:";
		std::cin >> std::ws;
		std::getline(std::cin, UserInputOperation);
		//Checks If UserInputOperation.size() Is Not 1 To Invalidate The Input
		if (UserInputOperation.size() != 1) {
			std::cout << "[SYSTEM ERROR] Invalid Input!" << std::endl;
		}
		else {
			//Converts CharUserInputOperation To Lowercase Then Compares It To The VALID_OPERATIONS_SET To See If It Exist, If It Is Found Then It Is A Valid Operation
			CharUserInputOperation = std::tolower(UserInputOperation.at(0));
			auto ValidOperationsSetIterator = VALID_OPERATIONS_SET.find(CharUserInputOperation);
			if (ValidOperationsSetIterator != VALID_OPERATIONS_SET.end()) {
				bool OperationExecutedSuccessfully = true;
				std::cout << "[SYSTEM MESSAGE] Operation [" << CharUserInputOperation << "]: " << OPERATIONS_MAP.at(CharUserInputOperation) << "; Executing..." << std::endl;
				//If/Else Statements To Handle Each Operation
				if (CharUserInputOperation == '+') {
					//Insertion
					std::string UserInputNewCoefficient = GetUserInput("Integer", "[SYSTEM MESSAGE] Please Enter Coefficient To Insert:");
					if (UserInputNewCoefficient.compare("Cancel") != 0) {
						std::string UserInputNewExponent = GetUserInput("Integer", "[SYSTEM MESSAGE] Please Enter Exponent To Insert:");
						if (UserInputNewExponent.compare("Cancel") != 0) {
							if (!Polynomial1.Insert(std::stoi(UserInputNewCoefficient), std::stoi(UserInputNewExponent))) {
								OperationExecutedSuccessfully = false;
							};
						};
					};
				}
				else if (CharUserInputOperation == '-') {
					//Remove
					std::string UserInputRemoveExponent = GetUserInput("Integer", "[SYSTEM MESSAGE] Please Enter Exponent To Remove: ");
					if (UserInputRemoveExponent.compare("Cancel") != 0) {
						if (!Polynomial1.Remove(std::stoi(UserInputRemoveExponent))) {
							OperationExecutedSuccessfully = false;
						};
					};
				}
				else if (CharUserInputOperation == '?') {
					//Search
					std::string UserInputSearchExponent = GetUserInput("Integer", "[SYSTEM MESSAGE] Please Enter Exponent To Search: ");
					if (UserInputSearchExponent.compare("Cancel") != 0) {
						if (!Polynomial1.Search(std::stoi(UserInputSearchExponent))) {
							OperationExecutedSuccessfully = false;
						};
					};
				}
				else if (CharUserInputOperation == 'p') {
					//Print
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial 1" << std::endl;
					std::cout << Polynomial1;
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial 2" << std::endl;
					std::cout << Polynomial2;
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
				}
				else if (CharUserInputOperation == 'v') {
					//Print Reverse
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial 1" << std::endl;
					Polynomial1.PrintReverse();
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial 2" << std::endl;
					Polynomial2.PrintReverse();
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
				}
				else if (CharUserInputOperation == 'c') {
					//Extraction Operator For Console
					std::cout << "[SYSTEM MESSAGE] Polynomial Must Be In This Format (Must Have ' + ' Between The Terms) Example: <1x^20 + 3x^16 + 15x^4 + 2x^3 + 16x^2 + 5x^0>" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Please Enter A Polynomial For Polynomial 2:";
					std::cin >> Polynomial2;
				}
				else if (CharUserInputOperation == 'f') {
					//Extraction Operator For File
					std::ifstream ReadFile("p3.txt");
					if (ReadFile.is_open()) {
						while (!ReadFile.eof()) {
							ReadFile >> Polynomial2;
						};
						ReadFile.close();
					}
					else {
						std::cout << "[SYSTEM ERROR] Failed To Open File!" << std::endl;
						OperationExecutedSuccessfully = false;
					};
				}
				else if (CharUserInputOperation == 'r') {
					//Reset
					Polynomial1.Reset("Polynomial 1 (One)");
					Polynomial2.Reset("Polynomial 2 (Two)");
				}
				else if (CharUserInputOperation == 'e') {
					//Evaluate
					std::string UserInputX = GetUserInput("Double", "[SYSTEM MESSAGE] Please Enter X Value To Evaluate The Polynomial: ");
					if (UserInputX.compare("Cancel") != 0) {
						std::cout << "[SYSTEM MESSAGE] Polynomial Evaluation: " << Polynomial1.Evaluate(std::stod(UserInputX)) << std::endl;
					};
				}
				else if (CharUserInputOperation == 'd') {
					//Derivative (For Polynomial 1)
					if (!Polynomial1.Derivative()) {
						OperationExecutedSuccessfully = false;
					};
				}
				else if (CharUserInputOperation == '1') {
					//Copy Constructor
					std::cout << "[SYSTEM MESSAGE] Test Poly Copy Constructor" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Poly Polynomial3(Polynomial3);" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial 3" << std::endl;
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					Poly Polynomial3(Polynomial1);
					Polynomial3.Print();
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
				}
				else if (CharUserInputOperation == '2') {
					//Destructor
					std::cout << "[SYSTEM MESSAGE] Test Poly Destructor" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial 4" << std::endl;
					Poly* Polynomial4Pointer = new Poly();
					for (int Increment = -5; Increment <= 5; Increment++) {
						(*Polynomial4Pointer).Insert(Increment, Increment);
					};
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					(*Polynomial4Pointer).Print();
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					(*Polynomial4Pointer).ManuallyDeallocate();
					delete Polynomial4Pointer;
					Polynomial4Pointer = nullptr;
				}
				else if (CharUserInputOperation == '3') {
					//Assignment Operator
					std::cout << "[SYSTEM MESSAGE] Test Assignment Operator" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial 5 (Before Assignment Operator):" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Poly Polynomial5;" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial5.Print();" << std::endl;
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					Poly Polynomial5;
					Polynomial5.Print();
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial 5 (After Assignment Operator):" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial5 = Polynomial1;" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial5.Print();" << std::endl;
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					Polynomial5 = Polynomial1;
					Polynomial5.Print();
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
				}
				else if (CharUserInputOperation == '4') {
					//Addition Operator
					std::cout << "[SYSTEM MESSAGE] Test Addition Operator" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Poly Polynomial6 = Polynomial1 + Polynomial2;" << std::endl;
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					Poly Polynomial6 = Polynomial1 + Polynomial2;
					Polynomial6.Print();
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
				}
				else if (CharUserInputOperation == '5') {
					//Subtraction Operator
					std::cout << "[SYSTEM MESSAGE] Test Subtraction Operator" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Poly Polynomial7 = Polynomial1 - Polynomial2;" << std::endl;
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					Poly Polynomial7 = Polynomial1 - Polynomial2;
					Polynomial7.Print();
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
				}
				else if (CharUserInputOperation == '6') {
					//Addition Assignment Operator
					std::cout << "[SYSTEM MESSAGE] Test Addition Assignment Operator" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial 1 (Before Addition Assignment Operator):" << std::endl;
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					Polynomial1.Print();
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynomial 1 (After Addition Assignment Operator):" << std::endl;
					std::cout << "[SYSTEM MESSAGE] Polynoial1 += Polynomial2;" << std::endl;
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
					Polynomial1 += Polynomial2;
					Polynomial1.Print();
					std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
				}
				else if (CharUserInputOperation == '7') {
					//Derivative (For Polynomial 2)
					if (!Polynomial2.Derivative()) {
						OperationExecutedSuccessfully = false;
					};
				}
				else if (CharUserInputOperation == 'm') {
					//Print Menu
					PrintMenu();
				}
				else if (CharUserInputOperation != 'q'  && CharUserInputOperation != 'x') {
					//Quit Or Cancel
					OperationExecutedSuccessfully = false;
				}
				//Operation Success Or Error Messages
				if (OperationExecutedSuccessfully) {
					std::cout << "[SYSTEM MESSAGE] Operation [" << CharUserInputOperation << "]: " << OPERATIONS_MAP.at(CharUserInputOperation) << "; Executed Successfully!" << std::endl;
				}
				else {
					std::cout << "[SYSTEM MESSAGE] Operation [" << CharUserInputOperation << "]: " << OPERATIONS_MAP.at(CharUserInputOperation) << "; Executed Unsuccessfully!" << std::endl;
				};
			}
			else {
				std::cout << "[SYSTEM ERROR] Invalid Input!" << std::endl;
			};
		};
	} while (CharUserInputOperation != 'q');
	std::cout << "[SYSTEM MESSAGE] Quitting Program..." << std::endl;
};
/*
----------------------------------------------------------------------------------------------------
GET USER INPUT
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: GetUserInput();
Function Description: Gets User Input From Console & Validates It
Return Value: String
Incoming Params: InputType (String), OutputMessage (String)
Outgoing Params: UserInput (String)
*/
std::string GetUserInput(std::string InputType, std::string OutputMessage) {
	std::string UserInput = "";
	bool ValidUserInput = false;
	do {
		std::cout << OutputMessage;
		std::cin >> std::ws;
		std::getline(std::cin, UserInput);
		if (UserInput.compare("x") != 0 && UserInput.compare("X") != 0) {
			//Call Try Catch To Validate User Input Based On If It Is Required To Be An Integer Or Double
			if (InputType.compare("Integer") == 0) {
				TryCatch(ValidUserInput, "[SYSTEM ERROR] Invalid Input, Please Enter An Integer!", "[SYSTEM ERROR] Invalid Input, Integer Value Is Too Large!", InputType, UserInput);
			}
			else if (InputType.compare("Double") == 0) {
				TryCatch(ValidUserInput, "[SYSTEM ERROR] Invalid Input, Please Enter An Double!", "[SYSTEM ERROR] Invalid Input, Double Value Is Too Large!", InputType, UserInput);
			};
		};
	} while (UserInput.compare("x") != 0 && UserInput.compare("X") != 0 && ValidUserInput == false);
	//Exits Loop When Cancel Operator Is Inputted Or ValidatedUserInput Is True
	if (UserInput.compare("x") == 0 || UserInput.compare("X") == 0) {
		std::cout << "[SYSTEM MESSAGE] Cancelled Successfully!" << std::endl;
		UserInput = "Cancel";
	};
	return UserInput;
};
/*
----------------------------------------------------------------------------------------------------
TRY CATCH
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: TryCatch();
Function Description: Validates UserInput To Be An Integer Or Double
Return Value: Void
Incoming Params: ValidUserInput (Boolean), INVALID_ARGUMENT_ERROR_MESSAGE (String), OUT_OF_RANGE_ERROR_MESSAGE (String), InputType (String), UserInput (String)
Outgoing Params: ValidUserInput (Boolean)
*/
void TryCatch(bool& ValidUserInput, std::string INVALID_ARGUMENT_ERROR_MESSAGE, std::string OUT_OF_RANGE_ERROR_MESSAGE, std::string InputType, std::string UserInput) {
	//Parses The UserInput As An Integer Or Double
	try {
		if (InputType.compare("Integer") == 0) {
			int UserInputToInteger = std::stoi(UserInput);
		}
		else if (InputType.compare("Double") == 0) {
			double UserInputToDouble = std::stod(UserInput);
		};
		ValidUserInput = true;
	}
	catch (const std::invalid_argument& INVALID_ARGUMENT_ERROR) {
		std::cout << INVALID_ARGUMENT_ERROR_MESSAGE << std::endl;
	}
	catch (const std::out_of_range& OUT_OF_RANGE_ERROR) {
		std::cout << OUT_OF_RANGE_ERROR_MESSAGE << std::endl;
	};
	//If It Fails Output The Coresponding Error Message
};