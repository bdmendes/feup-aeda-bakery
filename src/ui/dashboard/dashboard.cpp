//
// Created by bdmendes on 16/11/20.
//

#include "dashboard.h"

Dashboard::Dashboard(Store &store, Person *person) : UI(store), _person(person){
}

void Dashboard::show() {
    printLogo({});
    std::cout << SEPARATOR;
    print(_person->getName(),util::BLUE);

    std::cout << "\nusername: " << _person->getCredential().username
    << "\npassword: " << std::string(_person->getCredential().password.size(),'*')
    << "\n\nTax ID: " << ((_person->getTaxId() == Person::DEFAULT_TAX_ID) ?
    "Not provided" : std::to_string(_person->getTaxId()));
}

void Dashboard::viewOrders(Client *client, Worker* worker) {
    printLogo("Order view");
    std::cout << SEPARATOR;
    bool hasOrders = _store.orderManager.print(std::cout,client,worker);
    std::cout << SEPARATOR << "\n";

    if (hasOrders) {
        std::vector<std::string> options = {
                "expand <index> - view order details",
                "edit <index> - edit order details"
        };
        if (client != nullptr){
            options.emplace_back("deliver <index> <evaluation> - mark order as delivered and evaluate it");
            options.emplace_back("remove <index> - cancel requested order");
        }
        printOptions(options);
    }

    for(;;){
        try {
            std::string input = readCommand();
            if (input == BACK) return;
            else if (hasOrders && client != nullptr && validInput1Cmd2ArgsDigit(input, "deliver")) {
                int idx = std::stoi(to_words(input).at(1)) - 1;
                int eval = std::stoi(to_words(input).at(2));
                _store.orderManager.get(idx, client)->deliver(eval, 0);
            } else if (hasOrders && client != nullptr && validInput1Cmd1ArgDigit(input,"remove")){
                int idx = std::stoi(to_words(input).at(1)) - 1;
                _store.orderManager.remove(idx);
            } else if (hasOrders && validInput1Cmd1ArgDigit(input, "expand")) {
                int idx = std::stoi(to_words(input).at(1)) - 1;
                expandOrder(_store.orderManager.get(idx, client));
            } else if (hasOrders && validInput1Cmd1ArgDigit(input,"edit")){
                int idx = std::stoi(to_words(input).at(1)) - 1;
                editOrder(_store.orderManager.get(idx, client));
            }
            else {printError(); continue;}
            break;
        }
        catch (std::exception& e){
            std::cout << e.what() << "\n";
        }
    }

    viewOrders(client);
}

void Dashboard::changeCredential(Person *person){
    std::cout << "\n" << SEPARATOR;
    std::string username, password;
    for(;;){
        std::cout << "new username: ";
        std::string input1 = readCommand();
        std::cout << "confirm new username: ";
        std::string input2 = readCommand();
        if (input2 != input1) std::cout << "\nUsernames did not match! Try again.\n";
        else{
            username = input1;
            break;
        }
    }
    for(;;){
        std::cout << "\nNew password: ";
        std::string input1 = readCommand();
        std::cout << "Confirm new username: ";
        std::string input2 = readCommand();
        if (input2 != input1) std::cout << "\nUsernames did not match! Try again.\n";
        else{
            password = input1;
            break;
        }
    }
    person->setCredential({username,password});
}

void Dashboard::expandOrder(Order *order) {
    printLogo("Order details");
    std::cout << SEPARATOR;
    order->print(std::cout);
    std::cout << SEPARATOR << "\n";

    for (;;) {
        std::string input = readCommand();
        if (input == BACK) return;
        else printError();
    }
}

