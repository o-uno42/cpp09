#include "BitcoinExchange.hpp"
#include <cstring>
#include <sstream>

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &a){
    *this = a;
}

BitcoinExchange & BitcoinExchange::operator = (const BitcoinExchange &a){
    if (this != &a)
        this->_database = a._database;
    return *this;
}

std::map<std::string, float>BitcoinExchange::getDatabase(){
    return _database;
}


std::multimap<std::string, float>BitcoinExchange::getInputDatabase(){
    return _inputDatabase;
}

bool date_exists(int year, int month, int day) {
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    struct tm timeinfo = {};
    timeinfo.tm_year = year - 1900; //la struct tm rappresenta gli anni dal 1900
    timeinfo.tm_mon = month - 1;    // (0 -11)
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = 12;//settato a mezzogiorno per evitare problemi con l'ora legale
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;
    timeinfo.tm_isdst = -1;// -1 per far determinare l'ora legale al sistema 

    // creo un valid time_t a partire dalla data, altrimenti non esiste
    time_t t = mktime(&timeinfo);
    if (t == (time_t)-1) {
        return false;
    }

    return (timeinfo.tm_year == year - 1900) &&
           (timeinfo.tm_mon == month - 1) &&
           (timeinfo.tm_mday == day);
}

bool BitcoinExchange::checkDate(std::string line) {
    std::istringstream iss(line);
    std::string date;
    int year, month, day;

    if (!getline(iss, date, '|')) {
        LOG_ERR("Error: bad date : " << line);
        return false;
    }

    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        LOG_ERR("error: bad date : " << line);
        return false;
    }

    std::istringstream yearStream(date.substr(0, 4));
    std::istringstream monthStream(date.substr(5, 2));
    std::istringstream dayStream(date.substr(8, 2));

    if (!(yearStream >> year) || !(monthStream >> month) || !(dayStream >> day)) {
        LOG_ERR("error: bad date : " << line);
        return false;
    }

    if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31) {
        LOG_ERR("error: bad date : " << line);
        return false;
    }

    if (!date_exists(year, month, day)) {
        LOG_ERR("error: date doesnt exists : " << line);
        return false;
    }
    return true;
}


bool BitcoinExchange::checkNbBitcoin(float nb){
    std::ostringstream oss;
    oss << nb;
    if (nb < 0){
        LOG_ERR("Error: not a positive number : " << nb);
        return false;
    }
    else if (nb > 1000){
        LOG_ERR("Error: too large a number : " << nb);
        return false;
    }
    return true;
}

std::string trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.size() - 1;
    while (start < str.size() && (str[start] == ' ' || str[start] == '\t' || str[start] == '\r' || str[start] == '\n')) {
        ++start;
    }
    while (end > start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\r' || str[end] == '\n')) {
        --end;
    }
    return str.substr(start, end - start + 1);
}


bool BitcoinExchange::parseInput(std::string fileName){

    std::ifstream file;
    std::string line;
    std::string date;
    std::string nbStr;
    float nbFloat;

    try{
        file.open(fileName.c_str());
    }
    catch (...){
        LOG_ERR("Error: could not open file : " << fileName);
        return false;
    }

    while (getline(file, line)){
        if(line.find('|') == std::string::npos){
            LOG_ERR("Error: bad input  => " << line);
            continue;
        }
        std::istringstream iss(line);
        getline(iss, date, '|');
        date = trim(date);
        getline(iss, nbStr, '\n');

        std::istringstream nbFloatStream(nbStr);
        if (!(nbFloatStream >> nbFloat)) {
            LOG_ERR("Error: invalid line");
            continue;
        }
        if (checkNbBitcoin(nbFloat) && checkDate(date)){
            _inputDatabase.insert(std::make_pair(date, nbFloat));
        }
    }
    return true;
}

void BitcoinExchange::createDatabase(){
    std::ifstream file;
    std::string line;
    std::string date;
    std::string nbStr;
    float nbFloat;

    file.open("data.csv");
    if (!file.is_open()) {
        LOG_ERR("Error: could not open file data.csv.");
        return;
    }

    while (getline(file, line)){
        std::istringstream iss(line);
        getline(iss, date, ',');
        date = trim(date);
        getline(iss, nbStr, '\n');

        std::istringstream nbFloatStream(nbStr);
        if (!(nbFloatStream >> nbFloat)) {
            continue;
        }
        _database[date] = nbFloat;
    }
}
