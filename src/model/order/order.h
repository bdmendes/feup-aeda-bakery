//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_ORDER_H
#define SRC_ORDER_H

#include "exception/product_exception.h"
#include "exception/order_exception.h"

#include "model/person/person/person.h"
#include "model/product/product.h"
#include "model/product/product_manager.h"
#include "model/date/date.h"

#include <fstream>
#include <map>


class Order {
public:
    Order(Client& client, Worker& worker, Date date = {});
    // friend OrderManager; - to consider...

    bool hasDiscount() const;
    bool hasProduct(Product* product);
    bool wasDelivered() const;

    const Worker& getWorker() const;
    const Client& getClient() const;

    std::map<Product*, unsigned int, ProductSmaller> getProducts() const;

    float getClientEvaluation() const;
    float getFinalPrice() const;
    float getTotal() const;

    Date getDate() const;

    Product* addProduct(Product* product, unsigned quantity = 1);
    Product* removeProduct(Product* product, unsigned quantity);
    Product* removeProduct(Product* product);
    Product* removeProduct(unsigned position, unsigned quantity);
    Product* removeProduct(unsigned position);

    void deliver(float clientEvaluation);

    bool operator==(const Order& rhs) const;
    bool operator<(const Order& o2) const;

private:
    std::map<Product*, unsigned int, ProductSmaller> _products;
    void updateTotalPrice();
    float _totalPrice;
    Client& _client;
    Worker& _worker;
    float _clientEvaluation;
    bool _delivered;
    Date _date;
};

#endif //SRC_ORDER_H
