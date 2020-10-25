//
// Created by Filipa on 10/25/2020.
//

#ifndef SRC_STOREEXCEPTIONS_H
#define SRC_STOREEXCEPTIONS_H

#include <iostream>
#include <string>

class StoreExceptions {
public:
    StoreExceptions(std::string name);

protected:
    std::string _name;
};

class StoreHasNoWorkers : StoreExceptions{
public:
    StoreHasNoWorkers(std::string name);
    std::ostream & operator<<(std::ostream& out);
};


#endif //SRC_STOREEXCEPTIONS_H
