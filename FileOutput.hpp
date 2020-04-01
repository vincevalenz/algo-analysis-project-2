//
// Created by Vincent Valenzuela and Ari Encarnacion
//

#ifndef PROJECT02_FILEOUTPUT_HPP
#define PROJECT02_FILEOUTPUT_HPP

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Graph.h"

void write_to_file(Graph g, std::string file) {
    std::ofstream output("out"+file);

    output << "There are " << g.getNumOfClients() << " clients in this file.\n";

    output << std::endl;
    int revenue = g.getTotalPayment();
    output << "Optimal revenue earned is " << revenue;
    output << std::endl;

    output << "Clients contributing to this optimal revenue: ";
    std::vector<int> optimalClients = g.getFinalClients();
    for(int i = 1; i < int(optimalClients.size()) - 1; i++) {
        if(i < int(optimalClients.size()) - 2)
            output << optimalClients[i] << ", ";
        else
            output << optimalClients[i];
    }
    output << std::endl;

    output.close();
}

#endif //PROJECT02_FILEOUTPUT_HPP
