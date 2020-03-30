//
// Created by Vincent Valenzuela on 3/29/20.
//

#include "TopologicalSort.h"

std::vector<RentalForm *> TopologicalSort::topSort(std::vector<std::vector<int> > clientMatrix, std::vector<RentalForm> &clients) {
    RentalForm forms[clients.size()];
    int edgeCount[clients.size()];

    for (int v=0; v < clientMatrix.size(); v++) {
        for (int i=0; i<clientMatrix[v].size(); i++) {
            if (clientMatrix[v][i] > 0)
                edgeCount[clientMatrix[v][i]]++;
        }
    }


}