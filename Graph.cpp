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

        std::cout << "testing top sort\n";
    std::vector<int> sorted = topSort();
    for (int i : sorted){
        std::cout << sorted[i] << " ";
    }
    std::cout << "\n------------------\n\n";


    std::cout << "testing nodes\n";
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].empty()) {
            std::cout << "EMPTY";
        }

        for (int j = 0; j < nodes[i].size(); j++) {
            std::cout << nodes[i][j] << " ";
        }
        std::cout << std::endl;
    }


    //Traverse topological sort in REVERSE
    std::vector<int> maxAmounts;
    for(int topIdx = int(sorted.size()) - 1; topIdx >= 0; topIdx--) {
        int maxOfCurIdx = F(topIdx);
        maxAmounts.push_back(maxOfCurIdx);
    }
    for(auto & amt: maxAmounts) {
        std::cout << amt << ' ';
    }
}

int Graph::F(int n) {
    // If end node
    if(n == nodes.size() - 1) {
        return 0;
    }

    if(n > 0) {
        if(nodes.at(n).size() > 1) {
            std::vector<int> possibleMax;
            // go through all possible nodes and get all values
            for(int i = 0; i < nodes.at(n).size(); i++) {
               possibleMax.push_back(F(i));
            }

            int chosenMax = -1;
            for(auto & num: possibleMax) {
                if (num > chosenMax)
                     chosenMax = num;
            }
            return chosenMax;
        }

        return F(nodes[n][0]) + clients.at(n - 1).getAmount();
    }

    //If start node
    return F(n + 1);
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
//        std::cout << n << " ";
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