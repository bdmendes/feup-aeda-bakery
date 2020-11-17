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
    std::set<Client *, PersonSmaller> getAll();

    Client* add(std::string name, bool premium = false, int taxID = Person::DEFAULT_TAX_ID,
             Credential credential = {Client::DEFAULT_USERNAME, Client::DEFAULT_PASSWORD});
    void remove(Client* client);
    void remove(unsigned position);

    void read(std::ifstream& file);
    bool print(std::ostream& os, bool showData = true);
private:
    std::set<Client*, PersonSmaller> _clients;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_MANAGER_H
