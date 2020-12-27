
#include "order.h"

#include "util/util.h"

const char* Order::DEFAULT_LOCATION = "Head Office";

Order::Order(Client &client, Worker &worker, std::string location, Date date) :
        _client(&client), _worker(&worker), _clientEvaluation(0), _delivered(false),
        _totalPrice(0.0f), _requestDate(date), _deliverDate(date), _products(),
        _deliverLocation(std::move(location)){
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
    _totalPrice = 0.0f;
    for(const auto &product : _products){
        _totalPrice += (product.first->getPrice() * product.second);
    }
}

Product * Order::addProduct(Product* product, unsigned quantity) {
    if (quantity == 0) throw std::invalid_argument("Quantity cannot be 0!");
    if (_delivered) throw OrderWasAlreadyDelivered(*_client, *_worker, _requestDate);

    if (hasProduct(product)) _products[product] += quantity;
    else{
        _products[product] = quantity;
        product->addInclusion();
    }
    updateTotalPrice();
    return product;
}

void Order::removeProduct(Product *product) {
    if (_delivered) throw OrderWasAlreadyDelivered(*_client, *_worker, _requestDate);
    if (hasProduct(product)){
        _products.erase(product);
        updateTotalPrice();
        product->removeInclusion();
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
        it->first->removeInclusion();
    }
    else throw InvalidProductPosition(position, _products.size());
}

void Order::deliver(int clientEvaluation, bool updatePoints, int deliverDuration) {
    if (_delivered) throw OrderWasAlreadyDelivered(*_client, *_worker, _requestDate);
    if (clientEvaluation < 0 || clientEvaluation > 5) throw InvalidOrderEvaluation(clientEvaluation,*_client);

    _clientEvaluation = clientEvaluation;
    _delivered = true;
    _worker->removeOrderToDeliver();
    _worker->addEvaluation(clientEvaluation);
    _client->addEvaluation(clientEvaluation);

    if (deliverDuration != 0) _deliverDate.addMinutes(deliverDuration);
    else _deliverDate = Date();

    if (hasDiscount()) _client->addDiscount();

    if (updatePoints){
        if (hasDiscount()) _client->resetPoints();
        _client->addPoints(10* static_cast<unsigned int>(_totalPrice)); //For each euro adds 10 points
    }
}

bool Order::operator==(const Order &rhs) const {
    return *_client == *rhs.getClient() && *_worker == *rhs.getWorker()
    && _deliverLocation == rhs.getDeliverLocation() && _requestDate == rhs.getRequestDate()
    && wasDelivered() == rhs.wasDelivered() && getProducts() == rhs.getProducts();
}

bool Order::operator<(const Order &o2) const {
    if (wasDelivered() != o2.wasDelivered()){
        return wasDelivered();
    }
    if (_client->getMeanEvaluation() != o2._client->getMeanEvaluation()){
        return _client->getMeanEvaluation() > o2._client->getMeanEvaluation();
    }
    return _client->getNumDiscounts() > o2._client->getNumDiscounts();
}

void Order::print(std::ostream &os) const {
    os << "Requested by " << getClient()->getName() << " (mean evaluation: "
       << util::to_string(getClient()->getMeanEvaluation()) << "; past discounts: "
       << getClient()->getNumDiscounts()
       << ") on " << getRequestDate().getCompleteDate() << std::endl;

    if (!wasDelivered()){
        os << "To be delivered by " << getWorker()->getName() << " (who works at " <<
        getWorker()->getLocation() << ") at " <<
        getDeliverLocation() << "\n\n";
    }
    else {
        os << "Delivered by " << getWorker()->getName() << " (who works at "
        << getWorker()->getLocation() << ") on " << getDeliverDate().getCompleteDate()
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
    os << std::endl << util::to_string(getFinalPrice()) + " euros (" + discount + ")" << "\n";
}

Date Order::getDeliverDate() const {
    if (!_delivered) throw OrderWasNotDeliveredYet(*_client, *_worker, _requestDate);
    return _deliverDate;
}

std::string Order::getDeliverLocation() const {
    return _deliverLocation;
}

void Order::setDeliverLocation(const std::string& location, Worker* newWorker) {
    if (_delivered) throw OrderWasAlreadyDelivered(*_client,*_worker,_deliverDate);
    getWorker()->removeOrderToDeliver();
    _worker = newWorker;
    _worker->addOrderToDeliver();
    _deliverLocation = location;
}
