#include <iostream>
#pragma once
#ifndef CONVERTOR_P_10
#define CONVERTOR_P_10
class Convertor_P_10
{
public:
	/*
	Transform the frac part to demical number system
		P_num - number
		P - the base of number system
		eps - accuracy
	*/
    static double ConvertFrac(std::string p_num, int p, int eps);

	/*
	Transform the symbol to int
		ch - symbol
	*/
    static int CharToNum(char ch);

	/*
	Transform the whole part to decimal number system
		P_num - number
		P - the base of number system
	*/
    static double ConvertInt(std::string p_num, int p);

	/*
	Transform the number from other number system to 10 number system
		P_num - number
		P-the base of number system
		eps - accuracy
	*/
    static double Convert(std::string p_num, int p, int eps);
};
#endif
