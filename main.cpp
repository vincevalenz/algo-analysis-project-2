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
    std::cout << "testing build DAG\n";
    Graph g(clients);
    g.buildMatrix();
    g.print();
    std::cout << "------------------\n\n";

    std::cout << "testing top sort\n";
    std::vector<int> sorted = g.topSort();
    for (int i : sorted){
        std::cout << sorted[i] << " ";
    }
    std::cout << "\n------------------\n\n";

    std::cout << "testing nodes\n";
    std::vector< std::vector<int> > nodes = g.getNodes();
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes[i].size(); j++)
            std::cout << nodes[i][j] << " ";
        std::cout << std::endl;
    }


    //testing optimal path -- in progress
    g.getOptimalPath();
}
