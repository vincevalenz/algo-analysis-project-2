//
// Created by Ari Encarnacion on 3/28/2020.
//

#ifndef PROJECT02_GRAPH_H
#define PROJECT02_GRAPH_H

#include <iostream>
#include <utility>
#include <vector>
#include "RentalForm.hpp"

class Graph {
public:
 explicit Graph(std::vector<RentalForm> c): clients{c} {init_clientMatrix();}

 void init_clientMatrix() {
     int default_value = 0;
     int M = clients.size() + 2;
     std::vector<std::vector<int>> temp(M, std::vector<int>(M,default_value));
     clientMatrix = temp;
     matrixSize = clients.size() + 2;
 }

 void buildMatrix();

 void print();

private:
    int matrixSize;
    std::vector<RentalForm> clients;
    std::vector<std::vector<int>> clientMatrix;


};


#endif //PROJECT02_GRAPH_H