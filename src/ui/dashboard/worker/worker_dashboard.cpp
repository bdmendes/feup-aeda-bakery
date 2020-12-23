#include "worker_dashboard.h"

WorkerDashboard::WorkerDashboard(Store &store, Worker *worker) : Dashboard(store, worker), _worker(worker){
}

void WorkerDashboard::show() {
    Dashboard::show();
    std::cout << "\nWork location: " << _worker->getLocation()
              << "\nSalary: " << util::to_string(_worker->getSalary()) << " euros"
              << "\nTo deliver: " << _worker->getUndeliveredOrders() << " orders\n"
              << "\nRating: ";
    if (_worker->getMeanEvaluation() != 0) std::cout << util::to_string(_worker->getMeanEvaluation()) << " points\n";
    else std::cout << "None yet\n";

    std::cout << SEPARATOR << "\n";
    const std::vector<std::string> options = {
            "edit account - change personal details",
            "manage stock - review and modify store stock",
            "manage orders - check my past assigned orders",
            "manage clients - let a new customer login",
            "logout - exit and request credential next time"
    };
    printOptions(options);

    for (;;) {
        std::string input = readCommand();
        if (input == BACK) return;
        else if (validInput1Cmd(input,"logout")){
            _worker->setLogged(false);
            return;
        }
        else if (validInput1Cmd1Arg(input,"edit","account")){
            managePersonalData(_worker);
            break;
        }
        else if (validInput1Cmd1Arg(input,"manage","stock")){
            manageStock();
            break;
        }
        else if (validInput1Cmd1Arg(input,"manage","orders")){
            manageOrders(nullptr, _worker);
            break;
        }
        else if (validInput1Cmd1Arg(input,"manage","clients")){
            manageClients();
            break;
        }
        else printError();
    }

    show();
}
