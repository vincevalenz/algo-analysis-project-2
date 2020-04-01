//
// Created by Vincent Valenzuela and Ari Encarnacion on 3/29/20.
//

#ifndef PROJECT02_CLIENTPARSER_HPP
#define PROJECT02_CLIENTPARSER_HPP


#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include "RentalForm.hpp"

class ClientParser {
public:
    ClientParser();
    ClientParser(std::string);
    RentalForm getClient();

private:
    int s, e, am;
    std::string inFile;
    std::ifstream inStream;

};


#endif //PROJECT02_CLIENTPARSER_HPP
