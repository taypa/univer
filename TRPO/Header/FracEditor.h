#ifndef FRACEDITOR_H
#define FRACEDITOR_H
#pragma once

#include <iostream>
#include <string>

class FracEditor
{
private:
	std::string fraction_ = "0/1";
	const std::string DELIMITER_ = "/";

public:
	FracEditor();

	bool IsZero();

	std::string AddSign();
	
	std::string AddDigit(int digit);

	std::string AddZero();

	std::string AddDelimiter();

	std::string DeleteRight();

	std::string Clear();

	std::string GetString();

	void SetString(std::string string);

};
#endif