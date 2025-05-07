#include "BitcoinExchange.hpp"
#include <map>
#include <ostream>
#include <string>

void BitcoinExchange::calculateNewValue(const std::multimap<std::string, float>& inputDatabase, const std::map<std::string, float>& csvDatabase) {
    std::ifstream file;
    std::string line;
    std::string date;
    std::string nbStr;

    std::multimap<std::string, float> newValue;
    
    // creo la multimap con data e value
    std::multimap<std::string, float>::const_iterator inputIt;
    for (inputIt = inputDatabase.begin(); inputIt != inputDatabase.end(); ++inputIt) {
        const std::string& inputDate = inputIt->first;
        float inputValue = inputIt->second;

        if (!checkDate(inputDate)) {
            LOG_ERR("Error: bad date format : " << inputDate);
            continue;
        }
        
        // cerco il match esatto delle date
        std::map<std::string, float>::const_iterator exactMatch = csvDatabase.find(inputDate);
        if (exactMatch != csvDatabase.end()) {
            float result = inputValue * exactMatch->second;
            LOG(inputDate << " => " << inputValue << " * " << exactMatch->second << " = " << result);
            newValue.insert(std::make_pair(inputDate, result));
            continue;
        }
        
        // se non la trovo, setto la data più vicina
        std::map<std::string, float>::const_iterator lowerBound = csvDatabase.lower_bound(inputDate);
        
        if (lowerBound == csvDatabase.begin() && lowerBound->first > inputDate) {
            LOG_ERR("No suitable date found in CSV for: " << inputDate);
        } else {
            if (lowerBound == csvDatabase.end()) {
                --lowerBound;
            }
            //mi muovo indietro fintanto che trovo date superiori a quella cercata
            if (lowerBound->first > inputDate && lowerBound != csvDatabase.begin()) {
                --lowerBound;
            }
            // faccio puntare lowerBound alla data minore + vicina
            float result = inputValue * lowerBound->second;
            LOG(inputDate << " => " << inputValue << " * " << lowerBound->second << " = " << result << "        |   [closest lower date : " << lowerBound->first << "]");
            newValue.insert(std::make_pair(inputDate, result));
        }
    }
}


int main(int ac, char *av[]){

    BitcoinExchange btc;

    std::ifstream file;
    if (ac != 2){
        LOG_ERR("usage: ./btc <file>");
        return 1;
    }

    try{
        btc.createDatabase();
        btc.parseInput(av[1]);
    }
    catch(...){
        LOG_ERR("Error");
        return 1;
    }

    btc.calculateNewValue(btc.getInputDatabase(), btc.getDatabase());

    std::cout << "\n--- Time tests: " << std::endl;
    std::cout << (date_exists(2024, 2, 29) ? "Exists" : "Does not exist") << std::endl;
    std::cout << (date_exists(2023, 2, 29) ? "Exists" : "Does not exist") << std::endl;

}

