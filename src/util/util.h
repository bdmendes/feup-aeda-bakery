//
// Created by bdmendes on 31/10/20.
//

#ifndef FEUP_AEDA_PROJECT_UTIL_H
#define FEUP_AEDA_PROJECT_UTIL_H

#include <string>
#include <iostream>
#include <iomanip>

namespace util {

    static const char SPACE = ' ';
    static const char DELIM = ',';
    static const int LARGE_COL_WIDTH = 20;
    static const int SMALL_COL_WIDTH = 15;
    static const char* SEPARATOR =
            "---------------------------------------------------------------------\n";

    bool isdigit(const std::string& str);
    bool contains(const std::string& str, const std::string& expected);
    void normalize(std::string& str, bool isName = false);
    void stripSpecialChars(std::string& str);
    void lowercase(std::string& str);
    std::string to_string (float n);

    std::string column(std::string str, bool large = false);
}

#endif //FEUP_AEDA_PROJECT_UTIL_H
