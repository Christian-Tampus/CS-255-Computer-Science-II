/*
Student Name: Christian Tampus
File Name: Stumap.h
Description: Stumap Header File
Course Number: CS 255
Section Number: 02 (Tuesday/Thursday)
Due Date: 10/30
*/
/*
----------------------------------------------------------------------------------------------------
DEPENDENCIES
----------------------------------------------------------------------------------------------------
*/
#ifndef _STUMAP_H
#define _STUMAP_H
#include <iostream>
#include <unordered_map>
#include <functional>
/*
----------------------------------------------------------------------------------------------------
CLASS DECLERATION
----------------------------------------------------------------------------------------------------
*/
class STUMAP {
private:
	/*
	----------------------------------------------------------------------------------------------------
	PRIVATE DATA MEMBERS
	----------------------------------------------------------------------------------------------------
	*/
	int* IdList;
	double* ScoreList;
	int Cursor;
	int Size;
	int MaxSize;
	bool IsManuallyDestructed = false; //This Boolean Prevents Print Out When Not Manually Deallocated. Only Changed Before Manually Executing The Destructor When Testing The [3] Demo Destructor Routine.
public:
	/*
	----------------------------------------------------------------------------------------------------
	PUBLIC DATA MEMBERS
	----------------------------------------------------------------------------------------------------
	*/
	STUMAP(int InitialMaxSize = 10);
	STUMAP(const STUMAP& STUMAP_RIGHT);
	void ManualDelete();
	void Allocate();
	void Deallocate();
	void CopyData(bool CopyParallelArrays, const STUMAP& STUMAP_RIGHT);
	~STUMAP();
	STUMAP& operator=(const STUMAP& STUMAP_RIGHT);
	void InsertAt(int Id, double Score, int Index);
	void Append(int Id, double Score);
	void Remove(int Id);
	void AtCursor();
	void GoToBeg();
	void GoToEnd();
	void GoToNext();
	void GoToPrev();
	void Print();
	void SortByID();
	void SortByScore();
	void Sorter(bool SortById);
	double GetMin()const;
	double GetMax()const;
	double GetMean()const;
	double GetMedian()const;
	double SearchId(int Id)const;
	friend std::ostream& operator<<(std::ostream& OS, const STUMAP& STUMAP_RIGHT);
	//Character Based Indexing To Call The Void Methods
	std::unordered_map<char, std::function<void()>> VoidMethods{
		{'p',[this]() {this->Print(); }},
		{'@',[this]() {this->AtCursor(); }},
		{'b',[this]() {this->GoToBeg(); }},
		{'e',[this]() {this->GoToEnd(); }},
		{'>',[this]() {this->GoToNext(); }},
		{'<',[this]() {this->GoToPrev(); }},
		{'5',[this]() {this->SortByID(); }},
		{'6',[this]() {this->SortByScore(); }},
	};
};
#endif