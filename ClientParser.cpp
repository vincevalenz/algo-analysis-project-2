//
// Created by Vincent Valenzuela on 3/29/20.
//

#include "ClientParser.hpp"

ClientParser::ClientParser(std::string file) {
    inFile = std::move(file);
    inStream.open(inFile, std::ios::in);
    if (!inStream.is_open()) {
        std::cout << "Make sure that " << inFile << " exists and is readable. Terminating.";
        exit(2);
    }
}

RentalForm ClientParser::getClient() {

    if (inStream.eof()) {
        return {};
    }

    try {
        if (inStream >> s >> e >> am)
            return  {s, e, am};
        else
            throw std::runtime_error("Error reading data file. Check format and remove extra new line chars \nExiting...");
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }
}