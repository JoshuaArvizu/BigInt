#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase)
{
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input string will contain
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=35]
//  The input string may contain
//      - a negative sign ('-') to signify that the number is negative.
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase)
{
    if(setbase < 2 || setbase > 36)
    {
        throw InvalidBaseException();
    }
    /************* You complete *************/
    base = setbase;
    int digit, size = s.length() - 1, minSign = 0;
    if(s[0] == '-')
    {
        isPositive = false;
        // dont want to push the minus sign into the vector
        minSign = 1;
    }
    for(int i = size; i >= minSign; i--)
    {
        if(isalpha(s[i]) > 0)
        {
            digit = (int) (s[i] - 65) + 10;
            vec.push_back(digit);
        }
        else
        {
            digit = (int) s[i]-48;
            vec.push_back(digit);
        }
    }
}


/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input,int setbase)
{
    if(setbase < 2 || setbase > 36)
    {
        throw InvalidBaseException();
    }
    /************* You complete *************/
    base = setbase;
    if(input < 0)
    {
        isPositive = false;
        input *= -1;
    }

    int temp = input;
    while(input != 0)
    {
        input /= base;
        vec.push_back(temp%base);
        temp = input;
    }
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
// (You can also think of this function as the same as the assignment operator (=))
// (but without a return statement because you are overriding the current object)
*/
BigInt::BigInt(const BigInt &b)
{
    /************* You complete *************/
    base = b.base;
    isPositive = b.isPositive;

    int size = b.vec.size();
    for(int i = 0; i < size; i++)
    {
        vec.push_back(b.vec[i]);
    }
}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  OVERRIDING a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){
    /************* You complete *************/
    // incase of self assignment
    if(this == &b)
    {
        return *this;
    }
    base = b.base;
    isPositive = b.isPositive;
    // clear existing data
    vec.clear();
    int size = b.vec.size();
    for(int i = 0; i < size; i++)
    {
        vec.push_back(b.vec[i]);
    }
    return *this; 
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){

    /************* You complete *************/

  
  
  
  

  return "";//for now
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const{

    /************* You complete *************/


  
  
  
  
 
  return 0;//for now
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

    //HINT:
    //1. do NOT call the to_int() or to_string() function
    //2. do NOT convert bigInt to other datatypes first (e.g., long long, int)
    
    //First let's compare the signs
    //    - if the signs aren't the same,
    //              how do you know which one is larger?

    //If they have the same sign, let's compare their vec sizes 
    //    - what if both are positive, but a's vec is larger (a or b is larger?)
    //    - other cases?
    
    //If they have the same vec size, let's compare their digits one by one
    // Starting from the most-significant digits. --> in what vector position?
    // Remember that the BigInt vectors are in reverse order!
    //    - what if both are positive, but the digit of a is greater than that of b (a or b is larger?)
    //    - other cases?
    
    //If ALL digits are the same, then they MUST be equal!!
    if(!b.isPositive && this->isPositive)
    {
        return 1;
    }
    else if(b.isPositive && !this->isPositive)
    {
        return -1;
    }
    // when we get here we know the two numbers have the same sign (either both pos or negative)
    if(b.vec.size() > this->vec.size())
    {
        if(!b.isPositive && !this->isPositive)
        {
            return 1;
        }
        return -1;
    }
    else if(b.vec.size() < this->vec.size())
    {
        if(!b.isPositive && !this->isPositive)
        {
            return -1;
        }
        return 1;
    }
    else
    {
        int size = b.vec.size() - 1;
        // since we put the integers in reverse order we have to start with the nth-1 index of the array
        for(int i = size; i >= 0; i--)
        {
            if(b.vec[i] > this->vec[i])
            {
                // if num is negative smaller is greater
                if(!this->isPositive)
                {
                    return 1;
                }
                return -1;
            }
            else if(b.vec[i] < this->vec[i])
            {
                if(!this->isPositive)
                {
                    return -1;
                }
                return 1;
            }
        }
    }
    return 0;
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
    /************ You complete ************/
    if(a.compare(b) == 0)
    {
        return true;
    }
    return false;
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
    /************* You complete ************/
    if(a.compare(b) != 0)
    {
        return true;
    }
    return false;
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
    /************* You complete *************/
    if(a.compare(b) == 0 || a.compare(b) == -1)
    {
        return true;
    }
    return false;
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
    /************* You complete *************/
    if(a.compare(b) == 1 || a.compare(b) == 0)
    {
        return true;
    }
    return false;
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
    /************* You complete *************/
    if(a.compare(b) == 1)
    {
        return true;
    }
    return false;
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
    /************* You complete *************/
    if(a.compare(b) == -1)
    {
        return true;
    }
    return false;
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  
  


  return a;//for now
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

    

  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  
  
  

  return a;//for now
}


/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/


    
    
    
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){

    /************* You complete *************/

    
    

  return a;//for now
}



/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/


    

  
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  

    


    return a;//for now
}


/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/



    
  
  
  
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
  

    
    
    return a;//for now
}


/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    /************* You complete *************/


  
  
  
  
    return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

    /************* You complete *************/



  
  

}



/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
  
  
  
  
  
    return a;//for now
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/


  
  
  
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    /************* You complete *************/
  
  

  
  
    return a;//for now
}


/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/


  
  
    return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF SANITY CHECK FUNCTIONS
//YOU CAN USE THEM, BUT DO NOT CHANGE ANYTHING
//THESE FUNCTIONS ARE COMPLETE.
//******************************************************************
void BigInt::printVecItems(){
  cout<<"[";
  for(size_t i = 0;i<vec.size();i++){
    cout<<vec[i];
    if(i < vec.size()-1){
      cout<<",";
    }
  }
  cout<<"]"<<endl;
}

bool BigInt::getSign(){
	return isPositive;
}

int BigInt::getBase(){
	return base;
}
//******************************************************************
//END OF SANITY CHECKS SECTION
//******************************************************************