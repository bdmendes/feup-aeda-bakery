//
// Created by bdmendes on 14/11/20.
//

#include "intro_menu.h"
#include "login_menu.h"

void IntroMenu::show() {
    for (;;) {
        printLogo();
        std::cout << SEPARATOR
                  << "Welcome to the Bakery Store management app.\n"
                  << "At any screen, type 'back' to go back.\n"
                  << SEPARATOR << std::endl;
        const std::vector<std::string> content = {
                "import <name> - import data from folder called name",
                "export <name> - export data to folder called name",
                "manage - enter store management"
        };
        printOptions(content);

        for (;;) {
            std::string input = readCommand();
            if (input == EXIT) return;
            if (validInput1Cmd(input, "manage")) {
                LoginMenu loginMenu(_store);
                loginMenu.show();
                break;
            }
            if (validInput1Cmd1Arg(input,"import",false)){
                printLogo();
                std::cout << "waiting for file handling to be implemented. press enter to exit\n";
                std::string input;
                std::getline(std::cin,input);
                break;
            }
            if (validInput1Cmd1Arg(input,"export",false)){
                printLogo();
                std::cout << "waiting for file handling to be implemented. press enter to exit\n";
                std::string input;
                std::getline(std::cin,input);
                break;
            }
            printError(false);
        }
    }
}

IntroMenu::IntroMenu(Store &s) : UI(s) {
}
