//
// Created by bdmendes on 14/11/20.
//

#include "boss_dashboard.h"

BossDashboard::BossDashboard(Store &store) : UI(store) {
}



void BossDashboard::show() {
    printLogo();
    std::cout << "Boss dashboard is work in progress. press enter to exit.";
    std::string input;
    std::getline(std::cin,input);
}
