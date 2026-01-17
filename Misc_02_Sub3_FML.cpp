/*
Student Name: Christian Tampus
File Name: Misc_02_Sub3_FML.cpp
Description: Miscellaneous Assignment 2: Parallel Arrays And Structs
Course Number: CS 255
Section Number: 02 (Tuesday/Thursday)
Due Date: 9/3
*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
struct PlayerDataStruct{
    std::string PlayerName;
    std::string PlayerId;
    int PlayerLevel;
    double PlayerExp;
    bool PlayerIsInGuild;
    PlayerDataStruct() : PlayerName(""), PlayerId(""), PlayerLevel(0), PlayerExp(0), PlayerIsInGuild(false) {};
    PlayerDataStruct(std::string InitPlayerName, std::string InitPlayerId, int InitPlayerLevel, double InitPlayerExp, bool InitPlayerIsInGuild) : PlayerName(InitPlayerName), PlayerId(InitPlayerId), PlayerLevel(InitPlayerLevel), PlayerExp(InitPlayerExp), PlayerIsInGuild(InitPlayerIsInGuild) {};
};
const std::string TXT_SUFFIX = ".txt";
const int PLAYER_DATA_COUNT = 5;
const std::string MENU_ARRAY[4] = {"[1] Print Array","[2] Fill Array","[3] Sort Array By Level","[0] Quit Program"};
const std::string INVALID_INPUT_MESSAGE = "[SYSTEM MESSAGE] You Entered An Invalid Input Try Again!";
void DisplayMenu(std::ifstream &InputFile, PlayerDataStruct PlayerDataStructArray[],int ArraySize, bool &IsStructArrayFilled);
void FillArrays(std::ifstream &InputFile, PlayerDataStruct PlayerDataStructArray[], bool &IsArraysFilled);
void PrintArrays(PlayerDataStruct PlayerDataStructArray[], int ArraySize);
std::vector<PlayerDataStruct> Merger(std::vector<PlayerDataStruct> LeftInputVector, std::vector<PlayerDataStruct> RightInputVector);
std::vector<PlayerDataStruct> Splitter(std::vector<PlayerDataStruct> InputVector);
void SortArrays(PlayerDataStruct PlayerDataStructArray[], int ArraySize);
/*
Function Name: main
Function Description: Driver Function, First Gets File Input From User And Sees If It Exists, If It Does, It Opens It, Searches The Array For The Number Of Lines & Divides By PLAYER_DATA_COUNT To Get The Player Data Quantity, Initializes PlayerDataStructArray Then Calls The DisplayMenu.
Return Value: Integer
Incoming Parameters: None
Outgoing Parameters: None
*/
int main(){
    std::cout << "[PROGRAM] Misc_02_Sub3_FML.cpp" << std::endl;
    std::string UserInputFileName, Temp;
    int FileLines = 0, PlayerCount = 0;
    std::ifstream InputFile;
    bool IsStructArrayFilled = false;
    do{
        std::cout << "Please Enter File To Read (Default: input.txt, Enter 'd' For Default W/O Quotes):";
        std::cin >> std::ws;
        std::getline(std::cin,UserInputFileName);
        if (UserInputFileName == "d"){
            UserInputFileName = "input.txt";
        }else if (UserInputFileName.size() <= TXT_SUFFIX.size() || UserInputFileName.size() > TXT_SUFFIX.size() && UserInputFileName.compare(UserInputFileName.size()-TXT_SUFFIX.size(),TXT_SUFFIX.size(),TXT_SUFFIX) != 0){
            UserInputFileName+=TXT_SUFFIX;
        };
        std::cout << "Input File Name You Entered: " + UserInputFileName << std::endl;
        InputFile.open(UserInputFileName);
        std::cout << (InputFile.fail() ? "File Name: "+UserInputFileName+" Does Not Exist!" : "File Name: "+UserInputFileName+" Successfully Opened!") << std::endl;
    }while(InputFile.fail() && !InputFile.is_open());
    while(!InputFile.eof()){
        std::getline(InputFile,Temp);
        FileLines++;
    };
    PlayerCount = FileLines/PLAYER_DATA_COUNT;
    PlayerDataStruct PlayerDataStructArray[PlayerCount];
    DisplayMenu(InputFile,PlayerDataStructArray,PlayerCount,IsStructArrayFilled);
    return 0;
}
/*
Function Name: DisplayMenu
Function Description: Displays The Menu Options
Return Value: Void
Incoming Parameters: InputFile (File), PlayerDataStructArray (PlayerDataStruct), ArraySize (Integer), IsStructArrayFilled (Boolean)
Outgoing Parameters: InputFile (File), PlayerDataStructArray (PlayerDataStruct), IsStructArrayFilled (Boolean)
*/
void DisplayMenu(std::ifstream &InputFile, PlayerDataStruct PlayerDataStructArray[],int ArraySize, bool &IsStructArrayFilled){
    std::cout << "Menu Options" << std::endl;
    for (int Index = 0; Index < sizeof(MENU_ARRAY)/sizeof(std::string); Index++){
        std::cout << MENU_ARRAY[Index] << std::endl;
    };
    std::string TempUserInputMenuOption;
    int MenuOptionToInteger = -1;
    do{
        std::cout << "Please Enter Option:";
        std::cin >> std::ws;
        std::getline(std::cin,TempUserInputMenuOption);
        try{
            MenuOptionToInteger = std::stoi(TempUserInputMenuOption);
            if (MenuOptionToInteger < 0 || MenuOptionToInteger > sizeof(MENU_ARRAY)/sizeof(std::string) - 1){
                std::cout << INVALID_INPUT_MESSAGE << std::endl;
            };
        }catch(const std::invalid_argument &INVALID_ARGUMENT_ERROR){
            MenuOptionToInteger = -1;
            std::cout << INVALID_INPUT_MESSAGE << std::endl;
        }catch(const std::out_of_range &OUT_OF_RANGE_ERROR){
            MenuOptionToInteger = -1;
            std::cout << INVALID_INPUT_MESSAGE << std::endl;
        };
        if (!IsStructArrayFilled && MenuOptionToInteger == 1 || !IsStructArrayFilled && MenuOptionToInteger == 3){
            std::cout << "[SYSTEM ERROR] Cannot Do This Operation Until `[2] Fill Array` Has Been Executed!" << std::endl;
            MenuOptionToInteger = -1;
        };
    }while(MenuOptionToInteger < 0 || MenuOptionToInteger > sizeof(MENU_ARRAY)/sizeof(std::string) - 1);
    switch(MenuOptionToInteger){
        case 1:
            PrintArrays(PlayerDataStructArray,ArraySize);
            DisplayMenu(InputFile,PlayerDataStructArray,ArraySize,IsStructArrayFilled);
            break;
        case 2:
            FillArrays(InputFile,PlayerDataStructArray,IsStructArrayFilled);
            DisplayMenu(InputFile,PlayerDataStructArray,ArraySize,IsStructArrayFilled);
            break;
        case 3:
            SortArrays(PlayerDataStructArray,ArraySize);
            DisplayMenu(InputFile,PlayerDataStructArray,ArraySize,IsStructArrayFilled);
            break;
        default:
            std::cout << "[SYSTEM MESSAGE] Program Terminated..." << std::endl;
            break;
    };
};
/*
Function Name: FillArrays
Function Description: Fills PlayerDataStructArray With Input File Values
Return Value: Void
Incoming Parameters: InputFile (File), PlayerDataStructArray (PlayerDataStruct), IsArraysFilled (Boolean)
Outgoing Parameters: InputFile (File), PlayerDataStructArray (PlayerDataStruct), IsArraysFilled (Boolean)
*/
void FillArrays(std::ifstream &InputFile, PlayerDataStruct PlayerDataStructArray[], bool &IsArraysFilled){
    InputFile.clear();
    InputFile.seekg(0,std::ios::beg);
    std::string Temp;
    int PositionData = 1, PositionIndex = 0;
    std::string TempName, TempId;
    int TempLevel, TempExp;
    bool TempGuild;
    while (!InputFile.eof()){
        switch(PositionData){
            case 1:
                std::getline(InputFile,TempName);
                break;
            case 2:
                std::getline(InputFile,TempId);
                break;
            case 3:
                std::getline(InputFile,Temp);
                TempLevel = std::stoi(Temp);
                break;
            case 4:
                std::getline(InputFile,Temp);
                TempExp = std::stod(Temp);
                break;
            case 5:
                std::getline(InputFile,Temp);
                TempGuild = (Temp.compare("true") == 0 ? true : false);
                break;
        };
        PositionData++;
        if (PositionData > 5){
            PlayerDataStructArray[PositionIndex] = PlayerDataStruct(TempName,TempId,TempLevel,TempExp,TempGuild);
            PositionData = 1;
            PositionIndex++;
        };
    };
    IsArraysFilled = true;
    std::cout << "[SYSTEM MESSAGE] Successfully Filled Arrays!" << std::endl;
};
/*
Function Name: PrintArrays
Function Description: Prints PlayerDataStructArray Contents
Return Value: Void
Incoming Parameters: PlayerDataStructArray (PlayerDataStruct), ArraySize (Integer)
Outgoing Parameters: PlayerDataStructArray (PlayerDataStruct)
*/
void PrintArrays(PlayerDataStruct PlayerDataStructArray[], int ArraySize){
    std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
    for (int Index = 0; Index < ArraySize; Index++){
        std::cout << "Player ["+std::to_string(Index)+"] Name: "+PlayerDataStructArray[Index].PlayerName+" Id: "+PlayerDataStructArray[Index].PlayerId+" Level: "+std::to_string(PlayerDataStructArray[Index].PlayerLevel)+" Exp: " << std::fixed << std::setprecision(2) << PlayerDataStructArray[Index].PlayerExp << " Is In A Guild: " << (PlayerDataStructArray[Index].PlayerIsInGuild ? "True" : "False") << std::endl;
    };
    std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "[SYSTEM MESSAGE] Successfully Printed Arrays!" << std::endl;
};
/*
Function Name: Merger
Function Description: Merger Section Of The Merge Sort Algorithm, Appends Values That Are Greatest Then To Least, Once The First While Loop Is Completed, Any Remaining Items Not Added Starting From The Left Vector Array Then To The Right Gets Appended Into The MergedVector Array Then Returned
Return Value: std::vector<PlayerDataStruct> (Vector Array)
Incoming Parameters: LeftInputVector (Vector Array), RightInputVector (Vector Array)
Outgoing Parameters: MergedVector (Vector Array)
*/
std::vector<PlayerDataStruct> Merger(std::vector<PlayerDataStruct> LeftInputVector, std::vector<PlayerDataStruct> RightInputVector){
    std::vector<PlayerDataStruct> MergedVector(LeftInputVector.size()+RightInputVector.size());
    int MergedVectorIndex = 0, LeftVectorIndex = 0, RightVectorIndex = 0;
    while(LeftVectorIndex < LeftInputVector.size() && RightVectorIndex < RightInputVector.size()){
        if (LeftInputVector[LeftVectorIndex].PlayerLevel > RightInputVector[RightVectorIndex].PlayerLevel){
            MergedVector[MergedVectorIndex] = LeftInputVector[LeftVectorIndex];
            LeftVectorIndex++;
        }else{
            MergedVector[MergedVectorIndex] = RightInputVector[RightVectorIndex];
            RightVectorIndex++;
        };
        MergedVectorIndex++;
    };
    while (LeftVectorIndex < LeftInputVector.size()){
        MergedVector[MergedVectorIndex] = LeftInputVector[LeftVectorIndex];
        LeftVectorIndex++;
        MergedVectorIndex++;
    };
    while (RightVectorIndex < RightInputVector.size()){
        MergedVector[MergedVectorIndex] = RightInputVector[RightVectorIndex];
        RightVectorIndex++;
        MergedVectorIndex++;
    };
    return MergedVector;
};
/*
Function Name: Splitter
Function Description: Splitter Section Of The Merge Sort Algorithm, It First Recursively Splits The Left Array Until The Base Case Is Met At A Length Of 1 Then Returns It, Then Recursively Splits The Right Array, Then Merges Both Arrays By Calling The Merger Function "Hence Divide & Conquer".
Return Value: std::vector<PlayerDataStruct> (Vector Array)
Incoming Parameters: LeftInputVector (Vector Array), RightInputVector (Vector Array)
Outgoing Parameters: MergedVector (Vector Array)
*/
std::vector<PlayerDataStruct> Splitter(std::vector<PlayerDataStruct> InputVector){
    if (InputVector.size() <= 1){
        return InputVector;
    };
    int MiddleIndex = InputVector.size()/2;
    std::vector<PlayerDataStruct> LeftInputVector(InputVector.begin(),InputVector.begin()+MiddleIndex);
    std::vector<PlayerDataStruct> RightInputVector(InputVector.begin()+MiddleIndex,InputVector.end());
    return Merger(Splitter(LeftInputVector),Splitter(RightInputVector));
};
/*
Function Name: SortArrays
Function Description: Initializes A Vector Of The PlayerDataStructArray Struct Values To Be Sorted By Player Level By The Merge Sort Algorithm (Splitter & Merger Functions). Afterwards Overwrites The PlayerDataStructArray Values With The Sorted Vector Struct Values
Return Value: Void
Incoming Parameters: PlayerDataStructArray (PlayerDataStruct), ArraySize (Integer)
Outgoing Parameters: PlayerDataStructArray (PlayerDataStruct)
*/
void SortArrays(PlayerDataStruct PlayerDataStructArray[], int ArraySize){
    std::vector<PlayerDataStruct> PlayerDataStructVector(ArraySize);
    for (int Index = 0; Index < ArraySize; Index++){
        PlayerDataStructVector[Index] = PlayerDataStruct(PlayerDataStructArray[Index].PlayerName,PlayerDataStructArray[Index].PlayerId,PlayerDataStructArray[Index].PlayerLevel,PlayerDataStructArray[Index].PlayerExp,PlayerDataStructArray[Index].PlayerIsInGuild);
    };
    PlayerDataStructVector = Splitter(PlayerDataStructVector);
    for (int Index = 0; Index < ArraySize; Index++){
        PlayerDataStructArray[Index] = PlayerDataStructVector[Index];
    };
    std::cout << "[SYSTEM MESSAGE] Successfully Sorted Arrays!" << std::endl;
};
