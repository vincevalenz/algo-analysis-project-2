//
// Created by Vincent Valenzuela
//

#ifndef PROJECT02_RENTALFORM_HPP
#define PROJECT02_RENTALFORM_HPP


class RentalForm {
public:
    int getStartDate() { return startDate; }
    int getEndDate() { return endDate; }
    int getAmount() { return amount; }
    void setStartDate(int s) { startDate = s; }
    void setEndDate(int e) { endDate = e; }
    void setAmount(int a) { amount = a; }

    RentalForm *getNext() { return next; }
    void setNext(RentalForm *f) { next = f; }

private:
    int startDate;
    int endDate;
    int amount;
    RentalForm *next;
};


#endif //PROJECT02_RENTALFORM_HPP
