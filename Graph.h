//
// Created by Ari Encarnacion and Vincent Valenzuela on 3/28/2020.
//

#ifndef PROJECT02_GRAPH_H
#define PROJECT02_GRAPH_H

#include <iostream>
#include <utility>
#include <vector>
#include "RentalForm.hpp"

class Graph {
public:
    explicit Graph(std::vector<RentalForm> c):      clients{c}
                                                    {
                                                        init_clientMatrix();
                                                    }
     void init_clientMatrix() {
         int default_value = 0;
         int M = clients.size();
         std::vector<std::vector<int>> temp(M, std::vector<int>(M,default_value));
         clientMatrix = temp;
         matrixSize = clients.size();
     }
    void buildMatrix();
    void getPath();
    void print_result();
    int getNumOfClients();
    int getTotalPayment();
    std::vector<int> getFinalClients();

private:

     void getOptPath();
     void topSort();
     void debug_printMatrix();

    int matrixSize;
    int revenue = -1;
    std::vector<RentalForm> clients;
    std::vector<std::vector<int>> clientMatrix;
    std::vector< std::vector<int> > nodes;
    std::vector<int> P;
    std::vector<int> ts;
    std::vector<int> rts;
    std::vector<int> path;
};


#endif //PROJECT02_GRAPH_H
