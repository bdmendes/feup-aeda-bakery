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
    static const unsigned LARGE_COL_WIDTH = 30;
    static const unsigned SMALL_COL_WIDTH = 15;

    bool isdigit(const std::string& str);
    bool contains(const std::string& str, const std::string& expected);
    void normalize(std::string& str, bool isName = false);
    void stripSpecialChars(std::string& str);
    void lowercase(std::string& str);

    std::string colGenerate(std::string str, int colSize = SMALL_COL_WIDTH);
}

#endif //FEUP_AEDA_PROJECT_UTIL_H
