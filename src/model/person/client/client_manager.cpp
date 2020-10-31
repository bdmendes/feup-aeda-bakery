//
// Created by bdmendes on 29/10/20.
//

#include "client_manager.h"
#include <algorithm>
#include <exception/person_exception.h>

ClientManager::ClientManager() : _clients(std::set<Client*, Smaller>()) {
}

bool ClientManager::has(Client *client) const {
    return std::find(_clients.begin(),_clients.end(), client) != _clients.end();
}

Client *ClientManager::get(unsigned position) {
    if (position >= _clients.size()) throw InvalidPersonPosition(position, _clients.size());
    auto it = _clients.begin(); std::advance(it, position);
    return *it;
}

std::set<Client *, Smaller> ClientManager::getAll() {
    return _clients;
}

Client* ClientManager::add(std::string name, bool premium, int tributaryNumber, Credential credential) {
    auto* client = new Client(std::move(name), premium, tributaryNumber, std::move(credential));
    if(has(client)) throw PersonAlreadyExists(client->getName(),client->getTributaryNumber());
    _clients.insert(client);
    return client;
}

Client* ClientManager::remove(Client *client) {
    auto position = std::find(_clients.begin(), _clients.end(),client);
    if(position == _clients.end())
        throw PersonDoesNotExist(client->getName(), client->getTributaryNumber());
    _clients.erase(position);
    return client;
}

Client* ClientManager::remove(unsigned position) {
    if(position >= _clients.size()) throw InvalidPersonPosition(position, _clients.size());
    auto it = _clients.begin(); std::advance(it, position);
    _clients.erase(it);
    return *it;
}

