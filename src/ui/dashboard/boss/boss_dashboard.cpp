//
// Created by bdmendes on 14/11/20.
//

#include "boss_dashboard.h"

BossDashboard::BossDashboard(Store &store) : Dashboard(store, &store.boss), _boss(&store.boss) {
}



void BossDashboard::show() {
    Dashboard::show();
}

void BossDashboard::manageProducts() {
    //showProducts(true);

    const std::vector<std::string> options = {
            "new product - add new product",
            "delete <index> - delete existing product"
    };
    printOptions(options);

    for(;;) {
        std::string input = readCommand();
        if (input == BACK) return;
        else if (validInput1Cmd1Arg(input, "new", "product")) {
            printLogo(); // to do
            break;
        } else if (validInput1Cmd1ArgDigit(input, "delete")) {
            try {
                int arg = std::stoi(to_words(input).at(1));
                _store.productManager.remove(_store.productManager.get(--arg));
                break;
            }
            catch (std::exception &e) {
                std::cout << e.what() << SPACE;
            }
        } else printError();
    }
}

void BossDashboard::addProduct() {

}
