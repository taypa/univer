#include "Convertor_P_10.h"
#include <cmath>

double Convertor_P_10::ConvertFrac(std::string p_num, int p, int eps)
{
	double res = 0;

    for (int i = 1; i <= p_num.length(); i++)
        res += CharToNum(p_num[i - 1]) * pow(p, i * (-1));

    res = floor(res * pow(10, eps) + .5) / pow(10, eps);//округление до требуемой точности но бывает не очень хорошо

	return res;
};

int Convertor_P_10::CharToNum(char ch)
{
	int res = ch < 58 ? ch - 48 : ch - 55;
	return res;
};

double Convertor_P_10::ConvertInt(std::string p_num, int p)
{
	double res = 0;

    for (size_t i{ p_num.length() }; i > 0; i--)
        res += CharToNum(p_num[p_num.length() - i]) * pow(p, i - 1);

	return res;
};

double Convertor_P_10::Convert(std::string p_num, int p, int eps)
{
	double res = 0;
    bool is_positive = p_num[0] == '-' ? 0 : 1;

	if (!is_positive)
        p_num.erase(0, 1);

    int pos_del = p_num.find('.');
    std::string whole_part = p_num.substr(0, pos_del);
    std::string frac_part;

    res += ConvertInt(whole_part, p);

    if (pos_del != -1)
	{
        frac_part = p_num.substr(pos_del + 1, p_num.length());
        res += ConvertFrac(frac_part, p, eps);
	}

	if (!is_positive)
		res *= -1;

	return res;
}
