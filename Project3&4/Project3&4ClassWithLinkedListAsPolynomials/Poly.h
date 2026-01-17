/*
Student Name: Christian Tampus
File Name: Poly.h
Description: Poly Header File
Course Number: CS 255
Section Number: 02 (Tuesday/Thursday)
Due Date: 11/19
*/
/*
----------------------------------------------------------------------------------------------------
DEPENDENCIES
----------------------------------------------------------------------------------------------------
*/
#ifndef _POLY_H
#define _POLY_H
#include <iostream>
using namespace std;
/*
----------------------------------------------------------------------------------------------------
TERM CLASS DECLERATION
----------------------------------------------------------------------------------------------------
*/
class Term {
private:
	/*
	----------------------------------------------------------------------------------------------------
	PRIVATE DATA MEMBERS
	----------------------------------------------------------------------------------------------------
	*/
	int Coefficient;
	int Exponent;
	Term* NextTerm;
	bool ManualDeallocation = false; //This Boolean Is Only Used For Testing The Destructor [2] Operation
	Term(int NewCoefficient);
	Term(int NewCoefficient, int NewExponent);
	Term(int NewCoefficient, int NewExponent, Term* NewNextTerm);
	~Term();
	friend class Poly;
	friend std::ostream& operator<<(std::ostream& OS, const Term& InputTerm);
};
/*
----------------------------------------------------------------------------------------------------
POLY CLASS DECLERATION
----------------------------------------------------------------------------------------------------
*/
class Poly {
private:
	/*
	----------------------------------------------------------------------------------------------------
	PRIVATE DATA MEMBERS
	----------------------------------------------------------------------------------------------------
	*/
	Term* HeadTerm;
	bool ManualDeallocation = false; //This Boolean Is Only Used For Testing The Destructor [2] Operation
public:
	/*
	----------------------------------------------------------------------------------------------------
	PUBLIC DATA MEMBERS
	----------------------------------------------------------------------------------------------------
	*/
	Poly();
	Poly(const Poly& Poly_RIGHT);
	~Poly();
	Poly& operator=(const Poly& Poly_RIGHT);
	Poly operator+(const Poly& Poly_RIGHT)const;
	Poly& operator+=(const Poly& Poly_RIGHT);
	Poly operator-(const Poly& Poly_RIGHT)const;
	void CopyData(const Poly& Poly_RIGHT);
	void Deallocate();
	void ManuallyDeallocate();
	bool Insert(int NewCoefficient, int NewExponent, bool AdditionArithmeticOperation = true);
	bool Remove(int RemoveExponent);
	bool Search(int SearchExponent)const;
	void Print()const;
	void PrintReverse()const;
	bool PrintReverseRecurser(Term* InputTermPointer, bool Simplified)const;
	void Reset(std::string PolynomialName);
	double Evaluate(double X)const;
	bool Derivative();
	friend std::ostream& operator<<(std::ostream& OS, const Poly& InputPoly);
	friend std::istream& operator>>(std::istream& IS, Poly& InputPoly);
};
#endif