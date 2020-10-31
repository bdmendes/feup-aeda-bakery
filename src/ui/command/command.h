//
// Created by bdmendes on 31/10/20.
//

#ifndef FEUP_AEDA_PROJECT_COMMAND_H
#define FEUP_AEDA_PROJECT_COMMAND_H

#include <string>

enum class CommandType{
    EXACT,
    CONTAINS
};

class Command {
public:
    Command(std::string input, std::string expected, CommandType type = CommandType::EXACT);
private:
    bool isValid() const;
    std::string _input;
    std::string _expected;
    CommandType _type;
};


#endif //FEUP_AEDA_PROJECT_COMMAND_H
