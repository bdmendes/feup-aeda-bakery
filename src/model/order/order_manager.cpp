
#include "order_manager.h"
#include "exception/file_exception.h"

OrderManager::OrderManager(ProductManager* pm, ClientManager* cm, WorkerManager* wm, LocationManager* lm) :
        _productManager(pm), _clientManager(cm), _workerManager(wm), _locationManager(lm), _orders{}{
}

bool OrderManager::has(Order *order) const {
    auto comp = [order](const Order* o2){
        return *order == *o2;
    };
    return std::find_if(_orders.begin(),_orders.end(),comp) != _orders.end();
}

Order* OrderManager::get(unsigned long position, Client* client, Worker* worker) const {
    std::vector<Order*> filtered;
    if (client != nullptr && worker != nullptr) throw std::invalid_argument("Can't choose both worker and client");
    else if (client != nullptr) filtered = get(client);
    else if (worker != nullptr) filtered = get(worker);
    else filtered = getAll();

    if (position >= filtered.size()) throw InvalidOrderPosition(position, filtered.size());
    return filtered.at(position);
}

std::vector<Order *> OrderManager::getAll() const {
    return _orders;
}

std::vector<Order *> OrderManager::get(Client *client) const {
    if (!_clientManager->has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    std::vector<Order*> filtered;
    for (const auto& order: _orders){
        if (order->getClient() == client) filtered.push_back(order);
    }
    return filtered;
}

std::vector<Order *> OrderManager::get(Worker *worker) const {
    if (!_workerManager->has(worker)) throw PersonDoesNotExist(worker->getName(), worker->getTaxId());
    std::vector<Order*> filtered;
    for (const auto& order: _orders){
        if (order->getWorker() == worker) filtered.push_back(order);
    }
    return filtered;
}

void OrderManager::sort() {
    auto comp = [](const Order* o1, const Order* o2){
        return *o1 < *o2;
    };
    std::sort(_orders.begin(), _orders.end(),comp);
}

Order* OrderManager::add(Client *client, const std::string& location, const Date &date) {
    if (!_clientManager->has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    if (!_locationManager->has(location)) throw LocationDoesNotExist(location);
    auto* order = new Order(*client,*_workerManager->getLessBusyWorker(),location,date);
    _orders.push_back(order);
    return order;
}

Order* OrderManager::add(Client* client, Worker* worker, const std::string& location, const Date& date){
    if (!_clientManager->has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    if (!_workerManager->has(worker)) throw PersonDoesNotExist(worker->getName(), worker->getTaxId());
    if (!_locationManager->has(location)) throw LocationDoesNotExist(location);
    auto* order = new Order(*client,*worker,location,date);
    _orders.push_back(order);
    return order;
}

void OrderManager::remove(Order *order) {
    auto position = std::find(_orders.begin(),_orders.end(),order);
    if (position == _orders.end()) throw OrderDoesNotExist();
    if (order->wasDelivered())
        throw OrderWasAlreadyDelivered(*order->getClient(),*order->getWorker(),order->getRequestDate());
    order->getWorker()->removeOrderToDeliver();
    _orders.erase(position);
}

void OrderManager::remove(unsigned long position) {
    if (position >= _orders.size()) throw OrderDoesNotExist();
    Order* order = _orders.at(position);
    if (order->wasDelivered())
        throw OrderWasAlreadyDelivered(*order->getClient(),*order->getWorker(),order->getRequestDate());
    order->getWorker()->removeOrderToDeliver();
    _orders.erase(_orders.begin() + position);
}

bool OrderManager::print(std::ostream &os, Client* client, Worker* worker) const {
    std::vector<Order*> toPrint;
    if (client != nullptr) toPrint = get(client);
    else if (worker != nullptr) toPrint = get(worker);
    else toPrint = getAll();

    if (toPrint.empty()) {
        os << "No orders here yet.\n";
        return false;
    }

    os << std::string(toPrint.size() / 10 + 3 ,util::SPACE);
    if (client == nullptr) os << util::column("CLIENT",true);
    if (worker == nullptr) os << util::column("WORKER",true);
    os << util::column("REQUESTED",true)
    << util::column("DELIVERED",true)
    << util::column("LOCATION", true) << "\n";

    int count = 1;
    for (const auto& o: toPrint){
        os << std::setw((int)toPrint.size() / 10 + 3) << std::to_string(count++) + ". ";
        if (client == nullptr) os << util::column(o->getClient()->getName(),true);
        if (worker == nullptr) os << util::column(o->getWorker()->getName(),true);
        os << util::column(o->getRequestDate().getCompleteDate(), true)
        << util::column(o->wasDelivered() ? o->getDeliverDate().getClockTime() + " (" +
        std::to_string(o->getClientEvaluation()) + " points)" : "Not Yet",true)
        << util::column(o->getDeliverLocation()) << "\n";
    }
    return true;
}

void OrderManager::read(const std::string &path) {
    std::ifstream file(path);
    if (!file) throw FileNotFound(path);

    auto getDate = [](std::string dateStr, std::string timeStr) {
        int day = 1, month = 1, year = 1900, hour = 0, minute = 0;
        std::replace(dateStr.begin(), dateStr.end(), '/', ' ');
        std::stringstream ssDate(dateStr);
        ssDate >> day >> month >> year;

        std::replace(timeStr.begin(), timeStr.end(), ':', ' ');
        std::stringstream ssTime(timeStr);
        ssTime >> hour >> minute;
        return Date(day, month, year, hour, minute);
    };

    auto getProduct = [&](const std::string &productLine) {
        std::string productName;
        float price = 1;
        int quantity = 1;

        std::stringstream ss(productLine);
        ss >> productName >> price >> quantity;
        std::replace(productName.begin(),productName.end(),'-',' ');
        Product *product = _productManager->get(productName, price);
        if (!_productManager->has(product)) throw ProductDoesNotExist(productName, price);
        return product;
    };

    bool readDetails = true;
    Order *order = nullptr;
    int clientEvaluation = -1;

    for (std::string line; getline(file, line);) {
        util::stripCarriageReturn(line);
        if (line.empty()) continue;

        if (readDetails) {
            readDetails = false;
            clientEvaluation = -1;
            std::string date, time, location;
            unsigned long clientTaxID = Person::DEFAULT_TAX_ID, workerTaxID = Person::DEFAULT_TAX_ID;

            std::stringstream ss(line);
            ss >> clientTaxID >> workerTaxID >> date >> time >> location >> clientEvaluation;

            Client* client = _clientManager->getClient(clientTaxID);
            Worker* worker = _workerManager->getWorker(workerTaxID);
            std::replace(location.begin(),location.end(),'-',' ');

            Order toTest(*client,*worker,location,getDate(date,time));
            if (has(&toTest)) {
                order = get(client,worker,location,getDate(date,time));
                continue;
            }
            order = add(client, worker, location, getDate(date, time));

        } else if (line.at(0) == '-') {
            if (order && !order->wasDelivered() && clientEvaluation != -1) order->deliver(clientEvaluation);
            readDetails = true;
            order = nullptr;
        }
        else {
            Product *product = getProduct(line);
            if (!order) throw OrderDoesNotExist();
            if (!order->wasDelivered() && _productManager->has(product)) order->addProduct(product);
        }
    }
}

void OrderManager::write(const std::string &path) {
    std::ofstream file(path);
    if (!file) throw FileNotFound(path);

    for (const auto &order: _orders) {
        std::string styledLocationName = order->getDeliverLocation();
        std::replace(styledLocationName.begin(),styledLocationName.end(),' ','-');
        file << order->getClient()->getTaxId() << " " << order->getWorker()->getTaxId() << " "
             << order->getRequestDate().getCompleteDate() << " " << styledLocationName;
        if (order->wasDelivered()) file << " " << order->getClientEvaluation();
        file << "\n";

        for (const auto& p : order->getProducts()) {
            std::string nameToSave = p.first->getName();
            std::replace(nameToSave.begin(),nameToSave.end(),' ','-');
            file << nameToSave << " " << p.first->getPrice() << " " << p.second << "\n";
        }
        file << util::SEPARATOR;
    }
}

OrderManager::~OrderManager() {
    for (auto& o : _orders) delete o;
}

std::vector<Order *> OrderManager::get(const std::string &location) const {
    std::vector<Order*> filtered;
    for (const auto& order: _orders){
        if (order->getDeliverLocation() == location) filtered.push_back(order);
    }
    return filtered;
}

Order *OrderManager::get(Client *client, Worker *worker, const std::string &location, const Date &date) {
    Order toTest = Order(*client,*worker,location,date);
    for (const auto& o: _orders) if (*o == toTest) return o;
    throw OrderDoesNotExist();
}
