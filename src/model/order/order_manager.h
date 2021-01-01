
#ifndef FEUP_AEDA_PROJECT_ORDER_MANAGER_H
#define FEUP_AEDA_PROJECT_ORDER_MANAGER_H

#include "order.h"

#include "model/product/product_manager.h"
#include "model/person/client/client_manager.h"
#include "model/person/worker/worker_manager.h"

#include <exception/person_exception.h>

#include <algorithm>
#include <queue>
#include "model/store/location_manager.h"

/**
 * Class which encapsulates a Order* and allows operators to be overloaded for them.
 */
class OrderEntry{
public:
    /**
     * Create a new null OrderEntry object.
     */
    OrderEntry() : _order(nullptr){};
    /**
     * Create a new OrderEntry object.
     * @param order
     */
    explicit OrderEntry(Order* order) : _order(order) {};
    /**
     * Get the Order* which the OrderEntry encapsulates
     * @return the pointer to the order
     */
    Order* getOrder() const { return _order; };
    /**
     * Sets a new order
     * @param order the order to be set
     */
    void setOrder(Order* order) { _order = order; };
    /**
     * A OrderEntry comparison is based on the Order defined operator.
     * @param rhs the product to be compared to
     * @return the inequality of the orders
     */
    bool operator<(const OrderEntry& rhs) const{
        if(!getOrder() || !rhs.getOrder()) return false;
        return *getOrder() < *rhs.getOrder();
    }
    /**
     * A OrderEntry comparison is based on the Order defined operator.
     * @param rhs the product to be compared to
     * @return the equality of the orders
     */
    bool operator==(const OrderEntry& rhs) const{
        if(!getOrder() || !rhs.getOrder()) return false;
        return *getOrder() == *rhs.getOrder();
    }
private:
    /**
     * The pointer that is encapsulated.
     */
    Order* _order;
};

/**
 * Class that manages the store orders.
 */
class OrderManager {
public:
    /**
     *  Creates a new OrderManager object.
     *
     * @param pm the product manager
     * @param cm the client manager
     * @param wm the worker manager
     * @param lm the location manager
     */
    OrderManager(ProductManager* pm, ClientManager* cm, WorkerManager* wm, LocationManager* lm);

    /**
     * Destructs the OrderManager object.
     */
    ~OrderManager();

    /**
     * Checks if the order is on the orders list.
     *
     * @param order the order
     * @return true, if the order is on the orders queue; false, otherwise
     */
    bool has(Order* order) const;

    /**
     * Gets the order, at a certain position, either from the orders queue of the client, or from the orders queue of the
     * worker. If neither is provided, all orders are considered to count the position.
     *
     * @param position the position
     * @param client the client
     * @param worker the worker
     * @return the order at that position from the respective orders list (client or worker)
     */
    Order* get(unsigned long position, Client* client = nullptr, Worker* worker = nullptr) const;

    /**
     * Gets the list of all orders.
     *
     * @return the list of all orders
     */
    std::priority_queue<OrderEntry> getAll() const;

    /**
     * Gets the pointer to the order with provided details.
     *
     * @param client who requested the order
     * @param worker who is assigned to the order
     * @param location the order delivery location
     * @param date the order request date
     * @return order if found
     */
    Order* get(Client* client, Worker* worker, const std::string& location, const Date& date);

    /**
     * Gets the list of all orders requested by a certain client.
     *
     * @param client the client
     * @return the orders list relative to that client
     */
    std::priority_queue<OrderEntry> get(Client* client) const;

    /**
     * Gets the list of all orders delivered by a certain worker.
     *
     * @param worker the worker
     * @return the orders list relative to that worker
     */
    std::priority_queue<OrderEntry> get(Worker* worker) const;

    /**
     * Gets the list of all orders delivered in a certain store location.
     *
     * @param location the store location
     * @return the orders list relative to that store location
     */
    std::priority_queue<OrderEntry> get(const std::string& location) const;

    /**
     * Adds a new order to the orders list created from that data: client, store location and date.
     *
     * @param client the client
     * @param location the location
     * @param date the date
     * @return the new order add to the orders list
     */
    Order* add(Client* client, const std::string& location = Order::DEFAULT_LOCATION, const Date &date = {});

