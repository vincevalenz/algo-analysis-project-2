//
// Created by Ari Encarnacion on 3/28/2020.
//

#include "Graph.h"
#include <iomanip>
#include <cmath>
#include <queue>
#include <algorithm>

void Graph::print() {
    //label matrix
    std::cout << std::left << std::setw(10) << "";
    std::cout<< std::left << std::setw(8)<< "S" <<  ' ';
    for(int i=1; i < matrixSize-1; i++) {
    std::cout << std::left << std::setw(8) << i << ' ';
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
            std::cout << std::left << std::setw(8) << i << ' ';
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

    topSort();
//    std::cout << "testing top sort\n";
//    for (auto & num: ts){
//        std::cout << num << " ";
//    }
//    std::cout << "\n------------------\n\n";

//    std::cout << "testing nodes\n";
//    for (int i = 0; i < nodes.size(); i++) {
//        if (nodes[i].empty()) {
//            std::cout << "EMPTY";
//        }
//
//        for (int j = 0; j < nodes[i].size(); j++) {
//            std::cout << nodes[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;

    //Traverse topological sort in REVERSE
    P.resize(ts.size()); // P resized to topSort vector for later storage
    for(int idx = int(ts.size()) - 1; idx >= 0; idx--) {
        int maxOfIdx = F(ts.at(idx));
        f_array.push_back(maxOfIdx);
    }
    std::reverse(f_array.begin(), f_array.end());

//    std::cout << "f_array is: ";
//    for(auto & amt: f_array) {
//        std::cout << amt << ' ';
//    }
//    std::cout << '\n';
//    std::cout << "topSort is: ";
//    for (auto & num: ts){
//        std::cout << num << " ";
//    }
//    std::cout << '\n';

    for(int i = 0; i < P.size(); i++) {
        P.at(i) = getMaxOf(nodes[ts.at(i)]);
    }

//    std::cout << "P array is: ";
//    for(auto & p: P) {
//        std::cout << p << ' ';
//    }
//    std::cout << '\n';

    path.push_back(0);
    int n = P.at(0);
    while(n != -88) {
        path.push_back(n);
        n = P.at(getIdxOf(ts, n));
    }

//    std::cout << "path array is: ";
//    for(auto & entry: path) {
//        std::cout << entry << ' ';
//    }
//    std::cout << '\n';
}



int Graph::getTotalPayment() {
    //return f_array.at(getIdxOf(ts, path.at(1)));
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



int Graph::getMaxOf(std::vector<int> nodes) {
    if(nodes.size() == 1) {
        return nodes.at(0);
    }

    if(nodes.empty()) {
        return -88;
    }

    int maxNode = nodes.at(0), maxVal = -1;
    for(auto & node: nodes) {
        // input is nodes
        // 2 3
        // 4
        // 4
        // 1
        //choose the max one

        //getIdx of node in ts
        int f_idx = getIdxOf(ts, node);
        if(f_array.at(f_idx) > maxVal) {
            maxNode = node;
            maxVal = f_array.at(f_idx);
        }
    }

    return maxNode;
}



int Graph::getIdxOf(std::vector<int> vec, int n) {
    int index = 0;
    while(vec.at(index) != n) {
        index++;
    }
    return index;
}



int Graph::F(int n) {
    // If end node
    if(n == nodes.size() - 1) {
        return 0;
    }


    if(nodes.at(n).size() > 1) {
        std::vector<int> possibleMax;
        // go through all possible nodes and get all values
        for(int i = 0; i < nodes.at(n).size(); i++) {
           possibleMax.push_back(F(nodes[n].at(i)));
        }

        // pick and return the max of collected values
        int chosenMax = -1, it = 0;
        for(auto & num: possibleMax) {
            if (num > chosenMax) {
                chosenMax = num;
            }
            it++;
        }
        return chosenMax;
    }

    return F(nodes[n][0]) + clients.at(n - 1).getAmount();
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
    for (int i=0; i<(int)nodes.size(); i++){
        std::cout << std::left << std::setw(4);
        if (i != (int) nodes.size() - 1)
            (i == 0) ? std::cout << "S" : std::cout << i;
        else
            std::cout  << "E";

        for (auto & num : nodes[i]) {
            std::cout << num << ":";
            (num == (int) nodes.size()-1) ? std::cout << "0": std::cout << clients[num-1].getAmount() << ", ";
        }
        std::cout << std::endl;
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


void Graph::print_final() {
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