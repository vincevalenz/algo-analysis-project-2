#include <iostream>
#include "Property.h"
#include "Graph.h"
#include <iomanip>

int main() {

    RentalForm
            c3("c3",50,80,120),
            c1("c1", 10,40,100),
            c2("c2",20,70,200);


    //DAG example
    //1. call constructor with client vector
    //2. call buildMatrix()
    //3. call print() to check
    std::vector<RentalForm> allClients = {c1,c2,c3};
    Graph g(allClients);
    g.print();
    std::cout << "-------------\n";
    g.buildMatrix();
    g.print();
}
