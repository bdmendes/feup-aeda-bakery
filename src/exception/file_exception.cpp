//
// Created by bdmendes on 17/11/20.
//

#include "file_exception.h"

FileNotFound::FileNotFound() : std::logic_error("File not found.")
{}
