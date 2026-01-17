#ifndef _MONEY_H
#define _MONEY_H
#include <iostream>
using namespace std;
class Money{
    private:
        int Dollars;
        int Cents;
    public:
        Money(int InputDollars = 0, int InputCents = 0); //Constructor
        void ValidateInput(); //Input Validation
        int GetDollars(); //Getter (Dollars)
        int GetCents(); //Getter (Cents)
        void SetDollars(int NewInputDollars); //Setter (Dollars)
        void SetCents(int NewInputCents); //Setter (Cents)
        Money operator+(const Money&)const; //Overloaded Addition Operator (Class Method)
        Money operator-(const Money&)const; //Overloaded Subtraction Operator (Class Method)
        Money operator*(const Money&)const; //Overloaded Multiplication Operator (Class Method)
        Money operator/(const Money&)const; //Overloaded Division Operator (Class Method)
        Money operator--(); //Overloaded Prefix Decrement Operator (Class Method)
        Money operator--(int); //Overloaded Postfix Decrement Operator (Class Method)
        friend Money operator++(Money&); //Overloaded Prefix Increment Operator (Friend Function)
        friend Money operator++(Money&, int); //Overloaded Postfix Increment Operator (Friend Function)
        friend ostream& operator<<(ostream&, const Money&); //Overloaded Extraction Operator (Friend Function)
        friend istream& operator>>(istream&, Money&); //Overloaded Insertion Operator (Friend Function)
        friend bool operator==(const Money&, const Money&); //Overloaded Equality Operator (Friend Function)
        friend bool operator!=(const Money&, const Money&); //Overloaded Not Equals Operator (Friend Function)
        friend bool operator>(const Money&, const Money&); //Overloaded Greater Than Operator (Friend Function)
        friend bool operator<(const Money&, const Money&); //Overloaded Less Than Operator (Friend Function)
        friend bool operator>=(const Money&, const Money&); //Overloaded Greater Than Or Equal To Operator (Friend Function)
        friend bool operator<=(const Money&, const Money&); //Overloaded Less Than Or Equal To Operator (Friend Function)
};
#endif
