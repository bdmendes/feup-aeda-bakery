//
// Created by bdmendes on 14/11/20.
//

#include "client_dashboard.h"

ClientDashboard::ClientDashboard(Store &store, Client *client) : Dashboard(store, client), _client(client){

}

void ClientDashboard::show() {
    Dashboard::show();
    std::cout << "\nStatus: " << (_client->isPremium() ? "Premium" : "Basic")
            << "\nAccumulated: " << _client->getPoints() << " points\n" << SEPARATOR << "\n";

    const std::vector<std::string> options = {
            "edit account - change personal details",
            "new order - request something new",
            "manage orders - review and evaluate past requested orders",
            "logout - exit and request credential next time"
    };
    printOptions(options);

    for (;;) {
        try {
            std::string input = readCommand();
            if (input == BACK) return;
            else if (validInput1Cmd(input, "logout")) _client->setLogged(false);
            else if (validInput1Cmd1Arg(input, "edit", "account")) managePersonalData(_client);
            else if (validInput1Cmd1Arg(input, "new", "order")) editOrder(_store.orderManager.add(_client));
            else if (validInput1Cmd1Arg(input, "manage", "orders")) manageOrders(_client);
            else { printError(); continue; }
            break;
        }
        catch(std::exception&e){
            std::cout << e.what() << "\n";
        }
    }

    show();
}

