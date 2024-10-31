#include "Editor.h"

Editor::Editor(std::string num) : num_(num) {}

Editor::Editor(){}

bool Editor::IsZero()
{
    return num_ == "0";
}

void Editor::AddSign()
{
    if (num_[0] == '-')
        num_.erase(0, 1);
    else
        num_.insert(num_.begin(), '-');
}

void Editor::AddNumeral(double digit, int p, int eps)
{
    std::string res = Convertor_10_P::Do(digit, p, eps);
    num_ += res;
}

void Editor::AddZero()
{
    num_ += '0';
}

void Editor::AddDelimiter()
{
    num_ += delimiter_;
}

void Editor::Clear()
{
    num_.clear();
    Editor::AddZero();
}

void Editor::DeleteRigth()
{
    num_.pop_back();
    if (num_.back() == '.')
        num_.pop_back();
    if (num_=="")
        Editor::AddZero();
}

void Editor::set_num(std::string num, int old_p, int new_p, int eps)
{
    double num_10 = Convertor_P_10::Convert(num, old_p, eps);
    num_ = Convertor_10_P::Do(num_10, new_p, eps);
}

void Editor::set_num(std::string num)
{
    num_ = num;
}

std::string Editor::get_num()
{
    return this->num_;
}
