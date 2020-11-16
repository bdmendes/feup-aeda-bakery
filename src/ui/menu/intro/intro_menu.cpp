//
// Created by bdmendes on 14/11/20.
//

#include "intro_menu.h"
#include "ui/menu/login/login_menu.h"

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
            if (validInput1Cmd1ArgFree(input,"import")){
                printLogo("Import data");
                std::cout << "waiting for file handling to be implemented. press enter to exit\n";
                std::string i;
                std::getline(std::cin,i);
                break;
            }
            if (validInput1Cmd1ArgFree(input,"export")){
                printLogo("Export data");
                std::cout << "waiting for file handling to be implemented. press enter to exit\n";
                std::string i;
                std::getline(std::cin,i);
                break;
            }
            printError();
        }
    }
}

IntroMenu::IntroMenu(Store &s) : UI(s) {
}
