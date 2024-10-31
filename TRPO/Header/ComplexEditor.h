#ifndef COMPLEX_H
#define COMPLEX_H
#pragma once

#include <iostream>
#include <string>
class ComplexEditor
{
private:
	std::string number_;

public:
	ComplexEditor();

	bool IsZero();

	//непонятно как знак добавить. ко всему числу или только к какой-то одной части
	/*std::string AddSign*/();

	std::string AddDigit(int digit);

	std::string AddZero();

	std::string DeleteRight();

	std::string Clear();

	std::string GetNum();

	void SetNum(std::string num);
};

#endif