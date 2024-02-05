#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class BigInt
{
private:
	string value;
	bool neg;
public:
	BigInt(int val = 0);
	BigInt(const string& text);
	BigInt(const BigInt& copy);
	BigInt operator+(const BigInt& val) const;
	BigInt operator+(int val) const;
	BigInt operator-(const BigInt& val) const;
	BigInt operator-(int val) const;
	BigInt operator*(const BigInt& val) const;
	BigInt operator*(int val) const;
	BigInt operator+=(const BigInt& rhs);
	BigInt operator-=(const BigInt& rhs);
	BigInt operator*=(const BigInt& rhs);
	bool operator==(const BigInt& val) const;
	bool operator==(const int val) const;
	bool operator==(const char* val) const;
	bool operator!=(const BigInt& val) const;
	bool operator<(const BigInt& val) const;
	bool operator<(int val) const;
	bool operator<=(const BigInt& val) const;
	bool operator>(const BigInt& val) const;
	bool operator>(int val) const;
	bool operator>=(const BigInt& val) const;
	BigInt& operator++();
	BigInt operator++(int);
	BigInt& operator--();
	BigInt operator--(int);
	BigInt power(BigInt base, BigInt pwr);
	BigInt operator/(BigInt val) const;
	BigInt operator/(int val) const;
	BigInt Mod(BigInt base, BigInt with);
	BigInt random(const BigInt& start, const BigInt& end) const;
	operator string();
	operator int();
	~BigInt();
	string add(string num1, string num2) const;
	string subtract(string num1, string num2) const;
	string multiply(string num1, string num2) const;
	friend ostream& operator<<(ostream& output, const BigInt& val);
	friend istream& operator>>(istream& input, BigInt& val);
};

char na = '0';

string BigInt::add(string num1, string num2) const
{
	string result = "";
	int carry = 0;
	int sum = 0;
	int i = num1.size();
	i--;
	int j = num2.size();
	j--;

	while (i >= 0 || j >= 0 || carry != 0)
	{
		sum = carry;
		if (i >= 0)
		{
			sum += num1[i] - na;
			i--;
		}
		if (j >= 0)
		{
			sum += num2[j] - na;
			j--;
		}
		carry = sum / 10;
		sum = sum % 10;
		result += (char)(sum + na);
	}
	for (auto it1 = result.begin(), it2 = prev(result.end()); it1 < it2; ++it1, --it2)
	{
		swap(*it1, *it2);
	}
	return result;
}

string BigInt::subtract(string num1, string num2) const
{
	string result = "";
	int bor = 0;
	int diff = 0;
	int i = num1.size() - 1;
	int j = num2.size() - 1;

	while (i >= 0 || j >= 0 || bor != 0)
	{
		diff = bor;
		if (i >= 0)
		{
			diff += num1[i] - na;
			i--;
		}
		if (j >= 0)
		{
			diff -= num2[j] - na;
			j--;
		}
		if (diff < 0)
		{
			diff += 10;
			bor = -1;
		}
		else
		{
			bor = 0;
		}
		result += (char)(diff + na);
	}

	for (auto it1 = result.begin(), it2 = prev(result.end()); it1 < it2; ++it1, --it2)
		swap(*it1, *it2);
	while (result.size() > 1 && result[0] == na)
		result.erase(result.begin());
	return result;
}

string BigInt::multiply(string num1, string num2) const
{
	string result(num1.size() + num2.size(), na);
	for (int i = num1.size() - 1; i >= 0; i--)
	{
		for (int j = num2.size() - 1; j >= 0; j--)
		{
			int product = (num1[i] - na) * (num2[j] - na) + (result[i + j + 1] - na);
			result[i + j + 1] = product % 10 + na;
			result[i + j] += product / 10;
		}
	}
	while (result.size() > 1 && result[0] == na)
	{
		result.erase(result.begin());
	}
	return result;
}

BigInt::BigInt(int val)
{
	if (val >= 0)
		neg = 0;
	else
	{
		neg = 1;
		val *= -1;
	}
	value = to_string(val);
}

BigInt::BigInt(const string& text)
{
	if (text[0] != '-')
	{
		neg = 0;
		value = text;
	}
	else
	{
		neg = 1;
		value = text.substr(1);
	}
}

BigInt::BigInt(const BigInt& copy)
{
	value = copy.value;
	neg = copy.neg;
}

BigInt BigInt::operator+(const BigInt& val) const
{
	BigInt result;
	if (neg == val.neg)
	{
		result.value = add(value, val.value);
		result.neg = neg;
	}
	else
	{
		if (value == val.value)
		{
			result.value = "0";
			result.neg = 0;
		}
		else if (value.size() > val.value.size() || (value.size() == val.value.size() && value > val.value))
		{
			result.value = subtract(value, val.value);
			result.neg = neg;
		}
		else
		{
			result.value = subtract(val.value, value);
			result.neg = val.neg;
		}
	}
	return result;
}

BigInt BigInt::operator+(int val) const
{
	return *this + BigInt(val);
}

