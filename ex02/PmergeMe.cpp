#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &a){
    *this = a;
}

PmergeMe & PmergeMe::operator = (const PmergeMe &a){
    if (this != &a)
        *this = a;
    return *this;
}