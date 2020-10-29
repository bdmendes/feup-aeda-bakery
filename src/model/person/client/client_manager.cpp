//
// Created by bdmendes on 29/10/20.
//

#include "client_manager.h"
#include <algorithm>
#include <exception/person_exception.h>

ClientManager::ClientManager() : _clients() {
}

bool ClientManager::has(Client *client) const {
    return std::find(_clients.begin(),_clients.end(), client) != _clients.end();
}

Client *ClientManager::get(unsigned int position) {
    if (position >= _clients.size()) throw std::invalid_argument("Out of bounds client position");
    return _clients.at(position);
}

std::vector<Client *> ClientManager::getAll() {
    return _clients;
}

void ClientManager::remove(Client *client) {
    auto position = std::find(_clients.begin(), _clients.end(),client);
    if(position == _clients.end())
        throw PersonDoesNotExist(client->getName(), client->getTributaryNumber());
    _clients.erase(position);
}

void ClientManager::remove(unsigned int position) {
    if(position >= _clients.size()) throw std::invalid_argument("Out of bounds client position");
    _clients.erase(_clients.begin() + position);
}

void ClientManager::add(std::string name, bool premium, int tributaryNumber, Credential credential) {
    auto* client = new Client(std::move(name), premium, tributaryNumber, std::move(credential));
    if(has(client)) throw PersonAlreadyExists(client->getName(),client->getTributaryNumber());
    _clients.push_back(client);
}
