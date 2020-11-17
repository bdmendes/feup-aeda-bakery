//
// Created by bdmendes on 14/11/20.
//

#include "ui/dashboard/boss/boss_dashboard.h"
#include "ui/dashboard/worker/worker_dashboard.h"
#include "ui/dashboard/client/client_dashboard.h"
#include "login_menu.h"

void LoginMenu::show() {
    printLogo("Login");
    const std::vector<std::string> content = {
            "Worker",
            "Client",
            "Boss"
    };
    printOptions(content,"What is your role on the company?");

    for (;;) {
        std::string input = readCommand();
        if (input == BACK) return;
        else if (validInput1Cmd(input, "worker")) selectPerson(false);
        else if (validInput1Cmd(input, "client")) selectPerson(true);
        else if (validInput1Cmd(input, "boss")) login(&_store.boss);
        else { printError(); continue; }
        break;
    }

    show();
}

LoginMenu::LoginMenu(Store &store) : UI(store) {
}

void LoginMenu::selectPerson(bool client) {
    bool hasPersons;
    printLogo("Login");

    std::cout << SEPARATOR;
    if (!client) hasPersons = _store.workerManager.print(std::cout, false);
    else hasPersons = _store.clientManager.print(std::cout, false);
    std::cout << SEPARATOR << "\n";

    if (hasPersons) std::cout << "Choose an index: ";

    for (;;) {
        try {
            std::string input = readCommand();
            if (input == BACK) return;
            if (hasPersons && validInput1CmdFree(input)) {
                unsigned personPosition = std::stoi(to_words(input).at(0)) - 1;
                if (!client) login(_store.workerManager.get(personPosition));
                else login(_store.clientManager.get(personPosition));
            }
            else {printError(true); continue; }
            break;
        }
        catch (std::exception& e){
            std::cout << e.what() << SPACE;
            continue;
        }
    }
}

void LoginMenu::login(Person *person) {
    if (!person->isLogged()) {
        printLogo("Authentication");
        std::cout << "Dear " << person->getName() << ", please enter your credentials.\n"
        << "Default is '" << person->getDefaultCredential().username
        << "', '" << person->getDefaultCredential().password << "'\n";

        std::cout << "\nUsername: ";
        for (;;) {
            std::string input = readCommand(false);
            if (input == BACK) return;
            else if (validInput1Cmd(input, person->getCredential().username)) break;
            std::cout << "Wrong username. Try again: ";
        }

        std::cout << "Password: ";
        for (;;) {
            std::string input = readCommand(false);
            if (input == BACK) return;
            else if (validInput1Cmd(input, person->getCredential().password)) break;
            std::cout << "Wrong password. Try again: ";
        }

        person->setLogged(true);
    }
    if (dynamic_cast<Worker *>(person)) WorkerDashboard(_store, dynamic_cast<Worker *>(person)).show();
    else if (dynamic_cast<Client *>(person)) ClientDashboard(_store,dynamic_cast<Client *>(person)).show();
    else if (dynamic_cast<Boss *>(person)) BossDashboard(_store).show();
}
