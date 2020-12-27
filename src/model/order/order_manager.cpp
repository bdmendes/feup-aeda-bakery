
#include "order_manager.h"
#include "exception/file_exception.h"

OrderManager::OrderManager(ProductManager* pm, ClientManager* cm, WorkerManager* wm, LocationManager* lm) :
        _productManager(pm), _clientManager(cm), _workerManager(wm), _locationManager(lm), _orders{}{
}

bool OrderManager::has(Order *order) const {
    std::priority_queue<OrderEntry> orders = _orders;
    while (!orders.empty()){
        const auto& o = orders.top().getOrder();
        orders.pop();
        if (*o == *order) return true;
    }
    return false;
}

Order* OrderManager::get(unsigned long position, Client* client, Worker* worker) const {
    std::priority_queue<OrderEntry> filtered;
    if (client != nullptr && worker != nullptr)
        throw std::invalid_argument("Can't choose both worker and client");
    else if (client != nullptr) filtered = get(client);
    else if (worker != nullptr) filtered = get(worker);
    else filtered = getAll();

    unsigned long counter = 0;
    std::priority_queue<OrderEntry> orders = _orders;
    while(!orders.empty()) {
        const auto& order = orders.top().getOrder();
        orders.pop();
        if(counter == position) return order;
        counter++;
    }
    throw InvalidOrderPosition(position, filtered.size());
}

std::priority_queue<OrderEntry> OrderManager::getAll() const {
    return _orders;
}

