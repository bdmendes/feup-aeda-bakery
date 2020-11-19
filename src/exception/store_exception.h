
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
     * Creates a new StoreHasNoWorkers object.
     */
    explicit StoreHasNoWorkers();
};

#endif //FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H
