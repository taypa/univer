#include "Number.h"

Number::Number(){}

Number::Number(std::string num, unsigned p, unsigned eps) : num_(num), p_(p), eps_(eps)
{}

Number::Number(const Number &copy)
{
    this->num_ = copy.num_;
    this->p_ = copy.p_;
    this->eps_ = copy.eps_;
}


Number Number::operator + (const Number& num)
{
	Convertor_P_10 elem1, elem2;
    double number1 = elem1.Convert(this->num_, this->p_, this->eps_);
    double number2 = elem2.Convert(num.num_, num.p_, num.eps_);

    std::string res = Convertor_10_P::Do(number1 + number2, num.p_, std::min(this->eps_, num.eps_));

    return Number(res,  num.p_, std::min(this->eps_, num.eps_));

}

Number Number::operator * (const Number& num)
{
	Convertor_P_10 elem1, elem2;
    double number1 = elem1.Convert(this->num_, this->p_, this->eps_);
    double number2 = elem2.Convert(num.num_, num.p_, num.eps_);

    std::string res = Convertor_10_P::Do(number1 * number2, num.p_, std::min(this->eps_, num.eps_));

    return Number(res,  num.p_, std::min(this->eps_, num.eps_));
}

Number Number::operator - (const Number& num)
{
	Convertor_P_10 elem1, elem2;
    double number1 = elem1.Convert(this->num_, this->p_, this->eps_);
    double number2 = elem2.Convert(num.num_, num.p_, num.eps_);

    std::string res = Convertor_10_P::Do(number1 - number2, num.p_, std::min(this->eps_, num.eps_));

    return Number(res,  num.p_, std::min(this->eps_, num.eps_));
}

Number Number::operator / (const Number& num)
{
	Convertor_P_10 elem1, elem2;
    double number1 = elem1.Convert(this->num_, this->p_, this->eps_);
    double number2 = elem2.Convert(num.num_, num.p_, num.eps_);

    std::string res = Convertor_10_P::Do(number1 / number2, num.p_, std::min(this->eps_, num.eps_));

    return Number(res,  num.p_, std::min(this->eps_, num.eps_));
}

Number Number::reverse()
{
	Convertor_P_10 elem;
    double number = elem.Convert(this->num_, this->p_, this->eps_);

    std::string res = Convertor_10_P::Do(1 / number, this->p_, this->eps_);

    return Number(res, this->p_, this->eps_);
}

Number Number::square()
{
	Convertor_P_10 elem;
    double number = elem.Convert(this->num_, this->p_, this->eps_);

    std::string res = Convertor_10_P::Do(number * number, this->p_, this->eps_);

    return Number(res, this->p_, this->eps_);
}

void Number::set_num(std::string num_)
{
    this->num_ = num_;
}

void Number::set_p(unsigned p_)
{
    this->p_ = p_;
}

void Number::set_eps(unsigned eps_)
{
    this->eps_ = eps_;
}

std::string Number::get_num()
{
    return this->num_;
}

unsigned Number::get_p()
{
    return this->p_;
}

unsigned Number::get_eps()
{
    return this->eps_;
}
