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

bool UI::isValid(std::string input, const std::vector<std::string> &args, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);

    if (words.size() != !cmd.empty() + 1) return false;
    if (args.empty()) return words.at(0) == cmd;

    return cmd.empty() ?
        std::find(args.begin(),args.end(),words.at(0)) != args.end()
        : (words.at(0) == cmd && std::find(args.begin(),args.end(),words.at(1)) != args.end());
}

bool UI::isValid(std::string input, const std::string &arg, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);

    if (words.size() != !cmd.empty() + 1) return false;
    if (arg.empty()) return words.at(0) == cmd;
    return cmd.empty() ? words.at(0) == arg : (words.at(0) == cmd && words.at(1) == arg);
}

void UI::printOptions(const std::vector<std::string> &options, bool index, std::string message) {
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
