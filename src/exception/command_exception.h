//
// Created by bdmendes on 31/10/20.
//

#ifndef FEUP_AEDA_PROJECT_COMMAND_EXCEPTION_H
#define FEUP_AEDA_PROJECT_COMMAND_EXCEPTION_H

#include <stdexcept>

class InvalidCommand : public std::invalid_argument {
public:
    explicit InvalidCommand(const std::string& message);
};

#endif //FEUP_AEDA_PROJECT_COMMAND_EXCEPTION_H
