//
// Created by bdmendes on 07/11/20.
//

#include "ui.h"
#include "ui/menu/intro_menu.h"

const char* UI::BACK = "back";

UI::UI(Store &store) : _store(store){
}

std::string UI::readCommand() {
    std::string input;
    std::getline(std::cin,input);
    normalize(input);
    return input;
}

bool UI::isValid(std::string input, const std::vector<std::string> &args, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);

    if (words.size() != !cmd.empty() + 1) return false;
    return cmd.empty() ?
        std::find(args.begin(),args.end(),words.at(0)) != args.end()
        : (words.at(0) == cmd && std::find(args.begin(),args.end(),words.at(1)) != args.end());
}

bool UI::isValid(std::string input, const std::string &arg, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);

    if (words.size() != !cmd.empty() + 1) return false;
    return cmd.empty() ? words.at(0) == arg : (words.at(0) == cmd && words.at(1) == arg);
}

bool UI::isValid(std::string input, const int maxIdxArg, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);

    if (words.size() != !cmd.empty() + 1) return false;
    if (!cmd.empty() && words.at(0) != cmd) return false;

    int argPos = cmd.empty()? 0 : 1;
    for (const auto& argChar: words.at(argPos)) if (!std::isdigit(argChar)) return false;
    int arg = std::stoi(words.at(argPos));
    return arg >= 1 && arg <= maxIdxArg;
}

void UI::printOptions(const std::vector<std::string> &options, bool index) {
    if (index){
        int counter = 1;
        std::cout << "Choose 1-" << std::to_string(options.size()) << ":\n";
        for (const auto& o: options) std::cout << std::to_string(counter++) << ". " << o << '\n';
    }
    else {
        std::cout << "Available commands:\n";
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
