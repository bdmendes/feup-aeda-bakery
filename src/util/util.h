//
// Created by bdmendes on 31/10/20.
//

#ifndef FEUP_AEDA_PROJECT_UTIL_H
#define FEUP_AEDA_PROJECT_UTIL_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_set>

namespace util {

    static const char SPACE = ' ';
    static const char DELIM = ',';
    static const char TOPIC = '|';
    static const char* SEPARATOR = "------------------------------------------------";
    static const int LARGE_COL_WIDTH = 20;
    static const int SMALL_COL_WIDTH = 15;

    bool isdigit(const std::string& str);
    bool contains(const std::string& str, const std::string& expected);
    void normalize(std::string& str, bool isName = false);
    void stripSpecialChars(std::string& str);
    void lowercase(std::string& str);
    std::string to_string (float n);
    std::string column(std::string str, bool large = false);
    std::vector<std::string> to_words(const std::string& input);

    static const char* ANSI_ANNOUNCE_COLOR = "\033[38;5;";
    static const char* ANSI_RESET_CONSOLE = "\033[0m";
    static const char* ANSI_CLEAR_SCREEN = "\x1B[2J\x1B[H";

    static const int RED = 160;
    static const int GREEN = 2;
    static const int BLUE = 6;

    void clearScreen();
    void print(const std::string& s, int color);
}

#endif //FEUP_AEDA_PROJECT_UTIL_H
