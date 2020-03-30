//
// Created by Vincent Valenzuela on 3/29/20.
//

#ifndef PROJECT02_TOPOLOGICALSORT_H
#define PROJECT02_TOPOLOGICALSORT_H


#include <vector>
#include <queue>
#include "RentalForm.hpp"

class TopologicalSort {
public:
    std::vector<RentalForm*> topSort(std::vector<std::vector<int>> clientMatrix, std::vector<RentalForm> &clients);

private:
    std::vector<RentalForm*> stack;
    std::queue<RentalForm*> queue;

};


#endif //PROJECT02_TOPOLOGICALSORT_H
