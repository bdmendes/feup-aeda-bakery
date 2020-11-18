//
// Created by bdmendes on 17/11/20.
//

#ifndef FEUP_AEDA_PROJECT_FILE_EXCEPTION_H
#define FEUP_AEDA_PROJECT_FILE_EXCEPTION_H

#include <stdexcept>

#include "../model/product/product_manager.h"
#include "../model/person/worker/worker_manager.h"
#include "../model/person/client/client_manager.h"
#include "../model/order/order_manager.h"
#include "../model/date/date.h"


class FileNotFound : public std::logic_error{
public:
    explicit FileNotFound(const std::string& path);
};


#endif //FEUP_AEDA_PROJECT_FILEEXCEPTION_H
