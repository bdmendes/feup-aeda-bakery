//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_CLIENT_MANAGER_H
#define FEUP_AEDA_PROJECT_CLIENT_MANAGER_H

#include "client.h"

#include "util/util.h"
#include <iostream>
#include <fstream>

class ClientManager {
public:
    ClientManager();

    bool has(Client* client) const;

    Client* get(unsigned position);
    std::set<Client *, PersonSmaller> getAll();

    Client* add(std::string name, int taxID = Person::DEFAULT_TAX_ID, bool premium = false,
             Credential credential = {Client::DEFAULT_USERNAME, Client::DEFAULT_PASSWORD});
    void remove(Client* client);
    void remove(unsigned position);

    void read(const std::string& path);
    void write(const std::string& path);
    bool print(std::ostream& os, bool showData = true);

    Client* getClient(int taxID) const;

private:
    std::set<Client*, PersonSmaller> _clients;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_MANAGER_H
