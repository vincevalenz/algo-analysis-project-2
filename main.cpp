#include <iostream>
#include "Property.h"
#include "Graph.h"
#include <iomanip>

int main() {

    //Testing Rental Form

    RentalForm c1("c1", 10,40,100),
            c2("c2",20,70,200),
            c3("c3",50,80,120);


    std::vector<RentalForm> allClients = {c1,c2,c3};
    Graph g(allClients);
    g.print();
    std::cout << "-------------\n";
    g.buildMatrix();
    g.print();
//









//    std::vector<RentalForm> allClients = {start, c1,c2,c3, end};
//    for(auto & client : allClients) {
//        std::cout <<"start: " << client.getStartDate() << std::endl;
//        std::cout <<"end: " << client.getEndDate() << std::endl;
//        std::cout <<"amount: "  << client.getAmount() << std::endl;
//        std::cout << "-------\n";
//    }
//
//    //init matrix
//    const int ROW = allClients.size(), COL = allClients.size();
//    int clientMatrix[ROW][COL];
//    for(int i=0; i < allClients.size(); i++) {
//        for(int k=0; k < allClients.size(); k++) {
//            clientMatrix[i][k] = 0;
//        }
//    }



}
