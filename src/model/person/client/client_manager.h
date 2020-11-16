//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_CLIENT_MANAGER_H
#define FEUP_AEDA_PROJECT_CLIENT_MANAGER_H

#include "client.h"

#include "util/util.h"
#include <iostream>

class ClientManager {
public:
    ClientManager();

    bool has(Client* client) const;

    Client* get(unsigned position);
    Client* get(int taxId);
    std::set<Client *, PersonSmaller> getAll();
    Client* add(std::string name, int tributaryNumber = 999999999, bool premium = false,
             Credential credential = {"client", "client"});
    void remove(Client* client);
    void remove(unsigned position);

    void read(std::ifstream& file);
    void write(std::ofstream& file) const;
    void print(std::ostream& os);
private:
    std::set<Client*, PersonSmaller> _clients;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_MANAGER_H
