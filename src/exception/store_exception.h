
#ifndef FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H
#define FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H

#include <stdexcept>
#include <iostream>

/**
 * Class relative to the exception of a store without workers.
 */
class StoreHasNoWorkers : public std::logic_error{
public:
    /**
     * Creates a new StoreHasNoWorkers exception object.
     */
    explicit StoreHasNoWorkers();
};

/**
 * Class relative to the exception of a nonexistent store location.
 */
class LocationDoesNotExist : public std::invalid_argument{
public:
    /**
     *  Creates a new LocationDoesNotExist exception object.
     *
     * @param location the store location
     */
    explicit LocationDoesNotExist(const std::string& location);
};

/**
 * To be thrown when the user searches for the location with a invalid index
 */
class InvalidLocationPosition : public std::invalid_argument{
public:
    /**
     * Create a new Invalid
     * @param position the set index
     */
    explicit InvalidLocationPosition(unsigned long position);
};

#endif //FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H
