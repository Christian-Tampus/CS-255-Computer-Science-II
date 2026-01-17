//Fraction.h --> Fraction Class Specification
#ifndef _FRACTION_H
#define _FRACTION_H
#include <iostream>
using namespace std;


class Fraction{
	int num;
	int den;
public:
	
	Fraction(int n=0, int d=1);

	void reduce();
	
	int GetNum()const;
	int GetDen()const;

	void SetNum(int n);
	void SetDen(int d);


	Fraction operator+(const Fraction&)const;
	Fraction operator-(const Fraction&)const;
	Fraction operator*(const Fraction&)const;
	Fraction operator/(const Fraction&)const;

	Fraction operator++();
	Fraction operator++(int);
	friend Fraction operator--(Fraction&);
	friend Fraction operator--(Fraction&, int);

	friend ostream& operator<<(ostream&, const Fraction&);
	friend istream& operator>>(istream&, Fraction&);

	friend bool isExact(const Fraction&, const Fraction&);	//checks exact values
	friend bool operator == (const Fraction&, const Fraction&);	//checks equivalency
	friend bool operator <  (const Fraction&, const Fraction&);	
	friend bool operator >  (const Fraction&, const Fraction&);	
	friend bool operator <= (const Fraction&, const Fraction&);	
	friend bool operator >= (const Fraction&, const Fraction&);
	friend bool operator != (const Fraction&, const Fraction&);	

};

#endif
