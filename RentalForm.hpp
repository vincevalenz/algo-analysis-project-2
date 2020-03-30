//
// Created by Vincent Valenzuela and Ari Encarnacion
//

#ifndef PROJECT02_RENTALFORM_HPP
#define PROJECT02_RENTALFORM_HPP


#include <string>

class RentalForm {
public:
    RentalForm(): name{}, startDate{-1}, endDate{-1}, amount{-1}{}
    RentalForm(std::string n, int s, int e, int a): name{n}, startDate{s}, endDate{e}, amount{a}{}
    std::string getName() { return name; }
    int getStartDate() { return startDate; }
    int getEndDate() { return endDate; }
    int getAmount() { return amount; }

private:
    std::string name;
    int startDate;
    int endDate;
    int amount;
};


#endif //PROJECT02_RENTALFORM_HPP
