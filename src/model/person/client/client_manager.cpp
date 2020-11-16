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
    return _clients.find(client) != _clients.end();
}

Client *ClientManager::get(unsigned position) {
    if (position >= _clients.size()) throw InvalidPersonPosition(position, _clients.size());
    auto it = _clients.begin(); std::advance(it, position);
    return *it;
}

std::set<Client *, PersonSmaller> ClientManager::getAll() {
    return _clients;
}

Client* ClientManager::add(std::string name, bool premium, int taxID, Credential credential) {
    auto* client = new Client(std::move(name), premium, taxID, std::move(credential));
    if(has(client)) throw PersonAlreadyExists(client->getName(), client->getTaxId());
    _clients.insert(client);
    return client;
}

void ClientManager::remove(Client *client) {
    auto position = _clients.find(client);
    if(position == _clients.end())
        throw PersonDoesNotExist(client->getName(), client->getTaxId());
    _clients.erase(position);
}

void ClientManager::remove(unsigned position) {
    if(position >= _clients.size()) throw InvalidPersonPosition(position, _clients.size());
    auto it = _clients.begin(); std::advance(it, position);
    _clients.erase(it);
}

void ClientManager::print(std::ostream &os, bool showData) {
    int idxPadding = static_cast<int>(std::to_string(_clients.size()).size() + 2);

    os << std::string(idxPadding, util::SPACE)
    << util::column("NAME", true)
    << util::column("TAX ID");
    if (showData){
        os << util::column("TYPE")
                << util::column("ACCUMULATED");
    }
    std::cout << "\n";

    int count = 1;
    for (const auto& c: _clients){
        os << std::setw(idxPadding) << std::left << std::to_string(count++) + ". ";
        c->print(os,showData);
        os << "\n";
    }
}

