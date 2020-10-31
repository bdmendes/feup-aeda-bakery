//
// Created by bdmendes on 29/10/20.
//

#include "order_manager.h"

OrderManager::OrderManager(ProductManager &pm, ClientManager &cm, WorkerManager &wm) :
        _productManager(pm), _clientManager(cm), _workerManager(wm), _orders(std::set<Order*, OrderSmaller>()){
}

bool OrderManager::has(Order *order) const {
    auto comp = [order](const Order* o2){
        return *order == *o2;
    };
    return std::find_if(_orders.begin(),_orders.end(),comp) != _orders.begin();
}

Order* OrderManager::get(unsigned int position) {
    if (position >= _orders.size()) throw InvalidOrderPosition(position, _orders.size());
    auto it = _orders.begin(); std::advance(it, position);
    return *it;
}

std::set<Order *, OrderSmaller> OrderManager::getAll() const {
    return _orders;
}

std::set<Order *, OrderSmaller> OrderManager::get(Client *client) {
    if (!_clientManager.has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    std::set<Order*, OrderSmaller> filtered;
    for (const auto& order: _orders){
        if (order->getClient() == *client) filtered.insert(order);
    }
    return filtered;
}

std::set<Order *, OrderSmaller> OrderManager::get(Worker *worker) {
    if (!_workerManager.has(worker)) throw PersonDoesNotExist(worker->getName(), worker->getTaxId());
    std::set<Order*, OrderSmaller> filtered;
    for (const auto& order: _orders){
        if (order->getWorker() == *worker) filtered.insert(order);
    }
    return filtered;
}

Order* OrderManager::add(Client *client) {
    if (!_clientManager.has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    _orders.insert(new Order(*client,*_workerManager.getAvailable()));
    return *_orders.rbegin();
}

void OrderManager::remove(Order *order) {
    auto position = std::find(_orders.begin(),_orders.end(),order);
    if (position == _orders.end())
        throw OrderDoesNotExist();
    _orders.erase(position);
}

void OrderManager::write(std::ostream &os) const {
    //needs to be modularized...
    std::array<std::string,5> cakeCategories = {
            "General", "Pie", "Sponge", "Puff Pastry", "Crunchy Cake"
    };

    for (const auto& o: _orders){
        // order details
        os << "Requested by " << o->getClient().getName()
        << " on " << o->getDate().getCompleteDate() << std::endl;
        if (!o->wasDelivered()){
            os << "To be delivered by " << o->getWorker().getName() << std::endl;
        }
        else {
            os << "Delivered by " << o->getWorker().getName() //increment date and include it here later...
            << " (evaluated with " << o->getClientEvaluation() << " points)" << std::endl;
        }

        os << std::endl;

        //products
        os << util::column("Product description",true)
        << util::column("Category")
        << util::column("Unit price")
        << util::column("Quantity") << std::endl;

        for (const auto& p: o->getProducts()){
            std::string category;
            auto* bread = dynamic_cast<Bread*>(p.first);
            auto* cake = dynamic_cast<Cake*>(p.first);
            if (bread != nullptr){
                category = bread->isSmall() ? "Small bread" : "Big bread";
            }
            else{
                category = cakeCategories.at(static_cast<unsigned long>(cake->getCategory()));
            }

            os << util::column(p.first->getName(),true)
            << util::column(category)
            << util::column(util::to_string(p.first->getPrice()))
            << util::column(std::to_string(p.second)) << std::endl;
        }

        //total price
        std::string discount = o->hasDiscount() ? "With discount" : "No discount";
        os << std::endl << util::to_string(o->getFinalPrice()) + "€ (" + discount + ")"
        << std::endl;
    }
}
