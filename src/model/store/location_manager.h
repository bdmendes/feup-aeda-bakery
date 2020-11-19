//
// Created by bdmendes on 19/11/20.
//

#ifndef FEUP_AEDA_PROJECT_LOCATION_MANAGER_H
#define FEUP_AEDA_PROJECT_LOCATION_MANAGER_H

#include "model/order/order.h"

class LocationManager {
public:
    LocationManager();
    std::set<std::string> getAll();
    bool has(const std::string& location);
    void add(const std::string& location);
    void remove(const std::string& location);
    void remove(unsigned long index);
    void read(const std::string& path);
    void write(const std::string &path);
private:
    std::set<std::string> _locations;
};


#endif //FEUP_AEDA_PROJECT_LOCATION_MANAGER_H
