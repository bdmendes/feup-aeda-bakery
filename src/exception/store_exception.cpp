
#include "store_exception.h"

StoreHasNoWorkers::StoreHasNoWorkers() :
    std::logic_error("This store has no workers!"){
}

LocationDoesNotExist::LocationDoesNotExist(const std::string &location):
    invalid_argument(location + " does not exist.") {
}

LocationAlreadyExists::LocationAlreadyExists(const std::string &location):
    invalid_argument(location + " already exists.") {
}