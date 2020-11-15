//
// Created by bdmendes on 14/11/20.
//

#include "intro_menu.h"
#include "login_menu.h"

void IntroMenu::show() {
    for (;;) {
        printLogo();
        std::cout << SEPARATOR << std::endl
                  << "Welcome to the Bakery Store management app.\n"
                  << "At any screen, type 'back' to go back, or 'exit' to exit.\n"
                  << SEPARATOR << std::endl << std::endl;
        const std::vector<std::string> content = {
                "import <name> - import data from folder called name",
                "export <name> - export data to folder called name",
                "manage - enter store management"
        };
        printOptions(content,false);

        for (;;) {
            std::string input = readCommand();
            if (input == EXIT) return;
            if (isValid(input, "manage")) {
                LoginMenu loginMenu(_store);
                loginMenu.show();
                break;
            }
            printError(false);
        }
    }
}

IntroMenu::IntroMenu(Store &s) : UI(s) {
}
