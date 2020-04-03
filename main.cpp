//
// Created by Vincent Valenzuela and Ari Encarnacion on 3/29/20.
//

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
    clients.push_back(RentalForm(0,0,0));      //start node
    RentalForm c = parser.getClient();

    while (c.getStartDate() > -1) {                     // client nodes
        clients.push_back(c);
        c = parser.getClient();
    }
    clients.push_back(c);                               // end node

    //build dag from parsed client file
    Graph g(clients);
    g.buildMatrix();

    //get optimal path and print result
    g.getPath();
    g.print_result();

    write_to_file(g, file);
}
