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
    int k = 0;
    while (k < (int)edgeCount.size()) {
        std::cout << k << std::setw(4);
        k++;
    }
    std::cout << "\n";

    for (auto & v : edgeCount) {
        std::cout << v << std::setw(4);
    }
    std::cout << "\n";
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
    std::cout << "sorted\n";
    for (auto & v : sorted) {
        std::cout << v << std::setw(4);
    }

    std::cout << "\n\n";

    for (int i=0; i<(int)clients.size(); i++)
        std::cout << i << ":" << clients[i].getAmount() << "  ";
    std::cout << "\n\n";
    for (int i=0; i<(int)nodes.size(); i++) {
        if (i == 0) std::cout << "S" <<  std::setw(6);
        else if (i == (int)nodes.size()-1) std::cout << "E     0";
        else if (i < 10) std::cout << i << std::setw(6);
        else std::cout << i << std::setw(5);
        //std::cout << "EC:" << edgeCount[i] << std::left <<  std::setw(4);
        for (auto & p : nodes[i]) {
            std::cout << p << ":" << clients[p-1].getAmount() << "  ";
        }
        std::cout << std::endl;
    }

    ts = sorted;
}

void Graph::getOptPath() {
    int end = (int)ts.size()-1;
    std::vector<int> weight(end+1, 0);
    std::vector<int> opath(end+1, -1);
    std::vector<int> wRef(end+1, 0);
    for (int i=0; i<end+1; i++) {
        wRef[ts[i]] = i;
    }
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
                if (W < weight[wRef[j]]) {
                    W = weight[wRef[j]];
                    p = j;
                }
            }
        }
        else {
            W = clients[n - 1].getAmount();
            for (auto &j : nodes[n]) {
                if (W < weight[wRef[j]] + clients[n - 1].getAmount()) {
                    W = weight[wRef[j]] + clients[n - 1].getAmount();
                    p = j;
                }
            }
        }
        weight[v] = W;
        opath[v] = p;
    }
    for (auto & w : weight) std::cout << std::setw(6) << w ;
    std::cout << "   weight\n\n";
    for (auto & w : opath) std::cout << std::setw(6) << w ;
    std::cout << "   path\n\n";
    for (auto & w : wRef) std::cout << std::setw(6) << w ;
    std::cout << "   wRef\n\n";
    for (int i=0; i<end+1; i++) std::cout << std::setw(6) << i ;
    std::cout << "   index\n\n";
    for (auto & v : ts) std::cout << std::setw(6) << v;
    std::cout << "   sorted\n";

    P = opath;
    rts = wRef;
}

int Graph::getTotalPayment() {
    if (revenue > -1)
        return revenue;
    int v = 0;
    int rev = 0;
    while (v < (int)clients.size()) {
        rev += clients[P[v]-1].getAmount();
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
    std::cout << "There are " << getNumOfClients() << " clients in this file.\n";

    std::cout << std::endl;
    std::cout << "Optimal revenue earned is " << getTotalPayment();
    std::cout << std::endl;

    std::cout << "Clients contributing to this optimal revenue: ";
    int numOfClients = (int)path.size();
    for(auto & c : path) {
        numOfClients--;
        if(numOfClients == 0)
            std::cout << c << ":" << clients[c-1].getAmount();
        else
            std::cout << c << ":" << clients[c-1].getAmount() << ", ";

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