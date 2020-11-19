//
// Created by bdmendes on 19/11/20.
//

#include <algorithm>
#include "exception/file_exception.h"
#include "location_manager.h"

LocationManager::LocationManager() : _locations(){
    _locations.insert(Order::DEFAULT_LOCATION);
}

bool LocationManager::has(const std::string& location) {
    return std::find(_locations.begin(), _locations.end(), location) != _locations.end();
}

void LocationManager::add(const std::string& location) {
    _locations.insert(location);
}

void LocationManager::remove(const std::string& location) {
    if (!has(location)) throw LocationDoesNotExist(location);
    _locations.erase(std::find(_locations.begin(), _locations.end(), location));
}

void LocationManager::read(const std::string& path) {
    std::ifstream file(path);
    if (!file) throw FileNotFound(path);

    for (std::string line; std::getline(file,line);){
        if (line.empty()) continue;
        std::replace(line.begin(),line.end(),'-',' ');
        add(line);
    }
}

void LocationManager::write(const std::string &path) {
    std::ofstream file(path);
    if (!file) throw FileNotFound(path);

    for (const auto& b: _locations){
        std::string styledName = b;
        std::replace(styledName.begin(),styledName.end(),' ','-');
        file << styledName << "\n";
    }
}

std::set<std::string> LocationManager::getAll() {
    return _locations;
}
