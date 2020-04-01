//
// Created by Vincent Valenzuela and Ari Encarnacion
//

#ifndef PROJECT02_FILEOUTPUT_HPP
#define PROJECT02_FILEOUTPUT_HPP

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Graph.h"

void write_to_file(Graph &g, std::string file) {
    std::ofstream output("out"+file);

    output << "There are " << g.getNumOfClients() << " clients in this file.\n";

    output << std::endl;
    output << "Optimal revenue earned is " << g.getTotalPayment();
    output << std::endl;

    output << "Clients contributing to this optimal revenue: ";
    std::vector<int> optimalClients = g.getFinalClients();
    int numOfClients = (int)optimalClients.size();
    for(auto & c : optimalClients) {
        numOfClients--;
        if(numOfClients == 0)
            output << c;
        else
            output << c << ", ";

    }
    output << std::endl;

    output.close();
}

#endif //PROJECT02_FILEOUTPUT_HPP
