#ifndef _QUEUE_H
#define _QUEUE_H
#include <iostream>
using namespace std;
class Queue{
private:
	int ItemsInQueue = 0;
	int EnqueueIndex = 0;
	int DequeueIndex = 0;
	int QueueSize;
	int* QueueArray;
	bool IsFull()const;
	bool IsEmpty()const;
	void Print()const; //TESTING PURPOSES  
	void InitArrayElements(); //TESTING PURPOSES  
public:
	Queue(int InitialQueueSize = 5);
	bool Enqueue(int Item);
	bool Dequeue(int& Item);
	bool CutInLine(int Item, int LinePosition);
	int GetSize()const; //TESTING PURPOSES  
};
#endif