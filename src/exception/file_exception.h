
#ifndef FEUP_AEDA_PROJECT_FILE_EXCEPTION_H
#define FEUP_AEDA_PROJECT_FILE_EXCEPTION_H

#include <stdexcept>

#include "../model/product/product_manager.h"
#include "../model/person/worker/worker_manager.h"
#include "../model/person/client/client_manager.h"
#include "../model/order/order_manager.h"
#include "../model/date/date.h"

/**
 * Class relative to the exception of a file not found.
 */
class FileNotFound : public std::logic_error{
public:
    /**
     * Creates a new FileNotFound exception object.
     *
     * @param path the file path
     */
    explicit FileNotFound(const std::string& path);
};


#endif //FEUP_AEDA_PROJECT_FILEEXCEPTION_H
