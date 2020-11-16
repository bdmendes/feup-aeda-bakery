//
// Created by bdmendes on 07/11/20.
//

#include "ui.h"
#include "ui/menu/intro_menu.h"

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

bool UI::validInput1Word(const std::string &input, bool digit) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 1 && (!digit || isdigit(words.at(0)));
}

bool UI::validInput1Cmd(std::string input, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 1 && words.at(0) == cmd;
}

bool UI::validInput1Cmd1Arg(std::string input, const std::string &cmd, bool digitArg) {
    std::vector<std::string> words = to_words(input);
    if (words.size() != 2 || words.at(0) != cmd) return false;
    return !digitArg || isdigit(words.at(1));
}

bool UI::validInput1Cmd1Arg(std::string input, const std::string &cmd, const std::vector<std::string> &args) {
    std::vector<std::string> words = to_words(input);
    if (words.size() != 2 || words.at(0) != cmd) return false;
    return std::find(args.begin(),args.end(),words.at(1)) != args.end();
}

bool UI::validInput1Cmd1Arg(const std::string& input, const std::string &cmd, const std::string &arg) {
    std::vector<std::string> words = to_words(input);
    if (words.size() != 2 || words.at(0) != cmd) return false;
    return words.at(1) == arg;
}

bool UI::validInput1Cmd2Args(const std::string& input, const std::string &cmd, const std::vector<std::string> &args1,
                             const std::vector<std::string> &args2) {
    std::vector<std::string> words = to_words(input);
    if (words.size() != 3 || words.at(0) != cmd) return false;
    return std::find(args1.begin(),args1.end(),words.at(1)) != args1.end()
    && std::find(args2.begin(),args2.end(),words.at(2)) != args1.end();
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
    if (index) std::cout << "Please enter a number as requested! ";
    else std::cout << "Please enter a command as requested! ";
}

void UI::printLogo() {
    util::clearScreen();
    util::print("BAKERY STORE\n\n",util::BLUE);
}
