//
// Created by Vincent Valenzuela and Ari Encarnacion
//

#ifndef PROJECT02_RENTALFORM_HPP
#define PROJECT02_RENTALFORM_HPP


//#include <vector>

class RentalForm {
public:
    RentalForm(): startDate{-1}, endDate{-1}, amount{-1}{}
    RentalForm(int start, int end, int amt): startDate{start}, endDate{end}, amount{amt}{}
    int getStartDate() { return startDate; }
    int getEndDate() { return endDate; }
    int getAmount() { return amount; }
    void setStartDate(int s) { startDate = s; }
    void setEndDate(int e) { endDate = e; }
    void setAmount(int a) { amount = a; }

private:
    int startDate;
    int endDate;
    int amount;
};


#endif //PROJECT02_RENTALFORM_HPP
