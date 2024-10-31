#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <iostream>

template<class T>
class Processor
{
private:
    T lop_res_;
    T rop_;
    char operation_ = 'N';
public:
    Processor(){}

    void ResetProcessor(T lop_res = T(), T rop = T())
    {
        lop_res_ = lop_res;
        rop_ = rop;
        operation_ = 'N';
    }

    void PerformOperation()
    {
        if (operation_ != 'N')
        {
            switch (operation_)
            {
            case '+':
                lop_res_ = lop_res_ + rop_;
                break;

            case '-':
                lop_res_ = lop_res_ - rop_;
                break;

            case '*':
                lop_res_ = lop_res_ * rop_;
                break;

            case '/':
                lop_res_ = lop_res_ / rop_;
                break;
            }
        }
    }

    void CalculateFunc(char func)
    {
        switch (func)
        {
        case 'R':
            rop_ = rop_.reverse();
            break;

        case 'S':
            rop_ = rop_.square();
            break;
        }
    }

    T GetLeft()
    {
        return lop_res_;
    }

    void SetLeft(T operand)
    {
        lop_res_ = operand;
    }

    T GetRight()
    {
        return rop_;
    }

    void SetRight(T operand)
    {
        rop_ = operand;
    }

    char GetOperation()
    {
        return operation_;
    }

    void SetOperation(char operation)
    {
        operation_ = operation;
    }
};

#endif // PROCESSOR_H
