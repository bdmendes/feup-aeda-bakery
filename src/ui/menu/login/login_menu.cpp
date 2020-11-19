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
        else if (validInput1Cmd(input, "worker")){
            selectPerson(PersonRole::WORKER);
            break;
        }
        else if (validInput1Cmd(input, "client")){
            selectPerson(PersonRole::CLIENT);
            break;
        }
        else if (validInput1Cmd(input, "boss")){
            login(&_store.boss);
            break;
        }
        else printError();
    }

    show();
}

LoginMenu::LoginMenu(Store &store) : UI(store) {
}

void LoginMenu::selectPerson(PersonRole role) {
    bool hasPersons = false;
    printLogo("Login");

    std::cout << SEPARATOR;
    if (role == PersonRole::CLIENT) hasPersons = _store.workerManager.print(std::cout, false);
    else if (role == PersonRole::WORKER) hasPersons = _store.clientManager.print(std::cout, false);
    std::cout << SEPARATOR << "\n";

    if (hasPersons){
        const std::vector<std::string> options = {
                "login <index> - login in person's account"
        };
        printOptions(options);
    }

    for (;;) {
        try {
            std::string input = readCommand();
            if (input == BACK) return;
            else if (hasPersons && validInput1Cmd1ArgDigit(input,"login")) {
                unsigned long personPosition = std::stoul(to_words(input).at(1)) - 1;
                if (role == PersonRole::CLIENT) login(_store.workerManager.get(personPosition));
                else login(_store.clientManager.get(personPosition));
                break;
            }
            else printError();
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
        std::cout << SEPARATOR << "Dear " << person->getName() << ", please enter your credentials.\n"
        << "Default is '" << person->getDefaultCredential().username
        << "', '" << person->getDefaultCredential().password << "'.\n" << SEPARATOR;

        std::cout << "\nUsername: ";
        for (;;) {
            std::string input = readCommand(false);
            if (input == BACK) return;
            else if (validInput1Cmd(input, person->getCredential().username)) break;
            std::cout << "Wrong username. Try again: ";
        }

        std::cout << "\nPassword: ";
        for (;;) {
            std::string input = readCommand(false);
            if (input == BACK) return;
            else if (validInput1Cmd(input, person->getCredential().password)) break;
            std::cout << "Wrong password. Try again: ";
        }

        person->setLogged(true);
    }

    switch (person->getRole()){
        case PersonRole::WORKER:
            WorkerDashboard(_store,_store.workerManager.getWorker(person->getTaxId())).show();
            break;
        case PersonRole::CLIENT:
            ClientDashboard(_store, _store.clientManager.getClient(person->getTaxId())).show();
            break;
        case PersonRole::BOSS:
            BossDashboard(_store).show();
            break;
    }
}
