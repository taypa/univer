#pragma once
#ifndef EDITOR
#define EDITOR
#include <iostream>
#include <Convertor_P_10.h>
#include <Convertor_10_P.h>
class Editor
{
private:
    std::string num_;
    std::string zero_ = "0";
    std::string delimiter_ = ".";

public:
	Editor(std::string num_);

    Editor();

    bool IsZero();

    void AddSign();

    void AddNumeral(double digit, int p, int eps);

    void AddZero();

    void AddDelimiter();

    void Clear();

    void DeleteRigth();

    void set_num(std::string num_, int old_p, int new_p, int eps);

    void set_num(std::string num_);

    std::string get_num();

};

#endif
