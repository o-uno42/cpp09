#include "RPN.hpp"

void RPN::operationStack(char c) {
    int a = _stack.top(); //legge l'elemento
    _stack.pop(); //lo rimuove
    int b = _stack.top();
    _stack.pop();
    switch (c) {
        case '+':
            _stack.push(b + a);
            break;
        case '-':
            _stack.push(b - a);
            break;
        case '*':
            _stack.push(b * a);
            break;
        case '/':
            if (a == 0) {
                LOG_ERR("error: division by zero.");
                return;
            }
            _stack.push(b / a);
            break;
        default:
            LOG_ERR("error: unknown operator.");
            break;
    }
}

void RPN::setStack(std::string operation) {
    std::istringstream iss(operation);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
            int number;
            std::istringstream(token) >> number;
            _stack.push(number);
        }
        else if (token == "+") {
            if (_stack.size() < 2) {
                LOG_ERR("error: not enough operands for +");
                return;
            }
            operationStack('+');
        }
        else if (token == "-") {
            if (_stack.size() < 2) {
                LOG_ERR("error: not enough operands for -");
                return;
            }
            operationStack('-');
        }
        else if (token == "*") {
            if (_stack.size() < 2) {
                LOG_ERR("error: not enough operands for *");
                return;
            }
            operationStack('*');
        }
        else if (token == "/") {
            if (_stack.size() < 2) {
                LOG_ERR("error: not enough operands for /");
                return;
            }
            operationStack('/');
        }
        else {
            LOG_ERR("error: invalid token: " << token);
            return;
        }
    }

    if (!_stack.empty()) {
        if (_stack.size() != 1) {
            LOG_ERR("error: invalid expression");
        }
        else{
            LOG(_stack.top());
        }
    } else {
        LOG_ERR("error: empty stack");
    }
}

bool checkValidOperation(std::string operation){
    int i = 0;
    const char *check = operation.c_str();
    int nbEndValues = 0;

    while(check[i]){
        if (check[i] != '+' && check[i] != '-' && check[i] != '*' && check[i] != '/' && check[i] != ' '
            && check[i] != '\t' && !(check[i] >= '0' && check[i] <= '9')){
            LOG_ERR("Error");
            return false;
        }
        if (check[i] == '+' || check[i] == '-' || check[i] == '*' || check[i] == '/'){
            nbEndValues--;
        }
        i++;
    }
    return true;
}

int main(int ac, char *av[]){

    RPN rpn;
    if (ac == 2){
        if(checkValidOperation(av[1]))
            rpn.setStack(av[1]);
        else{
            return 1;
        }
    }
    else{
        LOG("usage: ./RPN \"inverted Polish mathematical expression\"");
    }

    // per testare ho usato : https://www.rpn-calc.com/
}