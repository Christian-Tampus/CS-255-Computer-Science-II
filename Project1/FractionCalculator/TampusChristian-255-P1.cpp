/*
Student Name: Christian Tampus
File Name: TampusChristian-255-P1.cpp
Description: Fraction Calculator (Menu Based & User Input Based Fraction Calculators)
Course Number: CS 255
Section Number: 02 (Tuesday/Thursday)
Due Date: 9/26
*/
//Import Libraries
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "Fraction.h"
//#include "Fraction.cpp" //Uncomment '#include "Fraction.cpp" In Case Fraction.cpp Does Not Compile When The File Is Not Classified As Part Of A Project.
//Constant Variables
const int MENU_OPTION_1_ARRAY_SIZE = 4, MENU_OPTION_1_ARRAY_OPTIONS_COUNT = 2, MENU_OPTION_2_ARRAY_SIZE = 22, MENU_OPTION_3_ARRAY_SIZE = 6, MENU_OPTION_2_ARRAY_OPTIONS_COUNT = 20, FRACTION_OPTIONS_ARRAY_SIZES = 4, FRACTION_OPTIONS_ARRAY_OPTIONS_COUNT = 2, VALID_OPERATOR_ARRAY_SIZE = 16;
const std::string INVALID_INPUT_MESSAGE = "[SYSTEM MESSAGE] Invalid Input!", SYNTAX_ERROR = "[SYSTEM MESSAGE] Syntax Error!";
const std::string MENU_OPTION_1_ARRAY[MENU_OPTION_1_ARRAY_SIZE] = {"Calculator Options","[1] Fraction Calculator (TM)","[2] Fraction Calculator X-TREME (TM)","[0] Quit Program"};
const std::string MENU_OPTION_2_ARRAY[MENU_OPTION_2_ARRAY_SIZE] = {"Fraction Calculator (TM) Menu Options","[1] Add Fractions","[2] Subtract Fractions","[3] Multiply Fractions","[4] Divide Fractions","[5] Prefix Increment Fraction","[6] Postfix Increment Fraction","[7] Prefix Decrement Fraction","[8] Postfix Decrement Fraction","[9] Check If ===","[10] Check If ==","[11] Check If <","[12] Check If >","[13] Check If <=","[14] Check If >=","[15] Check If !=","[16] Reduce Fraction","[17] Get Numerator","[18] Get Denominator","[19] Set Numerator","[20] Set Denominator","[0] Exit Fraction Calculator (TM) Menu Options"};
const std::string MENU_OPTION_3_ARRAY[MENU_OPTION_3_ARRAY_SIZE] = {"Fraction Calculator X-TREME (TM) Menu Options","Allowed Inputs: ~ 0 1 2 3 4 5 6 7 8 9 + - * / ++ -- == === != > < >= <= _ ( | )","Rules: Fractions Must Be Inside Parenthesis, Increment & Decrement Operations Can Only Be At The Start [Prefix --(1|2), ++(1|2)] Or End [Postfix (1|2)--, (1|2)++] Of An Input, Reduce [(100|50)_] Operator Can Only Be At The End Of An Input, No Spaces Allowed!","Order Of Operations: From Left To Right (Ignores Standard Order Of Operations).","Example Input: --(1|2)+(~3|4)-(5|~6)*(~7|~8)/(9|10)>(~11|12)<(13|~14)>=(~15|~16)<=(17|18)==(~19|20)===(21|~22)!=(~23|~24)++_","Please Enter Fractions To Calculate Or Press [0] To Exit Fraction Calculator X-TREME (TM) Menu Options:"};
const std::string FRACTION_PREFIX_INCREMENT_ARRAY[FRACTION_OPTIONS_ARRAY_SIZES] = {"Prefix Increment Fraction Menu","[1] Prefix Increment Fraction 1","[2] Prefix Increment Fraction 2","[0] Exit Prefix Increment Fraction Menu"};
const std::string FRACTION_POSTFIX_INCREMENT_ARRAY[FRACTION_OPTIONS_ARRAY_SIZES] = {"Postfix Increment Fraction Menu","[1] Postfix Increment Fraction 1","[2] Postfix Increment Fraction 2","[0] Exit Postfix Increment Fraction Menu"};
const std::string FRACTION_PREFIX_DECREMENT_ARRAY[FRACTION_OPTIONS_ARRAY_SIZES] = {"Prefix Decrement Fraction Menu","[1] Prefix Decrement Fraction 1","[2] Prefix Decrement Fraction 2","[0] Exit Prefix Decrement Fraction Menu"};
const std::string FRACTION_POSTIFX_DECREMENT_ARRAY[FRACTION_OPTIONS_ARRAY_SIZES] = {"Postfix Decrement Fraction Menu","[1] Postfix Decrement Fraction 1","[2] Postfix Decrement Fraction 2","[0] Exit Postfix Decrement Fraction Menu"};
const std::string FRACTION_REDUCE_MENU_OPTIONS_ARRAY[FRACTION_OPTIONS_ARRAY_SIZES] = {"Reduce Fraction Menu","[1] Reduce Fraction 1","[2] Reduce Fraction 2","[0] Exit Reduce Fraction Menu"};
const std::string FRACTION_GET_NUMERATOR_MENU_OPTIONS_ARRAY[FRACTION_OPTIONS_ARRAY_SIZES] = {"Get Numerator Menu","[1] Fraction 1 Numerator","[2] Fraction 2 Numerator","[0] Exit Get Numerator Menu"};
const std::string FRACTION_GET_DENOMINATOR_MENU_OPTIONS_ARRAY[FRACTION_OPTIONS_ARRAY_SIZES] = {"Get Denominator Menu","[1] Fraction 1 Denominator","[2] Fraction 2 Denominator","[0] Exit Get Denominator Menu"};
const std::string FRACTION_SET_NUMERATOR_MENU_OPTIONS_ARRAY[FRACTION_OPTIONS_ARRAY_SIZES] = {"Set Numerator Menu","[1] Fraction 1 Numerator","[2] Fraction 2 Numerator","[0] Exit Set Numerator Menu"};
const std::string FRACTION_SET_DENOMINATOR_MENU_OPTIONS_ARRAY[FRACTION_OPTIONS_ARRAY_SIZES] = {"Set Denominator Menu","[1] Fraction 1 Denominator","[2] Fraction 2 Denominator","[0] Exit Set Denominator Menu"};
//Constant Variables Used For The Input Validation Used For The Delimiters Or Key Characters To Find & Verify.
const std::string VALID_OPERATORS_ARRAY[VALID_OPERATOR_ARRAY_SIZE] = {"+","-","*","/","++","--","==","===","!=",">","<",">=","<=","++_","--_","_"};
const std::set<char> VALID_INPUT_CHARACTERS_SET = {'0','1','2','3','4','5','6','7','8','9','+','-','*','/','(',')','|','=','>','<','_','!','~'};
const std::set<char> DELIMITER_SET = {'+','-','*','/','(',')','=','>','<','_','!'};
//Constant Variables Used To Replace If User Inputs A Value Larger Than What Can Be Parsed To An Int Data Type, For Example The Number: 100000000000 Or -100000000000 Will Be Changed To 2147483647 & -2147483647 Respectively.
const int LARGEST_INTEGER = 2147483647, SMALLEST_INTEGER = -2147483647;
//Function Prototypes
void Output(std::string OutputMessage, Fraction &Fraction1, Fraction &Fraction2, std::string IncrementDecrement = "None", bool IsFraction1 = true);
int GetUserInput(const std::string MenuArray[], int MenuOptionArraySize, int MenuOptionsCount);
void DisplayMenu1(Fraction &Fraction1, Fraction &Fraction2);
void DisplayMenu2(Fraction &Fraction1, Fraction &Fraction2);
void DisplayFractionOptions(std::string Action, Fraction &Fraction1, Fraction &Fraction2);
void Add(Fraction &Fraction1, Fraction &Fraction2);
void Subtract(Fraction &Fraction1, Fraction &Fraction2);
void Multiply(Fraction &Fraction1, Fraction &Fraction2);
void Divide(Fraction &Fraction1, Fraction &Fraction2);
void PreFixIncrement(Fraction &Fraction1, Fraction &Fraction2);
void PostFixIncrement(Fraction &Fraction1, Fraction &Fraction2);
void PreFixDecrement(Fraction &Fraction1, Fraction &Fraction2);
void PostFixDecrement(Fraction &Fraction1, Fraction &Fraction2);
void Exact(Fraction &Fraction1, Fraction &Fraction2);
void Equal(Fraction &Fraction1, Fraction &Fraction2);
void LessThan(Fraction &Fraction1, Fraction &Fraction2);
void GreaterThan(Fraction &Fraction1, Fraction &Fraction2);
void LessThanOrEqualTo(Fraction &Fraction1, Fraction &Fraction2);
void GreaterThanOrEqualTo(Fraction &Fraction1, Fraction &Fraction2);
void NotEquals(Fraction &Fraction1, Fraction & Fraction2);
void ReduceFraction(Fraction &Fraction1, Fraction &Fraction2);
void OutputGetNumDenFractionValues(std::string NumDenLabel, Fraction &Fraction1, Fraction &Fraction2, const std::string MenuArray[], int ArraySize, int ArrayCount, bool IsNumerator);
void SetNumDenFractionValues(std::string NumDenLabel, Fraction &Fraction1, Fraction &Fraction2, const std::string MenuArray[], int ArraySize, int ArrayCount, bool IsNumerator);
void GetNumerator(Fraction &Fraction1, Fraction &Fraction2);
void GetDenominator(Fraction &Fraction1, Fraction &Fraction2);
void SetNumerator(Fraction &Fraction1, Fraction &Fraction2);
void SetDenominator(Fraction &Fraction1, Fraction &Fraction2);
//Function Array To The Menu Based Fraction Calculator (Fraction Calculator Option 1), Instead Of Using A Switch Or If Statements, It Indexes The Proper Function Based On User Input, Offset By -1 So It Properly Indexes The Array. Example: User Chooses Option [1], It Will Index 0.
void (*FractionFunctionsArray[20])(Fraction &Fraction1, Fraction &Fraction2) = {Add,Subtract,Multiply,Divide,PreFixIncrement,PostFixIncrement,PreFixDecrement,PostFixDecrement,Exact,Equal,LessThan,GreaterThan,LessThanOrEqualTo,GreaterThanOrEqualTo,NotEquals,ReduceFraction,GetNumerator,GetDenominator,SetNumerator,SetDenominator};
bool ValidateInput(std::string UserInput, std::vector<std::string> &InputFractionsVector, std::vector<std::string> &InputOperatorsVector);
void DisplayMenu3();
/*
Function Name: main
Brief Description: Main Driver Function, Initializes Fraction 1 & 2 For Fraction Calculator Then Displays The First Menu To Let User Choose Between 2 Fraction Calculators
Return Value: Integer
Incoming Parameters: None
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
int main(){
    std::cout << "TEXAN INSTRUMENTS (TM) Version 1.0.0" << std::endl;
    std::cout << "Developed By Christian Tampus" << std::endl;
    Fraction Fraction1(1,1), Fraction2(1,1);
    DisplayMenu1(Fraction1,Fraction2);
    std::cout << "[SYSTEM MESSAGE] Program Terminated..." << std::endl;
    return 0;
};
/*
Function Name: Output
Brief Description: Outputs The Results For The Fraction Calculator (Note: Does Not Output For Fraction Calculator X-TREME)
Return Value: Void
Incoming Parameters: OutputMessage (String), Fraction1 (Fraction), Fraction2 (Fraction), IncrementDecrement (String), IsFraction(Bool)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void Output(std::string OutputMessage, Fraction &Fraction1, Fraction &Fraction2, std::string IncrementDecrement, bool IsFraction1){
    std::cout << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    if (IncrementDecrement.compare("None") == 0){
        //Standard Output Message For The Menu Based Fraction Calculator
        std::cout << "Fraction 1: " << Fraction1 << std::endl;
        std::cout << "Fraction 2: " << Fraction2 << std::endl;
        std::cout << OutputMessage << std::endl;
    }else{
        //Output Messages To Test For Prefix & Postfix Increment & Decrement Operators For The Menu Based Fraction Calculator
        if (IncrementDecrement.compare("PreFixIncrement") == 0){
            if (IsFraction1){
                std::cout << "[PREV] Prefix Increment Fraction 1: " << ++Fraction1 << std::endl;
                std::cout << "[CURR] Prefix Increment Fraction 1: " << Fraction1 << std::endl;
            }else{
                std::cout << "[PREV] Prefix Increment Fraction 2: " << ++Fraction2 << std::endl;
                std::cout << "[CURR] Prefix Increment Fraction 2: " << Fraction2 << std::endl;
            };
        }else if (IncrementDecrement.compare("PostFixIncrement") == 0){
            if (IsFraction1){
                std::cout << "[PREV] Postfix Increment Fraction 1: " << Fraction1++ << std::endl;
                std::cout << "[CURR] Postfix Increment Fraction 1: " << Fraction1 << std::endl;
            }else{
                std::cout << "[PREV] Postfix Increment Fraction 2: " << Fraction2++ << std::endl;
                std::cout << "[CURR] Postfix Increment Fraction 2: " << Fraction2 << std::endl;
            };
        }else if (IncrementDecrement.compare("PreFixDecrement") == 0){
            if (IsFraction1){
                std::cout << "[PREV] Prefix Decrement Fraction 1: " << --Fraction1 << std::endl;
                std::cout << "[CURR] Prefix Decrement Fraction 1: " << Fraction1 << std::endl;
            }else{
                std::cout << "[PREV] Prefix Decrement Fraction 2: " << --Fraction2 << std::endl;
                std::cout << "[CURR] Prefix Decrement Fraction 2: " << Fraction2 << std::endl;
            };
        }else if (IncrementDecrement.compare("PostFixDecrement") == 0){
            if (IsFraction1){
                std::cout << "[PREV] Postfix Decrement Fraction 1: " << Fraction1-- << std::endl;
                std::cout << "[CURR] Postfix Decrement Fraction 1: " << Fraction1 << std::endl;
            }else{
                std::cout << "[PREV] Postfix Decrement Fraction 2: " << Fraction2-- << std::endl;
                std::cout << "[CURR] Postfix Decrement Fraction 2: " << Fraction2 << std::endl;
            };
        };
    };
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << std::endl;
};
/*
Function Name: GetUserInput
Brief Description: Gets User Input For The Menu Options
Return Value: Integer
Incoming Parameters: MenuArray (String Array), MenuOptionArraySize (Integer), MenuOptionsCount (Integer)
Outgoing Parameters: UserInputToInteger (Integer)
*/
int GetUserInput(const std::string MenuArray[], int MenuOptionArraySize, int MenuOptionsCount){
    std::cout << std::endl;
    std::string UserInput;
    int UserInputToInteger = -1;
    for (int Index = 0; Index < MenuOptionArraySize; Index++){
        std::cout << MenuArray[Index] << std::endl;
    };
    std::cout << std::endl;
    do{
        //Dynamically Get The User Input For Whatever Menu & Option Range Inputted Into The Function, Can Handle Errors If User Inputs An Invalid Argument Or A Valid But Out Of Range Input When Parsing To An Integer.
        std::cout << "Choose Option:";
        std::cin >> std::ws;
        std::getline(std::cin,UserInput);
        try{
            UserInputToInteger = std::stoi(UserInput);
            if (UserInputToInteger < 0 || UserInputToInteger > MenuOptionsCount){
                std::cout << INVALID_INPUT_MESSAGE << std::endl;
            };
        }catch(const std::invalid_argument &INVALID_ARGUMENT_ERROR){
            UserInputToInteger = -1;
            std::cout << INVALID_INPUT_MESSAGE << std::endl;
        }catch(const std::out_of_range &OUT_OF_RANGE_ERROR){
            UserInputToInteger = -1;
            std::cout << INVALID_INPUT_MESSAGE << std::endl;
        };
    }while(UserInputToInteger < 0 || UserInputToInteger > MenuOptionsCount);
    return UserInputToInteger;
};
/*
Function Name: DisplayMenu1
Brief Description: Displays First Menu To Let User Choose Between 2 Fraction Calculators (Standard & X-TREME)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void DisplayMenu1(Fraction &Fraction1, Fraction &Fraction2){
    int UserMenu1Option = GetUserInput(MENU_OPTION_1_ARRAY,MENU_OPTION_1_ARRAY_SIZE,MENU_OPTION_1_ARRAY_OPTIONS_COUNT);
    //Switch Used To Display Menu Based (Option 1) Fraction Calculator Or The Input Based (Option 2) Fraction Calculator X-TREME
    switch(UserMenu1Option){
        case 1:
            DisplayMenu2(Fraction1,Fraction2);
            break;
        case 2:
            DisplayMenu3();
            break;
        default:
            break;
    };
    if (UserMenu1Option != 0){
        DisplayMenu1(Fraction1,Fraction2);
    };
};
/*
Function Name: DisplayMenu2
Brief Description: Displays Second Menu For The Standard Fraction Calculator, Calls The Functions By A Function Array, Indexing With Their Option With 1 Offset.
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void DisplayMenu2(Fraction &Fraction1, Fraction &Fraction2){
    int UserMenu2Option = GetUserInput(MENU_OPTION_2_ARRAY,MENU_OPTION_2_ARRAY_SIZE,MENU_OPTION_2_ARRAY_OPTIONS_COUNT);
    if (UserMenu2Option != 0){
        //When The User Inputs A Valid Option & Did Not Choose To Exit The Menu, It Will Index The Function Array To Call The Designated Function To Execute The Operation, Example: User Chooses Option [10] It Will Index And Call The Function At 9.
        FractionFunctionsArray[UserMenu2Option-1](Fraction1,Fraction2);
        DisplayMenu2(Fraction1,Fraction2);
    }else{
        std::cout << "[SYSTEM MESSAGE] Exited Menu Options 2 Successfully!" << std::endl;
    };
};
/*
Function Name: DisplayFractionOptions
Brief Description: Displays The Current Fraction 1 & 2 Values To Let User Choose Which One To Pick When Doing A Method/Friend Function With The Fraction Class
Return Value: Void
Incoming Parameters: Action (String) Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void DisplayFractionOptions(std::string Action, Fraction &Fraction1, Fraction &Fraction2){
    //This Is Part Of The Sub Menu Of The Menu Based Fraction Calculator (Option 1).
    std::cout << "Please Choose Which Fraction To " << Action << std::endl;
    std::cout << "Fraction 1: " << Fraction1 << std::endl;
    std::cout << "Fraction 2: " << Fraction2 << std::endl;
};
/*
Function Name: Add
Brief Description: Adds The Fractions Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void Add(Fraction &Fraction1, Fraction &Fraction2){
    Fraction NewFraction = Fraction1 + Fraction2;
    Output("Fraction 1 + Fraction 2 ?: "+std::to_string(NewFraction.GetNum())+"/"+std::to_string(NewFraction.GetDen()),Fraction1,Fraction2);
};
/*
Function Name: Subtract
Brief Description: Subtracts The Fractions Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void Subtract(Fraction &Fraction1, Fraction &Fraction2){
    Fraction NewFraction = Fraction1 - Fraction2;
    Output("Fraction 1 - Fraction 2 ?: "+std::to_string(NewFraction.GetNum())+"/"+std::to_string(NewFraction.GetDen()),Fraction1,Fraction2);
};
/*
Function Name: Multiply
Brief Description: Multiplies The Fractions Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void Multiply(Fraction &Fraction1, Fraction &Fraction2){
    Fraction NewFraction = Fraction1 * Fraction2;
    Output("Fraction 1 * Fraction 2 ?: "+std::to_string(NewFraction.GetNum())+"/"+std::to_string(NewFraction.GetDen()),Fraction1,Fraction2);
};
/*
Function Name: Divide
Brief Description: Divides The Fractions Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void Divide(Fraction &Fraction1, Fraction &Fraction2){
    Fraction NewFraction = Fraction1 / Fraction2;
    Output("Fraction 1 / Fraction 2 ?: "+std::to_string(NewFraction.GetNum())+"/"+std::to_string(NewFraction.GetDen()),Fraction1,Fraction2);
};
/*
Function Name: PreFixIncrement
Brief Description: Calls DisplayFractionOptions Then Gets The User Input To Calculate Which Fraction To Prefix Increment Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void PreFixIncrement(Fraction &Fraction1, Fraction &Fraction2){
    //Display Sub Menu Of The Menu Based Fraction Calculator (Option 1) Then Get The User Input To Apply The Operation At The Selected Fraction (Fraction1 Or Fraction 2).
    DisplayFractionOptions("Prefix Increment",Fraction1,Fraction2);
    int FractionOption = GetUserInput(FRACTION_PREFIX_INCREMENT_ARRAY,FRACTION_OPTIONS_ARRAY_SIZES,FRACTION_OPTIONS_ARRAY_OPTIONS_COUNT);
    Output("None",Fraction1,Fraction2,"PreFixIncrement",(FractionOption == 1 ? true : false));
};
/*
Function Name: PostFixIncrement
Brief Description: Calls DisplayFractionOptions Then Gets The User Input To Calculate Which Fraction To Postfix Increment Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void PostFixIncrement(Fraction &Fraction1, Fraction &Fraction2){
    //Display Sub Menu Of The Menu Based Fraction Calculator (Option 1) Then Get The User Input To Apply The Operation At The Selected Fraction (Fraction1 Or Fraction 2).
    DisplayFractionOptions("Postfix Increment",Fraction1,Fraction2);
    int FractionOption = GetUserInput(FRACTION_POSTFIX_INCREMENT_ARRAY,FRACTION_OPTIONS_ARRAY_SIZES,FRACTION_OPTIONS_ARRAY_OPTIONS_COUNT);
    Output("None",Fraction1,Fraction2,"PostFixIncrement",(FractionOption == 1 ? true : false));
};
/*
Function Name: PreFixDecrement
Brief Description: Calls DisplayFractionOptions Then Gets The User Input To Calculate Which Fraction To Prefix Decrement Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void PreFixDecrement(Fraction &Fraction1, Fraction &Fraction2){
    //Display Sub Menu Of The Menu Based Fraction Calculator (Option 1) Then Get The User Input To Apply The Operation At The Selected Fraction (Fraction1 Or Fraction 2).
    DisplayFractionOptions("Prefix Decrement",Fraction1,Fraction2);
    int FractionOption = GetUserInput(FRACTION_PREFIX_DECREMENT_ARRAY,FRACTION_OPTIONS_ARRAY_SIZES,FRACTION_OPTIONS_ARRAY_OPTIONS_COUNT);
    Output("None",Fraction1,Fraction2,"PreFixDecrement",(FractionOption == 1 ? true : false));
};
/*
Function Name: PostFixDecrement
Brief Description: Calls DisplayFractionOptions Then Gets The User Input To Calculate Which Fraction To Postfix Decrement Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void PostFixDecrement(Fraction &Fraction1, Fraction &Fraction2){
    //Display Sub Menu Of The Menu Based Fraction Calculator (Option 1) Then Get The User Input To Apply The Operation At The Selected Fraction (Fraction1 Or Fraction 2).
    DisplayFractionOptions("Postfix Decrement",Fraction1,Fraction2);
    int FractionOption = GetUserInput(FRACTION_POSTIFX_DECREMENT_ARRAY,FRACTION_OPTIONS_ARRAY_SIZES,FRACTION_OPTIONS_ARRAY_OPTIONS_COUNT);
    Output("None",Fraction1,Fraction2,"PostFixDecrement",(FractionOption == 1 ? true : false));
};
/*
Function Name: Exact
Brief Description: Calculates Both Fractions If Fraction1 === Fraction2 Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void Exact(Fraction &Fraction1, Fraction &Fraction2){
    Output((isExact(Fraction1,Fraction2) ? "Fraction 1 === Fraction 2 ?: True" : "Fraction 1 === Fraction 2 ?: False"),Fraction1,Fraction2);
};
/*
Function Name: Equal
Brief Description: Calculates Both Fractions If Fraction1 == Fraction2 Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void Equal(Fraction &Fraction1, Fraction &Fraction2){
    Output((Fraction1 == Fraction2 ? "Fraction 1 == Fraction 2 ?: True": "Fraction 1 == Fraction 2 ?: False"),Fraction1,Fraction2);
};
/*
Function Name: LessThan
Brief Description: Calculates Both Fractions If Fraction1 < Fraction2 Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void LessThan(Fraction &Fraction1, Fraction &Fraction2){
    Output((Fraction1 < Fraction2 ? "Fraction 1 < Fraction 2 ?: True": "Fraction 1 < Fraction 2 ?: False"),Fraction1,Fraction2);
};
/*
Function Name: GreaterThan
Brief Description: Calculates Both Fractions If Fraction1 > Fraction2 Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void GreaterThan(Fraction &Fraction1, Fraction &Fraction2){
    Output((Fraction1 > Fraction2 ? "Fraction 1 > Fraction 2 ?: True" : "Fraction 1 > Fraction 2 ?: False"),Fraction1,Fraction2);
};
/*
Function Name: LessThanOrEqualTo
Brief Description: Calculates Both Fractions If Fraction1 <= Fraction2 Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void LessThanOrEqualTo(Fraction &Fraction1, Fraction &Fraction2){
    Output((Fraction1 <= Fraction2 ? "Fraction 1 <= Fraction 2 ?: True" : "Fraction 1 <= Fraction 2 ?: False"),Fraction1,Fraction2);
};
/*
Function Name: GreaterThanOrEqualTo
Brief Description: Calculates Both Fractions If Fraction1 >= Fraction2 Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void GreaterThanOrEqualTo(Fraction &Fraction1, Fraction &Fraction2){
    Output((Fraction1 >= Fraction2 ? "Fraction 1 >= Fraction 2 ?: True" : "Fraction 1 >= Fraction 2 ?: False"),Fraction1,Fraction2);
};
/*
Function Name: NotEquals
Brief Description: Calculates Both Fractions If Fraction1 != Fraction2 Then Calls Output To Display The Result (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void NotEquals(Fraction &Fraction1, Fraction & Fraction2){
    Output((Fraction1 != Fraction2 ? "Fraction 1 != Fraction 2 ?: True" : "Fraction 1 != Fraction 2 ?: False"),Fraction1,Fraction2);
};
/*
Function Name: ReduceFraction
Brief Description: Calls DisplayFractionOptions Then Gets The User Input To Get The Fraction Option To Reduce (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void ReduceFraction(Fraction &Fraction1, Fraction &Fraction2){
    DisplayFractionOptions("Reduce",Fraction1,Fraction2);
    int FractionOption = GetUserInput(FRACTION_REDUCE_MENU_OPTIONS_ARRAY,FRACTION_OPTIONS_ARRAY_SIZES,FRACTION_OPTIONS_ARRAY_OPTIONS_COUNT);
    if (FractionOption == 0){
        std::cout << "[SYSTEM MESSAGE] Exited Reduce Fraction Menu Successfully!" << std::endl;
    }else{
        if (FractionOption == 1){
            Fraction1.reduce();
        }else{
            Fraction2.reduce();
        };
        std::cout << "[SYSTEM MESSAGE] Reduced Fraction " << FractionOption << " Successfully!" << std::endl;
    };
};
/*
Function Name: OutputGetNumDenFractionValues
Brief Description: Outputs The Numerator Or Denominator Of The Selected Fraction Option (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: NumDenLabel (String), Fraction1 (Fraction), Fraction2 (Fraction), MenuArray (String Array), ArraySize (Integer), ArrayCount (Integer), IsNumerator (Boolean)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void OutputGetNumDenFractionValues(std::string NumDenLabel, Fraction &Fraction1, Fraction &Fraction2, const std::string MenuArray[], int ArraySize, int ArrayCount, bool IsNumerator){
    int FractionOption = GetUserInput(MenuArray,ArraySize,ArrayCount);
    if (FractionOption == 0){
        std::cout << "[SYSTEM MESSAGE] Exited Get Fraction " << NumDenLabel << " Menu Successfully!" << std::endl;
    }else{
        Output("Fraction "+std::to_string(FractionOption)+" "+NumDenLabel+": "+std::to_string((FractionOption == 1 ? (IsNumerator ? Fraction1.GetNum() : Fraction1.GetDen()) : (IsNumerator ? Fraction2.GetNum() : Fraction2.GetDen()))),Fraction1,Fraction2);
    };
};
/*
Function Name: SetNumDenFractionValues
Brief Description: Sets The Numerator Or Denominator Of The Selected Fraction Option (This Only Works For The Standard Fraction Calculator)
Return Value: Void
Incoming Parameters: NumDenLabel (String), Fraction1 (Fraction), Fraction2 (Fraction), MenuArray (String Array), ArraySize (Integer), ArrayCount (Integer), IsNumerator (Boolean)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void SetNumDenFractionValues(std::string NumDenLabel, Fraction &Fraction1, Fraction &Fraction2, const std::string MenuArray[], int ArraySize, int ArrayCount, bool IsNumerator){
    //Display Sub Menu Of The Menu Based Fraction Calculator (Option 1) Then Get The User Input To Apply The Operation At The Selected Fraction (Fraction1 Or Fraction 2), If User Chooses Option 0, It Will Exit The Sub Menu & Print A System Message Indicating Successful Exit.
    int FractionOption = GetUserInput(MenuArray,ArraySize,ArrayCount);
    if (FractionOption == 0){
        std::cout << "[SYSTEM MESSAGE] Exited Set Fraction " << NumDenLabel << " Menu Successfully!" << std::endl;
    }else{
        std::string UserInput;
        int NewFractionValue;
        bool IsValidIntegerValue = false;
        do{
            //After User Chooses Which Fraction To Set The Numerator Or Denominator To, This Loop Will Validate The Input To Make Sure It Is A Valid Integer, Can Handle Errors When The Input Is Not A Valid Integer Or If The Integer Is To Large (Out Of Range) For The Integer Data Type.
            std::cout << "Please Enter A New " << NumDenLabel << " For Fraction " << FractionOption << std::endl;
            std::cin >> std::ws;
            std::getline(std::cin,UserInput);
            try{
                NewFractionValue = std::stoi(UserInput);
                IsValidIntegerValue = true;
            }catch(const std::invalid_argument &INVALID_ARGUMENT_ERROR){
                std::cout << INVALID_INPUT_MESSAGE << std::endl;
            }catch(const std::out_of_range &OUT_OF_RANGE_ERROR){
                std::cout << INVALID_INPUT_MESSAGE << std::endl;
            };
        }while(!IsValidIntegerValue);
        //Sets The Numerator & Denominators Of Both Fraction 1 & 2, If It Is Not The Fraction Option It Will Set It To The Current Value By Using The .GetNum() Or .GetDen() Method
        Fraction1.SetNum((IsNumerator && FractionOption == 1 ? NewFractionValue : Fraction1.GetNum()));
        Fraction1.SetDen((!IsNumerator && FractionOption == 1 ? NewFractionValue : Fraction1.GetDen()));
        Fraction2.SetNum((IsNumerator && FractionOption == 2 ? NewFractionValue : Fraction2.GetNum()));
        Fraction2.SetDen((!IsNumerator && FractionOption == 2 ? NewFractionValue : Fraction2.GetDen()));
        std::cout << "[SYSTEM MESSAGE] Updated Fraction " << FractionOption << " " << NumDenLabel << " Successfully!" << std::endl;
    };
};
/*
Function Name: GetNumerator
Brief Description: Calls DisplayFractionOptions Then Calls OutputGetNumDenFractionValues To Get The Numerator
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void GetNumerator(Fraction &Fraction1, Fraction &Fraction2){
    DisplayFractionOptions("Get Numerator From",Fraction1,Fraction2);
    OutputGetNumDenFractionValues("Numerator",Fraction1,Fraction2,FRACTION_GET_NUMERATOR_MENU_OPTIONS_ARRAY,FRACTION_OPTIONS_ARRAY_SIZES,FRACTION_OPTIONS_ARRAY_OPTIONS_COUNT,true);
};
/*
Function Name: GetDenominator
Brief Description: Calls DisplayFractionOptions Then Calls OutputGetNumDenFractionValues To Get The Denominator
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void GetDenominator(Fraction &Fraction1, Fraction &Fraction2){
    DisplayFractionOptions("Get Denominator From",Fraction1,Fraction2);
    OutputGetNumDenFractionValues("Denominator",Fraction1,Fraction2,FRACTION_GET_DENOMINATOR_MENU_OPTIONS_ARRAY,FRACTION_OPTIONS_ARRAY_SIZES,FRACTION_OPTIONS_ARRAY_OPTIONS_COUNT,false);
};
/*
Function Name: SetNumerator
Brief Description: Calls DisplayFractionOptions Then Calls SetNumDenFractionValues To Set The Numerator
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void SetNumerator(Fraction &Fraction1, Fraction &Fraction2){
    DisplayFractionOptions("Set Numerator To",Fraction1,Fraction2);
    SetNumDenFractionValues("Numerator",Fraction1,Fraction2,FRACTION_SET_NUMERATOR_MENU_OPTIONS_ARRAY,FRACTION_OPTIONS_ARRAY_SIZES,FRACTION_OPTIONS_ARRAY_OPTIONS_COUNT,true);
};
/*
Function Name: SetDenominator
Brief Description: Calls DisplayFractionOptions Then Calls SetNumDenFractionValues To Set The Denominator
Return Value: Void
Incoming Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
Outgoing Parameters: Fraction1 (Fraction), Fraction2 (Fraction)
*/
void SetDenominator(Fraction &Fraction1, Fraction &Fraction2){
    DisplayFractionOptions("Set Denominator To",Fraction1,Fraction2);
    SetNumDenFractionValues("Denominator",Fraction1,Fraction2,FRACTION_SET_DENOMINATOR_MENU_OPTIONS_ARRAY,FRACTION_OPTIONS_ARRAY_SIZES,FRACTION_OPTIONS_ARRAY_OPTIONS_COUNT,false);
};
/*
Function Name: ValidateInput
Brief Description: Validates The User Input For The Fraction Calculator X-TREME, Can Handle Invalid Arguments, Invalid Characters, Invalid Character Placement Etc.
Return Value: Void
Incoming Parameters: UserInput (String), InputFractionsVector (String Vector), InputOperatorsVector (String Vector)
Outgoing Parameters: ValidInput (Boolean)
*/
bool ValidateInput(std::string UserInput, std::vector<std::string> &InputFractionsVector, std::vector<std::string> &InputOperatorsVector){
    //Any Input Less Than 5 Is Automatically Invalid, Since The Smallest Valid Input Is 2 Parenthesis, 1 Fraction Divider & 2 Integers, A Total Of 5 Characters Example: (1|2)
    if (UserInput.size() < 5){
        return false;
    };
    bool ValidInput = true, RecordFractionValues = false, RecordOperators = true;
    int ParenthesisStackCount = 0, CurrentOperatorRecordStartIndex = 0;
    std::string CurrentFractionValue = "", CurrentOperator = "";
    for (int Index1 = 0; Index1 < UserInput.size(); Index1++){
        //This Checks The VALID_INPUT_CHARACTERS_SET To Make Sure The Current Character Is A Valid Character, Since The IsValidCharacter Is Initially Declared As False, If It Was Not Set To True, It Will Make ValidInput False Which Makes The Input Invalid
        bool IsValidCharacter = false;
        auto ValidInputCharactersSetIterator = VALID_INPUT_CHARACTERS_SET.find(UserInput[Index1]);
        if (ValidInputCharactersSetIterator != VALID_INPUT_CHARACTERS_SET.end()){
            IsValidCharacter = true;
        };
        if (!IsValidCharacter){
            ValidInput = false;
            break;
        };
        //This Uses A 'Stack' Based Approach Without Using An Actual Stack Array/Vector But Instead A Counter To Make Sure All Open Parenthesis & Closing Parenthesis Have A Pair In The Input, If At Any Point In The Loop ParenthesisStackCount > 0 Or < 1 It Will Invalidate The Input
        ParenthesisStackCount = (UserInput[Index1] == '(' ? ParenthesisStackCount + 1 : UserInput[Index1] == ')' ? ParenthesisStackCount - 1 : ParenthesisStackCount);
        if (ParenthesisStackCount < 0 || ParenthesisStackCount > 1){
            ValidInput = false;
            break;
        };
        //This Makes Sure That There Is Something Inside Each Parenthesis () In The Entire Input, If There Is Nothing Inside The Parenthesis, It Will Invalidate The Input, Example: () Is Invalid, (1|2) Is Valid
        if (UserInput[Index1] == '('){
            RecordFractionValues = true;
        }else if (UserInput[Index1] == ')'){
            RecordFractionValues = false;
            if (CurrentFractionValue.size() == 0){
                ValidInput = false;
                break;
            };
        }else if (RecordFractionValues){
            CurrentFractionValue += UserInput[Index1];
        };
        //This Is The Reducer Operator, It Makes Sure The Only Location It Is Allowed Is The Last Index Of The Input, If It Is Not, It Invalidates The Input, Example: _(1|2) Is Invalid, (1|2)_ Is Valid
        if (UserInput[Index1] == '_' && Index1 != UserInput.size()-1){
            ValidInput = false;
            break;
        };
        //This Records All The Operators In Between Closing & Opening Parenthesis )+( Before The First Opening Parenthesis --( And After The Last Closing Parenthesis )++ If It Detects That There Is No Operator In Between It Will Invalidate The Input, Example : (1|2)(3|4) Is Invalid, (1|2)+(3|4) Is Valid
        if (UserInput[Index1] == ')'){
            RecordOperators = true;
            CurrentOperatorRecordStartIndex = Index1 + 1;
        }else if (UserInput[Index1] == '('){
            RecordOperators = false;
            if (Index1-1 > 0 && UserInput[Index1-1] == ')'){
                ValidInput = false;
                break;
            };
        }else if (RecordOperators){
            CurrentOperator += UserInput[Index1];
            if (Index1+1 == UserInput.size()){
                RecordOperators = false;
            };
        };
        //For Each Recorded Operator, It Checks If It Is In The Valid Positions, For The Increment/Decrement Operators They Must Be At The Start Or End Of An Input To Be Valid, For The Reduce Operator It Must Be At The End, If It Is Any Other Operator As Long As They Are In Between Parenthesis & Not At The Edges Of The Input It Is A Valid Operator
        if (!RecordOperators && CurrentOperator.size() > 0){
            bool ValidOperator = false;
            for (int Index2 = 0; Index2 < VALID_OPERATOR_ARRAY_SIZE; Index2++){
                if (VALID_OPERATORS_ARRAY[Index2].compare(CurrentOperator) == 0){
                    if (CurrentOperator.compare("--") == 0 || CurrentOperator.compare("++") == 0){
                        //Makes Sure Decrement & Increment Operators Are Valid For Prefix & Postfix Positions In The Input
                        if (CurrentOperatorRecordStartIndex == 0 && CurrentOperatorRecordStartIndex + 2 < UserInput.size() && UserInput[CurrentOperatorRecordStartIndex+2] == '('){
                            ValidOperator = true;
                        }else if (CurrentOperatorRecordStartIndex - 1 >= 4 && UserInput[CurrentOperatorRecordStartIndex-1] == ')' && Index1+1 == UserInput.size()){
                            ValidOperator = true;
                        };
                    }else if (CurrentOperator.compare("++_") == 0 || CurrentOperator.compare("--_") == 0 || CurrentOperator.compare("_") == 0){
                        //Makes Sure Decrement & Increment Operators With Reduce Operator Are Valid For The End Position Of The User Input
                        if (CurrentOperatorRecordStartIndex - 1 >= 4 && UserInput[CurrentOperatorRecordStartIndex-1] == ')' && Index1+1 == UserInput.size()){
                            ValidOperator = true;
                        };
                    }else{
                        //Any Other Operators Are Valid As Long As They Are Not At The Edges Of The Input
                        if (CurrentOperatorRecordStartIndex != 0 && Index1+1 != UserInput.size()){
                            ValidOperator = true;
                        };
                    };
                    break;
                };
            };
            if (!ValidOperator){
                //If It Detected Any Invalid Operator, Invalidate The Entire Input
                ValidInput = false;
                break;
            }else{
                //Push Into The InputOperatorVector For Further Processing Later
                InputOperatorsVector.push_back(CurrentOperator);
            };
            CurrentOperator = "";
        };
    };
    //If ParenthesisStackCount Is Not Zero, There Is A Missing Pair For A Closing Or Opening Parenthesis, If That Is The Case Then Invalidate The Input
    if (ParenthesisStackCount != 0){
        return false;
    };
    //At This Point In The Validate Input Logic, As Long As It Is Still Valid, Further Validation Checks Must Still Occur
    if (ValidInput){
        //This For Loop Removes All Characters But The Following: 0 1 2 3 4 5 6 7 8 9 (<- These Are All Digits) | (<- This Represents The Fraction Divider) ~ (<- This Represents A Negative)
        std::vector<std::string> FractionsVector;
        std::string TempString;
        for (int Index = 0; Index < UserInput.size(); Index++){
            auto DelimiterSetIterator = DELIMITER_SET.find(UserInput[Index]);
            if (DelimiterSetIterator != DELIMITER_SET.end()){
                if (TempString.size() > 0){
                    //Push Into The FractionsVector To Record All Fraction Values In The Input For Further Processing Later
                    FractionsVector.push_back(TempString);
                    //This Vector Is Used To Record The Index Positions Of All Negative Symbols (~) In The TempString
                    std::vector<int> NegativeSymbolsIndexVector;
                    int NumOfNegativeSymbols = 0;
                    //For Loop To Record The Negative Symbols (~)
                    for (int Index2 = 0; Index2 < TempString.size(); Index2++){
                        if (TempString[Index2] == '~'){
                            NumOfNegativeSymbols++;
                            NegativeSymbolsIndexVector.push_back(Index2);
                        };
                    };
                    if (NumOfNegativeSymbols > 2){
                        //If NumOfNegativeSymbols Is Greater Than 2, Invalidate The Input, Fraction Values Can Only Have A Max Of 2 Negative Symbols (~), One In The Numerator And One In The Denominator
                        ValidInput = false;
                        break;
                    }else{
                        //This Loop Checks If The Positions Of The Negative Symbols (~) Are Not Positioned In The Correct Locations, If They Are Not, Invalidate The Input
                        for (int Index2 = 0; Index2 < NegativeSymbolsIndexVector.size(); Index2++){
                            //Invalidate The Input If The Current Negative Symbol (~) That Is Not At Index 0 Does Not Have A Fraction Divider To Its Left Side, Example: 1~|2 Is Invalid
                            if (NegativeSymbolsIndexVector[Index2] != 0 && NegativeSymbolsIndexVector[Index2] > 0 && TempString[NegativeSymbolsIndexVector[Index2]-1] != '|'){
                                ValidInput = false;
                                break;
                            };
                            //Invalidate The Input If The Current Negative Symbol (~) Is At Index 0 And The Character To Its Right Side Is Not A Digit, Example: ~~123|456 Is Invalid
                            if (NegativeSymbolsIndexVector[Index2] == 0 && NegativeSymbolsIndexVector[Index2]+1 < TempString.size() && !std::isdigit(TempString[NegativeSymbolsIndexVector[Index2]+1])){
                                ValidInput = false;
                                break;
                            };
                            //Invalidate The Input If The Current Negative Symbol (~) Is At The End Of The Temp String OR It Is In Between A Number On Its Left Side And The Fraction Divider On Its Right Side
                            if (NegativeSymbolsIndexVector[Index2] != 0 && NegativeSymbolsIndexVector[Index2]+1 == TempString.size() || NegativeSymbolsIndexVector[Index2] > 0 && NegativeSymbolsIndexVector[Index2]+1 < TempString.size() && !std::isdigit(TempString[NegativeSymbolsIndexVector[Index2]+1])){
                                ValidInput = false;
                                break;
                            };
                        };
                    };
                };
                //Set To Empty String To Record Next Fraction Values
                TempString = "";
            }else{
                //This Executes When No Delimiter Is Found And Continues To Build The TempString To Record All The Values Inside The Parenthesis That Represents The Fraction Values Example: --(~12345|~67890)++_ => TempString = ~12345|~67890
                TempString += UserInput[Index];
            };
        };
        //This For Loop Checks For The Number And Position Of The Fraction Divider Character (|)
        for (int Index1 = 0; Index1 < FractionsVector.size(); Index1++){
            int NumOfFractionDividers = 0;
            //If The Fraction Value Is Less Than 3 It Is Automatically An Invalid Fraction Value Since The Minimum Valid Fraction Value Has 2 Digits And 1 Fraction Divider, Example: 1|2 Is Valid, 1| Or |2 Or 12 Is Invalid
            if (FractionsVector[Index1].size() < 3){
                ValidInput = false;
            }else{
                for (int Index2 = 0; Index2 < FractionsVector[Index1].size(); Index2++){
                    //Loop Each Fraction Value To Count The Fraction Divider Quantity, If It Is Not In Between Digits Or The Quantity Is Over 1, Invalidate The Input
                    if (FractionsVector[Index1][Index2] == '|'){
                        NumOfFractionDividers++;
                        if (Index2-1 < 0 || Index2+1 >= FractionsVector[Index1].size() || NumOfFractionDividers > 1){
                            ValidInput = false;
                            break;
                        };
                    };
                };
                //If There Is Not At Least 1 Fraction Divider, Invalidate The Input
                if (NumOfFractionDividers == 0){
                    ValidInput = false;
                };
            };
            if (!ValidInput){
                //Break The Loop If Any Fraction Value Is Invalid
                break;
            }else{
                //Push Into The InputFractionsVector For Further Processing Later
                InputFractionsVector.push_back(FractionsVector[Index1]);
            };
        };
    };
    return ValidInput;
};
/*
Function Name: DisplayMenu3
Brief Description: Displays Menu 3 For The Options For Fraction Calculator X-TREME, Gets The User Input, Validates It Using The ValidateInput Function, If It Returns 0 It Exits The Menu, If It Returns A Valid Input It Evaluates It, Can Handle Out Of Range Errors When User Inputs A Number Larger Than The Int Data Type.
Return Value: Void
Incoming Parameters: None
Outgoing Parameters: None
*/
void DisplayMenu3(){
    //Display Menu 3 Options For The Input Based Fraction Calculator X-TREME
    std::cout << std::endl;
    for (int Index = 0; Index < MENU_OPTION_3_ARRAY_SIZE; Index++){
        std::cout << MENU_OPTION_3_ARRAY[Index] << std::endl;
    };
    bool ExitDisplayMenu3 = false;
    bool IsValidInput = false;
    int UserInputOption;
    std::string TempUserInput;
    std::vector<std::string> FractionsVector;
    std::vector<std::string> OperatorsVector;
    do{
        //Get User Input
        std::cout << "Enter Here: ";
        std::cin >> ws;
        std::getline(std::cin,TempUserInput);
        try{
            //Parse Int The Input String, If It Is Successful, Check If It Is 0, If It Is, Exit The Menu, If It Is Not, Display The Syntax Error & Clear The Vectors
            UserInputOption = std::stoi(TempUserInput);
            if (UserInputOption == 0){
                IsValidInput = true;
                ExitDisplayMenu3 = true;
            }else{
                std::cout << SYNTAX_ERROR << std::endl;
                FractionsVector.clear();
                OperatorsVector.clear();
            };
        }catch(const std::invalid_argument &INVALID_ARGUMENT_ERROR){
            //If Parse Int Fails Due Invalid Argument, Check If It Is A Valid Input To Evaluate The Fractions, If It Is Not, Display The Syntax Error
            IsValidInput = ValidateInput(TempUserInput,FractionsVector,OperatorsVector);
            if (!IsValidInput){
                std::cout << SYNTAX_ERROR << std::endl;
                FractionsVector.clear();
                OperatorsVector.clear();
            };
        }catch(const std::out_of_range &OUT_OF_RANGE_ERROR){
            //If Parse Int Fails Due To The Number Being Out Of Range For The Integer Data Type, Display The Syntax Error & Clear The Vectors
            std::cout << SYNTAX_ERROR << std::endl;
            FractionsVector.clear();
            OperatorsVector.clear();
        };
    }while (!IsValidInput);
    if (!ExitDisplayMenu3){
        //Reverse The Vectors To Pop The Left Side Fraction Values & Left Side Operators First.
        std::reverse(FractionsVector.begin(),FractionsVector.end());
        std::reverse(OperatorsVector.begin(),OperatorsVector.end());
        std::vector<std::string> OuputFractionsVector;
        if (OperatorsVector.size() > 0){
            //The FirstIteration & SkipFirstIteration Is Used To Check Which Vector To Pop/Evaluate First If The Input Starts With An Operator Or With A Fraction, Example: --(1|2) OR (1|2)++
            bool FirstIteration = true;
            bool SkipFirstIteration = (TempUserInput[0] == '(' ? true : false);
            bool IsTempFractionInitialized = false;
            Fraction TempFraction = Fraction();
            //Continue To Loop While One Of The Vectors Still Has A Fraction Or Operator To Be Evaluated
            while (!FractionsVector.empty() || !OperatorsVector.empty()){
                std::string OperationString;
                Fraction CurrentTempFraction = Fraction();
                bool SpecialOutput = false, Increment = false, Decrement = false, Add = false, Subtract = false, Multiply = false, Divide = false, Equals = false, Exact = false, NotEquals = false, GreaterThan = false, LessThan = false, GreaterThanOrEqualTo = false, LessThanOrEqualTo = false;
                if (!OperatorsVector.empty() && FirstIteration && !SkipFirstIteration || !OperatorsVector.empty() && !FirstIteration){
                    //Hold The Operation In A String & Dequeue It From The Operators Vector, Then Check Its Value To Change The Corresponding Boolean To True Or Execute The Operation On The Spot, Set The OperationString To Be Outputted Later
                    std::string OperatorsVectorDequeue = OperatorsVector.back();
                    OperatorsVector.pop_back();
                    if (OperatorsVectorDequeue.compare("++") == 0){
                        Increment = true;
                    }else if (OperatorsVectorDequeue.compare("--") == 0){
                        Decrement = true;
                    }else if (OperatorsVectorDequeue.compare("_") == 0){
                        TempFraction.reduce();
                        OperationString = "Reduce: ";
                    }else if (OperatorsVectorDequeue.compare("++_") == 0){
                        TempFraction++;
                        TempFraction.reduce();
                        OperationString = "Postfix Increment & Reduce: ";
                    }else if (OperatorsVectorDequeue.compare("--_") == 0){
                        TempFraction--;
                        TempFraction.reduce();
                        OperationString = "Postfix Decrement & Reduce: ";
                    }else if (OperatorsVectorDequeue.compare("+") == 0){
                        Add = true;
                        OperationString = "Add: ";
                    }else if (OperatorsVectorDequeue.compare("-") == 0){
                        Subtract = true;
                        OperationString = "Subtract: ";
                    }else if (OperatorsVectorDequeue.compare("*") == 0){
                        Multiply = true;
                        OperationString = "Multiply: ";
                    }else if (OperatorsVectorDequeue.compare("/") == 0){
                        Divide = true;
                        OperationString = "Divide: ";
                    }else if (OperatorsVectorDequeue.compare("==") == 0){
                        Equals = true;
                        OperationString = "Equals: ";
                    }else if (OperatorsVectorDequeue.compare("===") == 0){
                        Exact = true;
                        OperationString = "Exact: ";
                    }else if (OperatorsVectorDequeue.compare("!=") == 0){
                        NotEquals = true;
                        OperationString = "Not Equals: ";
                    }else if (OperatorsVectorDequeue.compare(">") == 0){
                        GreaterThan = true;
                        OperationString = "Greater Than : ";
                    }else if (OperatorsVectorDequeue.compare("<") == 0){
                        LessThan = true;
                        OperationString = "Less Than : ";
                    }else if (OperatorsVectorDequeue.compare(">=") == 0){
                        GreaterThanOrEqualTo = true;
                        OperationString = "Greater Than Or Equal To : ";
                    }else if (OperatorsVectorDequeue.compare("<=") == 0){
                        LessThanOrEqualTo = true;
                        OperationString = "Less Than Or Equal To: ";
                    };
                };
                if (!FractionsVector.empty()){
                    //Checks If The Fractions Vector Has Fraction Values Inside It Then Dequeues It, Records The Numerator & Denominator Values In A String To Be Used To Update The TempFraction Or CurrentTempFraction Numerator & Denominator Values
                    std::string FractionsVectorDequeue = FractionsVector.back();
                    FractionsVector.pop_back();
                    bool SwitchToDenominator = false;
                    std::string Numerator, Denominator;
                    for (int Index = 0; Index < FractionsVectorDequeue.size(); Index++){
                        if (FractionsVectorDequeue[Index] == '|'){
                            SwitchToDenominator = true;
                        }else{
                            if (SwitchToDenominator){
                                Denominator += FractionsVectorDequeue[Index];
                            }else{
                                Numerator += FractionsVectorDequeue[Index];
                            };
                        };
                    };
                    if (!IsTempFractionInitialized){
                        //If TempFraction Has NOT Been Initialized It Will Run The First Branch And Set The Numerator & Denominator Values, The Try/Catch Checks If The User Inputs A Value Too Large To Be Parse Int For The Integer Data Type And Thus Uses A Long Double To Parse It And Checks If Is A Negative Or Positive Value And Sets To The Corresponding Largest Or Smallest Integer Value
                        try{
                            int NewNumerator = (Numerator[0] == '~' ? -std::stoi(Numerator.substr(1)): std::stoi(Numerator));
                            TempFraction.SetNum(NewNumerator);
                        }catch (const std::out_of_range &OUT_OF_RANGE_ERROR){
                            long double NewNumerator = (Numerator[0] == '~' ? -std::stold(Numerator.substr(1)) : std::stold(Numerator));
                            TempFraction.SetNum((NewNumerator > 0 ? LARGEST_INTEGER : SMALLEST_INTEGER));
                            std::cout << "[SYSTEM ERROR]: Numerator Out Of Range For Integers! Setting Numerator To:" << TempFraction.GetNum() << std::endl;
                        };
                        try{
                            int NewDenominator = (Denominator[0] == '~' ? -std::stoi(Denominator.substr(1)) : std::stoi(Denominator));
                            TempFraction.SetDen(NewDenominator);
                        }catch (const std::out_of_range &OUT_OF_RANGE_ERROR){
                            long double NewDenominator = (Denominator[0] == '~' ? -std::stold(Denominator.substr(1)) : std::stold(Denominator));
                            TempFraction.SetDen((NewDenominator > 0 ? LARGEST_INTEGER : SMALLEST_INTEGER));
                            std::cout << "[SYSTEM ERROR]: Denominator Out Of Range For Integers! Setting Denominator To: " << TempFraction.GetDen() << std::endl;
                        };
                        IsTempFractionInitialized = true;
                    }else{
                        //If TempFraction Has Been Initialized It Will Run The Second Branch And Set The Numerator & Denominator Values, The Try/Catch Checks If The User Inputs A Value Too Large To Be Parse Int For The Integer Data Type And Thus Uses A Long Double To Parse It And Checks If Is A Negative Or Positive Value And Sets To The Corresponding Largest Or Smallest Integer Value
                        try{
                            int NewNumerator = (Numerator[0] == '~' ? -std::stoi(Numerator.substr(1)): std::stoi(Numerator));
                            CurrentTempFraction.SetNum(NewNumerator);
                        }catch (const std::out_of_range &OUT_OF_RANGE_ERROR){
                            long double NewNumerator = (Numerator[0] == '~' ? -std::stold(Numerator.substr(1)) : std::stold(Numerator));
                            CurrentTempFraction.SetNum((NewNumerator > 0 ? LARGEST_INTEGER : SMALLEST_INTEGER));
                            std::cout << "[SYSTEM ERROR]: Numerator Out Of Range For Integers! Setting Numerator To:" << CurrentTempFraction.GetNum() << std::endl;
                        };
                        try{
                            int NewDenominator = (Denominator[0] == '~' ? -std::stoi(Denominator.substr(1)) : std::stoi(Denominator));
                            CurrentTempFraction.SetDen(NewDenominator);
                        }catch (const std::out_of_range &OUT_OF_RANGE_ERROR){
                            long double NewDenominator = (Denominator[0] == '~' ? -std::stold(Denominator.substr(1)) : std::stold(Denominator));
                            CurrentTempFraction.SetDen((NewDenominator > 0 ? LARGEST_INTEGER : SMALLEST_INTEGER));
                            std::cout << "[SYSTEM ERROR]: Denominator Out Of Range For Integers! Setting Denominator To: " << CurrentTempFraction.GetDen() << std::endl;
                        };
                    };
                    //A Bunch Of Small If Statements To Execute The Appropriate Operation
                    if (Increment){
                        ++TempFraction;
                        OperationString = "Prefix Increment: ";
                    };
                    if (Decrement){
                        --TempFraction;
                        OperationString = "Prefix Decrement: ";
                    };
                    if (Add){
                        TempFraction = TempFraction + CurrentTempFraction;
                    };
                    if (Subtract){
                        TempFraction = TempFraction - CurrentTempFraction;
                    };
                    if (Multiply){
                        TempFraction = TempFraction * CurrentTempFraction;
                    };
                    if (Divide){
                        TempFraction = TempFraction / CurrentTempFraction;
                    };
                    if (Equals){
                        SpecialOutput = true;
                        OuputFractionsVector.push_back(OperationString+(TempFraction == CurrentTempFraction ? "True" : "False"));
                        TempFraction = CurrentTempFraction;
                    };
                    if (Exact){
                        SpecialOutput = true;
                        OuputFractionsVector.push_back(OperationString+(isExact(TempFraction,CurrentTempFraction) ? "True" : "False"));
                        TempFraction = CurrentTempFraction;
                    };
                    if (NotEquals){
                        SpecialOutput = true;
                        OuputFractionsVector.push_back(OperationString+(TempFraction != CurrentTempFraction ? "True" : "False"));
                        TempFraction = CurrentTempFraction;
                    };
                    if (GreaterThan){
                        SpecialOutput = true;
                        OuputFractionsVector.push_back(OperationString+(TempFraction > CurrentTempFraction ? "True" : "False"));
                        TempFraction = CurrentTempFraction;
                    };
                    if (LessThan){
                        SpecialOutput = true;
                        OuputFractionsVector.push_back(OperationString+(TempFraction < CurrentTempFraction ? "True" : "False"));
                        TempFraction = CurrentTempFraction;
                    };
                    if (GreaterThanOrEqualTo){
                        SpecialOutput = true;
                        OuputFractionsVector.push_back(OperationString+(TempFraction >= CurrentTempFraction ? "True" : "False"));
                        TempFraction = CurrentTempFraction;
                    };
                    if (LessThanOrEqualTo){
                        SpecialOutput = true;
                        OuputFractionsVector.push_back(OperationString+(TempFraction <= CurrentTempFraction ? "True" : "False"));
                        TempFraction = CurrentTempFraction;
                    };
                }else{
                    //These Two If Statements Are Used For the Postfix Increment & Decrement Operations
                    if (Increment){
                        TempFraction++;
                        OperationString = "Postfix Increment: ";
                    };
                    if (Decrement){
                        TempFraction--;
                        OperationString = "Postfix Decrement: ";
                    };
                };
                if (!SpecialOutput && OperationString.size() > 0){
                    //This Pushes The OperationString Concatenated With The Numerator & Denominator Values To The OutputFractionsVector To Be Printed Out Later
                    OuputFractionsVector.push_back(OperationString+std::to_string(TempFraction.GetNum())+"/"+std::to_string(TempFraction.GetDen()));
                };
                FirstIteration = false;
            };
        }else if (OperatorsVector.size() == 0 && FractionsVector.size() == 1){
            //This Branch Only Runs If There Is No Operations To Execute And Will Only Print Out The Fraction Value Itself, Example: (1|2)
            bool SwitchToDenominator = false;
            //Sets The Numerator & Denominator
            std::string Numerator, Denominator;
            for (int Index = 0; Index < FractionsVector[0].size(); Index++){
                if (FractionsVector[0][Index] == '|'){
                    SwitchToDenominator = true;
                }else{
                    if (SwitchToDenominator){
                        Denominator += FractionsVector[0][Index];
                    }else{
                        Numerator += FractionsVector[0][Index];
                    };
                };
            };
            //Initializes A TempFraction
            Fraction TempFraction = Fraction();
            //Sets The Numerator & Denominator Of The TempFraction, If The User Inputs A Value To Large For The Integer Data Type, It Parses It As A Long Double To Check If It Is A Negative Or Position And Sets The Value With The Corresponding Largest Or Smallest Integer Value
            try{
                int NewNumerator = (Numerator[0] == '~' ? -std::stoi(Numerator.substr(1)): std::stoi(Numerator));
                TempFraction.SetNum(NewNumerator);
            }catch (const std::out_of_range &OUT_OF_RANGE_ERROR){
                long double NewNumerator = (Numerator[0] == '~' ? -std::stold(Numerator.substr(1)) : std::stold(Numerator));
                TempFraction.SetNum((NewNumerator > 0 ? LARGEST_INTEGER : SMALLEST_INTEGER));
                std::cout << "[SYSTEM ERROR]: Numerator Out Of Range For Integers! Setting Numerator To:" << TempFraction.GetNum() << std::endl;
            };
            try{
                int NewDenominator = (Denominator[0] == '~' ? -std::stoi(Denominator.substr(1)) : std::stoi(Denominator));
                TempFraction.SetDen(NewDenominator);
            }catch (const std::out_of_range &OUT_OF_RANGE_ERROR){
                long double NewDenominator = (Denominator[0] == '~' ? -std::stold(Denominator.substr(1)) : std::stold(Denominator));
                TempFraction.SetDen((NewDenominator > 0 ? LARGEST_INTEGER : SMALLEST_INTEGER));
                std::cout << "[SYSTEM ERROR]: Denominator Out Of Range For Integers! Setting Denominator To: " << TempFraction.GetDen() << std::endl;
            };
            //This Pushes The OperationString Concatenated With The Numerator & Denominator Values To The OutputFractionsVector To Be Printed Out Later
            OuputFractionsVector.push_back("Fraction: "+std::to_string(TempFraction.GetNum())+"/"+std::to_string(TempFraction.GetDen()));
        };
        //Prints The Items Inside The OutputFractionsVector To Be Displayed On The Screen
        for (int Index = 0; Index < OuputFractionsVector.size(); Index++){
            std::cout << "[SYSTEM OUTPUT]: " << OuputFractionsVector[Index] << std::endl;
        };
        DisplayMenu3();
    }else{
        std::cout << "[SYSTEM MESSAGE] Exited Display Menu 3 Successfully!" << std::endl;
    };
};
