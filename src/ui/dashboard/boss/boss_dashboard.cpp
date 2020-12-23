#include "boss_dashboard.h"

BossDashboard::BossDashboard(Store &store) : Dashboard(store, &store.boss), _boss(&store.boss) {
}

void BossDashboard::show() {
    Dashboard::show();
    std::cout << "\n" << SEPARATOR << "\n";

    const std::vector<std::string> options = {
            "edit account - change personal details",
            "manage locations - expand your business to new places",
            "manage stock - review and modify store stock",
            "manage orders - review store orders",
            "manage staff - have a look at your workers",
            "manage clients - quickly peek and shout at them",
            "check stats - some math to keep you happy, boss",
            "logout - exit and request credential next time"
    };
    printOptions(options);

    for (;;) {
        std::string input = readCommand();
        if (input == BACK) return;
        else if (validInput1Cmd(input,"logout")){
            _boss->setLogged(false);
            return;
        }
        else if (validInput1Cmd1Arg(input,"edit","account")){
            managePersonalData(_boss);
            break;
        }
        else if (validInput1Cmd1Arg(input,"manage","stock")){
            manageStock();
            break;
        }
        else if (validInput1Cmd1Arg(input,"manage","locations")){
            manageLocations();
            break;
        }
        else if (validInput1Cmd1Arg(input,"manage","orders")){
            manageOrders(nullptr, nullptr);
            break;
        }
        else if (validInput1Cmd1Arg(input,"manage","staff")){
            manageStaff();
            break;
        }
        else if (validInput1Cmd1Arg(input,"manage","clients")){
            manageClients();
            break;
        }
        else if (validInput1Cmd1Arg(input,"check","stats")){
            showStats();
            break;
        }
        else printError();
    }

    show();
}

void BossDashboard::addWorker() {
    std::cout << "\n" << SEPARATOR;
    std::string name, input, location;
    unsigned long taxID;
    float salary;

    /* Name */
    std::cout << "Worker name: ";
    name = readCommand(false);
    if (name == BACK) return;

    /* taxID */
    for(;;){
        std::cout << "Tax ID: ";
        input = readCommand();
        if (isdigit(input)) break;
        else std::cout << "The ID must be an integer!\n";
    }
    taxID = std::stoul(input);

    /* Salary */
    for (;;){
        std::cout << "Salary: ";
        input = readCommand();
        if (isdigit(input,true)) break;
        else std::cout << "The salary must be a float. Do not include the coin symbol.\n";
    }
    salary = std::stof(input);

    /* Location */
    std::cout << "Work location (";
    {
        std::string locations;
        for (const auto& l: _store.locationManager.getAll()){
            locations += l + ", ";
        }
        if (!locations.empty()) locations = locations.substr(0,locations.size()-2);
        std::cout << locations << "): ";
    }
    for(;;){
        try{
            input = readCommand(false);
            if (!_store.locationManager.has(input)) throw LocationDoesNotExist(input);
            location = input;
            break;
        }
        catch(std::exception& e){
            std::cout << e.what() << "\n";
        }
    }

    _store.workerManager.add(location, name,taxID,salary);
}

void BossDashboard::manageStaff() {
    printLogo("The Staff");
    std::cout << SEPARATOR;
    bool hasStaff = _store.workerManager.print(std::cout);
    std::cout << SEPARATOR << "\n";

    std::vector<std::string> options = {
            "add worker - hire someone to join your team"
    };
    if (hasStaff){
        options.emplace_back("fire <index> - remove worker's account");
        options.emplace_back("set_salary <index> <salary> - change worker's salary");
    }
    printOptions(options);

    for(;;){
        try {
            std::string input = readCommand();
            if (input == BACK) return;
            else if (hasStaff && validInput1Cmd1ArgDigit(input,"fire")){
                unsigned long idx = std::stoul(to_words(input).at(1)) - 1;
                _store.workerManager.remove(idx);
                break;
            }
            else if (hasStaff && validInput1Cmd2ArgsDigit(input,"set_salary",true)){
                unsigned long idx = std::stoul(to_words(input).at(1)) - 1;
                float salary = std::stof(to_words(input).at(2));
                _store.workerManager.get(idx)->setSalary(salary);
                break;
            }
            else if (validInput1Cmd1Arg(input,"add","worker")){
                addWorker();
                break;
            }
            else printError();
        }
        catch(std::exception& e){
            std::cout << e.what() << "\n";
        }
    }

    manageStaff();
}

void BossDashboard::showStats() {
    printLogo("Some quick maths");
    std::cout << SEPARATOR;
    util::print(_store.getName(), util::BLUE);
    std::cout << "\nMean evaluation: " << _store.getEvaluation()
              << "\nRevenue: " << util::to_string(_store.getProfit()) << " euros\n"
              << "\nIt's a nice day out there.\n" << SEPARATOR << "\n";

    for(;;) {
        std::string input = readCommand();
        if (input == BACK) return;
        else printError();
    }
}

void BossDashboard::manageLocations() {
    printLogo("Store Locations");
    std::cout << SEPARATOR;

    int count = 1;
    for (const auto& l: _store.locationManager.getAll()){
        std::cout << count++ << ". " << l << "\n";
    }
    std::cout << SEPARATOR << "\n";

    std::vector<std::string> options = {
            "add location - add order delivery location",
            "remove <index> - remove order delivery location"
    };
    printOptions(options);

    for(;;){
        try {
            std::string input = readCommand();
            if (input == BACK) return;
            else if (validInput1Cmd1ArgDigit(input,"remove")){
                unsigned long idx = std::stoul(to_words(input).at(1)) - 1;
                _store.locationManager.remove(idx);
                break;
            }
            else if (validInput1Cmd1Arg(input,"add","location")){
                addLocation();
                break;
            }
            else printError();
        }
        catch(std::exception& e){
            std::cout << e.what() << "\n";
        }
    }

    manageLocations();
}

void BossDashboard::addLocation() {
    std::cout << "\n" << SEPARATOR;
    std::cout << "New location name: ";
    std::string input = readCommand(false);
    if (input == BACK) return;
    _store.locationManager.add(input);
}