void Dashboard::managePersonalData(Person *person) {
    printLogo("Edit account details");
    bool isClient = dynamic_cast<Client*>(person) != nullptr;

    std::vector<std::string> options = {
            "change credential - set new username or password",
            "change name - change your name",
    };
    if (isClient){
        options.emplace_back("set premium - make myself a premium client");
        options.emplace_back("set regular - make myself a regular client");
    };

    printOptions(options);
    for (;;){
        try {
            std::string input = readCommand();
            if (input == BACK) return;
            else if (validInput1Cmd1Arg(input, "change", "credential")) {
                changeCredential(person);
                break;
            } else if (validInput1Cmd1Arg(input, "change", "name")) {
                changeName(person);
                break;
            } else if (isClient && validInput1Cmd1Arg(input, "set", "regular")) {
                dynamic_cast<Client *>(person)->setPremium(false);
                break;
            }
            else if (isClient && validInput1Cmd1Arg(input, "set", "premium")) {
                dynamic_cast<Client *>(person)->setPremium(true);
                break;
            }
            else printError();
        }
        catch (std::exception& e){
            std::cout << e.what() << "\n";
        }
    }
}

void Dashboard::changeName(Person *person) {
    std::cout << "\n" << SEPARATOR;
    for(;;){
        try {
            std::cout << "New name: ";
            std::string input1 = readCommand();
            std::cout << "Confirm new name: ";
            std::string input2 = readCommand();
            if (input2 != input1) std::cout << "\nNames did not match! Try again.\n";
            else {
                person->setName(input1);
                break;
            }
        }
        catch (std::exception& e){
            std::cout << e.what() << "\n\n";
        }
    }
}

void Dashboard::printLogo(const std::string &detail) {
    util::clearScreen();
    std::string title = _store.getName() + " - " + _person->getName() + "'s personal area";
    if (!detail.empty()) title += " - " + detail;
    uppercase(title);
    util::print(title + "\n\n",util::BLUE);
}

void Dashboard::editOrder(Order* order) {
    if (!_store.orderManager.has(order)) throw std::invalid_argument("Couldn't find order to edit");
    for(;;){
        printLogo("Edit order");
        std::cout << "AVAILABLE STOCK\n" << SEPARATOR;
        _store.productManager.print(std::cout);
        std::cout << SEPARATOR << "\n"
                  << "ORDER DETAILS\n" << SEPARATOR;
        order->print(std::cout);
        std::cout << SEPARATOR << "\n";

        const std::vector<std::string> options = {
                "add <product_number> <quantity> - add product from stock",
                "remove <product_number> - remove product from order"
        };
        printOptions(options);

        for(;;) {
            try {
                std::string input = readCommand();
                if (input == BACK){
                    if (order->getProducts().empty()) _store.orderManager.remove(order);
                    return;
                }
                else if (validInput1Cmd2ArgsDigit(input, "add")) {
                    int idx = std::stoi(to_words(input).at(1)) - 1;
                    int quantity = std::stoi(to_words(input).at(2));
                    order->addProduct(_store.productManager.get(idx), quantity);
                } else if (validInput1Cmd1ArgDigit(input, "remove")) {
                    int idx = std::stoi(to_words(input).at(1)) - 1;
                    order->removeProduct(idx);
                } else {
                    printError();
                    continue;
                }
                break;
            }
            catch (std::exception &e) {
                std::cout << e.what() << "\n";
            }
        }
    }
}

void Dashboard::manageStock() {
    for (;;){
        printLogo("Manage stock");
        std::cout << SEPARATOR;
        _store.productManager.print(std::cout);
        std::cout << SEPARATOR << "\n";

        const std::vector<std::string> options = {
                "remove <number> - remove product from existing stock",
                "add cake - add a new cake to the stock",
                "add bread - add a new bread to the store"
        };
        printOptions(options);

        for (;;){
            try {
                std::string input = readCommand();
                if (input == BACK) return;
                else if (validInput1Cmd1Arg(input, "add", "cake")) {
                    //
                    break;
                } else if (validInput1Cmd1Arg(input, "add", "bread")) {
                    //
                    break;
                } else if (validInput1Cmd1ArgDigit(input, "remove")){
                    int idx = std::stoi(to_words(input).at(1)) - 1;
                    _store.productManager.remove(idx);
                    break;
                } else printError();
            }
            catch (std::exception& e){
                std::cout << e.what() << "\n";
            }
        }
    }
}

