//
// Created by bdmendes on 29/10/20.
//

#include "client_manager.h"
#include <algorithm>
#include <exception/person_exception.h>
#include <iomanip>
#include <exception/file_exception.h>

ClientManager::ClientManager() : _clients() {
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

Client* ClientManager::add(std::string name, int taxID, bool premium, Credential credential) {
    auto* client = new Client(std::move(name), taxID, premium, std::move(credential));
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

bool ClientManager::print(std::ostream &os, bool showData) {
    if (_clients.empty()){
        os << "No clients yet.\n";
        return false;
    }

    os << std::string(_clients.size()/10 + 3, util::SPACE)
    << util::column("NAME", true)
    << util::column("TAX ID");
    if (showData){
        os << util::column("TYPE")
        << util::column("ACCUMULATED")
        << util::column("FEEDBACK");
    }
    else os << util::column("LOGGED IN");
    std::cout << "\n";

    int count = 1;
    for (const auto& c: _clients){
        os << std::to_string(count++) + ". ";
        c->print(os,showData); os << "\n";
    }
    return true;
}

void ClientManager::read(const std::string &path) {
    std::ifstream file(path);
    if(!file) throw FileNotFound(path);

    std::string name, premium;
    int taxID;
    unsigned points;
    Credential credential;

    for(std::string line; getline(file, line); ){
        std::stringstream ss(line);
        ss>>name>>taxID>>premium>>points>>credential.username>>credential.password;

        std::replace(name.begin(), name.end(), '-', ' ');
        Client* client = add(name, taxID, premium == "premium", credential);
        client ->setPoints(points);
    }
}

void ClientManager::write(const std::string &path) {
    std::ofstream file(path);
    if(!file) throw FileNotFound(path);

    std::string nameToSave, premiumToSave;
    for(const auto & client: _clients){
        nameToSave = client->getName();
        std::replace(nameToSave.begin(), nameToSave.end(), ' ', '-');
        premiumToSave=(client->isPremium())? "premium" : "basic";
        file << nameToSave << " " << client->getTaxId() << " " << premiumToSave << " "
        << client->getPoints() << " " << client->getCredential().username << " "
        << client->getCredential().password<<'\n';
    }
}

Client *ClientManager::getClient(int taxID) const{
    for(const auto& _client : _clients){
        if (_client->getTaxId() == taxID) return _client;
    }
    throw PersonDoesNotExist(taxID);
}
