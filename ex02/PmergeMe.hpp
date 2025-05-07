#ifndef PMERGEME_H
# define PMERGEME_H

#include <cmath>
#include <iostream>
#include <vector>
#include <deque>
#include <unistd.h> 
#include <sstream>
#include <sys/time.h>

class PmergeMe {
    
    public:
        PmergeMe ();
        PmergeMe (const PmergeMe &a);
        ~PmergeMe ();
        PmergeMe & operator = (const PmergeMe &a);
        void printVect(const std::vector<int>& v);
        void printDeque(const std::deque<int>& v);
        double mergeInsertSortVector(std::vector<int>& container);
        double mergeInsertSortDeque(std::deque<int>& container);
    
};

#endif