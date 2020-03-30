#include <iostream>
#include "Property.h"
#include "Graph.h"
#include <iomanip>

int main() {

    RentalForm
            c1("c1", 20,80,600),
            c2("c2", 20,80,700),
            c3("c3", 40,90,800),
            c4("c4", 0,10,200),
            c5("c5", 7,86,5000),
            c6("c6", 100,101,15);

    //DAG example
    //1. call constructor with client vector
    //2. call buildMatrix()
    //3. call print() to check
    std::vector<RentalForm> allClients = {c1,c2,c3,c4,c5,c6};
    Graph g(allClients);
    g.print();
    std::cout << "-------------\n";
    g.buildMatrix();
    g.print();
}
