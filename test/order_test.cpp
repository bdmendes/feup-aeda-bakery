
#include <gtest/gtest.h>
#include "model/order/order.h"
#include "model/product/product.h"
#include "model/person/client/client.h"
#include "model/person/worker/worker.h"
#include "model/person/client/client_manager.h"
#include "model/person/worker/worker_manager.h"
#include "model/order/order_manager.h"

using testing::Eq;

TEST(Order, create_order){
    Client client("Alfredo Simoes");
    Worker worker("Lisboa", "Beatriz Silva", 950);
    std::string location = "Porto";
    Date date(14, 11, 2020, 16, 30);
    Order order(client,worker, location, date);

    EXPECT_EQ(client, *order.getClient());
    EXPECT_EQ(worker, *order.getWorker());
    EXPECT_EQ(location, order.getDeliverLocation());
    EXPECT_EQ(date, order.getRequestDate());
    EXPECT_FALSE(order.hasDiscount());
    EXPECT_FALSE(order.wasDelivered());
}

TEST(Order, has_discount){
    Client client1("Alfredo Simoes");
    Client client2("Alfredo Simoes");
    Client client3("Carlos Monteiro", 1238471736, true);
    Client client4("Carlos Monteiro", 1238471736, true);
    Worker worker("Lisboa", "Beatriz Silva",950);
    std::string location = "Maia";
    Date date(14, 11, 2020, 16, 30);

    Order order1(client1,worker, location, date); client1.setPoints(200);
    Order order2(client2, worker, location, date);
    Order order3(client3, worker, location, date); client3.setPoints(100);
    Order order4(client4, worker, location, date);

    EXPECT_TRUE(order1.hasDiscount());
    EXPECT_FALSE(order2.hasDiscount());
    EXPECT_TRUE(order3.hasDiscount());
    EXPECT_FALSE(order4.hasDiscount());
}

TEST(Order, has_product){
    LocationManager locationM;
    ClientManager clientM;
    WorkerManager workerM(&locationM);
    ProductManager productM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client = clientM.add("Jose Fernandes");
    Worker* worker = workerM.add(Order::DEFAULT_LOCATION, "Mario Rodrigues");
    Cake* cake = productM.addCake("Bolo de bolacha", 2.2);
    Bread* bread = productM.addBread("Pao de cereais", 0.7);

    Order* order = orderM.add(client, worker);

    EXPECT_FALSE(order->hasProduct(cake));
    EXPECT_FALSE(order->hasProduct(bread));

    orderM.addProduct(order, cake);

    EXPECT_TRUE(order->hasProduct(cake));
    EXPECT_FALSE(order->hasProduct(bread));

    orderM.addProduct(order, bread);

    EXPECT_TRUE(order->hasProduct(cake));
    EXPECT_TRUE(order->hasProduct(bread));
}

TEST(Order, was_delivered){
    LocationManager locationM;
    ClientManager clientM;
    WorkerManager workerM(&locationM);
    ProductManager productM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client = clientM.add("Jose Fernandes");
    Worker* worker = workerM.add(Order::DEFAULT_LOCATION, "Mario Rodrigues");
    Order* order = orderM.add(client, worker);

    EXPECT_FALSE(order->wasDelivered());

    orderM.deliver(order, 4);

    EXPECT_TRUE(order->wasDelivered());
}

TEST(Order, get_worker){
    Client client1("Alfredo Simoes");
    Worker worker1("Lisboa", "Beatriz Silva",950);
    Order order1(client1, worker1);

    EXPECT_EQ(worker1, *order1.getWorker());

    Client client2("Carlos Monteiro");
    Worker worker2("Head Office", "Joana Figueiredo", 839);
    Order order2(client2, worker2);

    EXPECT_EQ(worker2, *order2.getWorker());
}

TEST(Order, get_client){
    Client client1("Alfredo Simoes");
    Worker worker1("Lisboa", "Beatriz Silva",950);
    Order order1(client1, worker1);

    EXPECT_EQ(client1, *order1.getClient());

    Client client2("Carlos Monteiro");
    Worker worker2("Head Office", "Joana Figueiredo", 839);
    Order order2(client2, worker2);

    EXPECT_EQ(client2  , *order2.getClient());
}

TEST(Order, get_deliver_location){
    Client client1("Alfredo Simoes");
    Worker worker1("Head Office", "Beatriz Silva",950);
    Order order1(client1, worker1, "Matosinhos");

    EXPECT_EQ("Matosinhos", order1.getDeliverLocation());

    Client client2("Carlos Monteiro");
    Worker worker2("Head Office", "Joana Figueiredo", 839);
    Order order2(client2, worker2, "Vila do Conde");

    EXPECT_EQ("Vila do Conde", order2.getDeliverLocation());
}

TEST(Order, get_client_evaluation){
    LocationManager locationM;
    ClientManager clientM;
    WorkerManager workerM(&locationM);
    ProductManager productM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client = clientM.add("Jose Fernandes");
    Worker* worker = workerM.add(Order::DEFAULT_LOCATION, "Mario Rodrigues");
    Order* order = orderM.add(client, worker);

    EXPECT_THROW(order->getClientEvaluation(), OrderWasNotDeliveredYet);

    orderM.deliver(order, 4);

    EXPECT_EQ(4, order->getClientEvaluation());
}

