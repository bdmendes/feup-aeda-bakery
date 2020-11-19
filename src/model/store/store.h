#ifndef SRC_STORE_H
#define SRC_STORE_H

#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "model/person/person.h"
#include "model/person/boss/boss.h"
#include "model/order/order.h"
#include <exception/person_exception.h>
#include <exception/store_exception.h>
#include <exception/product_exception.h>

#include "model/product/product.h"

#include "../person/client/client_manager.h"
#include "../product/product_manager.h"
#include "../person/worker/worker_manager.h"
#include "../order/order_manager.h"
#include "location_manager.h"

class Order;

/**
 * Class relative to a store.
 */
class Store {
public:
    /**
     * Creates a new Store object.
     *
     * @param name the name
     */
    explicit Store(std::string name = "Bakery Store");

    /**
     * Sets the store name.
     *
     * @param name the name
     */
    void setName(const std::string& name);

    /**
     * Gets the store name.
     *
     * @return
     */
    std::string getName() const;

    /**
     * Gets the store evaluation given by the clients.
     */
    int getEvaluation() const;

    /**
     * Gets the store's profit.
     *
     * @return the store's profit
     */
    float getProfit() const;

    /**
    * Reads all the store data (boss, worker manager, product manager, client manager and order manager) from a
    * a file and creates new objects of the respective classes with that data.
    *
    * @param dataFolderPath the folder path
    * @return "Import succeeded." if the reading was succeeded; "Import failed!", otherwise
    */
    std::string read(const std::string& dataFolderPath);

    /**
     * Writes all the store data (boss, worker manager, product manager, client manager and order manager) to a file
     * and creates new objects of the respective classes with that data.
     *
     * @param dataFolderPath  the folder path
     * @return "Export succeeded." if the writing was succeeded; "Export failed!", otherwise
     */
    std::string write(const std::string& dataFolderPath);

    /**
     * The product manager associated to the store.
     */
    ProductManager productManager;

    /**
     * The client manager associated to the store.
     */
    ClientManager clientManager;

    /**
     * The worker manager associated to the store.
     */
    WorkerManager workerManager;

    /**
     * The order manager associated to the store.
     */
    OrderManager orderManager;

    /**
     * The location manager associated to the store.
     */
    LocationManager locationManager;

    /**
     * The boss associated to the store.
     */
    Boss boss;

private:
    /**
     * The store name.
     */
    std::string _name;
};

#endif //SRC_STORE_H