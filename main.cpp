#include <iostream>
#include <string>
#include "Graph.h"
#include "RentalForm.hpp"
#include "ClientParser.hpp"
#include "FileOutput.hpp"

int main(int argc, char *argv[]) {

    std::string file;
    std::cout << "Enter the file to read data: ";
    std::cin >> file;
    std::cout << std::endl;


    ClientParser parser(file);
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
    //g.getOptimalPath();
    g.topSort();
    g.getOptPath();
    g.print_final();

    write_to_file(g, file);

}
