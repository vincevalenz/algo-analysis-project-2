//
// Created by Ari Encarnacion on 3/28/2020.
//

#include "Graph.h"
#include <iomanip>
#include <cmath>
#include <queue>

void Graph::print() {
    //label matrix
    std::cout << std::left << std::setw(10) << "";
    std::cout<< std::left << std::setw(8)<< "S" <<  ' ';
    for(int i=1; i < matrixSize-1; i++) {
    std::cout << std::left << std::setw(8) << i-1 << ' ';
    }
    std::cout<< std::left << std::setw(8)<< "E" <<  ' ';
    std::cout <<'\n';

    //print values in clientMatrix
    for(int i= 0; i < matrixSize; i++) {
        if(i == 0) {
            std::cout<< std::left << std::setw(8)<< "S" <<  ' ';
        } else if (i == matrixSize-1) {
            std::cout<< std::left << std::setw(8)<< "E" <<  ' ';
        } else {
            std::cout << std::left << std::setw(8) << i-1 << ' ';
        }

        for(int k=0; k < matrixSize; k++) {
            std::cout << std::left << std::setw(8) << clientMatrix[i][k] << ' ';
        }
        std::cout<<'\n';
    }
}


void Graph::buildMatrix() {
    //connect inner nodes
    //traverses clients vector
    for(int i = 0; i < clients.size(); i++) {
        for(int k = 0; k < clients.size(); k++)
            if(clients.at(k).getStartDate() >= clients.at(i).getEndDate()) {
                clientMatrix[i+1].at(k+1) = clients.at(i).getAmount();
            }
    }

    //connect start node
    //traverses matrix
    bool noIn = true;
    for(int col = 1; col < matrixSize - 2; col++) {
        for (int row = 0; row < matrixSize - 1; row++) {
            int x = clientMatrix[row].at(col);
            if(clientMatrix[row].at(col) != -1) {
                noIn = false;
            }
        }
        if(noIn) {
            clientMatrix[0].at(col) = 0;
        }
        noIn = true;
    }

    //connect end node
    //traverses matrix
    bool noOut = true;
    for(int row = 1; row < matrixSize - 1; row++) {
        for (int col = 1; col < matrixSize - 1; col++) {
            if(clientMatrix[row].at(col) != -1) {
                noOut = false;
            }
        }
        if(noOut) {
            int f = clientMatrix[row].at(matrixSize-1);
            clientMatrix[row].at(matrixSize-1) = clients.at(row-1).getAmount();
        }
        noOut = true;
    }
}

void Graph::getOptimalPath() {
    std::cout << "Testing Graph::getOptimalPath()\n";
    for (int i = 0; i < clients.size(); i++) {
        std::cout << "client [" << i << "]:\n";
        std::cout << "   start: " << clients.at(i).getStartDate() << '\n';
        std::cout << "   end: " << clients.at(i).getEndDate() << '\n';
        std::cout << "   pay: " << clients.at(i).getAmount() << '\n';
    }

    //build rev_P
    std::vector<RentalForm> rev_P;
    RentalForm end(INFINITY, INFINITY, 0);
    rev_P.push_back(end);
    for (int i = clients.size() - 1; i >= 0; i--) {
        rev_P.push_back(clients.at(i));
    }
    RentalForm start(0, 0, 0);
    rev_P.push_back(start);


    std::cout << "rev_P vector ------\n";
    for (int i = 0; i < rev_P.size(); i++) {
        std::cout << "client [" << i << "]:\n";
        std::cout << "   start: " << rev_P.at(i).getStartDate() << '\n';
        std::cout << "   end: " << rev_P.at(i).getEndDate() << '\n';
        std::cout << "   pay: " << rev_P.at(i).getAmount() << '\n';
    }
}

// Topological Sorting
std::vector<int> Graph::topSort() {
    int size = clientMatrix.size();
    int n;
    std::queue<int> q;
    std::vector<int> sorted;
    std::vector<int> edgeCount(size, 0);


    for (int v=0; v < size; v++) {
        std::vector<int> edgeList;
        for (int i=0; i<size; i++) {
            if (clientMatrix[v][i] >= 0) {
                edgeCount[i]++;
                edgeList.push_back(i);
            }
        }
        nodes.push_back(edgeList);
    }

//    for (int i=0; i<nodes.size(); i++) {
//        std::cout <<  i << ": ";
//        for (int j=0; j<nodes[i].size(); j++)
//            std::cout << nodes[i][j] << " ";
//        std::cout << " | Edge Count: " << edgeCount[i] << std::endl;
//    }

    for (int i=0; i<size; i++) {
        if (edgeCount[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {
        n = q.front();
        std::cout << n << " ";
        for(int i=0; i<(int)nodes[n].size(); i++) {
            edgeCount[nodes[n][i]]--;
            if (edgeCount[nodes[n][i]] == 0)
                q.push(nodes[n][i]);
        }
        sorted.push_back(n);
        q.pop();
    }
//    std::cout << std::endl;
//    for (int i=0; i<nodes.size(); i++) {
//        std::cout <<  i << ": ";
//        for (int j=0; j<nodes[i].size(); j++)
//            std::cout << nodes[i][j] << " ";
//        std::cout << " | Edge Count: " << edgeCount[i] << std::endl;
//    }

    return sorted;
}

std::vector< std::vector<int> > Graph::getNodes() {
    return nodes;
}