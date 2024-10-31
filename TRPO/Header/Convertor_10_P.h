#include <iostream>
#pragma once
#ifndef CONVERTOR_10_P
#define CONVERTOR_10_P
class Convertor_10_P {
public:
    /*
    Transfer of number to another number system
        n - the number in 10 number system
        p - the base of the new number system
        c - accuracy
    */
    static std::string Do(double num, int p, int eps);

    /*
    Convert an integer value to a numeral number with the base p.
        d - the number
    */
    static char IntToChar(int ch);

    /*
    Convert an integer to a string
        n - the number
        p - the base of the new number system
    */
    static std::string IntToStr(int num, int p);

    /*
    Convert a fraction to a string
        n - the fraction in 10 number system
        p - the base of the new number system
        c - accuracy
    */
    static std::string FltToStr(double num, int p, int eps);
};
#endif


