#include "BigInt.h"
#include <iostream>
using namespace std;

int main()
{
BigInt a("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
BigInt b("9876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210");

//addition
BigInt c = a + b;
cout << "Addition: " << c << endl;

//subtraction
c = a - b;
cout << "Subtraction: " << c << endl;

//multiplication
c = a * b;
cout << "Multiplication: " << c << endl;

//division
c = a / b;
cout << "Division: " << c << endl;

//power
c = a.power(a, 2);
cout << "Power: " << c << endl;

//modulus
c = a.Mod(a, b);
cout << "Modulus: " << c << endl;

//increment/decrement
++a;
cout << "Increment: " << a << endl;
--a;
cout << "Decrement: " << a << endl;

//comparison
cout << "Equality: " << (a == b) << endl;
cout << "Inequality: " << (a != b) << endl;
cout << "Less than: " << (a < b) << endl;
cout << "Greater than: " << (a > b) << endl;
cout << "Less than or equal to: " << (a <= b) << endl;
cout << "Greater than or equal to: " << (a >= b) << endl;

//random number generation

BigInt start("10000000000000000000");
BigInt end("20000000000000000000");
BigInt randomNum = a.random(start, end);
cout << "Random number between " << start << " and " << end << ": " << randomNum << endl;

  
return 0;
}
