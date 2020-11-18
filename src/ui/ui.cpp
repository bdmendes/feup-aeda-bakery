//
// Created by bdmendes on 07/11/20.
//

#include "ui.h"

const char* UI::BACK = "back";
const char* UI::EXIT = "exit";

UI::UI(Store &store) : _store(store) {
}

std::string UI::readCommand(bool lowCase) {
    std::string input;
    std::getline(std::cin,input);
    normalize(input);
    if (lowCase) util::lowercase(input);
    return input;
}

bool UI::validInput1Cmd(const std::string& input, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 1 && words.at(0) == cmd;
}

bool UI::validInput1Cmd1ArgDigit(const std::string& input, const std::string &cmd, bool acceptFloat) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 2 && words.at(0) == cmd && isdigit(words.at(1),acceptFloat);
}

bool UI::validInput1Cmd1Arg(const std::string& input, const std::string &cmd, const std::string &arg) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 2 && words.at(0) == cmd && words.at(1) == arg;
}

bool UI::validInput1Cmd2ArgsDigit(const std::string &input, const std::string &cmd, bool acceptFloatArg2) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 3 && words.at(0) == cmd
           && isdigit(words.at(1)) && isdigit(words.at(2),acceptFloatArg2);
}


void UI::printOptions(const std::vector<std::string> &options, std::string message, bool index) {
    if (message.empty()) message = index ?
            "Choose 1-" + std::to_string(options.size()) : "Available commands:";
    std::cout << message << '\n';
    if (index){
        int counter = 1;
        for (const auto& o: options) std::cout << std::to_string(counter++) << ". " << o << '\n';
    }
    else {
        for (const auto& o: options) std::cout << "-> " << o << "\n";
    }
    std::cout << '\n';
}

void UI::printError(bool index) {
    if (index) std::cout << "Unrecognized index. Try again.\n";
    else std::cout << "Unrecognized command. Try again.\n";
}

void UI::printLogo(const std::string& detail) {
    util::clearScreen();
    std::string title = _store.getName();
    if (!detail.empty()) title += " - " + detail;
    uppercase(title);
    util::print(title + "\n\n",util::BLUE);
}

