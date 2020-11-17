//
// Created by bdmendes on 14/11/20.
//

#include "client_dashboard.h"

ClientDashboard::ClientDashboard(Store &store, Client *client) : Dashboard(store, client), _client(client){

}

void ClientDashboard::show() {
    Dashboard::show();
    std::cout << "\nStatus: " << (_client->isPremium() ? "Premium" : "Regular")
            << "\nAccumulated: " << _client->getPoints() << " points\n" << SEPARATOR << "\n";

    const std::vector<std::string> options = {
            "edit account - change personal details",
            "add order - request something new",
            "view orders - review and evaluate past requested orders",
            "logout - exit and request credential next time"
    };
    printOptions(options);

    for (;;) {
        std::string input = readCommand();
        if (input == BACK) return;
        else if (validInput1Cmd(input,"logout")){
            _client->setLogged(false);
            return;
        }
        else if (validInput1Cmd1Arg(input,"edit","account")){
            managePersonalData(_client);
            break;
        }
        else if (validInput1Cmd1Arg(input, "add", "order")) {
            editOrder(_store.orderManager.add(_client));
            break;
        }
        else if (validInput1Cmd1Arg(input,"view","orders")){
            viewOrders(_client);
            break;
        }
        printError();
    }

    show();
}

