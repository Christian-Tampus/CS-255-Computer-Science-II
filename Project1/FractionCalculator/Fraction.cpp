#include "Fraction.h"

Fraction::Fraction(int n, int d):num(n){
    if (d == 0)
       d  = 1;
    den = d;                       
}

//*******************************************************


//*******************************************************
int gcd(int one, int two){

	
    while( one != 0 ){ 
		int temp = one;
        one = two % one;
		two = temp;
    }
   
    return two;
}
    
//*******************************************************
void Fraction::reduce(){
	int divisor = gcd(num,den);
	num/=divisor;
	den/=divisor;
} 

//*******************************************************

int Fraction::GetNum()const{
	return num;
}
//*******************************************************
int Fraction::GetDen()const{
	return den;
}
//*******************************************************

void Fraction::SetNum(int n){
	num = n;
}
//*******************************************************
void Fraction::SetDen(int d){
	if (d==0)
		d = 1;
	den = d;
}

//*******************************************************
Fraction Fraction::operator+(const Fraction& f)const{
	Fraction temp;
	temp.num = num*f.den + den * f.num;
	temp.den = den * f.den;
	return temp;
}
//*******************************************************
Fraction Fraction::operator-(const Fraction& f)const{
	Fraction temp;
	temp.num = num*f.den - den * f.num;
	temp.den = den * f.den;
	return temp;
}

//*******************************************************
Fraction Fraction::operator*(const Fraction& f)const{
	Fraction temp;
	temp.num = num * f.num;
	temp.den = den * f.den;
	return temp;	
}

//*******************************************************
Fraction Fraction::operator/(const Fraction& f)const{
	Fraction temp;
	temp.num = num * f.den;
	temp.den = den * f.num;
	return temp;	
}

//*******************************************************
ostream& operator<<(ostream& os, const Fraction& f){
	os << f.num << "/" << f.den ;
	return os;
}


//*******************************************************
istream& operator>>(istream& is, Fraction& f){
	char dummy;
	is >> f.num >> dummy >> f.den;
	return is;
}

//*******************************************************
bool isExact(const Fraction& one , const Fraction& two){
     return one.num == two.num && one.den == two.den;
     
}
//*******************************************************
bool operator == (const Fraction& one, const Fraction& two){
	int left = one.num * two.den;
	int right = two.num * one. den;
	return left == right;
}

//*******************************************************
bool operator <  (const Fraction& one, const Fraction& two){
	int left = one.num * two.den;
	int right = two.num * one. den;
	return left < right;
}

//*******************************************************
bool operator >  (const Fraction& one, const Fraction& two){
	return !(one == two || one < two);
}

//*******************************************************
bool operator <= (const Fraction& one, const Fraction& two){
	return (one == two || one < two);
}

//*******************************************************
bool operator >= (const Fraction& one, const Fraction& two){
	return (one == two || one > two);
}

//*******************************************************
bool operator != (const Fraction& one, const Fraction& two){
	return !(one==two);
}

//*******************************************************
Fraction Fraction::operator++(){ // prefix
	num+=den;
	return *this;
}
//*******************************************************
Fraction Fraction::operator++(int){
	Fraction temp;
	temp = *this;
	num +=den;
	return temp;
}

//*******************************************************
Fraction operator--(Fraction& f){
	f.num-=f.den;
	return f;
}
	
//*******************************************************
Fraction operator--(Fraction& f, int){
	Fraction temp = f;
	f.num -= f.den;
	return temp;
}
