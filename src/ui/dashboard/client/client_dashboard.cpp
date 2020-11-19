#include "client_dashboard.h"

ClientDashboard::ClientDashboard(Store &store, Client *client) : Dashboard(store, client), _client(client){
}

void ClientDashboard::show() {
    Dashboard::show();
    std::cout << "\nStatus: " << (_client->isPremium() ? "Premium" : "Basic")
            << "\nAccumulated: " << _client->getPoints() << " points\n"
            << "\nFeedback: ";
    if (_client->getMeanEvaluation() != 0) std::cout << util::to_string(_client->getMeanEvaluation()) << " points\n";
    else std::cout << "None yet\n";
    std::cout << SEPARATOR << "\n";

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
            else if (validInput1Cmd(input, "logout")){
                _client->setLogged(false);
                return;
            }
            else if (validInput1Cmd1Arg(input, "edit", "account")){
                managePersonalData(_client);
                break;
            }
            else if (validInput1Cmd1Arg(input, "new", "order")){
                editOrder(_store.orderManager.add(_client,Order::DEFAULT_LOCATION));
                break;
            }
            else if (validInput1Cmd1Arg(input, "manage", "orders")){
                manageOrders(_client);
                break;
            }
            else printError();
        }
        catch(std::exception& e){
            std::cout << e.what() << "\n";
        }
    }

    show();
}

