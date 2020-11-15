//
// Created by bdmendes on 14/11/20.
//

#include "client_dashboard.h"

ClientDashboard::ClientDashboard(Store &store, Client *client) : UI(store), _client(client){

}

void ClientDashboard::show() {
    printLogo();
    printLogo();
    std::cout << "Client dashboard is work in progress. press enter to exit.";
    std::string input;
    std::getline(std::cin,input);
}
