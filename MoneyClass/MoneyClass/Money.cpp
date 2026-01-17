#include "Money.h"
Money::Money(int InputDollars, int InputCents):Dollars(InputDollars), Cents(InputCents){
    this->ValidateInput();
};
void Money::ValidateInput(){
    int TempTotalCents = (this->Dollars * 100) + this->Cents;
    this->Dollars = TempTotalCents / 100;
    this->Cents = TempTotalCents % 100;
};
int Money::GetDollars(){
    return this->Dollars;
};
int Money::GetCents(){
    return this->Cents;
};
void Money::SetDollars(int NewInputDollars){
    this->Dollars = NewInputDollars;
    this->ValidateInput();
};
void Money::SetCents(int NewInputCents){
    this->Cents = NewInputCents;
    this->ValidateInput();
};
Money Money::operator+(const Money& InputMoney)const{
    int ThisMoneyTotalCents = (this->Dollars * 100) + this->Cents;
    int InputMoneyTotalCents = (InputMoney.Dollars * 100) + InputMoney.Cents;
    Money TempMoney(0,ThisMoneyTotalCents + InputMoneyTotalCents);
    return TempMoney;
};
Money Money::operator-(const Money& InputMoney)const{
    int ThisMoneyTotalCents = (this->Dollars * 100) + this->Cents;
    int InputMoneyTotalCents = (InputMoney.Dollars * 100) + InputMoney.Cents;
    Money TempMoney(0,ThisMoneyTotalCents - InputMoneyTotalCents);
    return TempMoney;
};
Money Money::operator*(const Money& InputMoney)const{
    double ThisMoneyTotalDollars = this->Dollars + (this->Cents/100.00);
    double InputMoneyTotalDollars = InputMoney.Dollars + (InputMoney.Cents/100.00);
    Money TempMoney(0,ThisMoneyTotalDollars*InputMoneyTotalDollars*100);
    return TempMoney;
};
Money Money::operator/(const Money& InputMoney)const{
    double ThisMoneyTotalDollars = this->Dollars + (this->Cents/100.00);
    double InputMoneyTotalDollars = InputMoney.Dollars + (InputMoney.Cents/100.00);
    Money TempMoney(0,(ThisMoneyTotalDollars/InputMoneyTotalDollars)*100);
    return TempMoney;
};
Money Money::operator--(){
    int ThisMoneyTotalCents = ((this->Dollars - 1) * 100) + this->Cents;
    this->Dollars = 0;
    this->Cents = ThisMoneyTotalCents;
    this->ValidateInput();
    return *this;
};
Money Money::operator--(int){
    Money TempMoney = *this;
    int ThisMoneyTotalCents = ((this->Dollars - 1) * 100) + this->Cents;
    this->Dollars = 0;
    this->Cents = ThisMoneyTotalCents;
    this->ValidateInput();
    return TempMoney;
};
Money operator++(Money& InputMoney){
    int InputMoneyTotalCents = ((InputMoney.Dollars + 1) * 100) + InputMoney.Cents;
    InputMoney.Dollars = 0;
    InputMoney.Cents = InputMoneyTotalCents;
    InputMoney.ValidateInput();
    return InputMoney;
};
Money operator++(Money& InputMoney, int){
    Money TempInputMoney = InputMoney;
    int InputMoneyTotalCents = ((InputMoney.Dollars + 1) * 100) + InputMoney.Cents;
    InputMoney.Dollars = 0;
    InputMoney.Cents = InputMoneyTotalCents;
    InputMoney.ValidateInput();
    return TempInputMoney;
};
ostream& operator<<(ostream& OutputStream, const Money& InputMoney){
    OutputStream << "$" << InputMoney.Dollars << "." << InputMoney.Cents;
    return OutputStream;
};
istream& operator>>(istream& InputStream, Money& InputMoney){
    InputStream >> InputMoney.Dollars >> InputMoney.Cents;
    InputMoney.ValidateInput();
    return InputStream;
};
bool operator==(const Money& LeftHandMoney, const Money& RightHandMoney){
    int LeftHandMoneyTotalCents = (LeftHandMoney.Dollars * 100) + LeftHandMoney.Cents;
    int RightHandMoneyTotalCents = ((RightHandMoney.Dollars * 100) + RightHandMoney.Cents);
    return LeftHandMoneyTotalCents == RightHandMoneyTotalCents;
};
bool operator!=(const Money& LeftHandMoney, const Money& RightHandMoney){
    int LeftHandMoneyTotalCents = (LeftHandMoney.Dollars * 100) + LeftHandMoney.Cents;
    int RightHandMoneyTotalCents = ((RightHandMoney.Dollars * 100) + RightHandMoney.Cents);
    return LeftHandMoneyTotalCents != RightHandMoneyTotalCents;
};
bool operator>(const Money& LeftHandMoney, const Money& RightHandMoney){
    int LeftHandMoneyTotalCents = (LeftHandMoney.Dollars * 100) + LeftHandMoney.Cents;
    int RightHandMoneyTotalCents = ((RightHandMoney.Dollars * 100) + RightHandMoney.Cents);
    return LeftHandMoneyTotalCents > RightHandMoneyTotalCents;
};
bool operator<(const Money& LeftHandMoney, const Money& RightHandMoney){
    int LeftHandMoneyTotalCents = (LeftHandMoney.Dollars * 100) + LeftHandMoney.Cents;
    int RightHandMoneyTotalCents = ((RightHandMoney.Dollars * 100) + RightHandMoney.Cents);
    return LeftHandMoneyTotalCents < RightHandMoneyTotalCents;
};
bool operator>=(const Money& LeftHandMoney, const Money& RightHandMoney){
    int LeftHandMoneyTotalCents = (LeftHandMoney.Dollars * 100) + LeftHandMoney.Cents;
    int RightHandMoneyTotalCents = ((RightHandMoney.Dollars * 100) + RightHandMoney.Cents);
    return LeftHandMoneyTotalCents >= RightHandMoneyTotalCents;
};
bool operator<=(const Money& LeftHandMoney, const Money& RightHandMoney){
    int LeftHandMoneyTotalCents = (LeftHandMoney.Dollars * 100) + LeftHandMoney.Cents;
    int RightHandMoneyTotalCents = ((RightHandMoney.Dollars * 100) + RightHandMoney.Cents);
    return LeftHandMoneyTotalCents <= RightHandMoneyTotalCents;
};
