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
 explicit Graph(std::vector<RentalForm> c): clients{c}, nodes{}, P{}, ts{}, f_array{}, path{} {init_clientMatrix();}
 void init_clientMatrix() {
     int default_value = -1;
     int M = clients.size() + 2;
     std::vector<std::vector<int>> temp(M, std::vector<int>(M,default_value));
     clientMatrix = temp;
     matrixSize = clients.size() + 2;
 }
 void buildMatrix();
 void print();
 void getOptimalPath();
 void topSort();
 int F(int);
 std::vector< std::vector<int> > getNodes();
 int getIdxOf(std::vector<int>, int n);
 int getMaxOf( std::vector<int>);
 int getNumOfClients();
 int getTotalPayment();
 std::vector<int> getFinalClients();

private:
    int matrixSize;
    std::vector<RentalForm> clients;
    std::vector<std::vector<int>> clientMatrix;
    std::vector< std::vector<int> > nodes;
    std::vector<int> P;
    std::vector<int> ts;
    std::vector<int> f_array;
    std::vector<int> path;


};


#endif //PROJECT02_GRAPH_H
