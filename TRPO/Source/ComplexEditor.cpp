#include "ComplexEditor.h"

ComplexEditor::ComplexEditor() {};

bool ComplexEditor::IsZero()
{
	return number_ == "0+0i";
}

//std::string ComplexEditor::AddSign()
//{
//}

std::string ComplexEditor::AddDigit(int digit)
{
	number_ += std::to_string(digit);
	return number_;
}

std::string ComplexEditor::AddZero()
{
	number_ += "0";
	return number_;
}

std::string ComplexEditor::DeleteRight()
{
	number_.pop_back();
	return number_;
}
std::string ComplexEditor::Clear()
{
	number_.clear();
	number_ = "0+0i";
	return number_;
}

std::string ComplexEditor::GetNum()
{
	return number_;
}

void ComplexEditor::SetNum(std::string num)
{
	number_ = num;
}