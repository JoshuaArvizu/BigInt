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
    if(input == 0)
    {
        vec.push_back(input);
    }
    int temp = input;
    // convert num to any base
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
    string number = "";
    char digit;
    int size = vec.size();
    bool leadingZero = false;
    if(vec[size - 1] == 0)
    {
        leadingZero = true;
    }
    if(!isPositive && !leadingZero)
    {
        number += "-";
    }
    for(int i = size - 1; i >= 0; i--)
    {
        if(vec[i] >= 10)
        {
            digit = (char) ((vec[i] + 65) - 10);
        }
        else
        {
            digit = (char) (vec[i]+48);
        }
        // answer should not have leading zeros
        if(leadingZero && digit == '0')
        {
            continue;
        }
        else
        {
            // adds negative if needed and only adds it once
            if(!isPositive && leadingZero)
            {
                number += "-";
            }
            leadingZero = false;
            number += digit;
        }
    }
    if(leadingZero)
    {
        return "0";
    }
    return number;
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
    int bigInt = 0, size = vec.size();
    // it not long long will never get INT_MAX to compare properly
    long long result = 0;

    for(int i = 0; i < size; i++)
    {
        result = (vec[i] * pow(base, i));
        result += bigInt;
        if(result >= INT_MAX && isPositive)
        {
            return INT_MAX;
        }
        if(result <= INT_MIN && !isPositive)
        {
            return INT_MIN;
        }
        bigInt += (vec[i] * pow(base, i));
    }
    if(!isPositive)
    {
        bigInt *= -1;
    }
    return bigInt;
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

    if(!b.isPositive && isPositive)
    {
        return 1;
    }
    else if(b.isPositive && !isPositive)
    {
        return -1;
    }

    if(b.vec.size() > vec.size())
    {
        if(!b.isPositive && !isPositive)
        {
            return 1;
        }
        return -1;
    }
    else if(b.vec.size() < vec.size())
    {
        if(!b.isPositive && !isPositive)
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
            if(b.vec[i] > vec[i])
            {
                // if num is negative smaller is greater
                if(!isPositive)
                {
                    return 1;
                }
                return -1;
            }
            else if(b.vec[i] < vec[i])
            {
                if(!isPositive)
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
    BigInt temp = a;
    temp += b;
    return temp;//for now
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
    if(isPositive && !b.isPositive)
    {
        BigInt temp = b;
        temp.isPositive = true;
        return *this -= temp;
    }
    if(!isPositive && b.isPositive)
    {
        bool signChange = false;
        isPositive = true;
        if(*this < b)
        {
            signChange = true;
        }
        *this -= b;
        if(signChange)
        {
            isPositive = true;
        }
        else
        {
            isPositive = false;
        }
        return *this;
    }
    int carry = 0, remainder, index = max(vec.size(), b.vec.size()), valA = 0, valB = 0;
    for(int i = 0; i < index; i++)
    {
        // make sure the memory we access is valid
        if(i < (int) b.vec.size())
        {
            valB = b.vec[i];
        }
        else
        {
            valB = 0;
        }
        if(i < (int) vec.size())
        {
               valA = vec[i];
        }
        else
        {
            valA = 0;
        }
        // addition algo
        if(valA + carry > valA)
        {
            valA += carry;
            carry = 0;
        }
        if(valA + valB >= base)
        {
            carry = valA + valB + carry;
            remainder = carry % base;
            carry /= base;
            if(i < (int) vec.size())
            {
                vec[i] = remainder;
            }
            else
            {
                vec.push_back(remainder);
            }
        }
        else
        {
            if(i < (int) vec.size())
            {
                vec[i] = valA + valB;
            }
            else
            {
                vec.push_back(valA+valB);
            }
        }
    }
    if(carry != 0)
    {
        vec.push_back(carry);
    }

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
    BigInt temp = a;
    temp -= b;
    return temp;
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
    int dif = 0, size = max(b.vec.size(), vec.size()), mode = 0;
    bool borrowed = false, aLessThanB = false;
    // in this case if "a" has less digits then "b" we have to use push_back
    // because we have to return a and the vec in a has to be able to contain all the digits of the subtraction
    for(int i = vec.size(); i < size; i++)
    {
        vec.push_back(0);
    }
    if(*this < b)
    {
        if(!isPositive && !b.isPositive)
        {
            mode = 2;
        }
        else if(!isPositive && b.isPositive)
        {
            aLessThanB = true;
            mode = 3;
        }
        else
        {
            isPositive = false;
            mode = 1;
        }
    }
    else if(*this > b)
    {
        if(isPositive && b.isPositive)
        {
            mode = 2;
        }
        else if(!isPositive && !b.isPositive)
        {
            isPositive = true;
            mode = 1;
        }
        else if(isPositive && !b.isPositive)
        {
            mode = 3;
        }
    }
    int valA = 0, valB = 0;
    for(int i = 0; i < size; i++)
    {
        if(i < (int) b.vec.size())
        {
            valB = b.vec[i];
        }
        else
        {
            valB = 0;
        }
        if(i < (int) vec.size())
        {
               valA = vec[i];
        }
        else
        {
            valA = 0;
        }
        // make sure the memory we access exist
        if(i < (int) vec.size())
        {
            switch(mode)
            {
                case 1:
                    dif = valB - valA;
                    break;
                case 2:
                    dif = valA - valB;
                    break;
                case 3:
                    if(aLessThanB)
                    {
                        isPositive = true;
                        *this += b;
                        isPositive = false;
                    }
                    else
                    {
                        BigInt temp = b;
                        temp.isPositive = true;
                        *this += temp;
                    }
                    return *this;
                default:
                    dif = valA - valB;
            }
        }
        else
        {
            if(*this < b && isPositive && b.isPositive)
            {
                dif = b.vec[i];
            }
            else if(*this > b && isPositive && b.isPositive)
            {
                dif = vec[i];
            }
        }
        // when borrow occurs subtract 1 from that column
        if(borrowed)
        {
            borrowed = false;
            dif--;
        }
        // less than 0 means subtraction requires a borrow
        if(dif < 0)
        {
            dif += base;
            borrowed = true;
        }
        vec[i] = dif;
    }
    if(vec[vec.size()-1] == 0)
    {
        for(unsigned int i = vec.size()-1; i > 0; i--)
        {
            if(vec[i] == 0)
            {
                vec.erase(vec.begin() + (vec.size()-1));
            }
            else
            {
                break;
            }
        }
    }
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
    BigInt temp = a;
    temp *= b;
    return temp;
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
    BigInt total(base);
    int carry = 0, remainder = 0;
    total.vec.push_back(0);

    for(int i = 0; i < (int) b.vec.size(); i++)
    {
        BigInt temp(base);
        for(int k = 0; k < i; k++)
        {
            temp.vec.push_back(0);
        }
        for(int j = 0; j < (int) vec.size(); j++)
        {
            if(vec[j] * b.vec[i] >= base)
            {
                carry = vec[j] * b.vec[i] + carry;
                remainder = carry % base;
                carry /= base;
                temp.vec.push_back(remainder);
            }
            else
            {
                temp.vec.push_back(vec[j] * b.vec[i] + carry);
                carry = 0;
            }
        }
        if(carry != 0)
        {
            temp.vec.push_back(carry);
        }
        carry = 0;
        total += temp;
    }
    if((!isPositive && b.isPositive) || (isPositive && !b.isPositive))
    {
        total.isPositive = false;
    }
    return *this = total;
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
    BigInt temp = a;
    temp /= b;
    return temp;
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
    BigInt quotient(base), remainder(base);
    divisionMain(b, quotient, remainder);
    *this = quotient;
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
    BigInt temp = a;
    temp %= b;
    return temp;
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
    BigInt quotient(base), remainder(base);
    divisionMain(b, quotient, remainder);
    *this = remainder;
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
    BigInt divisor = b, dividend = *this, zero(0, base), one(1, base);
    divisor.isPositive = true;
    dividend.isPositive = true;

    if(*this == zero)
    {
        quotient.vec.push_back(0);
        remainder.vec.push_back(0);
    }
    else if(dividend == divisor)
    {
        quotient.vec.push_back(1);
        remainder.vec.push_back(0);
    }
    else if(divisor == one)
    {
        quotient = dividend;
        remainder.vec.push_back(0);
    }
    else
    {
        // pos starts counting from rightmost
        // div_seq starts from leftmost
        int position = dividend.vec.size() - 1, dividendSize = dividend.vec.size();
        // seq = sequence
        BigInt dividend_seq(base);
        dividend_seq.vec.push_back(dividend.vec[position]);

        while(position < dividendSize)
        {
            while(dividend_seq < divisor && position >= 0)
            {
                if(position != dividendSize)
                {
                    quotient.vec.insert(quotient.vec.begin() + 0, 0);
                }
                position--;
                if(position < 0)
                {
                    break;
                }
                dividend_seq.vec.insert(dividend_seq.vec.begin() + 0, dividend.vec[position]);
                // if dividend_seq vector size is greater than divisor, but it contains all zeros pop one zero so comparison operators work
                if((dividend_seq.vec.size() >= divisor.vec.size()) && (dividend_seq.vec[dividend_seq.vec.size()-1] == 0))
                {
                    dividend_seq.vec.erase(dividend_seq.vec.begin() + (dividend_seq.vec.size() - 1));
                }
            }
            if(position < 0)
            {
                break;
            }
            int times = 0;
            while(dividend_seq >= divisor)
            {
                dividend_seq -= divisor;
                times++;
            }
            quotient.vec.insert(quotient.vec.begin() + 0, times);
            if(dividend_seq == zero)
            {
                dividend_seq.vec.clear();
            }
            if(position < dividendSize && position != 0)
            {
                dividend_seq.vec.insert(dividend_seq.vec.begin() + 0, dividend.vec[position-1]);
            }
            position--;
        }
        if(dividend_seq.vec.empty())
        {
            dividend_seq.vec.push_back(0);
        }
        remainder = dividend_seq;
        if(remainder == zero)
        {
            remainder.isPositive = true;
        }
        else
        {
            remainder.isPositive = isPositive;
        }
    }
    if((remainder != zero) && (remainder.vec.size() > 0))
    {
        quotient.vec.push_back(0);
    }
    if((!isPositive && b.isPositive) || (isPositive && !b.isPositive))
    {
        quotient.isPositive = false;
    }
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
    BigInt temp = a;
    temp.exponentiation(b);
    return temp;
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
    BigInt x = *this, n = b, one("1", base), zero(0, base), two(2, base);

    if(n == one)
    {
        return *this;
    }
    else if(x == one)
    {
        one.isPositive = isPositive;
        return *this = one;
    }
    else if(n == zero)
    {
        x.vec.clear();
        x.vec.push_back(1);
        x.isPositive = true;
        return *this = x;
    }
    else
    {
        while(n != zero)
        {
            if(n % two == zero)
            {
                x *= x;
                n /= two;
            }
            else
            {
                x *= x;
                n = (n-one) / two;
            }
        }
    }

    return *this = x;
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