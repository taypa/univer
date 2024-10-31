#ifndef COMPLEX_H
#define COMPLEX_H
#pragma once
#include <iostream>
#include <string>
#include <math.h>
class Complex
{
private:
	double real_{ 0.0 }, image_{ 0.0 };
	const double PI_ = 3.141592653589793;

public:
	Complex(double real, double image);

	Complex(std::string number);

	Complex(const Complex& copy);

	Complex operator + (const Complex& number);

	Complex operator - (const Complex& number);

	Complex operator * (const Complex& number);

	Complex operator / (const Complex& number);

	Complex Square();

	Complex Reverse();

	Complex Minus();

	double Module();

	double AngleRadians();

	double AngleDegree();

	Complex Degree(int n);

	Complex Root(int n, int i);

	bool operator == (const Complex& number);

	bool operator != (const Complex& number);

	int GetRe();

	int GetIm();

	std::string GetReString();

	std::string GetImString();

	std::string GetNumString();
};


#endif // !COMPLEX_H