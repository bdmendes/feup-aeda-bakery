
#ifndef FEUP_AEDA_PROJECT_LOCATION_MANAGER_H
#define FEUP_AEDA_PROJECT_LOCATION_MANAGER_H

#include "model/order/order.h"

/**
 * Class that manages the store locations.
 */
class LocationManager {
public:
    /**
     * Creates a new LocationManager object.
     */
    LocationManager();

    /**
     * Gets the list of all available locations.
     *
     * @return the list of all available locations
     */
    std::set<std::string> getAll();

    /**
     * Checks if a certain location is on the locations list.
     *
     * @param location the location
     * @return true, if the location is on the locations list; false, otherwise
     */
    bool has(const std::string& location);

    /**
     * Adds a location to the locations list.
     *
     * @param location the location
     */
    void add(const std::string& location);

    /**
     * Removes a location from the locations list.
     *
     * @param location the location
     */
    void remove(const std::string& location);

    /**
     * Reads from a file all the locations data: name
     *
     * @param path
     */
    void read(const std::string& path);
    void write(const std::string &path);
private:
    std::set<std::string> _locations;
};


#endif //FEUP_AEDA_PROJECT_LOCATION_MANAGER_H
