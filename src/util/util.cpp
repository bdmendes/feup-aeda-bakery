//
// Created by bdmendes on 31/10/20.
//

#include <algorithm>
#include <sstream>
#include "util.h"

bool util::isdigit(const std::string &str) {
    return std::all_of(str.begin(),str.end(), [](const char c){return std::isdigit(c);});
}

bool util::contains(const std::string &str, const std::string &expected) {
    return str.find(expected) != std::string::npos;
}

void util::normalize(std::string &str, bool isName) {
    for (int i = 0; i < str.size(); ++i){
        //strip unneeded spaces
        if (str.at(i) == SPACE && (i == 0 || (i < str.size() - 1 && str.at(i+1) == SPACE))){
            str.erase(str.begin() + i);
            i--;
            continue;
        }

        //ensure only first word char is uppercase
        if (std::isupper(str.at(i)) && i > 0 && std::isupper(str.at(i-1))){
            str.at(i) = std::tolower(str.at(i));
            continue;
        }

        //if it's a person name, ensure first word char is uppercase
        if (isName && (i==0 || str.at(i-1) == SPACE) && std::islower(str.at(i))){
            str.at(i) = std::toupper(str.at(i));
        }
    }
}

void util::stripSpecialChars(std::string& str){
    str.erase(std::remove_if(str.begin(),str.end(),[](const char c){return !std::isalnum(c) && c != SPACE;}), str.end());
}

void util::lowercase(std::string &str) {
    std::transform(str.begin(),str.end(),str.begin(),[](unsigned char c){return std::tolower(c);});
}

std::string util::column(std::string str, bool large) {
    int colSize = large ? LARGE_COL_WIDTH : SMALL_COL_WIDTH;
    if (str.size() > colSize) str = str.substr(0,colSize - 3) + "...";
    std::ostringstream ss;
    ss << std::setw(colSize) << std::left << str << SPACE;
    return ss.str();
}

std::string util::to_string(float n) {
    std::ostringstream ss;
    ss.precision(2);
    ss << std::fixed << n;
    return ss.str();
}

void util::clearScreen(){
    std::cout << '\n' << ANSI_CLEAR_SCREEN;
}

void util::print(const std::string& s, const int color){
    std::cout << ANSI_ANNOUNCE_COLOR << color << "m" << s << ANSI_RESET_CONSOLE;
}

std::vector<std::string> util::to_words(const std::string& input) {
    std::vector<std::string> words;
    std::stringstream ss(input);
    for (std::string current; ss >> current;) words.push_back(current);
    return words;
}

void util::uppercase(std::string &str) {
    std::transform(str.begin(),str.end(),str.begin(),[](unsigned char c){return std::toupper(c);});
}
