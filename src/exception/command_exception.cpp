//
// Created by bdmendes on 31/10/20.
//

#include "command_exception.h"

InvalidCommand::InvalidCommand(const std::string& message) :
    std::invalid_argument(message){
}
