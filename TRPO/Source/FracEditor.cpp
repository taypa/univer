#include "FracEditor.h"

FracEditor::FracEditor(){}

bool FracEditor::IsZero()
{
	return this->fraction_.substr(0, this->fraction_.find(this->DELIMITER_)) == "0";
}

std::string FracEditor::AddSign()
{
	if (fraction_[0] == '-')
		fraction_.erase(0, 1);
	else
		fraction_.insert(fraction_.begin(), '-');
	return fraction_;
}

std::string FracEditor::AddDigit(int digit)
{
	fraction_ += std::to_string(digit);
	return fraction_;
}

std::string FracEditor::AddZero()
{
	fraction_ += "0";
	return fraction_;
}

std::string FracEditor::AddDelimiter()
{
	fraction_ += DELIMITER_;
	return fraction_;
}

std::string FracEditor::DeleteRight()
{
	fraction_.pop_back();
	if(fraction_.back() == '/')
		fraction_.pop_back();
	return fraction_;
}

std::string FracEditor::Clear()
{
	fraction_.clear();
	fraction_ = "0/1";
	return fraction_;
}

std::string FracEditor::GetString()
{
	return fraction_;
}

void FracEditor::SetString(std::string string)
{
	fraction_ = string;
}