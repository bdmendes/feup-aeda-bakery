//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_CLIENT_MANAGER_H
#define FEUP_AEDA_PROJECT_CLIENT_MANAGER_H

#include "client.h"

#include "util/util.h"
#include <iostream>
#include <fstream>

/**
 *
 */
class ClientManager {
public:
    /**
     * Creates a new client manager.
     */
    ClientManager();

    ~ClientManager();

    /**
     * Checks if the client is on the clients list of the client manager.
     *
     * @param client the client
     * @return true, if the client is on clients list; false, otherwise
     */
    bool has(Client* client) const;

    /**
     * Get the client on the clients list of the client manager at a certain position.
     *
     * @param position the position
     * @return the client in that position
     */
    Client* get(unsigned position);

    Client* getClient(int taxID) const;

    /**
     * Gets the clients list of the client manager.
     *
     * @return the clients list
     */
    std::set<Client *, PersonSmaller> getAll();

    /**
     * Adds a client to the clients list of the client manager.
     *
     * @param name the name
     * @param premium  the type of subscription
     * @param taxID the taxpayer identification number
     * @param credential the access credentials
     * @return the client added to de clients list of the client manager
     */

    Client* add(std::string name, int taxID = Person::DEFAULT_TAX_ID, bool premium = false,
             Credential credential = {Client::DEFAULT_USERNAME, Client::DEFAULT_PASSWORD});

    /**
     * Removes a client from the clients list of the client manager.
     *
     * @param client the client
     */
    void remove(Client* client);

    /**
     * Removes a client from the clients list of client manager, at a certain position.
     *
     * @param position the position
     */
    void remove(unsigned position);

    /**
     *Prints the all the clients' data.
     *
     * @param os the output stream
     * @param showData if true, prints all data: name, taxpayer identification number, subscription type and accumulated
     * points; otherwise, just prints the name and the taxpayer identification number.
     * @return true, if there are already clients; false, otherwise
     */
    bool print(std::ostream& os, bool showData = true);
  
    void read(const std::string& path);
    void write(const std::string& path);

private:
    /**
     * The clients list of the client manager.
     */
    std::set<Client*, PersonSmaller> _clients;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_MANAGER_H
