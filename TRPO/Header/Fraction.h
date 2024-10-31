#ifndef FRACTION_H
#define FRACTION_H
#pragma once

#include <iostream>
#include <string>

class Fraction
{
private:
	int numerator_, denominator_;

public:
	Fraction(int a, int b);

	Fraction(std::string frac);

	Fraction (const Fraction& copy);

	Fraction operator + (const Fraction& frac);

	Fraction operator - (const Fraction& frac);

	Fraction operator / (const Fraction& frac);

	Fraction operator * (const Fraction& frac);

	Fraction Square();

	Fraction Reverse();

	Fraction Minus();

	bool operator == (Fraction frac);

	bool operator > (Fraction frac);

	int GetNumerator();
	
	int GetDenominator();

	std::string GetNumerString();

	std::string GetDenomString();

	std::string GetFracString();
};

#endif // !FRACTION_H

