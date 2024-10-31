#include "Fraction.h"

int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

Fraction::Fraction(int numer, int denom) 
{
	int NOD = gcd(abs(numer), abs(denom));
	numerator_ = numer / NOD;
	denominator_ = denom / NOD;
}

Fraction::Fraction(std::string frac)
{
	int pos = frac.find("/");

	int numer = stoi(frac.substr(0, pos));
	int denom = stoi(frac.substr(pos + 1, frac.length() - pos));

	int NOD = gcd(numer, denom);

	numerator_ = numer / NOD;
	denominator_ = denom / NOD;
}
Fraction::Fraction(const Fraction& copy)
{
	this->numerator_ = copy.numerator_;
	this->denominator_ = copy.denominator_;
}

Fraction Fraction::operator + (const Fraction& frac)
{
	return Fraction(this->numerator_ * frac.denominator_ + this->denominator_ * frac.numerator_,
					this->denominator_ * frac.denominator_);
}

Fraction Fraction::operator - (const Fraction& frac)
{
	return Fraction(this->numerator_ * frac.denominator_ - this->denominator_ * frac.numerator_,
		this->denominator_ * frac.denominator_);
}

Fraction Fraction::operator / (const Fraction& frac)
{
	return Fraction(this->numerator_ * frac.denominator_, frac.numerator_ * this->denominator_);
}

Fraction Fraction::operator * (const Fraction& frac)
{
	return Fraction(this->numerator_ * frac.numerator_, this->denominator_ * frac.denominator_);
}

Fraction Fraction::Square()
{
	return Fraction(this->numerator_ * this->numerator_, this->denominator_ * this->denominator_);
}

Fraction Fraction::Reverse()
{
	return Fraction(this->denominator_, this->numerator_);
}

Fraction Fraction::Minus()
{
	return Fraction(0 - this->numerator_, this->denominator_);
}

bool Fraction::operator == (Fraction frac)
{
	return (this->numerator_ == frac.numerator_) && (this->denominator_ == frac.denominator_);
}

bool Fraction::operator >(Fraction frac)
{
	return (this->numerator_ * frac.denominator_) > (frac.numerator_ * this->denominator_);
}

int Fraction::GetNumerator()
{
	return this->numerator_;
}

int Fraction::GetDenominator() 
{
	return this->denominator_;
}

std::string Fraction::GetNumerString()
{
	return std::to_string(this->numerator_);
}

std::string Fraction::GetDenomString()
{
	return std::to_string(this->denominator_);
}

std::string Fraction::GetFracString()
{
	return GetNumerString() + "/" + GetDenomString();
}