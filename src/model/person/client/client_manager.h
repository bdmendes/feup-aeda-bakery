
#ifndef FEUP_AEDA_PROJECT_CLIENT_MANAGER_H
#define FEUP_AEDA_PROJECT_CLIENT_MANAGER_H

#include "client.h"
#include "util/util.h"

#include <iostream>
#include <fstream>

/**
 * Class that manages the store clients.
 */
class ClientManager {
public:
    /**
     * Creates a new ClientManager object.
     */
    ClientManager();

    /**
     * Destructs the ClientManager object.
     */
    ~ClientManager();

    /**
     * Checks if the client is on the clients list.
     *
     * @param client the client to check if is on the list
     * @return true, if there are no clients on the list yet; false, otherwise
     */
    bool has(Client* client) const;

    /**
     * Get the client on the clients list at a certain position.
     *
     * @param position the position
     * @return the client in that position
     */
    Client* get(unsigned position);

    /**
     * Gets a client from the clients list by its taxpayer identification number.
     *
     * @param taxID the taxpayer identification number
     * @return the client on the clients list with that taxpayer identification number
     */
    Client* getClient(int taxID) const;

    /**
     * Gets the clients list.
     *
     * @return the clients list
     */
    std::set<Client *, PersonSmaller> getAll();

    /**
     * Adds a client to the clients list.
     *
     * @param name the name
     * @param premium the subscription type (true, if it is premium; false, otherwise)
     * @param taxID the taxpayer identification number
     * @param credential the login credentials
     * @return the client added to de clients list of the client manager
     */
    Client* add(std::string name, int taxID = Person::DEFAULT_TAX_ID, bool premium = false,
             Credential credential = {Client::DEFAULT_USERNAME, Client::DEFAULT_PASSWORD});

    /**
     * Removes a client from the clients list.
     *
     * @param client the client to remove
     */
    void remove(Client* client);

    /**
     * Removes a client from the clients list at a certain position.
     *
     * @param position the position
     */
    void remove(unsigned position);

    /**
     * Prints all the clients data.
     *
     * @param os the output stream
     * @param showData if true, for all clients, prints all data: name, taxpayer identification number, subscription
     * type, accumulated points and mean evaluation; otherwise, just prints the name, the taxpayer identification number
     * and the log status.
     * @return true, if there are already clients; false, otherwise
     */
    bool print(std::ostream& os, bool showData = true);

    /**
     * Reads all the clients data (name, the taxpayer identification number and login credentials) from a file
     *  and creates new ones with that data.
     *
     * @param path the file path
     */
    void read(const std::string& path);

    /**
     * Writes all the clients data that are on the clients list (name, the taxpayer identification number and login
     * credentials) to a file.
     *
     * @param path the file path
     */
    void write(const std::string& path);
private:
    /**
     * The list of all the clients.
     */
    std::set<Client*, PersonSmaller> _clients;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_MANAGER_H
