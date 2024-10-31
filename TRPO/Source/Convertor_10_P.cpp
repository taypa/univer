#include "Convertor_10_P.h"
#include <cmath>
#include <algorithm>

std::string Convertor_10_P::Do(double num, int p, int eps)
{
	std::string res, flt_res;

	//Add a minus
    if (num < 0)
		res += 45;

	//Translate to positive num
    num = sqrt(num * num);
	double part{0}, fracPart;


    fracPart = round(modf(num, &part) * pow(10, eps)) / pow(10, eps);
	

    res += IntToStr(int(num), p);

    if (num != int(num))
	{
        flt_res += FltToStr(fracPart, p, eps);
		if (!flt_res.empty())
		{
			res += 46;
			res += flt_res;
		}
	}

	return res;
};

char Convertor_10_P::IntToChar(int ch)
{
    char result = ch < 10 ? ch + 48 : ch + 55;
	return result;
};

std::string Convertor_10_P::IntToStr(int num, int p)
{
	std::string res;

    while (num / p > 0)
	{
        res += IntToChar(num % p);
        num /= p;
	}

    res += IntToChar(num % p);

    reverse(res.begin(), res.end());

	return res;
};

std::string Convertor_10_P::FltToStr(double num, int p, int eps)
{
	std::string res;

    for (size_t i = 0; i < eps; i++)
	{
        res += IntToChar(int(num * p));
        num = num * p - int(num * p);
	}

	while (!res.empty() && res.back() == '0')//удаление лишних нулей в конце
		res.pop_back();


	return res;
};
