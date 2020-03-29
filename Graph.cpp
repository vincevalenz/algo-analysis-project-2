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

    //for all columns from 1 to end -1
    //check if entire column holds zeros.
    bool noIn = true;
    for(int col = 1; col < matrixSize - 2; col++) {
        for (int row = 0; row < matrixSize - 2; row++) {
            if(clientMatrix[col].at(row) != 0) {
                noIn = false;
            }
        }
        if(noIn) {
            clientMatrix[0].at(col)++;
        }
        noIn = true;
    }

    bool noOut = true;
    for(int row = 1; row < matrixSize - 2; row++) {
        for (int col = 1; col < matrixSize - 2; col++) {
            if(clientMatrix[row].at(col) != 0) {
                noOut = false;
            }
        }
        if(noOut) {
            clientMatrix[row].at(matrixSize-1)++;
        }
        noOut = true;
    }

}
