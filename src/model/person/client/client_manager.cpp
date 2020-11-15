//
// Created by bdmendes on 29/10/20.
//

#include "client_manager.h"
#include <algorithm>
#include <exception/person_exception.h>
#include <fstream>
#include <sstream>
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

Client* ClientManager::add(std::string name, bool premium, int tributaryNumber, Credential credential) {
    auto* client = new Client(std::move(name), premium, tributaryNumber, std::move(credential));
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

void ClientManager::print(std::ostream &os) {
    int numSpaces = static_cast<int>(std::to_string(_clients.size()).size() + 2);
    os << std::string(numSpaces,util::SPACE)
    << util::column("NAME", true)
    << util::column("TAX ID")
    << util::column("TYPE")
    << util::column("ACCUMULATED") << "\n";

    int count = 1;
    for (const auto& c: _clients){
        os << std::setw(numSpaces) << std::left << std::to_string(count++) + ". ";
        c->print(os);
        os << "\n";
    }
}

void ClientManager::read(std::ifstream &file) {
    //file.open("../model/data/clients.txt");
    if(!file.is_open()){
        //TODO throw FileNotFound
    }
    else{
        std::string line;
        std::string name;
        std::string premium;
        int tributaryNumber;
        Credential credential;

        while(getline(file, line)){
            std::stringstream client(line);
            client>>name>>premium>>tributaryNumber>>credential.username>>credential.password;

            std::replace(name.begin(), name.end(), '-', ' ');
            bool isPremium = (premium == "premium");
            add(name, isPremium, tributaryNumber, credential);
        }
        file.close();
    }
}

void ClientManager::write(std::ofstream &file) {
    //file.open("../model/data/clients.txt");
    if(!file.is_open()){
        //TODO throw FileNotFound
    }
    else{

        std::string nameToSave;
        std::string premiumToSave;

        for(const auto & client: _clients){
            nameToSave = client->getName();
            std::replace(nameToSave.begin(), nameToSave.end(), ' ', '-');
            premiumToSave=(client->isPremium())? "premium" : "not-premium";
            file<<nameToSave<<'\t'<<premiumToSave<<'\t'<<client->getTributaryNumber()<<client->getCredential().username<<client->getCredential().password<<'\n';
        }
        file.close();
    }
}

