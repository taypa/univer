#include "interface.h"

#include <QApplication>
#include <processor.h>
#include <Number.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface w;
    w.setWindowTitle("Calculator");
    w.show();
    return a.exec();
//    Number num1("A1.1", 16, 5);
//        Number num2("1B", 16, 5);
//        std::cout << num1.get_num() << std::endl;

//        Processor<Number> proc;



//        proc.SetLeft(num1);
//        proc.SetRight(num2);
//        proc.SetOperation('+');
//        proc.PerformOperation();
//        proc.CalculateFunc('R');
}
