#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <iostream>
#include <ctime>


#define LOG(msg) std::cout << msg << std::endl;
#define LOG_ERR(msg) std::cerr << msg << std::endl;
#define RED "\033[31m"
#define RESET "\033[0m"

class BitcoinExchange{
    std::map<std::string , float> _database;
    std::multimap<std::string , float> _inputDatabase;

    public:
        BitcoinExchange ();
        ~BitcoinExchange ();
        BitcoinExchange (const BitcoinExchange &a);
        BitcoinExchange & operator = (const BitcoinExchange &a);

        bool    parseInput(std::string file);
        void    createDatabase();
        std::map<std::string, float> getDatabase();
        std::multimap<std::string, float> getInputDatabase();
        bool    checkDate(std::string line);
        bool   checkNbBitcoin(float nb);
        void    calculateNewValue(const std::multimap<std::string, float>& inputDatabase, const std::map<std::string, float>& csvDatabase);
};

bool date_exists(int year, int month, int day);
std::string trim(const std::string& str);

#endif