/*
Student Name: Christian Tampus
File Name: Stumap.cpp
Description: Stumap C++ File
Course Number: CS 255
Section Number: 02 (Tuesday/Thursday)
Due Date: 10/30
*/
/*
----------------------------------------------------------------------------------------------------
DEPENDENCIES
----------------------------------------------------------------------------------------------------
*/
#include "Stumap.h"
#include <cmath>
#include <iomanip>
#include <string>
/*
----------------------------------------------------------------------------------------------------
DEFAULT CONSTRUCTOR
----------------------------------------------------------------------------------------------------
*/
/*
Constructor Name: STUMAP(int InitialMaxSize = 10);
Constructor Description: STUMAP Default Constructor
Return Value: None
Incoming Params: InitialMaxSize (Default Value)
Outgoing Params: None
*/
STUMAP::STUMAP(int InitialMaxSize) :Cursor(0), Size(0), MaxSize(InitialMaxSize) {
	this->Allocate();
	for (int Index = 0; Index < this->MaxSize; Index++) {
		this->InsertAt(-1, -1, Index);
	};
};
/*
----------------------------------------------------------------------------------------------------
COPY CONSTRUCTOR
-------------------------------------------------------------------------------------------------------
*/
/*
Constructor Name: STUMAP(const STUMAP& STUMAP_RIGHT);
Constructor Description: STUMAP Copy Constructor
Return Value: None
Incoming Params: STUMAP_RIGHT (STUMAP)
Outgoing Params: STUMAP_RIGHT (STUMAP)
*/
STUMAP::STUMAP(const STUMAP& STUMAP_RIGHT) {
	this->CopyData(false, STUMAP_RIGHT);
	this->Allocate();
	this->CopyData(true, STUMAP_RIGHT);
};
/*
----------------------------------------------------------------------------------------------------
MANUAL DELETE
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: ManualDelete();
Method Description: Sets IsManuallyDestructed To True
Return Value: Void
Incoming Params: None
Outgoing Params: None
Calling Object Purpose: Called Before A Manual Deallocation To Test [3] Demo Destructor
*/
void STUMAP::ManualDelete() {
	this->IsManuallyDestructed = true;
};
/*
----------------------------------------------------------------------------------------------------
ALLOCATOR
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Allocate();
Method Description: Sets IdList & ScoreList To Dynamic Arrays In The Heap
Return Value: Void
Incoming Params: None
Outgoing Params: None
Calling Object Purpose: To Allocate Dynamic Arrays To IdList & ScoreList To Store Incomming Data
*/
void STUMAP::Allocate() {
	this->IdList = new int[this->MaxSize];
	this->ScoreList = new double[this->MaxSize];
};
/*
----------------------------------------------------------------------------------------------------
DEALLOCATOR
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Deallocate();
Method Description: Deallocates IdList & ScoreList Then Sets Them Both To Nullptr & Resets The Private Data Member Values
Return Value: Void
Incoming Params: None
Outgoing Params: None
Calling Object Purpose: To Deallocate The Dynammic Arrays In The Heap When Out Of Scope.
*/
void STUMAP::Deallocate() {
	if (this->IdList != nullptr) {
		delete[] this->IdList;
		this->IdList = nullptr;
	};
	if (this->ScoreList != nullptr) {
		delete[] this->ScoreList;
		this->ScoreList = nullptr;
	};
	this->Cursor = 0;
	this->Size = 0;
	this->MaxSize = 0;
};
/*
----------------------------------------------------------------------------------------------------
COPY DATA
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: CopyData(bool CopyParallelArrays, const STUMAP& STUMAP_RIGHT);
Method Description: Sets The Private Data Members Or Sets IdList & ScoreList Data
Return Value: Void
Incoming Params: CopyParallelArrays (Boolean), STUMAP_RIGHT (STUMAP)
Outgoing Params: STUMAP_RIGHT (STUMAP)
Calling Object Purpose: CopyParallelArrays Boolean Determines The Action Of The Method; If True, Updates The Private Data Members; If False, Updates The IdList & ScoreList Data
*/
void STUMAP::CopyData(bool CopyParallelArrays, const STUMAP& STUMAP_RIGHT) {
	if (!CopyParallelArrays) {
		this->Cursor = STUMAP_RIGHT.Cursor;
		this->Size = STUMAP_RIGHT.Size;
		this->MaxSize = STUMAP_RIGHT.MaxSize;
	}
	else {
		for (int Index = 0; Index < STUMAP_RIGHT.Size; Index++) {
			this->InsertAt(STUMAP_RIGHT.IdList[Index], STUMAP_RIGHT.ScoreList[Index], Index);
		};
	};
};
/*
----------------------------------------------------------------------------------------------------
DESTRUCTOR
----------------------------------------------------------------------------------------------------
*/
/*
Destructor Name: ~STUMAP();
Destructor Description: Calls The Deallocate() Method First Then Checks If IsManuallyDestructed, If True, Prints A System Message
Return Value: None
Incoming Params: None
Outgoing Params: None
*/
STUMAP::~STUMAP() {
	this->Deallocate();
	if (this->IsManuallyDestructed) {
		std::cout << "[SYSTEM MESSAGE] STUMAP Destructor Executed Manually!" << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
ASSIGNMENT OPERATOR
----------------------------------------------------------------------------------------------------
*/
/*
Function Name: STUMAP::operator=(const STUMAP& STUMAP_RIGHT);
Function Description: Calls The Deallocate() Method First, Then Calls CopyData() To Update The Private Data Members, Then Calls Allocate() To Allocate New Dynamic Arrays, Finally Calls CopyData() Again To Update The New Dynamic Arrays Data
Return Value: None
Incoming Params: None
Outgoing Params: None
*/
STUMAP& STUMAP::operator=(const STUMAP& STUMAP_RIGHT) {
	if (this != &STUMAP_RIGHT) {
		this->Deallocate();
		this->CopyData(false, STUMAP_RIGHT);
		this->Allocate();
		this->CopyData(true, STUMAP_RIGHT);
	};
	return (*this);
};
/*
----------------------------------------------------------------------------------------------------
INSERTER
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: InsertAt(int Id, double Score, int Index);
Method Description: Updates IdList & ScoreList Data
Return Value: Void
Incoming Params: Id (Integer), Score (Double), Index (Integer)
Outgoing Params: None
Calling Object Purpose: Resuable Code To Insert New Data To IdList & ScoreList At A Specified Index
*/
void STUMAP::InsertAt(int Id, double Score, int Index) {
	this->IdList[Index] = Id;
	this->ScoreList[Index] = Score;
};
/*
----------------------------------------------------------------------------------------------------
APPENDER
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Append(int Id, double Score);
Method Description: Appends New Data Into IdList & ScoreList
Return Value: Void
Incoming Params: Id (Integer), Score (Double)
Outgoing Params: None
Calling Object Purpose: Appends New Data Into IdList & ScoreList If Id Is Does Not Already Exist Or If Size Is Less Than Max Size
*/
void STUMAP::Append(int Id, double Score) {
	bool IdAlreadyExist = false;
	for (int Index = 0; Index < this->Size; Index++) {
		if (this->IdList[Index] == Id) {
			IdAlreadyExist = true;
			break;
		};
	};
	if (!IdAlreadyExist && this->Size < this->MaxSize) {
		this->Cursor = this->Size;
		this->InsertAt(Id, Score, this->Cursor);
		this->Size++;
		std::cout << "[SYSTEM MESSAGE] Appended Id: " << Id << " Score: " << Score << " Successfully!" << std::endl;
	}
	else if (IdAlreadyExist && this->Size < this->MaxSize) {
		std::cout << "[SYSTEM ERROR] Attempted To Append Id: " << Id << " With Score: " << Score << " When The Id Already Exists In IdList!" << std::endl;
	}
	else if (this->Size >= this->MaxSize) {
		std::cout << "[SYSTEM ERROR] Attempted To Append Id: " << Id << " With Score: " << Score << " When The IdList & ScoreList Is Full!" << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
REMOVER
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Remove(int Id);
Method Description: Removes Data From IdList & ScoreList
Return Value: Void
Incoming Params: Id (Integer)
Outgoing Params: None
Calling Object Purpose: Removes Id & Score From IdList & ScoreList If Id Exist And The Size Is Greater Than Zero, Can Remove Duplicates Ids
*/
void STUMAP::Remove(int Id) {
	bool HasRemovedFromList = false;
	if (this->Size > 0) {
		for (int Index1 = 0; Index1 < this->Size; Index1++) {
			if (this->IdList[Index1] == Id) {
				std::cout << "[SYSTEM MESSAGE] Removed Id: " << this->IdList[Index1] << " From IdList At Index: " << Index1 << " Successfully!" << std::endl;
				std::cout << "[SYSTEM MESSAGE] Removed Score: " << this->ScoreList[Index1] << " From ScoreList At Index: " << Index1 << " Successfully!" << std::endl;
				this->InsertAt(-1, -1, Index1);
				for (int Index2 = Index1 + 1; Index2 < this->Size; Index2++) {
					this->InsertAt(this->IdList[Index2], this->ScoreList[Index2], Index2 - 1);
				};
				this->Size--;
				this->Cursor = (this->Cursor > this->Size - 1 ? this->Size - 1 : this->Cursor);
				HasRemovedFromList = true;
			};
		};
		for (int Index = this->Size; Index < this->MaxSize; Index++) {
			this->InsertAt(-1, -1, Index);
		};
	}
	else {
		std::cout << "[SYSTEM ERROR] IdList Is Empty!" << std::endl;
	};
	if (!HasRemovedFromList && this->Size > 0) {
		std::cout << "[SYSTEM ERROR] Id: " << Id << " Does Not Exist Inside IdList!" << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
AT CURSOR
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: AtCursor();
Method Description: Prints Index, Id & Score At Cursor Value
Return Value: Void
Incoming Params: None
Outgoing Params: None
Calling Object Purpose: To Print The Index, Id & Score At Cusor Value If It Exist, If Not Print Out -1 For Both Id & Score
*/
void STUMAP::AtCursor() {
	if (this->Size > 0) {
		std::cout << "At Cursor: [Index: " << this->Cursor << "] [Id: " << this->IdList[this->Cursor] << "] [Score: " << this->ScoreList[this->Cursor] << "]" << std::endl;
	}
	else {
		std::cout << "At Cursor: [Index: 0] [Id: -1] [Score: -1]" << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
GO TO BEG METHOD
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: GoToBeg();
Method Description: Moves Cursor To The First Index Available
Return Value: Void
Incoming Params: None
Outgoing Params: None
Calling Object Purpose: Moves Cursor To The First Index Available If The Size Is > 0
*/
void STUMAP::GoToBeg() {
	this->Cursor = (this->Size > 0 ? 0 : -1);
};
/*
----------------------------------------------------------------------------------------------------
GO TO END METHOD
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: GoToEnd();
Method Description: Moves Cursor To The Last Index Available
Return Value: Void
Incoming Params: None
Outgoing Params: None
Calling Object Purpose: Moves Cursor To The Last Index Available To The Size Minues One
*/
void STUMAP::GoToEnd() {
	this->Cursor = this->Size - 1;
};
/*
----------------------------------------------------------------------------------------------------
GO TO NEXT METHOD
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: GoToNext();
Method Description: Moves Cursor To The Next Available Index
Return Value: Void
Incoming Params: None
Outgoing Params: None
Calling Object Purpose: Moves Cursor To The Next Available Index, If Cursor Is Greater Than Size, Reset Cursor Back To Zero
*/
void STUMAP::GoToNext() {
	int PrevCursor = this->Cursor;
	if (this->Size > 0) {
		this->Cursor = (this->Cursor + 1 >= this->Size ? 0 : this->Cursor + 1);
	}
	else {
		this->Cursor = -1;
	}
	std::cout << "[SYSTEM MESSAGE] Previous Cursor: " << PrevCursor << " Current Cursor: " << this->Cursor << std::endl;
};
/*
----------------------------------------------------------------------------------------------------
GO TO PREV METHOD
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: GoToPrev();
Method Description: Moves Cursor To The Previous Available Index
Return Value: Void
Incoming Params: None
Outgoing Params: None
Calling Object Purpose: Moves Cursor To The Previous Available Index, If Cursor Is Less Than 0, Reset Cursor Back To Size Minus 1
*/
void STUMAP::GoToPrev() {
	int PrevCursor = this->Cursor;
	if (this->Size > 0) {
		this->Cursor = (this->Cursor - 1 < 0 ? this->Size - 1 : this->Cursor - 1);
	}
	else {
		this->Cursor = -1;
	};
	std::cout << "[SYSTEM MESSAGE] Previous Cursor: " << PrevCursor << " Current Cursor: " << this->Cursor << std::endl;
};
/*
----------------------------------------------------------------------------------------------------
PRINTER
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Print();
Method Description: Prints Entire IdList & ScoreList Data
Return Value: Void
Incoming Params: None
Outgoing Params: None
Calling Object Purpose: Gets Id Or Score With The Most Characters To Set The Padding For std::setw(Padding) Then Prints Them Line By Line, Id & Score Format
*/
void STUMAP::Print() {
	std::cout << "[SYSTEM MESSAGE] Test Print Routine" << std::endl;
	int Padding = 0;
	for (int Index = 0; Index < this->MaxSize; Index++) {
		int CurrentIdStringLength = std::to_string(this->IdList[Index]).size();
		int CurrentScoreStringLength = std::to_string(this->ScoreList[Index]).size();
		Padding = (CurrentIdStringLength > Padding ? CurrentIdStringLength : (CurrentScoreStringLength > Padding ? CurrentScoreStringLength : Padding));
	};
	for (int Index = 0; Index < this->MaxSize; Index++) {
		std::cout << "Index: " << std::setw(Padding) << std::left << Index << " Id: " << std::setw(Padding) << std::left << this->IdList[Index] << " Score: " << std::setw(Padding) << std::left << this->ScoreList[Index] << (Index == this->Cursor ? "<- Cursor @ [Index: " + std::to_string(Index) + "]" : "") << std::endl;
	};
};
/*
----------------------------------------------------------------------------------------------------
SORTER (BY ID)
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: SortByID();
Method Description: Sort IdList & ScoreList By Id
Return Value: Void
Incoming Params: None
Outgoing Params: None
Calling Object Purpose: Calls Sorter Helper Method With True As The Parameter To Sort By Id
*/
void STUMAP::SortByID() {
	this->Sorter(true);
};
/*
----------------------------------------------------------------------------------------------------
SORTER (BY SCORE)
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: SortByScore();
Method Description: Sort IdList & ScoreList By Score
Return Value: Void
Incoming Params: None
Outgoing Params: None
Calling Object Purpose: Calls Sorter Helper Method With False As The Parameter To Sort By Score
*/
void STUMAP::SortByScore() {
	this->Sorter(false);
};
/*
----------------------------------------------------------------------------------------------------
SORTER METHOD
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: Sorter(bool SortById);
Method Description: Sorts IdList & ScoreList
Return Value: Void
Incoming Params: SortById
Outgoing Params: None
Calling Object Purpose: Checks If SortById Is True To Sort By Id Or False To Sort By Score
*/
void STUMAP::Sorter(bool SortById) {
	for (int Index1 = 0; Index1 < this->Size; Index1++) {
		int ComparisonIndex = Index1;
		for (int Index2 = Index1 + 1; Index2 < this->Size; Index2++) {
			if (SortById && this->IdList[Index2] < this->IdList[ComparisonIndex] || !SortById && this->ScoreList[Index2] < this->ScoreList[ComparisonIndex]) {
				ComparisonIndex = Index2;
			};
		};
		int TempId = this->IdList[Index1];
		double TempScore = this->ScoreList[Index1];
		this->InsertAt(this->IdList[ComparisonIndex], this->ScoreList[ComparisonIndex], Index1);
		this->InsertAt(TempId, TempScore, ComparisonIndex);
	};
};
/*
----------------------------------------------------------------------------------------------------
GET MIN METHOD
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: GetMin();
Method Description: Returns The Min Value In ScoreList
Return Value: Double
Incoming Params: None
Outgoing Params: Min (Double)
Calling Object Purpose: Finds The Min Value In ScoreList Then Returns It
*/
double STUMAP::GetMin()const {
	double Min = -1;
	if (this->Size > 0) {
		Min = this->ScoreList[0];
		for (int Index = 0; Index < this->Size; Index++) {
			Min = (this->ScoreList[Index] < Min ? this->ScoreList[Index] : Min);
		};
	};
	return Min;
};
/*
----------------------------------------------------------------------------------------------------
GET MAX METHOD
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: GetMax();
Method Description: Returns The Max Value In ScoreList
Return Value: Double
Incoming Params: None
Outgoing Params: Max (Double)
Calling Object Purpose: Finds The Max Value In ScoreList Then Returns It
*/
double STUMAP::GetMax()const {
	double Max = -1;
	if (this->Size > 0) {
		Max = this->ScoreList[0];
		for (int Index = 0; Index < this->Size; Index++) {
			Max = (this->ScoreList[Index] > Max ? this->ScoreList[Index] : Max);
		};

	};
	return Max;
};
/*
----------------------------------------------------------------------------------------------------
GET MEAN METHOD
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: GetMean();
Method Description: Returns The Mean Of ScoreList
Return Value: Double
Incoming Params: None
Outgoing Params: Mean (Double)
Calling Object Purpose: Calculates The Sum Of The ScoreList Then Divides By The Size To Calculate The Mean
*/
double STUMAP::GetMean()const {
	double Mean = -1;
	if (this->Size > 0) {
		Mean = 0;
		for (int Index = 0; Index < this->Size; Index++) {
			Mean += this->ScoreList[Index];
		};
		Mean /= this->Size;
	};
	return Mean;
};
/*
----------------------------------------------------------------------------------------------------
GET MEDIAN METHOD
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: GetMedian();
Method Description: Returns The Median Of ScoreList
Return Value: Double
Incoming Params: None
Outgoing Params: Median (Double)
Calling Object Purpose: Calculates The Sum Of The ScoreList Then Divides By The Size To Calculate The Mean
*/
double STUMAP::GetMedian()const {
	double Median = -1;
	if (this->Size > 0) {
		double* TempScoreList = new double[this->Size];
		for (int Index = 0; Index < this->Size; Index++) {
			TempScoreList[Index] = this->ScoreList[Index];
		};
		for (int Index1 = 0; Index1 < this->Size; Index1++) {
			int ComparisonIndex = Index1;
			for (int Index2 = Index1 + 1; Index2 < this->Size; Index2++) {
				if (TempScoreList[Index2] < TempScoreList[ComparisonIndex]) {
					ComparisonIndex = Index2;
				};
			};
			double Temp = TempScoreList[Index1];
			TempScoreList[Index1] = TempScoreList[ComparisonIndex];
			TempScoreList[ComparisonIndex] = Temp;
		};
		int MiddleIndex = std::floor(this->Size / 2);
		Median = (this->Size % 2 != 0 ? TempScoreList[MiddleIndex] : (TempScoreList[MiddleIndex] + TempScoreList[MiddleIndex - 1]) / 2);
	};
	return Median;
};
/*
----------------------------------------------------------------------------------------------------
SEARCHER
----------------------------------------------------------------------------------------------------
*/
/*
Method Name: SearchId();
Method Description: Searches IdList If Id Exist Then Returns Score If It Exist Or -1
Return Value: Double
Incoming Params: None
Outgoing Params: -1 Or Score (Double)
Calling Object Purpose: Searches IdList If Id Exist Then Returns Score If It Exist Or -1
*/
double STUMAP::SearchId(int Id)const {
	if (this->Size > 0) {
		for (int Index = 0; Index < this->Size; Index++) {
			if (this->IdList[Index] == Id) {
				return this->ScoreList[Index];
			};
		};
	};
	return -1;
};
/*
----------------------------------------------------------------------------------------------------
INSERTION OPERATOR
----------------------------------------------------------------------------------------------------
*/
/*
Friend Function Name: std::ostream& operator<<(std::ostream& OS, const STUMAP& STUMAP_RIGHT);
Friend Function Description: Output IdList & ScoreList In An Array Format & Indicate The Position Of The Cursor With Brackets Example: [{1},2,3,4,5]
Return Value: std::ostream&
Incoming Params: OS (std::ostream&), STUMAP_RIGHT (STUMAP&)
Outgoing Params: OS (std::ostream&)
*/
std::ostream& operator<<(std::ostream& OS, const STUMAP& STUMAP_RIGHT) {
	OS << "[SYSTEM MESSAGE] Cursor: {" << STUMAP_RIGHT.Cursor << "}; Size: " << STUMAP_RIGHT.Size << "; Max Size: " << STUMAP_RIGHT.MaxSize << std::endl;
	OS << "[SYSTEM MESSAGE] IdList: [";
	for (int Index = 0; Index < STUMAP_RIGHT.MaxSize; Index++) {
		if (Index < STUMAP_RIGHT.Size) {
			if (STUMAP_RIGHT.Cursor == Index) {
				OS << "{" << STUMAP_RIGHT.IdList[Index] << (Index + 1 < STUMAP_RIGHT.MaxSize ? "}," : "}");
			}
			else {
				OS << STUMAP_RIGHT.IdList[Index] << (Index + 1 < STUMAP_RIGHT.MaxSize ? "," : "");
			};
		}
		else {
			if (STUMAP_RIGHT.Cursor == Index) {
				OS << (Index + 1 < STUMAP_RIGHT.MaxSize ? "{_}," : "{_}");
			}
			else {
				OS << (Index + 1 < STUMAP_RIGHT.MaxSize ? "_," : "_");
			};
		};
	};
	OS << "]" << std::endl;
	OS << "[SYSTEM MESSAGE] ScoreList: [";
	for (int Index = 0; Index < STUMAP_RIGHT.MaxSize; Index++) {
		if (Index < STUMAP_RIGHT.Size) {
			if (STUMAP_RIGHT.Cursor == Index) {
				OS << "{" << std::fixed << std::setprecision(2) << STUMAP_RIGHT.ScoreList[Index] << (Index + 1 < STUMAP_RIGHT.MaxSize ? "}," : "}");
			}
			else {
				OS << std::fixed << std::setprecision(2) << STUMAP_RIGHT.ScoreList[Index] << (Index + 1 < STUMAP_RIGHT.MaxSize ? "," : "");
			};
		}
		else {
			if (STUMAP_RIGHT.Cursor == Index) {
				OS << (Index + 1 < STUMAP_RIGHT.MaxSize ? "{_}," : "{_}");
			}
			else {
				OS << (Index + 1 < STUMAP_RIGHT.MaxSize ? "_," : "_");
			};
		};
	};
	OS << "]" << std::endl;
	return OS;
};