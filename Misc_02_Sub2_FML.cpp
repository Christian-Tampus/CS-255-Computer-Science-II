/*
Student Name: Christian Tampus
File Name: Misc_02_Sub2_FML.cpp
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
#include <unordered_map>
const std::string TXT_SUFFIX = ".txt";
const int PLAYER_DATA_COUNT = 5;
const std::string MENU_ARRAY[4] = {"[1] Print Array","[2] Fill Array","[3] Sort Array By Level","[0] Quit Program"};
const std::string INVALID_INPUT_MESSAGE = "[SYSTEM MESSAGE] You Entered An Invalid Input Try Again!";
void DisplayMenu(std::ifstream &InputFile, std::string PlayerNameArray[], std::string PlayerIdArray[], int PlayerLevelArray[], double PlayerExpArray[], bool PlayerIsInGuildArray[], int ArraySize, bool &IsArraysFilled);
void FillArrays(std::ifstream &InputFile, std::string PlayerNameArray[], std::string PlayerIdArray[], int PlayerLevelArray[], double PlayerExpArray[], bool PlayerIsInGuildArray[], bool &IsArraysFilled);
void PrintArrays(std::string PlayerNameArray[], std::string PlayerIdArray[], int PlayerLevelArray[], double PlayerExpArray[], bool PlayerIsInGuildArray[], int ArraySize);
std::vector<std::vector<int>> Merger(std::vector<std::vector<int>> LeftInputVector, std::vector<std::vector<int>> RightInputVector);
std::vector<std::vector<int>> Splitter(std::vector<std::vector<int>> InputVector);
void SortArrays(std::string PlayerNameArray[], std::string PlayerIdArray[], int PlayerLevelArray[], double PlayerExpArray[], bool PlayerIsInGuildArray[], int ArraySize);
struct PlayerDataStruct{
    std::string PlayerName;
    std::string PlayerId;
    int PlayerLevel;
    double PlayerExp;
    bool PlayerIsInGuild;
};
/*
Function Name: main
Function Description: Driver Function, First Gets File Input From User And Sees If It Exists, If It Does, It Opens It, Searches The Array For The Number Of Lines & Divides By PLAYER_DATA_COUNT To Get The Player Data Quantity, Initializes The Arrays Then Calls The DisplayMenu.
Return Value: Integer
Incoming Parameters: None
Outgoing Parameters: None
*/
int main(){
    std::cout << "[PROGRAM] Misc_02_Sub2_FML.cpp" << std::endl;
    std::string UserInputFileName, Temp;
    int FileLines = 0, PlayerCount = 0;
    std::ifstream InputFile;
    bool IsArraysFilled = false;
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
    std::string PlayerNameArray[PlayerCount];
    std::string PlayerIdArray[PlayerCount];
    int PlayerLevelArray[PlayerCount];
    double PlayerExpArray[PlayerCount];
    bool PlayerIsInGuildArray[PlayerCount];
    DisplayMenu(InputFile,PlayerNameArray,PlayerIdArray,PlayerLevelArray,PlayerExpArray,PlayerIsInGuildArray,PlayerCount,IsArraysFilled);
    return 0;
}
/*
Function Name: DisplayMenu
Function Description: Displays The Menu Options
Return Value: Void
Incoming Parameters: InputFile (File), PlayerNameArray (String Array), PlayerIdArray (String Array), PlayerLevelArray (Integer Array), PlayerExpArray (Double Array), PlayerIsInGuildArray (Boolean Array), ArraySize (Integer), IsArraysFilled (Boolean)
Outgoing Parameters: InputFile (File), PlayerNameArray (String Array), PlayerIdArray (String Array), PlayerLevelArray (Integer Array), PlayerExpArray (Double Array), PlayerIsInGuildArray (Boolean Array), IsArraysFilled (Boolean)
*/
void DisplayMenu(std::ifstream &InputFile, std::string PlayerNameArray[], std::string PlayerIdArray[], int PlayerLevelArray[], double PlayerExpArray[], bool PlayerIsInGuildArray[], int ArraySize, bool &IsArraysFilled){
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
        if (!IsArraysFilled && MenuOptionToInteger == 1 || !IsArraysFilled && MenuOptionToInteger == 3){
            std::cout << "[SYSTEM ERROR] Cannot Do This Operation Until `[2] Fill Array` Has Been Executed!" << std::endl;
            MenuOptionToInteger = -1;
        };
    }while(MenuOptionToInteger < 0 || MenuOptionToInteger > sizeof(MENU_ARRAY)/sizeof(std::string) - 1);
    switch(MenuOptionToInteger){
        case 1:
            PrintArrays(PlayerNameArray,PlayerIdArray,PlayerLevelArray,PlayerExpArray,PlayerIsInGuildArray,ArraySize);
            DisplayMenu(InputFile,PlayerNameArray,PlayerIdArray,PlayerLevelArray,PlayerExpArray,PlayerIsInGuildArray,ArraySize,IsArraysFilled);
            break;
        case 2:
            FillArrays(InputFile,PlayerNameArray,PlayerIdArray,PlayerLevelArray,PlayerExpArray,PlayerIsInGuildArray,IsArraysFilled);
            DisplayMenu(InputFile,PlayerNameArray,PlayerIdArray,PlayerLevelArray,PlayerExpArray,PlayerIsInGuildArray,ArraySize,IsArraysFilled);
            break;
        case 3:
            SortArrays(PlayerNameArray,PlayerIdArray,PlayerLevelArray,PlayerExpArray,PlayerIsInGuildArray,ArraySize);
            DisplayMenu(InputFile,PlayerNameArray,PlayerIdArray,PlayerLevelArray,PlayerExpArray,PlayerIsInGuildArray,ArraySize,IsArraysFilled);
            break;
        default:
            std::cout << "[SYSTEM MESSAGE] Program Terminated..." << std::endl;
            break;
    };
};
/*
Function Name: FillArrays
Function Description: Fills Arrays With Input File Values
Return Value: Void
Incoming Parameters: InputFile (File), PlayerNameArray (String Array), PlayerIdArray (String Array), PlayerLevelArray (Integer Array), PlayerExpArray (Double Array), PlayerIsInGuildArray (Boolean Array), IsArraysFilled (Boolean)
Outgoing Parameters: InputFile (File), PlayerNameArray (String Array), PlayerIdArray (String Array), PlayerLevelArray (Integer Array), PlayerExpArray (Double Array), PlayerIsInGuildArray (Boolean Array), IsArraysFilled (Boolean)
*/
void FillArrays(std::ifstream &InputFile, std::string PlayerNameArray[], std::string PlayerIdArray[], int PlayerLevelArray[], double PlayerExpArray[], bool PlayerIsInGuildArray[], bool &IsArraysFilled){
    InputFile.clear();
    InputFile.seekg(0,std::ios::beg);
    std::string Temp;
    int PositionData = 1, PositionIndex = 0;
    while (!InputFile.eof()){
        switch(PositionData){
            case 1:
                std::getline(InputFile,PlayerNameArray[PositionIndex]);
                break;
            case 2:
                std::getline(InputFile,PlayerIdArray[PositionIndex]);
                break;
            case 3:
                std::getline(InputFile,Temp);
                PlayerLevelArray[PositionIndex] = std::stoi(Temp);
                break;
            case 4:
                std::getline(InputFile,Temp);
                PlayerExpArray[PositionIndex] = std::stod(Temp);
                break;
            case 5:
                std::getline(InputFile,Temp);
                PlayerIsInGuildArray[PositionIndex] = (Temp.compare("true") == 0 ? true : false);
                break;
        };
        PositionData++;
        if (PositionData > 5){
            PositionData = 1;
            PositionIndex++;
        };
    };
    IsArraysFilled = true;
    std::cout << "[SYSTEM MESSAGE] Successfully Filled Arrays!" << std::endl;
};
/*
Function Name: PrintArrays
Function Description: Prints Array Contents
Return Value: Void
Incoming Parameters:PlayerNameArray (String Array), PlayerIdArray (String Array), PlayerLevelArray (Integer Array), PlayerExpArray (Double Array), PlayerIsInGuildArray (Boolean Array), ArraySize (Integer)
Outgoing Parameters:PlayerNameArray (String Array), PlayerIdArray (String Array), PlayerLevelArray (Integer Array), PlayerExpArray (Double Array), PlayerIsInGuildArray (Boolean Array)
*/
void PrintArrays(std::string PlayerNameArray[], std::string PlayerIdArray[], int PlayerLevelArray[], double PlayerExpArray[], bool PlayerIsInGuildArray[], int ArraySize){
    std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
    for (int Index = 0; Index < ArraySize; Index++){
        std::cout << "Player ["+std::to_string(Index)+"] Name: "+PlayerNameArray[Index]+" Id: "+PlayerIdArray[Index]+" Level: "+std::to_string(PlayerLevelArray[Index])+" Exp: " << std::fixed << std::setprecision(2) << PlayerExpArray[Index] << " Is In A Guild: " << (PlayerIsInGuildArray[Index] ? "True" : "False") << std::endl;
    };
    std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "[SYSTEM MESSAGE] Successfully Printed Arrays!" << std::endl;
};
/*
Function Name: Merger
Function Description: Merger Section Of The Merge Sort Algorithm, Appends Values That Are Greatest Then To Least, Once The First While Loop Is Completed, Any Remaining Items Not Added Starting From The Left Vector Array Then To The Right Gets Appended Into The MergedVector Array Then Returned
Return Value: std::vector<std::vector<int>> (2-D Vector Array)
Incoming Parameters: LeftInputVector (2-D Vector Array), RightInputVector (2-D Vector Array)
Outgoing Parameters: MergedVector (2-D Vector Array)
*/
std::vector<std::vector<int>> Merger(std::vector<std::vector<int>> LeftInputVector, std::vector<std::vector<int>> RightInputVector){
    std::vector<std::vector<int>> MergedVector(LeftInputVector.size()+RightInputVector.size(),std::vector<int>(2));
    int MergedVectorIndex = 0, LeftVectorIndex = 0, RightVectorIndex = 0;
    while(LeftVectorIndex < LeftInputVector.size() && RightVectorIndex < RightInputVector.size()){
        if (LeftInputVector[LeftVectorIndex][0] > RightInputVector[RightVectorIndex][0]){
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
Return Value: std::vector<std::vector<int>> (2-D Vector Array)
Incoming Parameters: LeftInputVector (2-D Vector Array), RightInputVector (2-D Vector Array)
Outgoing Parameters: MergedVector (2-D Vector Array)
*/
std::vector<std::vector<int>> Splitter(std::vector<std::vector<int>> InputVector){
    if (InputVector.size() <= 1){
        return InputVector;
    };
    int MiddleIndex = InputVector.size()/2;
    std::vector<std::vector<int>> LeftInputVector(InputVector.begin(),InputVector.begin()+MiddleIndex);
    std::vector<std::vector<int>> RightInputVector(InputVector.begin()+MiddleIndex,InputVector.end());
    return Merger(Splitter(LeftInputVector),Splitter(RightInputVector));
};
/*
Function Name: SortArrays
Function Description: Initializes A 2D Vector Of The Player Level Values To Be Sorted By The Merge Sort Algorithm (Splitter & Merger Functions). Creates Unordered Map With Index As The Key & PlayerDataStruct As The Value To Be Reference To Update All Arrays In The 2nd For Loop, This Is Because The Data Is Being Overwritten So That It Is In Sorted Order (Greatest To Least).
Return Value: Void
Incoming Parameters: PlayerNameArray (String Array), PlayerIdArray (String Array), PlayerLevelArray (Integer Array), PlayerExpArray (Double Array), PlayerIsInGuildArray (Boolean Array), ArraySize (Integer)
Outgoing Parameters: PlayerNameArray (String Array), PlayerIdArray (String Array), PlayerLevelArray (Integer Array), PlayerExpArray (Double Array), PlayerIsInGuildArray (Boolean Array)
*/
void SortArrays(std::string PlayerNameArray[], std::string PlayerIdArray[], int PlayerLevelArray[], double PlayerExpArray[], bool PlayerIsInGuildArray[], int ArraySize){
    std::vector<std::vector<int>> PlayerLevelVector(ArraySize,std::vector<int>(2));
    for (int Index = 0; Index < ArraySize; Index++){
        PlayerLevelVector[Index][0] = PlayerLevelArray[Index];
        PlayerLevelVector[Index][1] = Index;
    };
    PlayerLevelVector = Splitter(PlayerLevelVector);
    std::unordered_map<int,PlayerDataStruct> PlayerDataUnorderedMap;
    for (int Index = 0; Index < PlayerLevelVector.size(); Index++){
        PlayerDataStruct CurrentPlayerData;
        CurrentPlayerData.PlayerName = PlayerNameArray[Index];
        CurrentPlayerData.PlayerId = PlayerIdArray[Index];
        CurrentPlayerData.PlayerLevel = PlayerLevelArray[Index];
        CurrentPlayerData.PlayerExp = PlayerExpArray[Index];
        CurrentPlayerData.PlayerIsInGuild = PlayerIsInGuildArray[Index];
        PlayerDataUnorderedMap[Index] = CurrentPlayerData;
    };
    for (int Index = 0; Index < PlayerLevelVector.size(); Index++){
        PlayerNameArray[Index] = PlayerDataUnorderedMap[PlayerLevelVector[Index][1]].PlayerName;
        PlayerIdArray[Index] = PlayerDataUnorderedMap[PlayerLevelVector[Index][1]].PlayerId;
        PlayerLevelArray[Index] = PlayerDataUnorderedMap[PlayerLevelVector[Index][1]].PlayerLevel;
        PlayerExpArray[Index] = PlayerDataUnorderedMap[PlayerLevelVector[Index][1]].PlayerExp;
        PlayerIsInGuildArray[Index] = PlayerDataUnorderedMap[PlayerLevelVector[Index][1]].PlayerIsInGuild;
    };
    std::cout << "[SYSTEM MESSAGE] Successfully Sorted Arrays!" << std::endl;
};
