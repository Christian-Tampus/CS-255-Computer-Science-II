#include "Queue.h"
Queue::Queue(int InitialQueueSize):QueueSize(InitialQueueSize){
	this->QueueArray = new int[InitialQueueSize];
	InitArrayElements();
};
bool Queue::Enqueue(int Item){
	if (!IsFull()){
		this->QueueArray[this->EnqueueIndex] = Item;
		this->EnqueueIndex = (++this->EnqueueIndex) % this->QueueSize;
		ItemsInQueue++;
		std::cout << "1. [SUCCESS] CAN ADD (ENQUEUE)! ITEM ENQUEUED: " << Item << " ITEMS IN QUEUE: " << ItemsInQueue << std::endl; //TESTING PURPOSES
		Print(); //TESTING PURPOSES
		return true;
	};
	std::cout << "1. [ERROR] CANNOT ADD (ENQUEUE)! ITEM ATTEMPTED TO ENQUEUE: " << Item << std::endl; //TESTING PURPOSES
	Print(); //TESTING PURPOSES
	return false;
};
bool Queue::Dequeue(int& Item){
	if (!IsEmpty()){
		Item = this->QueueArray[this->DequeueIndex];
		this->QueueArray[this->DequeueIndex] = -1; //TESTING PURPOSES
		this->DequeueIndex = (++this->DequeueIndex) % this->QueueSize;
		ItemsInQueue--;
		std::cout << "2. [SUCCESS] CAN REMOVE (DEQUEUE)! ITEM DEQUEUED: " << Item << " ITEMS IN QUEUE: " << ItemsInQueue << std::endl;
		Print(); //TESTING PURPOSES
		return true;
	};
	std::cout << "2. [ERROR] CANNOT REMOVE (DEQUEUE)!" << std::endl; //TESTING PURPOSES
	Print(); //TESTING PURPOSES                                                            
	return false;
};
bool Queue::CutInLine(int Item, int LinePosition){
	if (!IsFull() && LinePosition >= 0 && LinePosition < this->QueueSize){
		if (LinePosition == this->EnqueueIndex){
			Enqueue(Item);
			std::cout << "3. [SUCCESS] CAN CUT INTO LINE! (NO SHIFTING) ITEM CUT IN LINE: " << Item << " AT LINE POSITION: " << LinePosition << " ITEMS IN QUEUE: " << ItemsInQueue << std::endl; //TESTING PURPOSES
		}else{
			std::cout << "3. [SUCCESS] CAN CUT INTO LINE! (HAS SHIFTING) ITEM CUT IN LINE: " << Item << " AT LINE POSITION: " << LinePosition << " ITEMS IN QUEUE: " << ItemsInQueue << std::endl; //TESTING PURPOSES
			this->EnqueueIndex = (++this->EnqueueIndex) % this->QueueSize;
			ItemsInQueue++;
			int PrevTemp = this->QueueArray[LinePosition];
			this->QueueArray[LinePosition] = Item;
			int ShiftIndex = (++LinePosition) % this->QueueSize;
			do{
				int CurrTemp = this->QueueArray[ShiftIndex];
				this->QueueArray[ShiftIndex] = PrevTemp;
				PrevTemp = CurrTemp;
				if (ShiftIndex != this->EnqueueIndex){
					ShiftIndex = (++LinePosition) % this->QueueSize;
				};
			}while (ShiftIndex != this->EnqueueIndex);
		};
		Print();
		return true;
	};
	std::cout << "3. [ERROR] CANNOT CUT INTO LINE! ITEM ATTEMPTED TO CUT INTO LINE: " << Item << " AT LINE POSITION: " << LinePosition << std::endl; //TESTING PURPOSES
	Print(); //TESTING PURPOSES
	return false;
};
bool Queue::IsFull()const{
	return this->ItemsInQueue >= this->QueueSize;   
};
bool Queue::IsEmpty()const{
	return this->ItemsInQueue <= 0;
};
int Queue::GetSize()const{
	return this->QueueSize; //TESTING PURPOSES
};
void Queue::Print()const{
	//TESTING PURPOSES
	std::cout << "Current Queue: [";
	for (int Index = 0; Index < this->QueueSize; Index++){
		std::cout << this->QueueArray[Index] << (Index+1 != this->QueueSize ? "," : "");
	};
	std::cout << "]" << std::endl;
};
void Queue::InitArrayElements(){
	//TESTING PURPOSES
	for (int Index = 0; Index < this->QueueSize; Index++){
		this->QueueArray[Index] = -1; //TESTING PURPOSES: INITIALIZE ARRAY TO BE ALL -1 (TO INIDICATE IT IS EMPTY)
	};
};