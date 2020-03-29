//
// Created by Ari Encarnacion on 3/28/2020.
//

#include "Graph.h"
#include <iomanip>

void Graph::print() {
    //print clientMatrix
    //label
    std::cout << "     ";
    std::cout<< std::left << std::setw(4)<< "s" <<  ' ';
    for(int i=1; i < matrixSize-1; i++) {
    std::cout << std::left << std::setw(4) << i << ' ';
    }
    std::cout<< std::left << std::setw(4)<< "e" <<  ' ';
    std::cout <<'\n';

    //print values in clientMatrix

    for(int i= 0; i < matrixSize; i++) {
        if(i == 0) {
            std::cout<< std::left << std::setw(4)<< "s" <<  ' ';
        } else if (i == matrixSize-1) {
            std::cout<< std::left << std::setw(4)<< "e" <<  ' ';
        } else {
            std::cout << std::left << std::setw(4) << i << ' ';
        }

        for(int k=0; k < matrixSize; k++) {
            std::cout << std::left << std::setw(4) << clientMatrix[i][k] << ' ';
        }

        std::cout<<'\n';
    }
}

void Graph::buildMatrix() {
    for(int i = 0; i < clients.size(); i++) {
        for(int k = 0; k < clients.size(); k++)
            if(clients.at(k).getStartDate() >= clients.at(i).getEndDate()) {
                clientMatrix[i+1].at(k+1)++;
            }
    }
}
