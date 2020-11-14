//
// Created by bdmendes on 14/11/20.
//

#include "intro_menu.h"
#include "login_menu.h"

void IntroMenu::show() {
    printLogo();
    std::cout << SEPARATOR << std::endl
                << "Welcome to the Bakery Store management app.\n"
                << "At any screen, type 'back' to go back.\n"
                << SEPARATOR << std::endl << std::endl;
    const std::vector<std::string> content = {
            "Import from file",
            "Export to file",
            "Manage store"
    };
    printOptions(content);
    for (;;) {
        std::string input = readCommand();
        if (input == BACK) return;
        if (isValid(input, content.size())){
            if (input == "3"){
                LoginMenu loginMenu(_store);
                loginMenu.show();
            }
            break;
        }
        printError();
    }
}

IntroMenu::IntroMenu(Store &s) : UI(s) {
}