std::priority_queue<OrderEntry> OrderManager::get(Client *client) const {
    if (!_clientManager->has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    std::priority_queue<OrderEntry> filtered, orders = _orders;
    while(!orders.empty()){
        const auto& orderEntry = orders.top();
        orders.pop();
        if(*orderEntry.getOrder()->getClient() == *client) filtered.push(orderEntry);
    }
    return filtered;
}

std::priority_queue<OrderEntry> OrderManager::get(Worker *worker) const {
    if (!_workerManager->has(worker)) throw PersonDoesNotExist(worker->getName(), worker->getTaxId());
    std::priority_queue<OrderEntry> filtered, orders = _orders;
    while(!orders.empty()){
        const auto& orderEntry = orders.top();
        orders.pop();
        if(*orderEntry.getOrder()->getWorker() == *worker) filtered.push(orderEntry);
    }
    return filtered;
}

Order* OrderManager::add(Client *client, const std::string& location, const Date &date) {
    if (!_clientManager->has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    if (!_locationManager->has(location)) throw LocationDoesNotExist(location);
    auto orderEntry = OrderEntry(new Order(*client,*_workerManager->getLessBusyWorker(location),location,date));
    _orders.push(orderEntry);
    return orderEntry.getOrder();
}

Order* OrderManager::add(Client* client, Worker* worker, const std::string& location, const Date& date){
    if (!_clientManager->has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    if (!_workerManager->has(worker)) throw PersonDoesNotExist(worker->getName(), worker->getTaxId());
    if (!_locationManager->has(location)) throw LocationDoesNotExist(location);
    auto order = OrderEntry(new Order(*client,*worker,location,date));
    _orders.push(order);
    return order.getOrder();
}

void OrderManager::remove(Order *order, bool updateWorkerOrders) {
    if(order->wasDelivered())
        throw OrderWasAlreadyDelivered(*order->getClient(),*order->getWorker(),order->getRequestDate());
    bool found = false;
    std::priority_queue<OrderEntry> newQueue;
    while(!_orders.empty()){
       const auto orderEntry = _orders.top();
        _orders.pop();
        if(!found && *orderEntry.getOrder() == *order){
            found = true;
            if (updateWorkerOrders) orderEntry.getOrder()->getWorker()->removeOrderToDeliver();
        }
        else newQueue.push(orderEntry);
    }
    _orders = newQueue;
    if(!found) throw OrderDoesNotExist();
}

void OrderManager::remove(unsigned long position, bool updateWorkerOrders) {
    if (position >= _orders.size()) throw OrderDoesNotExist();
    OrderEntry orderToRemove;
    unsigned long counter = 0;
    std::priority_queue<OrderEntry> newQueue;

    while(!_orders.empty()){
        const auto& orderEntry = _orders.top();
        _orders.pop();
        if(counter == position) orderToRemove.setOrder(orderEntry.getOrder());
        else newQueue.push(orderEntry);
        counter++;
    }
    _orders = newQueue;
    if (updateWorkerOrders) orderToRemove.getOrder()->getWorker()->removeOrderToDeliver();
}

bool OrderManager::print(std::ostream &os, Client* client, Worker* worker) const {
    std::priority_queue<OrderEntry> toPrint;
    if (client != nullptr) toPrint = get(client);
    else if (worker != nullptr) toPrint = get(worker);
    else toPrint = getAll();

    if (toPrint.empty()) {
        os << "No orders here yet.\n";
        return false;
    }

    os << "Note: Orders at the top have higher delivery priority.\n";
    os << "Delivered orders are kept at the bottom for historical reasons.\n\n";

    os << std::string(toPrint.size() / 10 + 3 ,util::SPACE);
    if (client == nullptr) os << util::column("CLIENT",true);
    if (worker == nullptr) os << util::column("WORKER",true);
    os << util::column("REQUESTED",true)
    << util::column("DELIVERED",true)
    << util::column("LOCATION", true) << "\n";

    unsigned count = 1;
    while(!toPrint.empty()){
        const auto& order = toPrint.top().getOrder();
        toPrint.pop();
        os << std::setw((int)toPrint.size() / 10 + 3) << std::to_string(count++) + ". ";
        if (client == nullptr) os << util::column(order->getClient()->getName(),true);
        if (worker == nullptr) os << util::column(order->getWorker()->getName(),true);
        os << util::column(order->getRequestDate().getCompleteDate(), true)
        << util::column(order->wasDelivered() ? order->getDeliverDate().getClockTime() + " (" +
        std::to_string(order->getClientEvaluation()) + " points)" : "Not Yet",true)
        << util::column(order->getDeliverLocation()) << "\n";
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
        }
        else if (line.at(0) == '-') {
            if (order && !order->wasDelivered() && clientEvaluation != -1){
                // client points are kept in the client file, so do not change them
                deliver(order, clientEvaluation, false);
            }
            readDetails = true;
            order = nullptr;
        }
        else {
            Product *product = getProduct(line);
            if (!order) throw OrderDoesNotExist();
            if (!order->wasDelivered() && _productManager->has(product)) addProduct(order,product);
        }
    }
}

void OrderManager::write(const std::string &path) {
    std::ofstream file(path);
    if (!file) throw FileNotFound(path);

    std::priority_queue<OrderEntry> orders = _orders;
    while(!orders.empty()){
        const auto& order = _orders.top().getOrder();
        _orders.pop();
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
    while(!_orders.empty()){
        delete _orders.top().getOrder();
        _orders.pop();
    }
}

std::priority_queue<OrderEntry> OrderManager::get(const std::string &location) const {
    std::priority_queue<OrderEntry> filtered, orders = _orders;
    while(!orders.empty()){
        auto orderEntry = orders.top();
        orders.pop();
        if(orderEntry.getOrder()->getDeliverLocation() == location) filtered.push(orderEntry);
    }
    return filtered;
}

Order* OrderManager::get(Client *client, Worker *worker, const std::string &location, const Date &date) {
    std::priority_queue<OrderEntry> orders = _orders;
    Order toTest = Order(*client, *worker, location, date);
    while(!orders.empty()){
        const auto& order = orders.top().getOrder();
        orders.pop();
        if(*order == toTest) return order;
    }
    throw OrderDoesNotExist();
}

Product *OrderManager::addProduct(Order *order, Product *product, unsigned int quantity) {
    if (!has(order)) throw OrderDoesNotExist();
    _productManager->remove(product);
    order->addProduct(product,quantity);
    _productManager->add(product);
    return product;
}

void OrderManager::removeProduct(Order *order, Product *product) {
    if (!has(order)) throw OrderDoesNotExist();
    _productManager->remove(product);
    order->removeProduct(product);
    _productManager->add(product);
}

void OrderManager::removeProduct(Order *order, unsigned long position) {
    if (!has(order)) throw OrderDoesNotExist();

    auto orderProd = order->getProducts();
    auto it = orderProd.begin();
    if (position >= orderProd.size()) throw std::invalid_argument("Invalid product position");
    std::advance(it,position);

    _productManager->remove(it->first);
    order->removeProduct(position);
    _productManager->add(it->first);
}

void OrderManager::setDeliveryLocation(Order *order, const string &location) {
    Worker* newWorker = _workerManager->getLessBusyWorker(location);
    order->setDeliverLocation(location,newWorker);
}

void OrderManager::deliver(Order *order, int clientEvaluation, bool updatePoints, int deliverDuration) {
    remove(order, false);
    order->deliver(clientEvaluation, updatePoints, deliverDuration);
    _orders.push(OrderEntry(order));
}
