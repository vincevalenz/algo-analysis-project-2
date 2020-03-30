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

//    for (int i=0; i<clients.size(); i++){
//        std::cout << "Start Date: " << clients[i].getStartDate()
//                << ", End Date: " << clients[i].getEndDate()
//                << ", Amount: " << clients[i].getAmount()
//                << std::endl;
//    }


    //1. call constructor with client vector
    //2. call buildMatrix()
    //3. call print() to check
    Graph g(clients);
    g.print();
    std::cout << "-------------\n";
    g.buildMatrix();
    g.print();

    std::vector<int> sorted = g.topSort();
    for (int i : sorted){
        std::cout << sorted[i] << " ";
    }
}
