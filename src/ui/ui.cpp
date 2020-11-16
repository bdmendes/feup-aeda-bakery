//
// Created by bdmendes on 07/11/20.
//

#include "ui.h"
#include "ui/menu/intro/intro_menu.h"

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

bool UI::validInput1CmdFree(const std::string &input, bool digit) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 1 && (!digit || isdigit(words.at(0)));
}

bool UI::validInput1Cmd(std::string input, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 1 && words.at(0) == cmd;
}

bool UI::validInput1Cmd1ArgDigit(std::string input, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 2 && words.at(0) == cmd && isdigit(words.at(1));
}

bool UI::validInput1Cmd1Arg(std::string input, const std::string &cmd, const std::vector<std::string> &args) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 2 && words.at(0) == cmd
    && std::find(args.begin(),args.end(),words.at(1)) != args.end();
}

bool UI::validInput1Cmd1Arg(const std::string& input, const std::string &cmd, const std::string &arg) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 2 && words.at(0) == cmd && words.at(1) == arg;
}

bool UI::validInput1Cmd2Args(const std::string& input, const std::string &cmd, const std::vector<std::string> &args1,
                             const std::vector<std::string> &args2) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 3 && words.at(0) == cmd
    && std::find(args1.begin(),args1.end(),words.at(1)) != args1.end()
    && std::find(args2.begin(),args2.end(),words.at(2)) != args1.end();
}

bool UI::validInput1Cmd1ArgFree(const std::string& input, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 2 && words.at(0) == cmd;
}

bool UI::validInput1Cmd2ArgsDigit(const std::string &input, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 3 && words.at(0) == cmd
           && isdigit(words.at(1)) && isdigit(words.at(2));
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
    if (index) std::cout << "Unrecognized index. Try again: ";
    else std::cout << "Unrecognized command. Try again: ";
}

void UI::printLogo(const std::string& detail) const{
    util::clearScreen();
    std::string title = _store.getName();
    if (!detail.empty()) title += " - " + detail;
    uppercase(title);
    util::print(title + "\n\n",util::BLUE);
}

