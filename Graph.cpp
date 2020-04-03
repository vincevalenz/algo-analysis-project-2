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
    for(int row = 1; row < clients.size()-1; row++) {
        clientMatrix[0][row] = 1;
        bool end = true;
        for(int col = 1; col < clients.size()-1; col++) {
            if (clients[row].getEndDate() <= clients[col].getStartDate()) {
                clientMatrix[row][col] = 1;
                clientMatrix[0][col] = 0;
                end = false;
            }
        }
        if (end) clientMatrix[row][matrixSize-1] = 1;
    }
}

void Graph::getPath() {
    topSort();
    getOptPath();
}

// Topological Sorting
void Graph::topSort() {

    std::queue<int> q;
    std::vector<int> edgeCount(matrixSize, 0);


    for (int v=0; v < matrixSize; v++) {
        std::vector<int> edgeList;
        for (int i=0; i<matrixSize; i++) {
            if (clientMatrix[v][i] == 1) {
                edgeCount[i]++;
                edgeList.push_back(i);
            }
        }
        nodes.push_back(edgeList);
    }

    for (int i=0; i<matrixSize; i++) {
        if (edgeCount[i] == 0)
            q.push(i);
    }

    int n;
    while (!q.empty()) {
        n = q.front();
        for(int i=0; i<(int)nodes[n].size(); i++) {
            edgeCount[nodes[n][i]]--;
            if (edgeCount[nodes[n][i]] == 0)
                q.push(nodes[n][i]);
        }
        ts.push_back(n);
        q.pop();
    }
}

// Finding Optimal Path
void Graph::getOptPath() {
    int end = (int)ts.size()-1;
    std::vector<int> weight(end+1, 0);
    std::vector<int> opath(end+1, 0);
    std::vector<int> wRef(end+1, 0);
    for (int i=0; i<end+1; i++) {
        wRef[ts[i]] = i;
    }

    for (int v = end-1; v >=0; v--) {
        int W = 0;
        int n = ts[v];
        int cW = clients[n].getAmount();
        int p = end;
        if (v == 0) {
            for (auto & j : nodes[n]) {
                if (W < weight[wRef[j]]) {
                    W = weight[wRef[j]];
                    p = j;
                }
            }
        }
        else {
            for (auto & j : nodes[n]) {
                if (W < weight[wRef[j]] + cW) {
                    W = weight[wRef[j]] + cW;
                    p = j;
                }
            }
        }
        weight[v] = W;
        opath[v] = p;
    }
    P = opath;
    rts = wRef;
}

int Graph::getTotalPayment() {
    if (revenue > -1)
        return revenue;
    int v = 0;
    int rev = 0;
    while (v < (int)clients.size()-2) {
        rev += clients[P[v]].getAmount();
        path.push_back(P[v]);
        v = rts[P[v]];
    }
    revenue = rev;
    return revenue;
}

std::vector<int> Graph::getFinalClients() {
    return path;
}

int Graph::getNumOfClients() {
    return clients.size();
}

void Graph::print_result() {
    std::cout << "There are " << getNumOfClients()-2 << " clients in this file.\n";

    std::cout << std::endl;
    std::cout << "Optimal revenue earned is " << getTotalPayment();
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