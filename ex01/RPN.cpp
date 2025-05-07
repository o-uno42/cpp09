#include "RPN.hpp"

RPN::RPN(){};

RPN::~RPN(){};

RPN::RPN(const RPN &a){
    *this = a;
}

RPN & RPN::operator = (const RPN &a){
    if (this != &a)
        this->_stack = a._stack;
    return *this;
}