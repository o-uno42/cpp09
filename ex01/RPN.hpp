#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>

#define LOG(msg) std::cout << msg << std::endl;
#define LOG_ERR(msg) std::cerr << msg << std::endl;

class RPN{
    
    std::stack<int> _stack;

    public:
        RPN();
        ~RPN();
        RPN(const RPN &a);
        RPN & operator = (const RPN &a);
        std::stack<int> getStack();
        void setStack(std::string operation);
        void operationStack(char c);
        void checkIsValid(const std::string& expr);

};


#endif