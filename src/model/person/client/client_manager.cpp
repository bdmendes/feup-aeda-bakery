//
// Created by bdmendes on 29/10/20.
//

#include "client_manager.h"
#include <algorithm>
#include <exception/person_exception.h>
#include <iomanip>

ClientManager::ClientManager() : _clients(std::set<Client*, PersonSmaller>()) {
}

bool ClientManager::has(Client *client) const {
    return std::find(_clients.begin(),_clients.end(), client) != _clients.end();
}

Client *ClientManager::get(unsigned position) {
    if (position >= _clients.size()) throw InvalidPersonPosition(position, _clients.size());
    auto it = _clients.begin(); std::advance(it, position);
    return *it;
}

std::set<Client *, PersonSmaller> ClientManager::getAll() {
    return _clients;
}

Client* ClientManager::add(std::string name, bool premium, int tributaryNumber, Credential credential) {
    auto* client = new Client(std::move(name), premium, tributaryNumber, std::move(credential));
    if(has(client)) throw PersonAlreadyExists(client->getName(), client->getTaxId());
    _clients.insert(client);
    return client;
}

void ClientManager::remove(Client *client) {
    auto position = std::find(_clients.begin(), _clients.end(),client);
    if(position == _clients.end())
        throw PersonDoesNotExist(client->getName(), client->getTaxId());
    _clients.erase(position);
}

void ClientManager::remove(unsigned position) {
    if(position >= _clients.size()) throw InvalidPersonPosition(position, _clients.size());
    auto it = _clients.begin(); std::advance(it, position);
    _clients.erase(it);
}

void ClientManager::write(std::ostream &os) {
    os << util::column("Name", true)
    << util::column("Tax ID")
    << util::column("Is premium?")
    << util::column("Accumulated")
    << std::endl;
    for (const auto& c: _clients){
        std::string premiumState = c->isPremium() ? "Yes" : "No";
        os << util::column(c->getName(), true)
        << util::column(std::to_string(c->getTaxId()))
        << util::column(premiumState)
        << util::column(std::to_string(c->getPoints()) + " points") << std::endl;
    }
}

