//
// Created by bdmendes on 14/11/20.
//

#include "login_menu.h"

void LoginMenu::show() {
    printLogo();
    const std::vector<std::string> content = {
            "Worker",
            "Client",
            "Boss"
    };
    printOptions(content,false,"What are you?");
    for (;;) {
        std::string input = readCommand();
        if (input == BACK) return;
        if (isValid(input, "worker")){
            // to do
            std::cout << "very nice!";
            break;
        }
        printError();
    }
}

LoginMenu::LoginMenu(Store &store) : UI(store) {
}
