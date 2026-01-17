/*
Student Name: Christian Tampus
File Name: Source.cpp
Description: Stumap Source/Driver C++ File
Course Number: CS 255
Section Number: 02 (Tuesday/Thursday)
Due Date: 10/30
*/
/*
----------------------------------------------------------------------------------------------------
DEPENDENCIES
----------------------------------------------------------------------------------------------------
*/
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include "Stumap.h"
/*
----------------------------------------------------------------------------------------------------
CONSTANT VARIABLES
----------------------------------------------------------------------------------------------------
*/
const std::string MENU_OPTIONS_ARRAY[20] = { "[Character] Operation Description","[+] Insert","[-] Remove","[?] Search","[p] Print","[@] At Cursor","[b] Go To Beginning","[e] Go To End","[>] Go To Next","[<] Go To Prev","[1] Demo Constructor","[2] Demo Copy Constructor","[3] Demo Destructor","[4] Demo Assignment Operator","[5] Sort By ID","[6] Sort By Score","[7] Print Stats","[m] Print Menu","[q] Quit Program","[x] Cancel" };
const std::set<char> VALID_OPERATIONS_SET = { '+','-','?','p','@','b','e','>','<','1','2','3','4','5','6','7','m','q','x' };
const std::unordered_map<char, std::string> OperationMap = { {'+',"Insert"},{'-',"Remove"},{'?',"Search"},{'p',"Print"},{'@',"At Cursor"},{'b',"Go To Beg"},{'e',"Go To End"},{'>',"Go To Next"},{'<',"Go To Prev"},{'1',"Demo Constructor"},{'2',"Demo Copy Constructor"},{'3',"Demo Destructor"},{'4',"Demo Assignment Operator"},{'5',"Sort By Id (Low To High)"},{'6',"Sort By Score (Low To High)"},{'7',"Print Stats"},{'m',"Print Menu"},{'x',"Cancel"},{'q',"Quit Program"} };
/*
----------------------------------------------------------------------------------------------------
FUNCTION PROTOTYPES/DECLERATIONS
----------------------------------------------------------------------------------------------------
*/
void DisplayMenu();
void GetOperationInput();
std::string GetUserInput(std::string InputType, std::string OutputMessage);
void TryCatch(bool& ValidUserInput, std::string INVALID_ARGUMENT_ERROR_MESSAGE, std::string OUT_OF_RANGE_ERROR_MESSAGE, std::string InputType, std::string UserInput);
/*
----------------------------------------------------------------------------------------------------
MAIN/DRIVER
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: Main();
Function Description: Calls DisplayMenu() Then Calls GetOperationInput();
Return Value: 0 (Integer)
Incoming Params: None
Outgoing Params: None
*/
int main() {
	std::cout << "Stumap (TM) Version 1.0.0" << std::endl;
	std::cout << "Developed By Christian Tampus" << std::endl << std::endl;
	//Calls Display Menu Once, Then Calls OperationInput
	DisplayMenu();
	GetOperationInput();
	std::cout << "[SYSTEM MESSAGE] Program Terminated..." << std::endl;
	return 0;
};
/*
----------------------------------------------------------------------------------------------------
FUNCTION DEFINITIONS
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: DisplayMenu();
Function Description: Prints All Menu Options In Array
Return Value: Void
Incoming Params: None
Outgoing Params: None
*/
void DisplayMenu() {
	std::cout << "Menu Options" << std::endl;
	//Loop MENU_OPTIONS_ARRAY And Print The Menu Options
	for (int Index = 0; Index < (sizeof(MENU_OPTIONS_ARRAY) / sizeof(MENU_OPTIONS_ARRAY[0])); Index++) {
		std::cout << MENU_OPTIONS_ARRAY[Index] << std::endl;
	};
};
/*
Function Name: GetOperation();
Function Description: Obtains UserInput For Operation
Return Value: None
Incoming Params: None
Outgoing Params: None
*/
void GetOperationInput() {
	std::string UserInput;
	char CharUserInput = ' ';
	STUMAP Stumap1(5);
	do {
		std::cout << "[SYSTEM MESSAGE] Please Enter An Operation To Execute:";
		std::cin >> std::ws;
		std::getline(std::cin, UserInput);
		//If UserInput Is Not Of Size 1, It Is Automatically An Invalid Input
		if (UserInput.size() > 1 || UserInput.size() <= 0) {
			std::cout << "[SYSTEM ERROR] Invalid Input!" << std::endl;
		}
		else {
			//Check The Set To See If CharUserInput Is A Valid Character Operation, If It Is Valid Go Inside The First If Statement Branch, If Not Print A System Message Invalid Input
			CharUserInput = std::tolower(UserInput.at(0));
			auto ValidOperationsSetIterator = VALID_OPERATIONS_SET.find(CharUserInput);
			if (ValidOperationsSetIterator != VALID_OPERATIONS_SET.end()) {
				//Uses A UMap To Print The Designated String For The CharUserInput
				std::cout << "[SYSTEM MESSAGE] Operation [" << CharUserInput << "]: " << OperationMap.at(CharUserInput) << std::endl;
				if (CharUserInput == '+' || CharUserInput == '-' || CharUserInput == '?') {
					//If CharUserInput Is +,-,? (Insert,Remove,Search) Call GetUserInput Then Check If It Was Not Cancelled Proceed To The Appropriate If/Else Branch To Execute The Code For The Appropriate Operation
					std::string UserInputId = GetUserInput("Integer", "[SYSTEM MESSAGE] Please Enter Id To " + OperationMap.at(CharUserInput) + " [Integer Value]:");
					if (UserInputId.compare("Cancel") != 0) {
						if (CharUserInput == '+') {
							std::string UserInputScore = GetUserInput("Double", "[SYSTEM MESSAGE] Please Enter Score To Append [Double Value]:");
							if (UserInputScore.compare("Cancel") != 0) {
								Stumap1.Append(std::stoi(UserInputId), std::stod(UserInputScore));
							};
						}
						else if (CharUserInput == '-') {
							Stumap1.Remove(std::stoi(UserInputId));
						}
						else if (CharUserInput == '?') {
							double UserScore = Stumap1.SearchId(std::stoi(UserInputId));
							std::cout << (UserScore == -1 ? "[SYSTEM MESSAGE] Attempted To Search For Id: " + UserInputId + "; Does Not Exist In IdList! Score: " : "[SYSTEM MESSAGE] Id: " + UserInputId + " Score: ") << UserScore << std::endl;
						};
						std::cout << Stumap1;
					};
				}
				else if (CharUserInput == 'p' || CharUserInput == '@' || CharUserInput == 'b' || CharUserInput == 'e' || CharUserInput == '>' || CharUserInput == '<' || CharUserInput == '5' || CharUserInput == '6') {
					//If CharUserInput Is p,@,b,e,>,<,5,6 Index The VoidMethods UMap (Key/Value(Function)) By CharUserInput Character Then Call The Function That Calls The Appropriate Method 
					Stumap1.VoidMethods.at(CharUserInput)();
					std::cout << Stumap1;
				}
				else if (CharUserInput == '1') {
					//Demo Constructor
					STUMAP DemoConstructor;
					std::cout << DemoConstructor;
				}
				else if (CharUserInput == '2') {
					//Demo Copy Constructor
					STUMAP DemoCopyConstructor(Stumap1);
					std::cout << "[SYSTEM MESSAGE] STUMAP Stumap1(5);" << std::endl;
					std::cout << Stumap1;
					std::cout << "[SYSTEM MESSAGE] STUMAP DemoCopyConstructor(Stumap1);" << std::endl;
					std::cout << DemoCopyConstructor;
				}
				else if (CharUserInput == '3') {
					//Demo Destructor By Creating A New STUMAP Then Call The ManualDelete() Method That Updates IsManuallyDestructed To True To Print A System Message Indicating The Destructor Working When Manually Deallocated/Deleted
					STUMAP* DemoDestructor = new STUMAP();
					(*DemoDestructor).ManualDelete();
					delete DemoDestructor;
					DemoDestructor = nullptr;
				}
				else if (CharUserInput == '4') {
					//Demo Assignment Operator
					std::string UserInputInitialMaxSize = GetUserInput("Integer", "Please Enter An Integer Value To Set [InitialMaxSize] Of [DemoAssignmentOperatorStumap1]:");
					if (UserInputInitialMaxSize.compare("Cancel") != 0) {
						STUMAP DemoAssignmentOperatorStumap1(std::stoi(UserInputInitialMaxSize));
						STUMAP DemoAssignmentOperatorStumap2;
						DemoAssignmentOperatorStumap2 = DemoAssignmentOperatorStumap1;
						std::cout << "[SYSTEM MESSAGE] STUMAP DemoAssignmentOperatorStumap1(" << std::stoi(UserInputInitialMaxSize) << ");" << std::endl;
						std::cout << DemoAssignmentOperatorStumap1;
						std::cout << "[SYSTEM MESSAGE] STUMAP DemoAssignmentOperatorStumap2;" << std::endl;
						std::cout << "[SYSTEM MESSAGE] DemoAssignmentOperatorStumap2 = DemoAssignmentOperatorStumap1;" << std::endl;
						std::cout << DemoAssignmentOperatorStumap2;
					};
				}
				else if (CharUserInput == '7') {
					//Display The Min,Max,Mean,Median
					std::cout << "Min: " << Stumap1.GetMin() << std::endl;
					std::cout << "Max: " << Stumap1.GetMax() << std::endl;
					std::cout << "Mean: " << Stumap1.GetMean() << std::endl;
					std::cout << "Median: " << Stumap1.GetMedian() << std::endl;
					std::cout << Stumap1;
				}
				else if (CharUserInput == 'm') {
					//Redisplay The Menu
					DisplayMenu();
				}
				else {
					//Prints When Cancelled
					std::cout << "[SYSTEM MESSAGE] Cancelled Successfully!" << std::endl;
				};
				std::cout << "---------------------------------------------" << std::endl << std::endl;
			}
			else {
				//Invalid Input
				std::cout << "[SYSTEM ERROR] Invalid Input!" << std::endl;
			};
		};
	} while (CharUserInput != 'q');
	std::cout << "[SYSTEM MESSAGE] Quitting Program..." << std::endl;
};
/*
Function Name: GetUserInput(std::string InputType, std::string OutputMessage);
Function Description: Gets The User Input For Integers Or Doubles & Validates It
Return Value: UserInput (String)
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
		//If UserInput Is Not 'x' Or 'X', Call TryCatch To Attempt To Parse It As An Integer Or Double To Validate The UserInput
		if (UserInput.compare("x") != 0 && UserInput.compare("X") != 0) {
			if (InputType.compare("Integer") == 0) {
				TryCatch(ValidUserInput, "[SYSTEM ERROR] Invalid Input, Please Enter An Integer!", "[SYSTEM ERROR] Invalid Input, Integer Value Is Too Large!", InputType, UserInput);
			}
			else if (InputType.compare("Double") == 0) {
				TryCatch(ValidUserInput, "[SYSTEM ERROR] Invalid Input, Please Enter An Double!", "[SYSTEM ERROR] Invalid Input, Double Value Is Too Large!", InputType, UserInput);
			};
		};
	} while (UserInput.compare("x") != 0 && UserInput.compare("X") != 0 && ValidUserInput == false);
	//Exits The Loop If Cancelled Or UserInput Is Validated, If Cancelled Will Print Out A System Message
	if (UserInput.compare("x") == 0 || UserInput.compare("X") == 0) {
		std::cout << "[SYSTEM MESSAGE] Cancelled Successfully!" << std::endl;
		UserInput = "Cancel";
	};
	return UserInput;
};
/*
Function Name: TryCatch(bool& ValidUserInput, std::string INVALID_ARGUMENT_ERROR_MESSAGE, std::string OUT_OF_RANGE_ERROR_MESSAGE, std::string InputType, std::string UserInput);
Function Description: Parses UserInput To An Integer Or Double To Validate The User Input
Return Value: Void
Incoming Params: ValidUserInput (Boolean), INVALID_ARGUMENT_ERROR_MESSAGE (String), OUT_OF_RANGE_ERROR_MESSAGE (String)
Outgoing Params: None
*/
void TryCatch(bool& ValidUserInput, std::string INVALID_ARGUMENT_ERROR_MESSAGE, std::string OUT_OF_RANGE_ERROR_MESSAGE, std::string InputType, std::string UserInput) {
	try {
		//Checks If InputType Is Equal To An Integer Or Double Then Parses It, If It Is Successfull Updates ValidUserInput To True
		if (InputType.compare("Integer") == 0) {
			int UserInputToInteger = std::stoi(UserInput);
		}
		else if (InputType.compare("Double") == 0) {
			double UserInputToDouble = std::stod(UserInput);
		};
		ValidUserInput = true;
	}
	catch (const std::invalid_argument& INVALID_ARGUMENT_ERROR) {
		//Print INVALID_ARGUMENT_ERROR_MESSAGE If The Parse Caused An Error Due To Invalid Characters/Argument In The UserInput String
		std::cout << INVALID_ARGUMENT_ERROR_MESSAGE << std::endl;
	}
	catch (const std::out_of_range& OUT_OF_RANGE_ERROR) {
		//Print OUT_OF_RANGE_ERROR_MESSAGE If The Parse Caused An Error Due To The Value Being To Large
		std::cout << OUT_OF_RANGE_ERROR_MESSAGE << std::endl;
	};
};