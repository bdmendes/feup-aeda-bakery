//
// Created by bdmendes on 17/11/20.
//

#include "file_exception.h"

FileNotFound::FileNotFound(const std::string &path) : logic_error(path + " not found.") {
}
