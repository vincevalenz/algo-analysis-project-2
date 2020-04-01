//
// Created by Ari Encarnacion and Vincent Valenzuela on 3/28/2020.
//

#include "Graph.h"
#include <iomanip>
#include <cmath>
#include <queue>
#include <algorithm>

void Graph::buildMatrix() {
    //connect inner nodes
    for(int i = 0; i < clients.size(); i++) {
        for(int k = 0; k < clients.size(); k++)
            if(clients.at(k).getStartDate() >= clients.at(i).getEndDate()) {
                clientMatrix[i+1].at(k+1) = clients.at(i).getAmount();
            }
    }

    //connect start node
    bool noIn = true;
    for(int col = 1; col < matrixSize - 1; col++) {
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

void Graph::getPath() {
    topSort();
    getOptPath();
}

// Topological Sorting
void Graph::topSort() {

    int size = (int)clientMatrix.size();
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

    for (int i=0; i<size; i++) {
        if (edgeCount[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {
        n = q.front();
        for(int i=0; i<(int)nodes[n].size(); i++) {
            edgeCount[nodes[n][i]]--;
            if (edgeCount[nodes[n][i]] == 0)
                q.push(nodes[n][i]);
        }
        sorted.push_back(n);
        q.pop();
    }

    ts = sorted;
}

void Graph::getOptPath() {
    int end = (int)ts.size()-1;
    std::vector<int> weight(end+1, 0);
    std::vector<int> opath(end+1, -1);
    /*
     * nodes index:     0   1   2   3   4   5      <-- order of clients as parsed in
     * weight vals:     w   w   w   w   w   w      <-- highest weight possible for node
     * opt path:        2   5   3   5   5   -      <-- value indicates next best node to jump to
     *                                              -- path(node)=next -> path(next)=next1 ... will skip down the opt path
     */
    for (int v = end-1; v >=0; v--) {
        int W = 0;
        int n = ts[v];
        int p = end;
        if (v == 0) {
            for (auto & j : nodes[n]) {
                if (W < weight[j]) {
                    W = weight[j];
                    p = j;
                }
            }
        }
        else {
            W = clients[n - 1].getAmount();
            for (auto &j : nodes[v]) {
                if (W < weight[j] + clients[n - 1].getAmount()) {
                    W = weight[j] + clients[n - 1].getAmount();
                    p = j;
                }
            }
        }
        weight[v] = W;
        opath[v] = p;
    }
    P = opath;
}

int Graph::getTotalPayment() {
    int v = 0;
    int rev = 0;
    while (v < (int)clients.size()-1) {
        rev += clients[P[v]-1].getAmount();
        path.push_back(P[v]);
        v = P[v];
    }
    return rev;
}

std::vector<int> Graph::getFinalClients() {
    return path;
}

int Graph::getNumOfClients() {
    return clients.size();
}

void Graph::print_result() {
    std::cout << "There are " << getNumOfClients() << " clients in this file.\n";

    std::cout << std::endl;
    int revenue = getTotalPayment();
    std::cout << "Optimal revenue earned is " << revenue;
    std::cout << std::endl;

    std::cout << "Clients contributing to this optimal revenue: ";
    int numOfClients = (int)path.size();
    for(auto & c : path) {
        numOfClients--;
        if(numOfClients == 0)
            std::cout << c;
        else
            std::cout << c << ", ";

    }
    std::cout << std::endl;
}

void Graph::debug_printMatrix() {
    std::cout << std::left << std::setw(10) << "";
    std::cout<< std::left << std::setw(8)<< "S" <<  ' ';
    for(int i=1; i < matrixSize-1; i++) {
        std::cout << std::left << std::setw(8) << i << ' ';
    }
    std::cout<< std::left << std::setw(8)<< "E" <<  ' ';
    std::cout <<'\n';

    for(int i= 0; i < matrixSize; i++) {
        if(i == 0) {
            std::cout<< std::left << std::setw(8)<< "S" <<  ' ';
        } else if (i == matrixSize-1) {
            std::cout<< std::left << std::setw(8)<< "E" <<  ' ';
        } else {
            std::cout << std::left << std::setw(8) << i << ' ';
        }

        for(int k=0; k < matrixSize; k++) {
            std::cout << std::left << std::setw(8) << clientMatrix[i][k] << ' ';
        }
        std::cout<<'\n';
    }
}