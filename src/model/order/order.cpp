
#include "order.h"

#include "util/util.h"

const char* Order::DEFAULT_LOCATION = "Head Office";

Order::Order(Client &client, Worker &worker, std::string location, Date date) :
        _client(&client), _worker(&worker), _clientEvaluation(0), _delivered(false),
        _totalPrice(0.0f), _requestDate(date), _deliverDate(date), _products(),
        _deliverLocation(std::move(location)){
    updateTotalPrice();
    _client->addPoints(10* static_cast<unsigned int>(_totalPrice)); //For each euro adds 10 points
    _worker->addOrderToDeliver();
}

bool Order::hasDiscount() const {
    return _client->getPoints() >= 100*_client->isPremium() + 200*!_client->isPremium();
}

bool Order::hasProduct(Product* product){
    return _products.find(product) != _products.end() && _products[product] > 0;
}

bool Order::wasDelivered() const {
    return _delivered;
}

Worker* Order::getWorker() const {
    return _worker;
}

Client* Order::getClient() const {
    return _client;
}

std::map<Product *, unsigned int, ProductSmaller> Order::getProducts() const {
    return _products;
}

int Order::getClientEvaluation() const {
    if (!_delivered) throw OrderWasNotDeliveredYet(*_client, *_worker, _requestDate);
    return _clientEvaluation;
}

float Order::getFinalPrice() const {
    return hasDiscount() ? (_client->isPremium() ? 0.95f*_totalPrice : 0.98f*_totalPrice) : _totalPrice;
}

float Order::getTotal() const {
    return _totalPrice;
}

Date Order::getRequestDate() const {
    return _requestDate;
}

void Order::updateTotalPrice() {
    _totalPrice = 0;
    for(const auto &product : _products){
        _totalPrice += (product.first->getPrice() * product.second);
    }
}

Product * Order::addProduct(Product* product, unsigned quantity) {
    if (quantity == 0) throw std::invalid_argument("Quantity cannot be 0!");
    if (_delivered) throw OrderWasAlreadyDelivered(*_client, *_worker, _requestDate);
    if (hasProduct(product)) _products[product] += quantity;
    else _products[product] = quantity;
    updateTotalPrice();
    return product;
}

void Order::removeProduct(Product *product) {
    if (_delivered) throw OrderWasAlreadyDelivered(*_client, *_worker, _requestDate);
    if (hasProduct(product)){
        _products.erase(product);
        updateTotalPrice();
    }
    else throw ProductDoesNotExist(product->getName(),product->getPrice());
}

void Order::removeProduct(unsigned long position) {
    if (_delivered) throw OrderWasAlreadyDelivered(*_client, *_worker, _requestDate);
    auto it = _products.begin();
    if (position < _products.size()){
        std::advance(it,position);
        _products.erase(it);
        updateTotalPrice();
    }
    else throw InvalidProductPosition(position, _products.size());
}

void Order::deliver(int clientEvaluation, int deliverDuration) {
    if (_delivered) throw OrderWasAlreadyDelivered(*_client, *_worker, _requestDate);
    if (clientEvaluation < 0 || clientEvaluation > 5) throw InvalidOrderEvaluation(clientEvaluation,*_client);

    _clientEvaluation = clientEvaluation;
    _delivered = true;
    _worker->removeOrderToDeliver();
    _worker->addEvaluation(clientEvaluation);
    _client->addEvaluation(clientEvaluation);

    if (deliverDuration != 0) _deliverDate.addMinutes(deliverDuration);
    else _deliverDate = Date();

    if (hasDiscount()) _client->resetPoints();
    _client->addPoints(10* static_cast<unsigned int>(_totalPrice)); //For each euro adds 10 points
}

bool Order::operator==(const Order &rhs) const {
    return _client == rhs.getClient() && _worker == rhs.getWorker()
    && _delivered == rhs.wasDelivered() && _products == rhs.getProducts();
}

bool Order::operator<(const Order &o2) const {
    return _requestDate < o2.getRequestDate();
}

void Order::print(std::ostream &os) const {
    os << "Requested by " << getClient()->getName()
       << " on " << getRequestDate().getCompleteDate() << std::endl;

    if (!wasDelivered()){
        os << "To be delivered by " << getWorker()->getName() << " " << "at " <<
        getDeliverLocation() << "\n\n";
    }
    else {
        os << "Delivered by " << getWorker()->getName() << " on " << getDeliverDate().getCompleteDate()
        << " " << "at " << getDeliverLocation()
        << "\nClient evaluation: " << getClientEvaluation() << " points" << "\n\n";
    }

    //products
    if (!_products.empty()) {
        os << std::string(static_cast<unsigned int>(_products.size()) / 10 + 3, util::SPACE)
           << util::column("Product description", true)
           << util::column("Category")
           << util::column("Unit price")
           << util::column("Quantity") << "\n";
        int count = 1;
        for (const auto &p: getProducts()) {
            os << std::to_string(count++) + ". ";
            p.first->print(os);
            os << util::column(std::to_string(p.second)) << std::endl;
        }
    }
    else std::cout << "No products added\n";

    //total price
    const std::string discount = hasDiscount() ? "With discount" : "No discount";
    os << std::endl << util::to_string(getFinalPrice()) + "€ (" + discount + ")" << "\n";
}

Date Order::getDeliverDate() const {
    if (!_delivered) throw OrderWasNotDeliveredYet(*_client, *_worker, _requestDate);
    return _deliverDate;
}

std::string Order::getDeliverLocation() const {
    return _deliverLocation;
}

void Order::setDeliverLocation(const std::string& location) {
    if (_delivered) throw OrderWasAlreadyDelivered(*_client,*_worker,_deliverDate);
    _deliverLocation = location;
}
