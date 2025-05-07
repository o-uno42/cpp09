#include "PmergeMe.hpp"

double getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void PmergeMe::printVect(const std::vector<int>& v) {
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::printDeque(const std::deque<int>& v) {
    for (std::deque<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

double PmergeMe::mergeInsertSortVector(std::vector<int>& container) {
    double start = getTime();
    std::vector< std::pair<int, int> > pairs;
    std::vector<int> larger;
    std::vector<int> to_insert;

    std::vector<int>::iterator it = container.begin();
    while (it != container.end()) {
        int first = *it;
        ++it;
        if (it != container.end()) {
            int second = *it;
            if (first < second)
                pairs.push_back(std::make_pair(first, second));
            else
                pairs.push_back(std::make_pair(second, first));
            ++it;
        } else {
            pairs.push_back(std::make_pair(first, -1));
        }
    }

    for (std::size_t i = 0; i < pairs.size(); ++i) {
        if (pairs[i].second != -1) {
            larger.push_back(pairs[i].second);
        } else {
            larger.push_back(pairs[i].first);
        }        
    }

    if (larger.size() > 1)
        mergeInsertSortVector(larger);

    for (std::size_t i = 0; i < pairs.size(); ++i)
        if (pairs[i].second != -1)
            to_insert.push_back(pairs[i].first);

    while (!to_insert.empty()) {
        int val = to_insert.front();
        to_insert.erase(to_insert.begin());
        std::vector<int>::iterator pos = std::lower_bound(larger.begin(), larger.end(), val);
        larger.insert(pos, val);
    }

    container = larger; //aggiorno il container
    double end = getTime();
    return end - start;
}

double PmergeMe::mergeInsertSortDeque(std::deque<int>& container) {
    double start = getTime();
    std::deque< std::pair<int, int> > pairs;
    std::deque<int> larger;
    std::deque<int> to_insert;

    std::deque<int>::iterator it = container.begin();
    while (it != container.end()) {
        int first = *it;
        ++it;
        if (it != container.end()) {
            int second = *it;
            if (first < second)
                pairs.push_back(std::make_pair(first, second));
            else
                pairs.push_back(std::make_pair(second, first));
            ++it;
        } else {
            pairs.push_back(std::make_pair(first, -1));
        }
    }

    for (std::size_t i = 0; i < pairs.size(); ++i) {
        if (pairs[i].second != -1) {
            larger.push_back(pairs[i].second);
        } else {
            larger.push_back(pairs[i].first);
        }
    }

    if (larger.size() > 1)
        mergeInsertSortDeque(larger);

    for (std::size_t i = 0; i < pairs.size(); ++i)
        if (pairs[i].second != -1)
            to_insert.push_back(pairs[i].first);

    while (!to_insert.empty()) {
        int val = to_insert.front();
        to_insert.pop_front(); 
        std::deque<int>::iterator pos = std::lower_bound(larger.begin(), larger.end(), val);
        larger.insert(pos, val);
    }

    container = larger;
    double end = getTime();
    return end - start;
}

int main(int ac, char *av[]) {

    PmergeMe pmergeMe;

    if(ac < 3) {
        std::cerr << "Usage: " << av[0] << " <numbers>" << std::endl;
        return 1;
    }

    std::vector<int> vec;
    std::deque<int> deq;

    for (int i = 1; av[i]; i++) {
        std::istringstream iss(av[i]);
        int nb;
        iss >> nb;
        if (iss.fail() || !iss.eof()) {
            std::cerr << "Error: invalid input" << std::endl;
            return 1;
        }
        vec.push_back(nb);
        deq.push_back(nb);
    }
    std::cout << "Before (vector) :  ";
    pmergeMe.printVect(vec);
    double i = pmergeMe.mergeInsertSortVector(vec);
    std::cout << "After (vector): ";
    pmergeMe.printVect(vec);
    std::cout << "Time to process a range of " << vec.size() << " elements with vector : " << i << " us\n" << std::endl;

    std::cout << "Before (deque):  ";
    pmergeMe.printDeque(deq);
    double z = pmergeMe.mergeInsertSortDeque(deq);
    std::cout << "After (deque): ";
    pmergeMe.printDeque(deq);
    std::cout << "Time to process a range of " << vec.size() << " elements with deque : " << z << " us" << std::endl;

    return 0;
}
