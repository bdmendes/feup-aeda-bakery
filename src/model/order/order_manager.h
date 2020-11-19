
#ifndef FEUP_AEDA_PROJECT_ORDER_MANAGER_H
#define FEUP_AEDA_PROJECT_ORDER_MANAGER_H

#include "order.h"

#include "model/product/product_manager.h"
#include "model/person/client/client_manager.h"
#include "model/person/worker/worker_manager.h"

#include <exception/person_exception.h>

#include <algorithm>
#include <vector>
#include "model/store/location_manager.h"

/**
 * Class that manages the store orders.
 */
class OrderManager {
public:
    OrderManager(ProductManager* pm, ClientManager* cm, WorkerManager* wm, LocationManager* lm);
    ~OrderManager();

    /**
     * Checks if the order is on the orders list.
     *
     * @param order the order
     * @return true, if the order is on orders list; false, otherwise
     */
    bool has(Order* order) const;

    /**
     * Gets the order, at a certain position, either from the orders list of the client, or from the orders list of the
     * worker, never from both.
     *
     * @param position the position
     * @param client the client
     * @param worker the worker
     * @return the order at that position from the respective orders list (client or worker)
     */
    Order* get(unsigned position, Client* client = nullptr, Worker* worker = nullptr) const;

    /**
     * Gets the list of all orders.
     *
     * @return the list of all orders
     */
    std::vector<Order*> getAll() const;

    /**
     * Gets the list of all the orders requested by a certain client.
     *
     * @param client the client
     * @return the orders list
     */
    std::vector<Order*> get(Client* client) const;

    /**
     * Gets the list of all the orders delivered by a certain worker.
     *
     * @param worker the worker
     * @return the orders list
     */
    std::vector<Order*> get(Worker* worker) const;
    std::vector<Order*> get(const std::string& location) const;

    /**
     * Sorts the orders list by the request date.
     */
    void sort();
  
    Order* add(Client* client, const std::string& location, Date date = {});
    Order* add(Client* client, Worker* worker, const std::string& location, const Date& date = {});
    void remove(Order* order);

    /**
     * Removes an order from the orders list at a certain position.
     *
     * @param position the position
     */
    void remove(unsigned position);

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
    LocationManager* _locationManager;

    /**
     * The list of all orders.
     */
    std::vector<Order*> _orders;
};

#endif //FEUP_AEDA_PROJECT_ORDER_MANAGER_H
