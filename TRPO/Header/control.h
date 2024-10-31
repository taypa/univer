#ifndef CONTROL_H
#define CONTROL_H
#include <Editor.h>
#include <processor.h>
#include <Memory.h>
#include <Number.h>

class Control
{
private:
    Number number_;

public:
    Editor editor_;
    Processor<Number> proc_;
    Memory<Number> memory_;

    Control();

    std::string PerformEditorCommand(std::string command);

    std::string PerformOperation();

    std::string PerformFunc(std::string func);

    Number PerformMemory(std::string command, Number num);

};

#endif // CONTROL_H
