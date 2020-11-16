//
// Created by bdmendes on 16/11/20.
//

#include "dashboard.h"

Dashboard::Dashboard(Store &store, Person *person) : UI(store), _person(person){

}

void Dashboard::show() {
    printLogo("Personal Area");
    std::cout << SEPARATOR;
    print(_person->getName(),util::BLUE);

    std::cout << "\nusername: " << _person->getCredential().username
    << "\npassword: " << std::string(_person->getCredential().password.size(),'*')
    << "\n\nTax ID: " << ((_person->getTaxId() == Person::DEFAULT_TAX_ID) ?
    "Not provided" : std::to_string(_person->getTaxId()));
}

void Dashboard::viewOrders(Client *client) {
    for(;;) {
        printLogo("Order view");
        bool hasOrders = _store.orderManager.print(std::cout,client);
        std::cout << "\n";

        if (hasOrders) {
            std::vector<std::string> options = {
                    "expand <index> - view order details"
            };
            if (client != nullptr)
                options.emplace_back("deliver <index> <evaluation> - mark order as delivered and evaluate it");
            printOptions(options);
        }

        for(;;){
            try {
                std::string input = readCommand();
                if (input == BACK) return;
                else if (hasOrders && client != nullptr && validInput1Cmd2ArgsDigit(input, "deliver")) {
                    int idx = std::stoi(to_words(input).at(1));
                    int eval = std::stoi(to_words(input).at(2));
                    _store.orderManager.get(--idx, client)->deliver(eval);
                    break;
                } else if (hasOrders && validInput1Cmd1ArgDigit(input, "expand")) {
                    int idx = std::stoi(to_words(input).at(1));
                    expandOrder(_store.orderManager.get(--idx, client));
                    break;
                } else printError();
            }
            catch (std::exception& e){
                std::cout << e.what() << SPACE;
            }
        }
    }
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
        std::cout << "\nnew password: ";
        std::string input1 = readCommand();
        std::cout << "confirm new username: ";
        std::string input2 = readCommand();
        if (input2 != input1) std::cout << "\nUsernames did not match! Try again.\n";
        else{
            password = input1;
            break;
        }
    }
    person->setCredential({username,password});
}

void Dashboard::expandOrder(Order *order) const {
    printLogo("Order details");
}

void Dashboard::managePersonalData(Person *person) {
    printLogo("Edit account details");
    print(person->getName(),util::BLUE);
    std::cout << "\n";

    bool isClient = dynamic_cast<Client*>(person) != nullptr;

    std::vector<std::string> options = {
            "change credentials - set new username or password",
            "change name - change your name",
            "change taxID - change your tributary number"
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
            else if (validInput1Cmd1Arg(input, "change", "credentials")) {
                changeCredential(person);
                break;
            } else if (validInput1Cmd1Arg(input, "change", "name")) {
                changeName(person);
                break;
            } else if (validInput1Cmd1Arg(input, "change", "taxID")) {
                changeTaxID(person);
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
            std::cout << e.what() << SPACE;
        }
    }
}

void Dashboard::changeName(Person *person) {

}

void Dashboard::changeTaxID(Person *person) {

}

