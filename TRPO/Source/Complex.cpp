#include "Complex.h"

Complex::Complex(double real, double image)
{
	this->real_ = real;
	this->image_ = image;
}

Complex::Complex(std::string number) //?
{
	bool IsMinus;
	int pos_i;
	int pos = number.find("+");
	IsMinus = false;
	if (pos == -1)//если нет плюса в виде a+bi
	{
		pos = number.find("-");
		if(pos != -1)//если есть минус в виде a-bi
			IsMinus = true;
	}
	real_ = stoi(number.substr(0, pos));
	image_ = stoi(number.substr(pos + 1, number.length() - pos));
	if (IsMinus)
		image_ *= -1;
}

Complex::Complex(const Complex& copy)
{
	this->real_ = copy.real_;
	this->image_ = copy.image_;
}

Complex Complex::operator + (const Complex& number)
{
	return Complex(this->real_ + number.real_, this->image_ + number.image_);
}

Complex Complex::operator - (const Complex& number)
{
	return Complex(this->real_ - number.real_, this->image_ - number.image_);
}

Complex Complex::operator * (const Complex& number)
{
	return Complex(this->real_ * number.real_ - this->image_ * number.image_,
		this->real_ * number.image_ + number.real_ * this->image_);
}

Complex Complex::operator / (const Complex& number)
{
	return Complex((this->real_ * number.real_ + this->image_ * number.image_) / (number.real_ * number.real_ + number.image_ * number.image_),
		(number.real_ * this->image_ - this->real_ * number.image_) / (number.real_ * number.real_ + number.image_ * number.image_));
}

Complex Complex::Square()
{
	return Complex(this->real_ * this->real_ - this->image_ * this->image_,
		2 * this->real_ * this->image_);
}

Complex Complex::Reverse()
{
	return Complex(this->real_ / (this->real_ * this->real_ + this->image_ * this->image_),
		-this->image_ / (this->real_ * this->real_ + this->image_ * this->image_));
}

Complex Complex::Minus()
{
	return Complex(-this->real_, -this->image_);
}

double Complex::Module()
{
	return sqrt(this->real_ * this->real_ + this->image_ * this->image_);
}

double Complex::AngleRadians()
{
	if (this->real_ > 0)
		return atan(double(image_ / real_));
	else if (this->real_ == 0 && this->image_ > 0)
		return PI_ / 2;
	else if (this->real_ < 0)
		return atan(double(image_ / real_)) + PI_;
	else if (this->real_ == 0 && this->image_ < 0)
		return -PI_ / 2;
}

double Complex::AngleDegree()
{
	return AngleRadians() * PI_ / 180;
}

Complex Complex::Degree(int n)
{
	return Complex(pow(Module(), n) * cos(n * AngleRadians()),
		pow(Module(), n) * sin(n * AngleRadians()));
}

Complex Complex::Root(int n, int i)
{
	return Complex(pow(Module(), 1.0 / n) * (cos(AngleDegree() + 2 * i * PI_) / n),
		pow(Module(), 1.0 / n) * (sin(AngleDegree() + 2 * i * PI_) / n));
}

bool Complex::operator == (const Complex& number)
{
	return (this->real_ == number.real_) && (this->image_ == number.image_);
}
bool Complex::operator != (const Complex& number)
{
	return (this->real_ != number.real_) && (this->image_ != number.image_);
}

int Complex::GetRe()
{
	return this->real_;
}

int Complex::GetIm()
{
	return this->image_;
}

std::string Complex::GetReString()
{
	return std::to_string(this->real_);
}

std::string Complex::GetImString()
{
	return std::to_string(this->image_);
}

std::string Complex::GetNumString()
{
	if (this->image_ > 0)
		return GetReString() + "+" + GetImString() + "i";
	else
		return GetReString() + GetImString() + "i";
}