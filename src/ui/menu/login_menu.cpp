//
// Created by bdmendes on 14/11/20.
//

#include "ui/dashboard/boss_dashboard.h"
#include "ui/dashboard/worker_dashboard.h"
#include "ui/dashboard/client_dashboard.h"
#include "login_menu.h"

void LoginMenu::show() {
    printLogo();
    const std::vector<std::string> content = {
            "Worker",
            "Client",
            "Boss"
    };
    printOptions(content,"What are you?");

    for (;;) {
        std::string input = readCommand();
        if (input == BACK) return;
        else if (validInput1Cmd(input, "worker")){
            showPersons(PersonToShow::WORKER);
            break;
        }
        else if (validInput1Cmd(input, "client")){
            showPersons(PersonToShow::CLIENT);
            break;
        }
        else if (validInput1Cmd(input, "boss")){
            login(&_store.boss);
            break;
        }
        else printError();
    }
}

LoginMenu::LoginMenu(Store &store) : UI(store) {
}

void LoginMenu::showPersons(PersonToShow person) {
    printLogo();

    bool empty;
    if (person == PersonToShow::CLIENT) empty = _store.clientManager.getAll().empty();
    if (person == PersonToShow::WORKER) empty = _store.workerManager.getAll().empty();

    if (!empty){
        std::cout << SEPARATOR;
        if (person == PersonToShow::WORKER) _store.workerManager.print(std::cout,false);
        if (person == PersonToShow::CLIENT) _store.clientManager.print(std::cout,false);
        std::cout << SEPARATOR << std::endl;

        std::cout << "Choose an index: ";
    }
    else {
        std::cout << SEPARATOR << "Nothing here yet.\n";
        if (person == PersonToShow::WORKER) std::cout << "Go back and login as the boss to add some!\n";
        if (person == PersonToShow::CLIENT) std::cout << "Go back and login as a worker to add some!\n";
        std::cout << SEPARATOR << std::endl;
    }

    for (;;){
        std::string input = readCommand();
        if (input == BACK) return;
        if (validInput1Word(input)) {
            try {
                unsigned arg = std::stoi(to_words(input).at(0)) - 1;
                if (person == PersonToShow::WORKER){
                    login(_store.workerManager.get(arg));
                }
                if (person == PersonToShow::CLIENT){
                    login(_store.clientManager.get(arg));
                }
                break;
            }
            catch (std::exception &e) {
                std::cout << e.what() << SPACE;
                continue;
            }
        }
        else printError(true);
    }
}

void LoginMenu::login(Person *person) {
    printLogo();
    std::cout << "Dear " << person->getName() << ", please enter your credentials.\n";
    if (dynamic_cast<Worker *>(person) != nullptr) std::cout << "Default is 'worker', 'worker'.\n";
    if (dynamic_cast<Client *>(person) != nullptr) std::cout << "Default is 'client', 'client'.\n";
    if (dynamic_cast<Boss *>(person) != nullptr) std::cout << "Default is 'boss', 'boss'.\n";

    std::cout << "\nusername: ";
    for (;;) {
        std::string input = readCommand(false);
        if (input == BACK) return;
        if (validInput1Cmd(input, person->getCredential().username)) {
            break;
        }
        std::cout << "Wrong username. Try again: ";
    }

    std::cout << "password: ";
    for (;;) {
        std::string input = readCommand(false);
        if (input == BACK) return;
        if (validInput1Cmd(input, person->getCredential().password)) {
            if (dynamic_cast<Worker *>(person) != nullptr) WorkerDashboard(_store, dynamic_cast<Worker *>(person)).show();
            if (dynamic_cast<Client *>(person) != nullptr) ClientDashboard(_store,dynamic_cast<Client *>(person)).show();
            if (dynamic_cast<Boss *>(person) != nullptr) BossDashboard(_store).show();
            break;
        }
        std::cout << "Wrong password. Try again: ";
    }
}
