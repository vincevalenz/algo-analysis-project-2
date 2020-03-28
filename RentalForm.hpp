//
// Created by Vincent Valenzuela
//

#ifndef PROJECT02_RENTALFORM_HPP
#define PROJECT02_RENTALFORM_HPP


#include <vector>

class RentalForm {
public:
    int getStartDate() { return startDate; }
    int getEndDate() { return endDate; }
    int getAmount() { return amount; }
    void setStartDate(int s) { startDate = s; }
    void setEndDate(int e) { endDate = e; }
    void setAmount(int a) { amount = a; }

    std::vector<RentalForm*> &getEdges() { return edges; }
    void addEdge(RentalForm *f) { edges.push_back(f); }

private:
    int startDate;
    int endDate;
    int amount;
    std::vector<RentalForm*> edges;
};


#endif //PROJECT02_RENTALFORM_HPP
