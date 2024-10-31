#include<iostream>
#include <string>
#include "Convertor_10_P.h"
#include "Convertor_P_10.h"
#ifndef NUMBER
#define NUMBER
#pragma once


class Number
{
private:
    std::string num_ = "0";
    unsigned p_{10}, eps_{0};

public:
	Number();

	Number(std::string num, unsigned p, unsigned eps);

	Number(const Number& copy);


	Number operator + (const Number& num);

	Number operator * (const Number& num);

	Number operator - (const Number& num);

	Number operator / (const Number& num);

	Number reverse();

	Number square();


	void set_num(std::string num_);

	void set_p(unsigned p_);

	void set_eps(unsigned eps_);


	std::string get_num();

	unsigned get_p();

	unsigned get_eps();

};

#endif
