//
// Created by bdmendes on 14/11/20.
//

#include "worker_dashboard.h"

WorkerDashboard::WorkerDashboard(Store &store, Worker *worker) : Dashboard(store, worker), _worker(worker){
}

void WorkerDashboard::show() {
    Dashboard::show();
    std::cout << "\nSalary: " << util::to_string(_worker->getSalary())
              << "\nTo deliver: " << _worker->getUndeliveredOrders() << " orders\n" << SEPARATOR << "\n";

    const std::vector<std::string> options = {
            "edit account - change personal details",
            "view stock - review and modify store stock",
            "view orders - review and evaluate my past assigned orders",
            "add client - let a new customer login into the system"
            "logout - exit and request credential next time"
    };
    printOptions(options);

    for (;;) {
        std::string input = readCommand();
        if (input == BACK) return;
        else if (validInput1Cmd(input,"logout")) _worker->setLogged(false);
        else if (validInput1Cmd1Arg(input,"edit","account")) managePersonalData(_worker);
        else if (validInput1Cmd1Arg(input,"view","stock")) manageStock();
        else if (validInput1Cmd1Arg(input,"view","orders")) viewOrders(nullptr,_worker);
        else if (validInput1Cmd1Arg(input,"add","client")) addClient();
        else {printError(); continue;}
        break;
    }

    show();
}

void WorkerDashboard::addClient() {
    printLogo("Add client");
}
