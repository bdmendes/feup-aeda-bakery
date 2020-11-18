//
// Created by bdmendes on 14/11/20.
//

#include "intro_menu.h"
#include "ui/menu/login/login_menu.h"

void IntroMenu::show() {
    printLogo({});
    std::cout << SEPARATOR
              << "Welcome to the Bakery Store management app.\n"
              << "At any screen, type 'back' to go back.\n"
              << SEPARATOR << std::endl;
    const std::vector<std::string> content = {
            "import reset - import data from files; clear current store",
            "import update - import data from files; add new data to the current",
            "export data - export current store data to files",
            "manage store - enter store management"
    };
    printOptions(content);

    for (;;) {
        std::string input = readCommand();
        if (input == EXIT) return;
        if (validInput1Cmd1Arg(input, "manage","store")) {
            LoginMenu(_store).show();
            break;
        }
        if (validInput1Cmd1Arg(input,"import","reset")){
            importData(true);
            break;
        }
        if (validInput1Cmd1Arg(input,"import","update")){
            importData(false);
            break;
        }
        if (validInput1Cmd1Arg(input,"export","data")){
            exportData();
            break;
        }
        printError();
    }

    show();
}

IntroMenu::IntroMenu(Store &s) : UI(s) {
}

void IntroMenu::importData(bool doReset) {
    std::cout << "\nIMPORT DATA" << ((doReset)? " - RESET\n" : " - UPDATE\n")
    << SEPARATOR << "'data' folder path: ";
    std::string input = readCommand();
    if (input == BACK) return;
    std::cout << "\n" << _store.read(input, doReset)
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
