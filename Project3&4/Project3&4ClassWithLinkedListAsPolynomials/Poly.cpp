/*
Student Name: Christian Tampus
File Name: Poly.cpp
Description: Poly C++ File
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
#include <cmath>
#include <string>
#include <set>
#include <sstream>
#include <vector>
#include <regex>
using namespace std;
/*
----------------------------------------------------------------------------------------------------
CONSTANTS
----------------------------------------------------------------------------------------------------
*/
const std::set<char> VALID_CHARACTERS_SET = { ' ','x','^','+','-','0','1','2','3','4','5','6','7','8','9'};
/*
----------------------------------------------------------------------------------------------------
TERM CONSTRUCTORS
----------------------------------------------------------------------------------------------------
*/
/*
Constructor Name: Term::Term(int NewCoefficient);
Constructor Description: 1 Parameter Term Constructor
Return Value: None
Incoming Params: NewCoefficient (Integer)
Outgoing Params: None
*/
Term::Term(int NewCoefficient) :Coefficient(NewCoefficient), Exponent(1), NextTerm(nullptr) {};
/*
Constructor Name: Term::Term(int NewCoefficient, int NewExponent);
Constructor Description: 2 Parameter Term Constructor
Return Value: None
Incoming Params: NewCoefficient (Integer), NewExponent (Integer)
Outgoing Params: None
*/
Term::Term(int NewCoefficient, int NewExponent) :Coefficient(NewCoefficient), Exponent(NewExponent), NextTerm(nullptr) {};
/*
Constructor Name: Term::Term(int NewCoefficient, int NewExponent, Term* NewNextTerm);
Constructor Description: 3 Parameter Term Constructor
Return Value: None
Incoming Params: NewCoefficient (Integer), NewExponent (Integer), NewNextTerm (Pointer)
Outgoing Params: None
*/
Term::Term(int NewCoefficient, int NewExponent, Term* NewNextTerm) :Coefficient(NewCoefficient), Exponent(NewExponent), NextTerm(NewNextTerm) {};
/*
----------------------------------------------------------------------------------------------------
TERM DESTRUCTOR
----------------------------------------------------------------------------------------------------
*/
/*
Destructor Name: Term::~Term();
Destructor Description: Resets Coefficient & Exponent To 0, Sets NextTerm Pointer To Nullptr
Return Value: None
Incoming Params: None
Outgoing Params: None
*/
Term::~Term() {
	int Coefficient = this->Coefficient;
	int Exponent = this->Exponent;
	this->Coefficient = 0;
	this->Exponent = 0;
	this->NextTerm = nullptr;
	if (this->ManualDeallocation) {
		std::cout << "[SYSTEM MESSAGE] Term Destructor Executed For <" << Coefficient << "x^(" << Exponent << ")>" << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
TERM INSERTION OPERATOR
----------------------------------------------------------------------------------------------------
*/
/*
Friend Function Name: std::ostream& operator<<(std::ostream& OS, const Term& InputTerm);
Friend Function Description: Prints The Term In Cx^(E) Form, For C = Coefficient & E = Exponent
Return Value: std::ostream&
Incoming Params: OS (std::ostream&), InputTerm (Term&)
Outgoing Params: OS (std::ostream&)
*/
std::ostream& operator<<(std::ostream& OS, const Term& InputTerm) {
	if (InputTerm.Exponent == 1) {
		std::cout << InputTerm.Coefficient << "x";
	}
	else if (InputTerm.Exponent == 0) {
		std::cout << InputTerm.Coefficient;
	}
	else {
		std::cout << InputTerm.Coefficient << "x" << "^(" << InputTerm.Exponent << ")";
	};
	return OS;
};
/*
----------------------------------------------------------------------------------------------------
POLY CONSTRUCTOR
----------------------------------------------------------------------------------------------------
*/
/*
Constructor Name: Poly::Poly();
Constructor Description: Poly Default Constructor, Sets HeadTerm Pointer To Nullptr
Return Value: None
Incoming Params: None
Outgoing Params: None
*/
Poly::Poly() :HeadTerm(nullptr) {};
/*
----------------------------------------------------------------------------------------------------
POLY COPY CONSTRUCTOR
----------------------------------------------------------------------------------------------------
*/
/*
Constructor Name: Poly::Poly(const Poly& Poly_RIGHT);
Constructor Description: Poly Default Constructor, Sets HeadTerm Pointer To Nullptr
Return Value: None
Incoming Params: Poly_RIGHT (Poly&)
Outgoing Params: None
*/
Poly::Poly(const Poly& Poly_RIGHT) {
	this->CopyData(Poly_RIGHT);
	std::cout << "[SYSTEM MESSAGE] Polynomial Class Copy Constructor Successfully Executed!" << std::endl;
};
/*
----------------------------------------------------------------------------------------------------
POLY DESTRUCTOR
----------------------------------------------------------------------------------------------------
*/
/*
Destructor Name: Poly::~Poly();
Destructor Description: Calls The Deallocate() Method
Return Value: None
Incoming Params: None
Outgoing Params: None
*/
Poly::~Poly() {
	this->Deallocate();
};
/*
----------------------------------------------------------------------------------------------------
POLY ASSIGNMENT OPERATOR
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly& Poly::operator=(const Poly& Poly_RIGHT);
Method Description: If Calling Object Is Not Poly_RIGHT, Call The Deallocate() Then CopyData() Methods
Return Value: Poly&
Incoming Params: Poly_RIGHT (Poly&)
Outgoing Params: (*this) (Poly&)
*/
Poly& Poly::operator=(const Poly& Poly_RIGHT) {
	if (this != &Poly_RIGHT) {
		this->Deallocate();
		this->CopyData(Poly_RIGHT);
	};
	std::cout << "[SYSTEM MESSAGE] Polynomial Class Assignment Operator Successfully Executed!" << std::endl;
	return (*this);
};
/*
----------------------------------------------------------------------------------------------------
POLY ADDITION OPERATOR
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly Poly::operator+(const Poly& Poly_RIGHT)const;
Method Description: Creates A New PolynomialSum Instance Then Inserts Calling Object Polynomial Nodes Then Inserts Poly_RIGHT Nodes
Return Value: Poly
Incoming Params: Poly_RIGHT (Poly&)
Outgoing Params: PolynomialSum (Poly)
*/
Poly Poly::operator+(const Poly& Poly_RIGHT)const {
	Term* Poly_LEFTCurrentTermPointer = this->HeadTerm;
	Term* Poly_RIGHTCurrentTermPointer = Poly_RIGHT.HeadTerm;
	Poly PolynomialSum;
	while (Poly_LEFTCurrentTermPointer != nullptr) {
		PolynomialSum.Insert(Poly_LEFTCurrentTermPointer->Coefficient, Poly_LEFTCurrentTermPointer->Exponent);
		Poly_LEFTCurrentTermPointer = Poly_LEFTCurrentTermPointer->NextTerm;
	};
	while (Poly_RIGHTCurrentTermPointer != nullptr) {
		PolynomialSum.Insert(Poly_RIGHTCurrentTermPointer->Coefficient, Poly_RIGHTCurrentTermPointer->Exponent);
		Poly_RIGHTCurrentTermPointer = Poly_RIGHTCurrentTermPointer->NextTerm;
	};
	std::cout << "[SYSTEM MESSAGE] Polynomial Class Addition Operator Successfully Executed!" << std::endl;
	return PolynomialSum;
};
/*
----------------------------------------------------------------------------------------------------
POLY ADDITION ASSIGNMENT OPERATOR
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly& Poly::operator+=(const Poly& Poly_RIGHT);
Method Description: Sets The Calling Object Equal To Itself Plus The Poly_RIGHT
Return Value: Poly&
Incoming Params: Poly_RIGHT (Poly&)
Outgoing Params: *this (Poly&)
*/
Poly& Poly::operator+=(const Poly& Poly_RIGHT){
	*this = *this + Poly_RIGHT;
	std::cout << "[SYSTEM MESSAGE] Polynomial Class Addition Assignment Operator Successfully Executed!" << std::endl;
	return *this;
};
/*
----------------------------------------------------------------------------------------------------
POLY SUBTRACTION OPERATOR
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly Poly::operator-(const Poly& Poly_RIGHT)const;
Method Description: Creates A New PolynomialDifference Instance Then Inserts Calling Object Polynomial Nodes Then Inserts Poly_RIGHT Nodes With False As The 3rd Parameter
Return Value: Poly
Incoming Params: Poly_RIGHT (Poly&)
Outgoing Params: PolynomialDifference (Poly)
*/
Poly Poly::operator-(const Poly& Poly_RIGHT)const {
	Term* Poly_LEFTCurrentTermPointer = this->HeadTerm;
	Term* Poly_RIGHTCurrentTermPointer = Poly_RIGHT.HeadTerm;
	Poly PolynomialDifference;
	while (Poly_LEFTCurrentTermPointer != nullptr) {
		PolynomialDifference.Insert(Poly_LEFTCurrentTermPointer->Coefficient, Poly_LEFTCurrentTermPointer->Exponent);
		Poly_LEFTCurrentTermPointer = Poly_LEFTCurrentTermPointer->NextTerm;
	};
	while (Poly_RIGHTCurrentTermPointer != nullptr) {
		PolynomialDifference.Insert(Poly_RIGHTCurrentTermPointer->Coefficient, Poly_RIGHTCurrentTermPointer->Exponent, false);
		Poly_RIGHTCurrentTermPointer = Poly_RIGHTCurrentTermPointer->NextTerm;
	};
	std::cout << "[SYSTEM MESSAGE] Polynomial Class Subtraction Operator Successfully Executed!" << std::endl;
	return PolynomialDifference;
};
/*
----------------------------------------------------------------------------------------------------
POLY COPY DATA
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::CopyData(const Poly& Poly_RIGHT);
Method Description: Copies Poly_RIGHT Terms To Calling Object
Return Value: Void
Incoming Params: Poly_RIGHT (Poly&)
Outgoing Params: Poly_RIGHT (Poly&)
*/
void Poly::CopyData(const Poly& Poly_RIGHT) {
	Term* CurrentTermPointer = this->HeadTerm;
	Term* Poly_RIGHTCurrentTermPointer = Poly_RIGHT.HeadTerm;
	while (Poly_RIGHTCurrentTermPointer != nullptr) {
		if (CurrentTermPointer == nullptr) {
			this->HeadTerm = new Term(Poly_RIGHTCurrentTermPointer->Coefficient, Poly_RIGHTCurrentTermPointer->Exponent, nullptr);
			CurrentTermPointer = this->HeadTerm;
		}
		else {
			CurrentTermPointer->NextTerm = new Term(Poly_RIGHTCurrentTermPointer->Coefficient, Poly_RIGHTCurrentTermPointer->Exponent, nullptr);
			CurrentTermPointer = CurrentTermPointer->NextTerm;
		};
		Poly_RIGHTCurrentTermPointer = Poly_RIGHTCurrentTermPointer->NextTerm;
	};
};
/*
----------------------------------------------------------------------------------------------------
POLY DEALLOCATE
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::Deallocate();
Method Description: Deallocates The Term Nodes Of The Polynomial Then Sets The HeadTerm To Nullptr
Return Value: Void
Incoming Params: None
Outgoing Params: None
*/
void Poly::Deallocate() {
	Term* CurrentTermPointer = this->HeadTerm;
	while (CurrentTermPointer != nullptr) {
		Term* NextTermPointer = CurrentTermPointer->NextTerm;
		if (this->ManualDeallocation) {
			(*CurrentTermPointer).ManualDeallocation = true;
		};
		delete CurrentTermPointer;
		CurrentTermPointer = NextTermPointer;
	};
	this->HeadTerm = nullptr;
	if (this->ManualDeallocation) {
		std::cout << "[SYSTEM MESSAGE] Polynomial (Poly) Destructor Manually Called & Executed Successfully!" << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
POLY MANUALLY DEALLOCATE
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::ManuallyDeallocate();
Method Description: Sets The ManualDeallocation Boolean To True
Return Value: Void
Incoming Params: None
Outgoing Params: None
*/
void Poly::ManuallyDeallocate() {
	this->ManualDeallocation = true;
};
/*
----------------------------------------------------------------------------------------------------
POLY INSERT
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::Insert(int NewCoefficient, int NewExponent, bool AdditionArithmeticOperation);
Method Description: Inserts A New Term Node In Order Based On Exponent Value In Decreasing Order, Adds Or Subtracts The Coefficient Based On AdditionArithmeticOperation Boolean
Return Value: Boolean
Incoming Params: NewCoefficient (Integer), NewExponent (Integer), AdditionArithmeticOperation (Boolean)
Outgoing Params: InsertionSuccess (Boolean)
*/
bool Poly::Insert(int NewCoefficient, int NewExponent, bool AdditionArithmeticOperation) {
	bool InsertionSuccess = false;
	if (this->HeadTerm == nullptr || NewExponent > this->HeadTerm->Exponent) {
		this->HeadTerm = new Term(NewCoefficient, NewExponent, this->HeadTerm);
		if (this->HeadTerm != nullptr) {
			InsertionSuccess = true;
		};
	}
	else {
		Term* PreviousTermPointer = this->HeadTerm;
		Term* CurrentTermPointer = this->HeadTerm;
		while (CurrentTermPointer != nullptr) {
			if (NewExponent == CurrentTermPointer->Exponent) {
				if (AdditionArithmeticOperation) {
					CurrentTermPointer->Coefficient += NewCoefficient;
				}
				else {
					CurrentTermPointer->Coefficient -= NewCoefficient;
				};
				InsertionSuccess = true;
				break;
			}else if (NewExponent > CurrentTermPointer->Exponent) {
				PreviousTermPointer->NextTerm = new Term(NewCoefficient, NewExponent, CurrentTermPointer);
				if (PreviousTermPointer != nullptr) {
					InsertionSuccess = true;
				}
				break;
			};
			PreviousTermPointer = CurrentTermPointer;
			CurrentTermPointer = CurrentTermPointer->NextTerm;
		};
		if (!InsertionSuccess) {
			PreviousTermPointer->NextTerm = new Term(NewCoefficient, NewExponent, nullptr);
			if (PreviousTermPointer != nullptr) {
				InsertionSuccess = true;
			};
		};
	};
	return InsertionSuccess;
};
/*
----------------------------------------------------------------------------------------------------
POLY REMOVE
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::Remove(int RemoveExponent);
Method Description: Removes The Term That Equals RemoveExponent
Return Value: Boolean
Incoming Params: RemoveExponent (Integer)
Outgoing Params: RemovalSuccess (Boolean)
*/
bool Poly::Remove(int RemoveExponent) {
	bool RemovalSuccess = false;
	Term* PreviousTermPointer = this->HeadTerm;
	Term* CurrentTermPointer = this->HeadTerm;
	while (CurrentTermPointer != nullptr) {
		Term* CurrentTermPointerNextTerm = CurrentTermPointer->NextTerm;
		if (CurrentTermPointer->Exponent == RemoveExponent && CurrentTermPointer == this->HeadTerm) {
			delete this->HeadTerm;
			this->HeadTerm = nullptr;
			this->HeadTerm = CurrentTermPointerNextTerm;
			PreviousTermPointer = this->HeadTerm;
			CurrentTermPointer = this->HeadTerm;
			RemovalSuccess = true;
		}
		else if (CurrentTermPointer->Exponent == RemoveExponent) {
			delete PreviousTermPointer->NextTerm;
			PreviousTermPointer->NextTerm = nullptr;
			PreviousTermPointer->NextTerm = CurrentTermPointerNextTerm;
			CurrentTermPointer = CurrentTermPointerNextTerm;
			RemovalSuccess = true;
		}else if (CurrentTermPointer != nullptr) {
			PreviousTermPointer = CurrentTermPointer;
			CurrentTermPointer = CurrentTermPointer->NextTerm;
		};
	};
	return RemovalSuccess;
};
/*
----------------------------------------------------------------------------------------------------
POLY SEARCH
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::Search(int SearchExponent)const;
Method Description: Searches The Polynomial For The Term That Has An Exponent That Equals To SearchExponent
Return Value: Boolean
Incoming Params: SearchExponent (Integer)
Outgoing Params: TermFound (Boolean)
*/
bool Poly::Search(int SearchExponent)const {
	bool TermFound = false;
	Term* CurrentTermPointer = this->HeadTerm;
	std::cout << "[SYSTEM MESSAGE] Search Polynomial Of (" << SearchExponent << ") Exponent: <";
	while (CurrentTermPointer != nullptr) {
		if (CurrentTermPointer->Exponent == SearchExponent) {
			if (TermFound) {
				std::cout << ", ";
			};
			std::cout << (*CurrentTermPointer);
			TermFound = true;
		};
		CurrentTermPointer = CurrentTermPointer->NextTerm;
	};
	if (!TermFound) {
		std::cout << "EMPTY";
	};
	std::cout << ">" << std::endl;
	return TermFound;
};
/*
----------------------------------------------------------------------------------------------------
POLY PRINT
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::Print()const;
Method Description: Prints The Polynomial In Decreasing Order With Respect To The Exponent Value In A Simplified & Unsimplified Form
Return Value: Void
Incoming Params: None
Outgoing Params: None
*/
void Poly::Print()const {
	Term* CurrentTermPointer = this->HeadTerm;
	if (CurrentTermPointer != nullptr) {
		std::cout << "[SYSTEM MESSAGE] [Unsimplified] Polynomial: <";
		while (CurrentTermPointer != nullptr) {
			if (CurrentTermPointer != this->HeadTerm) {
				std::cout << " + ";
			};
			std::cout << (*CurrentTermPointer);
			CurrentTermPointer = CurrentTermPointer->NextTerm;
		};
		std::cout << ">" << std::endl;
		std::cout << "[SYSTEM MESSAGE]   [Simplified] Polynomial: <";
		bool PreviousTermPrinted = false;
		CurrentTermPointer = this->HeadTerm;
		while (CurrentTermPointer != nullptr) {
			if (CurrentTermPointer->Coefficient != 0) {
				if (PreviousTermPrinted) {
					std::cout << " + ";
				};
				std::cout << (*CurrentTermPointer);
				PreviousTermPrinted = true;
			};
			CurrentTermPointer = CurrentTermPointer->NextTerm;
		};
		std::cout << ">" << std::endl;
	}
	else {
		std::cout << "[SYSTEM MESSAGE] [Unsimplified] Polynomial: <EMPTY>" << std::endl;
		std::cout << "[SYSTEM MESSAGE]   [Simplified] Polynomial: <EMPTY>" << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
POLY PRINT REVERSE
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::PrintReverse()const;
Method Description: Prints The Polynomial In Reverse Decreasing Order With Respect To The Exponent Value In A Simplified & Unsimplified Form
Return Value: Void
Incoming Params: None
Outgoing Params: None
*/
void Poly::PrintReverse()const {
	if (this->HeadTerm != nullptr) {
		std::cout << "[SYSTEM MESSAGE] [Reversed Unsimplified] Polynomial: <";
		this->PrintReverseRecurser(this->HeadTerm,false);
		std::cout << ">" << std::endl;
		std::cout << "[SYSTEM MESSAGE]   [Reversed Simplified] Polynomial: <";
		this->PrintReverseRecurser(this->HeadTerm,true);
		std::cout << ">" << std::endl;
	}
	else {
		std::cout << "[SYSTEM MESSAGE] [Reversed Unsimplified] Polynomial: <EMPTY>" << std::endl;
		std::cout << "[SYSTEM MESSAGE]   [Reversed Simplified] Polynomial: <EMPTY>" << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
POLY PRINT REVERSE RECURSER
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::PrintReverse()const;
Method Description: PrintReverse Helper Method To Print The Term Nodes In Reverse Order
Return Value: Boolean
Incoming Params: InputTermPointer (Term Pointer) Simplified (Boolean)
Outgoing Params: True/False (Boolean)
*/
bool Poly::PrintReverseRecurser(Term* InputTermPointer, bool Simplified)const {
	if (InputTermPointer != nullptr) {
		bool PreviousTermPrinted = this->PrintReverseRecurser(InputTermPointer->NextTerm, Simplified);
		if (Simplified) {
			if (InputTermPointer->Coefficient != 0) {
				if (PreviousTermPrinted) {
					std::cout << " + ";
				};
				std::cout << (*InputTermPointer);
				return true;
			};
		}
		else {
			std::cout << (*InputTermPointer);
			if (this->HeadTerm != InputTermPointer) {
				std::cout << " + ";
			};
			return true;
		};
		return PreviousTermPrinted;
	}
	else {
		return false;
	};
};
/*
----------------------------------------------------------------------------------------------------
POLY RESET
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::Reset(std::string PolynomialName);
Method Description: Deallocates All Term Nodes In The Polynomial Then Sets The HeadTerm To Nullptr
Return Value: Void
Incoming Params: PolynomialName (String)
Outgoing Params: None
*/
void Poly::Reset(std::string PolynomialName) {
	Term* CurrentTermPointer = this->HeadTerm;
	while (CurrentTermPointer != nullptr) {
		Term* NextTermPointer = CurrentTermPointer->NextTerm;
		delete CurrentTermPointer;
		CurrentTermPointer = NextTermPointer;
	};
	this->HeadTerm = nullptr;
	std::cout << "[SYSTEM MESSAGE] Reset Polynomial " << PolynomialName << " Successfully!" << std::endl;
};
/*
----------------------------------------------------------------------------------------------------
POLY EVALUATE
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::Evaluate(double X)const;
Method Description: Evaluates The Polynomial With A Given X Value Then Returns The Result
Return Value: Double
Incoming Params: X (Double)
Outgoing Params: Evaluation (Double)
*/
double Poly::Evaluate(double X)const {
	double Evaluation = 0;
	Term* CurrentTermPointer = this->HeadTerm;
	if (CurrentTermPointer != nullptr) {
		std::cout << "[SYSTEM MESSAGE] [Evaluation] Polynomial: <";
		while (CurrentTermPointer != nullptr) {
			Evaluation += (CurrentTermPointer->Coefficient * std::pow(X, CurrentTermPointer->Exponent));
			std::cout << CurrentTermPointer->Coefficient << "(" << X << ")" << "^(" << CurrentTermPointer->Exponent << ")";
			CurrentTermPointer = CurrentTermPointer->NextTerm;
			if (CurrentTermPointer != nullptr) {
				std::cout << " + ";
			};
		};
		std::cout << ">" << std::endl;
	}
	else {
		std::cout << "[SYSTEM MESSAGE] [Evaluation] Polynomial: <EMPTY>" << std::endl;
	};
	return Evaluation;
};
/*
----------------------------------------------------------------------------------------------------
POLY DERIVATIVE
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Poly::Derivative();
Method Description: Gets The Derivative Of Each Term In The Polynomial
Return Value: Boolean
Incoming Params: None
Outgoing Params: DerivedSuccess (Boolean)
*/
bool Poly::Derivative() {
	bool DerivedSuccess = false;
	Term* CurrentTermPointer = this->HeadTerm;
	while (CurrentTermPointer != nullptr) {
		if (CurrentTermPointer->Exponent == 0) {
			CurrentTermPointer->Coefficient = 0;
		}
		else if (CurrentTermPointer->Exponent == 1) {
			CurrentTermPointer->Exponent = 0;
		}
		else {
			CurrentTermPointer->Coefficient *= CurrentTermPointer->Exponent;
			CurrentTermPointer->Exponent--;
		};
		CurrentTermPointer = CurrentTermPointer->NextTerm;
		DerivedSuccess = true;
	};
	return DerivedSuccess;
};
/*
----------------------------------------------------------------------------------------------------
POLY INSERTION OPERATOR
----------------------------------------------------------------------------------------------------
*/
/*
Friend Function Name: std::ostream& operator<<(std::ostream& OS, const Poly& InputPoly);
Friend Function Description: Calls The Print Method On InputPoly
Return Value: std::ostream& 
Incoming Params: OS (std::ostream&), InputPoly (Poly&)
Outgoing Params: OS (std::ostream&)
*/
std::ostream& operator<<(std::ostream& OS, const Poly& InputPoly) {
	InputPoly.Print();
	return OS;
};
/*
----------------------------------------------------------------------------------------------------
POLY EXTRACTION OPERATOR
----------------------------------------------------------------------------------------------------
*/
/*
Friend Function Name: std::istream& operator>>(std::istream& IS, Poly& InputPoly);
Friend Function Description: Validates The UserInputPolynomial To Be In The Valid Form <Cx^E[ + Cx^E]>, Where C = Coefficient & E = Exponent, Inside Brackets Are Optional []
Return Value: std::istream&
Incoming Params: IS (std::istream&), InputPoly (Poly&)
Outgoing Params: IS (std::istream&)
*/
std::istream& operator>>(std::istream& IS, Poly& InputPoly) {
	bool IsValidPolynomial = true;
	std::string UserInputPolynomial;
	std::getline(IS, UserInputPolynomial);
	//First Checks If Polynomial Is Of Size 6 Or Greater Since The Smallest Valid Polynomial Is 1 Term Of 6 Characters Length, Example: <1x^1>
	if (UserInputPolynomial.size() >= 6 && UserInputPolynomial[0] == '<' && UserInputPolynomial[UserInputPolynomial.size() - 1] == '>') {
		//Checks If UserInputPolynomial Only Has Valid Characters, If It Does Not, It Sets IsValidPolynomial To False
		for (int Index = 1; Index < UserInputPolynomial.size() - 1; Index++) {
			auto ValidCharactersSetIterator = VALID_CHARACTERS_SET.find(UserInputPolynomial[Index]);
			if (ValidCharactersSetIterator == VALID_CHARACTERS_SET.end()) {
				IsValidPolynomial = false;
				break;
			};
		};
		if (IsValidPolynomial) {
			//Breaks UserInputPolynomial By A Whitespace Delimiter And Inserts The Results Into A Vector Array
			UserInputPolynomial = UserInputPolynomial.substr(1, UserInputPolynomial.size() - 2);
			char WSDelimiter = ' ';
			std::stringstream ss(UserInputPolynomial);
			std::string Token;
			std::vector<std::string> StringSplitResultVector;
			while (std::getline(ss, Token, WSDelimiter)) {
				StringSplitResultVector.push_back(Token);
			};
			//For Loops The StringSplitResultVector And Validates Each Potential Term By A Regex, If It Does Not Match Will Set IsValidPolynomial Equal To False
			for (int Index = 0; Index < StringSplitResultVector.size(); Index++) {
				if (StringSplitResultVector[Index].size() > 1) {
					std::string RegexPattern = "^-?\\d+x\\^?-?\\d+$";
					std::regex regex(RegexPattern);
					if (!std::regex_match(StringSplitResultVector[Index], regex)) {
						IsValidPolynomial = false;
						break;
					};
				}
				else if (StringSplitResultVector[Index][0] != '+') {
					IsValidPolynomial = false;
					break;
				};
			};
			if (IsValidPolynomial) {
				//At This Point The Entire Polynomial Is Fully Validated In The Correct Form
				//For Loops The StringSplitResultVector Then Gets The Substring For Coefficient And Exponent Then Parses Them To An Integer To Insert It To InputPoly
				for (int Index = 0; Index < StringSplitResultVector.size(); Index++) {
					if (StringSplitResultVector[Index].size() > 1) {
						std::string CoefficientSubstring;
						std::string ExponentSubstring;
						for (int CharIndex = 0; CharIndex < StringSplitResultVector[Index].size(); CharIndex++) {
							if (StringSplitResultVector[Index][CharIndex] == 'x') {
								CoefficientSubstring = StringSplitResultVector[Index].substr(0, CharIndex);
							}
							else if (StringSplitResultVector[Index][CharIndex] == '^') {
								ExponentSubstring = StringSplitResultVector[Index].substr(CharIndex + 1, StringSplitResultVector[Index].size());
							};
						};
						InputPoly.Insert(std::stoi(CoefficientSubstring), std::stoi(ExponentSubstring));
					};
				};
			};
		};
	}
	else {
		IsValidPolynomial = false;
	};
	if (!IsValidPolynomial) {
		std::cout << "[SYSTEM ERROR] Invalid Input!" << std::endl;
	}
	else {
		std::cout << "[SYSTEM MESSAGE] Successfully Added The Terms Into The Polynomial!" << std::endl;
	};
	return IS;
};