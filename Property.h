//
// Created by Ari Encarnacion on 3/28/2020.
//

#ifndef PROJECT02_PROPERTY_H
#define PROJECT02_PROPERTY_H

#include "RentalForm.hpp"
#include <vector>

class Property {
public:
    Property(): clients{}{}
    void addClient(RentalForm);
private:
    std::vector<RentalForm> clients;
};


#endif //PROJECT02_PROPERTY_H
