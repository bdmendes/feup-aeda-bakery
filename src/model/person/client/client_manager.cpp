//
// Created by bdmendes on 29/10/20.
//

#include "client_manager.h"
#include <algorithm>
#include <exception/person_exception.h>
#include <fstream>
#include <sstream>

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
