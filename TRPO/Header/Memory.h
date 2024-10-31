#ifndef MEMORY
#define MEMORY
#pragma once

#include<iostream>

template <class T>

class Memory
{
private:
    T number_;
    std::string state_;

public:

    Memory(T num) : number_(num), state_("_Off") {}

    Memory(){}

    void Write(T num)
    {
        number_ = num;
        state_ = "_On";
    }

    T Take()
    {
        if(state_ == "_On")
            return number_;
        else return T();
    }


    void Add(T num)
    {
        if(state_ == "_On")
            number_ = number_ + num;
    }

    void Clear()
    {
        number_ = T();
        state_ = "_Off";
    }


    std::string get_state()
    {
        return state_;
    }


};

#endif