TEST(Order, get_total){
    LocationManager locationM;
    ClientManager clientM;
    WorkerManager workerM(&locationM);
    ProductManager productM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Cake* cake = productM.addCake("Bolo de bolacha", 2.2);
    Worker* worker = workerM.add(Order::DEFAULT_LOCATION, "Mario Rodrigues");
    unsigned int quantity = 10;

    Client* client1 = clientM.add("Jose Fernandes");
    Order* order1 = orderM.add(client1, worker);
    orderM.addProduct(order1, cake, quantity);

    EXPECT_EQ(10*2.2, order1->getTotal());

    Client* client2 = clientM.add("Mariana Teixeira");
    client2->addPoints(200);
    Order* order2 = orderM.add(client2, worker);
    orderM.addProduct(order2, cake, quantity);

    EXPECT_FLOAT_EQ(10*2.2, order2->getTotal());

    Client* client3 = clientM.add("Catarina Oliveira", Person::DEFAULT_TAX_ID, true);
    Order* order3 = orderM.add(client3, worker);
    orderM.addProduct(order3, cake, quantity);

    EXPECT_FLOAT_EQ(10*2.2, order3->getTotal());

    Client* client4 = clientM.add("Rodrigo Ferreira", Person::DEFAULT_TAX_ID, true);
    client4->addPoints(100);
    Order* order4 = orderM.add(client4, worker);
    orderM.addProduct(order4, cake, quantity);

    EXPECT_FLOAT_EQ(10*2.2, order4->getTotal());
}

TEST(Order, get_final_price){
    LocationManager locationM;
    ClientManager clientM;
    WorkerManager workerM(&locationM);
    ProductManager productM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Cake* cake = productM.addCake("Bolo de bolacha", 2.2);
    Worker* worker = workerM.add(Order::DEFAULT_LOCATION, "Mario Rodrigues");
    unsigned int quantity = 10;

    Client* client1 = clientM.add("Jose Fernandes");
    Order* order1 = orderM.add(client1, worker);
    orderM.addProduct(order1, cake, quantity);

    EXPECT_EQ(10*2.2, order1->getFinalPrice());

    Client* client2 = clientM.add("Mariana Teixeira");
    client2->addPoints(200);
    Order* order2 = orderM.add(client2, worker);
    orderM.addProduct(order2, cake, quantity);

    EXPECT_FLOAT_EQ(10*2.2*0.98, order2->getFinalPrice());

    Client* client3 = clientM.add("Catarina Oliveira", Person::DEFAULT_TAX_ID, true);
    Order* order3 = orderM.add(client3, worker);
    orderM.addProduct(order3, cake, quantity);

    EXPECT_FLOAT_EQ(10*2.2, order3->getFinalPrice());

    Client* client4 = clientM.add("Rodrigo Ferreira", Person::DEFAULT_TAX_ID, true);
    client4->addPoints(100);
    Order* order4 = orderM.add(client4, worker);
    orderM.addProduct(order4, cake, quantity);

    EXPECT_FLOAT_EQ(10*2.2*0.95, order4->getFinalPrice());
}

TEST(Order, get_request_date){
    Client client1("Alfredo Simoes");
    Worker worker1("Head Office", "Beatriz Silva",950);
    Date date1(23, 7, 2020, 14, 50);
    Order order1(client1, worker1, "Matosinhos", date1);

    EXPECT_TRUE(date1 == order1.getRequestDate());

    Client client2("Carlos Monteiro");
    Worker worker2("Head Office", "Joana Figueiredo", 839);
    Date date2(19, 8, 2019, 22, 30);
    Order order2(client2, worker2, "Vila do Conde", date2);

    EXPECT_TRUE(date2 == order2.getRequestDate());
}

TEST(Order, less_than_operator){
    LocationManager locationM;
    ClientManager clientM;
    WorkerManager workerM(&locationM);
    ProductManager productM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Alfredo Simoes");
    Client* client2 = clientM.add("Olivia Loureiro");
    Worker* worker = workerM.add("Head Office", "Beatriz Silva",950);

    Order* order1 = orderM.add(client1, worker);
    Order* order2 = orderM.add(client2, worker);

    EXPECT_FALSE(*order1 < *order2);
    EXPECT_FALSE(*order2 < *order1);

    orderM.deliver(order2, 4);

    EXPECT_TRUE(*order2 < *order1);

    orderM.deliver(order1, 3);

    EXPECT_TRUE(*order2 < *order1);

    Order* order3 = orderM.add(client1, worker);
    Order* order4 = orderM.add(client2, worker);
    client2->addDiscount();

    EXPECT_TRUE(*order4 < *order3);
}

TEST(Order, equality_operator){
    Date date(12, 1, 2012, 13, 50);
    LocationManager locationM;
    locationM.add("Lisboa");
    ClientManager clientM;
    WorkerManager workerM(&locationM);
    ProductManager productM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Alfredo Simoes");
    Worker* worker = workerM.add(Order::DEFAULT_LOCATION, "Beatriz Silva",950);

    Order* order1 = orderM.add(client1, worker, Order::DEFAULT_LOCATION, date);
    Order* order2 = orderM.add(client1, worker, Order::DEFAULT_LOCATION, date);

    EXPECT_TRUE(*order1 == *order2);

    Client* client2 = clientM.add("Olivia Loureiro");
    Order* order3 = orderM.add(client2, worker);

    EXPECT_FALSE(*order1 == *order3);
    EXPECT_FALSE(*order2 == *order3);

    Worker* worker1 = workerM.add(Order::DEFAULT_LOCATION, "Martim Simoes");
    Order* order4 = orderM.add(client1, worker1);

    EXPECT_FALSE(*order1 == *order4);
    EXPECT_FALSE(*order2 == *order4);
    EXPECT_FALSE(*order3 == *order4);

    Order* order5 = orderM.add(client1, worker1, "Lisboa");

    EXPECT_FALSE(*order1 == *order5);
    EXPECT_FALSE(*order2 == *order5);
    EXPECT_FALSE(*order3 == *order5);
    EXPECT_FALSE(*order4 == *order5);
}
