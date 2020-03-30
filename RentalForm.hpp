//
// Created by Vincent Valenzuela and Ari Encarnacion
//

#ifndef PROJECT02_RENTALFORM_HPP
#define PROJECT02_RENTALFORM_HPP


#include <string>

class RentalForm {
public:
    RentalForm(): startDate{-1}, endDate{-1}, amount{-1}{}
    RentalForm(int s, int e, int a) : startDate{s}, endDate{e}, amount{a}{}
    int getStartDate() { return startDate; }
    int getEndDate() { return endDate; }
    int getAmount() { return amount; }

private:
    int startDate;
    int endDate;
    int amount;
};


#endif //PROJECT02_RENTALFORM_HPP
