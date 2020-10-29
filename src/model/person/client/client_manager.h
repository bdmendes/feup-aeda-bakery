//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_CLIENT_MANAGER_H
#define FEUP_AEDA_PROJECT_CLIENT_MANAGER_H

#include "client.h"

class ClientManager {
public:
    ClientManager();
    bool has(Client* client) const;
    Client* get(unsigned position);
    std::vector<Client*> getAll();
    void add(std::string name, bool premium = false, int tributaryNumber = 999999999,
             Credential credential = {"client", "client"});
    void remove(Client* client);
    void remove(unsigned position);
    void read(std::ifstream& file);
    void write(std::ofstream& file);
private:
    std::vector<Client*> _clients;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_MANAGER_H
