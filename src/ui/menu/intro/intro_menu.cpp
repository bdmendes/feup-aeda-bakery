//
// Created by bdmendes on 14/11/20.
//

#include "intro_menu.h"
#include "ui/menu/login/login_menu.h"

void IntroMenu::show() {
    printLogo({});
    std::cout << SEPARATOR
              << "Welcome to the Bakery Store management app.\n"
              << "You start with a blank store. Import data or start fresh.\n"
              << "At any screen, type 'back' to go back.\n"
              << SEPARATOR << std::endl;
    const std::vector<std::string> content = {
            "import data - import data from files",
            "export data - export data to files",
            "manage store - enter store management"
    };
    printOptions(content);

    for (;;) {
        std::string input = readCommand();
        if (input == EXIT) return;
        else if (validInput1Cmd1Arg(input, "manage","store")) {
            LoginMenu(_store).show();
            break;
        }
        else if (validInput1Cmd1Arg(input,"import","data")){
            importData();
            break;
        }
        else if (validInput1Cmd1Arg(input,"export","data")){
            exportData();
            break;
        }
        else printError();
    }

    show(); // allow back
}

IntroMenu::IntroMenu(Store &s) : UI(s) {
}

void IntroMenu::importData() {
    std::cout << "\nIMPORT DATA\n"
    << SEPARATOR << "'data' folder path: ";
    std::string input = readCommand();
    if (input == BACK) return;
    std::cout << "\n" << _store.read(input)
    << "\nPress enter to go back. ";
    std::getline(std::cin,input);
}

void IntroMenu::exportData() {
    std::cout << "\nEXPORT DATA\n" << SEPARATOR
              << "'data' folder path: ";
    std::string input = readCommand();
    if (input == BACK) return;
    std::cout << "\n" << _store.write(input)
              << "\nPress enter to go back. ";
    std::getline(std::cin,input);
}
