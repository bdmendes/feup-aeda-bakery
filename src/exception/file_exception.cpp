//
// Created by laimi on 15/11/2020.
//

#include "file_exception.h"

FileNotFound::FileNotFound() : std::logic_error("File not found.")
{}