    /**
     * Adds a new order to the orders list created from that data: client, worker, store location and date.
     *
     * @param client the client
     * @param worker the worker
     * @param location the location
     * @param date the date
     * @return the new order added to the orders list
     */
    Order* add(Client* client, Worker* worker, const std::string& location = Order::DEFAULT_LOCATION, const Date& date = {});

    /**
     * Remove a certain order from the orders list.
     *
     * @param order the order
     */
    void remove(Order* order, bool updateWorkerOrders = true, bool destroy = true);

    /**
     * Removes an order from the orders list at a certain position.
     *
     * @param position the position
     */
    void remove(unsigned long position, bool updateWorkerOrders = true, bool destroy = true);


    /**
     * Wrapper to Order::addProduct(...) which updates the products BST to reflect the addition.
     * @param order the order to add the product; should be in the queue
     * @param product the product to be added; should be in the BST
     * @param quantity the requested quantity; defaults to 1
     * @return the product added
     */
    Product* addProduct(Order* order, Product* product, unsigned quantity = 1);

    /**
     * Wrapper to Order::removeProduct(...) which updates the products BST to reflect the removal.
     * @param order the order to remove the product; should be in the queue
     * @param product the product to be removed
     */
    void removeProduct(Order* order, Product* product);

    /**
     * Wrapper to Order::removeProduct(...) which updates the products BST to reflect the removal.
     * @param order the order to remove the product; should be in the queue
     * @param position the position of the product in the map of products to quantities in the order
     */
    void removeProduct(Order* order, unsigned long position);

    /**
     * Wrapper to Order::setDeliveryLocation(...) which allocates a new worker to deliver the order
     * in the newly requested location (if possible, working in that location) and frees the old one from the duty.
     * @param order the order to change the delivery location; should be in the queue
     * @param location the new delivery location
     */
    void setDeliveryLocation(Order* order, const std::string& location);

    /**
     * Wrapper to Order::deliver(...) which updates the orders queue to reflect the deliverance of the order
     * (the order now loses priority; stays in the queue for historical reasons).
     * @param order the order to be delivered
     * @param clientEvaluation the evaluation the client gave the order
     * @param updatePoints whether the client points should be updated; make false when reading from file so that the
     * previously read points from the client file aren't reset
     * @param deliverDuration the time the worker took to delivery the order; defaults to 30
     */
    void deliver(Order* order, int clientEvaluation, bool updatePoints = true, int deliverDuration = 30);

    /**
     * Reads all the orders on the file and its data: request date, products (name, price and requested quantity),
     * client (taxpayer identification number), worker (taxpayer identification number), delivery date (if the order was
     * already delivered) and order evaluation (also in case the order was already delivered). Then it adds each order
     * to the orders list.
     *
     * @param path the file path
     */
    void read(const std::string& path);

    /**
     * Writes all the orders data on the orders list: client taxpayer identification number, worker taxpayer
     * identification number, request date, delivery date (if it was already delivered) and all the products data (name,
     * price and requested quantity).
     *
     * @param path the file path
     */
    void write(const std::string& path);

    /**
     * For all the orders on the orders list, prints all its data : client name, worker name, request date, delivery
     * date (if it was already delivered) and the order evaluation given by the client (also just in case the order was
     * already delivered).
     *
     * @param os the output stream
     * @param client the client
     * @param worker the worker
     * @return true, if there are already orders on the orders list; false, otherwise
     */
    bool print(std::ostream& os, Client* client = nullptr, Worker* worker = nullptr) const;

private:
    /**
     * The store product manager.
     */
    ProductManager* _productManager;

    /**
     * The store client manager.
     */
    ClientManager* _clientManager;

    /**
     * The store worker manager.
     */
    WorkerManager* _workerManager;

    /**
     * The store location manager.
     */
    LocationManager* _locationManager;

    /**
     * The queue of all orders. Delivered orders are kept in the end for historical reasons.
     */
    std::priority_queue<OrderEntry> _orders;
};

#endif //FEUP_AEDA_PROJECT_ORDER_MANAGER_H