BigInt BigInt::operator-(const BigInt& val) const
{
	BigInt result;
	if (neg != val.neg)
	{
		result.value = add(value, val.value);
		result.neg = neg;
	}
	else
	{
		if (value == val.value)
		{
			result.value = "0";
			result.neg = 0;
		}
		else if (value.size() > val.value.size() || (value.size() == val.value.size() && value > val.value))
		{
			result.value = subtract(value, val.value);
			result.neg = neg;
		}
		else
		{
			result.value = subtract(val.value, value);
			result.neg = !neg;
		}
	}
	return result;
}

BigInt BigInt::operator-(int val) const
{
	return *this - BigInt(val);
}

BigInt BigInt::operator*(const BigInt& val) const
{
	BigInt result;
	result.value = multiply(value, val.value);
	if (result.value == "0")
		result.neg = 0;
	else
		result.neg = neg != val.neg;
	return result;
}

BigInt BigInt::operator+=(const BigInt& rhs)
{
	*this = *this + rhs;
	return *this;
}

BigInt BigInt::operator-=(const BigInt& rhs)
{
	*this = *this - rhs;
	return *this;
}

BigInt BigInt::operator*=(const BigInt& rhs)
{
	*this = *this * rhs;
	return *this;
}

bool BigInt::operator==(const BigInt& val) const
{
	return neg == val.neg && value == val.value;
}

bool BigInt::operator==(const char* val) const
{
	return *this == BigInt(val);
}

bool BigInt::operator!=(const BigInt& val) const
{
	return !(*this == val);
}

bool BigInt::operator<(const BigInt& val) const
{
	if (neg != val.neg)
	{
		return neg;
	}
	else if (value.size() != val.value.size())
	{
		return value.size() < val.value.size();
	}
	else
	{
		return value < val.value;
	}
}

bool BigInt::operator<=(const BigInt& val) const
{
	return *this < val || *this == val;
}

bool BigInt::operator>(const BigInt& val) const
{
	return !(*this <= val);
}

bool BigInt::operator>=(const BigInt& val) const
{
	return !(*this < val);
}

BigInt& BigInt::operator++()
{
	*this += 1;
	return *this;
}

BigInt BigInt::operator++(int)
{
	BigInt temp = *this;
	++*this;
	return temp;
}

BigInt& BigInt::operator--()
{
	*this -= 1;
	return *this;
}

BigInt BigInt::operator--(int)
{
	BigInt temp = *this;
	--*this;
	return temp;
}

BigInt::operator string()
{
	if (neg)
	{
		return "-" + value;
	}
	else
	{
		return value;
	}
}

BigInt::operator int()
{
	return value.size();
}

BigInt::~BigInt()
{
}


ostream& operator<<(ostream& output, const BigInt& val)
{
	if (val.neg)
	{
		output << "-";
	}
	output << val.value;
	return output;
}

istream& operator>>(istream& input, BigInt& val)
{
	string str;
	input >> str;
	val = BigInt(str);
	return input;
}

BigInt BigInt::power(BigInt base, BigInt pwr)
{
	BigInt i = 0;
	BigInt result = 1;
	while (pwr != i)
	{
		result *= base;
		pwr--;

	}
	return result;
}

BigInt BigInt::operator/(int val) const
{
	return *this / BigInt(val);
}

BigInt BigInt::operator/(BigInt val) const
{
	BigInt result;
	BigInt temp = *this;
	if (temp < val)
	{
		result.value = "0";
		result.neg = 0;
		return result;
	}
	else if (temp == val)
	{
		result.value = "1";
		result.neg = 0;
		return result;
	}
	else if (val.value == "1")
	{
		result.value = temp.value;
		result.neg = temp.neg != val.neg;
		return result;
	}
	else if (val.value == "0")
	{
		cout << "Error: Division by zero" << endl;
		exit(1);
	}
	else
	{
		result.value = "";
		result.neg = temp.neg != val.neg;
		while (temp >= val)
		{
			int i = 0;
			while (temp >= val * (i + 1))
			{
				i++;
			}
			temp -= val * i;
			result.value += (char)(i + na);
		}
	}
	return result;
}


bool BigInt::operator<(int val) const
{
	return *this < BigInt(val);
}

bool BigInt::operator>(int val) const
{
	return *this > BigInt(val);
}


BigInt BigInt::Mod(BigInt base, BigInt with)
{
	int base_len = base.value.size();
	int with_len = with.value.size();
	if (base_len > with_len) {
		string temp = "";
		for (int i = base_len - with_len; base.value[i] != '\0'; i++)
		{
			temp += base.value[i];
		}
		base = temp;
	}
	BigInt result = base - (base / with) * with;

	return result;
}

BigInt BigInt::operator*(int val) const
{
	return *this * BigInt(val);
}

BigInt BigInt::random(const BigInt& start, const BigInt& end) const
{
	if (start > end || start.neg || end.neg)
		return BigInt(0);
	BigInt range = end - start + 1;
	string range_str = range;
	int digits = range_str.size();
	BigInt random(0);

	do
	{
		random.value = "";
		for (int i = 0; i < digits; i++)
		{
			int digit = rand() % 10;
			char ch = digit + na;
			random.value += ch;
		}

		while (random.value.size() > 1 && random.value[0] == na)

			random.value.erase(random.value.begin());
	} while (random<start || random>end);
	return random;
}

bool BigInt::operator==(const int val) const
{
	return *this == BigInt(val);
}