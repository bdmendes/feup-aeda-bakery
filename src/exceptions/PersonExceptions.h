//
// Created by Filipa on 10/25/2020.
//

#ifndef SRC_PERSONEXCEPTIONS_H
#define SRC_PERSONEXCEPTIONS_H

#include <iostream>
#include <string>
class PersonExceptions {
public:
    PersonExceptions(std::string name, int tributaryNumber);
protected:
    std::string _name;
    int _tributaryNumber;

};

class ClientDoesNotExist : PersonExceptions{
public:
    ClientDoesNotExist(std::string name, int tributaryNumber);
    std::ostream & operator<<(std::ostream& out);

};

class WorkerDoesNotExist : PersonExceptions{
public:
    WorkerDoesNotExist(std::string name, int tributaryNumber);
    std::ostream & operator<<(std::ostream& out);
};



#endif //SRC_PERSONEXCEPTIONS_H
