#include <iostream>
#include "Graph.h"
#include <fstream>
#include "RentalForm.hpp"
#include "ClientParser.hpp"

int main(int argc, char *argv[]) {
    if ( argc != 2){
        std::cout << "Usage: " << argv[0] << " nameOfInputFile" << std::endl;
        exit(1);
    }

    ClientParser parser(argv[1]);
    std::vector<RentalForm> clients;
    RentalForm c = parser.getClient();

    while (c.getStartDate() > 0) {
        clients.push_back(c);
        c = parser.getClient();
    }

    //build dag from parsed client file
//    std::cout << "testing build DAG\n";
    Graph g(clients);
    g.buildMatrix();
//    g.print();
//    std::cout << "------------------\n\n";

    //testing optimal path -- in progress
    g.getOptimalPath();

    std::cout << "There are " << g.getNumOfClients() << " clients in this file.\n";

    std::cout << std::endl;
    int revenue = g.getTotalPayment();
    std::cout << "Optimal revenue earned is " << revenue;
    std::cout << std::endl;

    std::cout << "Clients contributing to this optimal revenue: ";
    std::vector<int> optimalClients = g.getFinalClients();
    for(int i = 1; i < int(optimalClients.size()) - 1; i++) {
        if(i < int(optimalClients.size()) - 2)
            std::cout << optimalClients[i] << ", ";
        else
            std::cout << optimalClients[i];
    }
    std::cout << std::endl;
}
