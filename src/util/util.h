//
// Created by bdmendes on 31/10/20.
//

#ifndef FEUP_AEDA_PROJECT_UTIL_H
#define FEUP_AEDA_PROJECT_UTIL_H

#include <string>

namespace util {

    char SPACE = ' ';
    char DELIM = ',';

    bool isdigit(const std::string& str);
    bool contains(const std::string& str, const std::string& expected);
    void normalize(std::string& str, bool isName = false);
    void stripSpecialChars(std::string& str);
    void lowercase(std::string& str);
}

#endif //FEUP_AEDA_PROJECT_UTIL_H
