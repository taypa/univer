#include "control.h"

Control::Control(){}

std::string Control::PerformEditorCommand(std::string command)
{

    if (command == "CE")
        editor_.Clear();

    else if (command == "BackSpace")
        editor_.DeleteRigth();

    else if (command == "C")
    {
        editor_.Clear();
//        memory_.Clear();
        number_.set_num(editor_.get_num());
        number_.set_eps(5);
        number_.set_p(10);
        proc_.ResetProcessor();
    }

    else if (command == "+/-")
        editor_.AddSign();

    else if (command == ".")
        editor_.AddDelimiter();

    return editor_.get_num();
}

std::string Control::PerformOperation()
{
    proc_.PerformOperation();
    return proc_.GetLeft().get_num();
}

std::string Control::PerformFunc(std::string func)
{
    char operation;
    if (func == "Sqr")
        operation = 'S';

    else if (func == "1/x")
        operation = 'R';

    proc_.CalculateFunc(operation);

    return proc_.GetRight().get_num();
}

Number Control::PerformMemory(std::string command, Number num)
{
    if (command == "MC")
    {
        memory_.Clear();
        return num;
    }

    else if(command == "MS")
    {
        memory_.Write(num);
        return num;
    }

    else if(command == "MR")
    {
        //memory_.Take();
        return memory_.Take();
    }

    else
    {
        memory_.Add(num);
        return memory_.Take();
    }

}
