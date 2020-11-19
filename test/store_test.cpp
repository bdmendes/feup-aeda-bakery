
#include <gtest/gtest.h>
#include "model/store/store.h"
#include "model/store/location_manager.h"

#include <algorithm>

using testing::Eq;

TEST(Store, create_store){
    Store store1;

    EXPECT_EQ("Bakery Store", store1.getName());

    Store store2("Padaria Pao Quente");

    EXPECT_EQ("Padaria Pao Quente", store2.getName());
}

TEST(Store, set_name){
    Store store;
    store.setName("Padaria Doce Cereal");

    EXPECT_EQ("Padaria Doce Cereal", store.getName());

    store.setName("Padaria Diamante");

    EXPECT_EQ("Padaria Diamante", store.getName());
}

TEST(ClientManager, has_client){
    ClientManager clientM;

    EXPECT_TRUE(clientM.getAll().empty());

    Client* client1 = clientM.add("Cristina Lopes");

    EXPECT_TRUE(clientM.has(client1));

    Client* client2 = clientM.add("Joao Manuel", false, 284917316, {"jonasManel", "joao123"});

    EXPECT_TRUE(clientM.has(client1));
    EXPECT_TRUE(clientM.has(client2));
}

TEST(ClientManager, add_client){
    unsigned position = 0;
    Client client1("Rodrigo Pereira");
    std::set<Client*, PersonSmaller> clients;
    ClientManager clientM;

    EXPECT_EQ(0, clientM.getAll().size());

    clientM.add("Rodrigo Pereira");
    Client* getClient = clientM.get(position);

    EXPECT_EQ(1, clientM.getAll().size());
    EXPECT_TRUE(client1 == *getClient);

    Client client2("Maria Joao", true, 174829123, {"mariaj", "123"});
    clientM.add("Maria Joao", true, 174829123, {"mariaj", "123"});
    getClient = clientM.get(position++);

    EXPECT_EQ(2, clientM.getAll().size());
    EXPECT_TRUE(client2 == *getClient);
}

TEST(ClientManager, remove_client_by_pointer){
    ClientManager clientM;
    Client* client1 = clientM.add("Henrique Vaz");
    Client* client2 = clientM.add("Sofia Rebelo");
    unsigned position = 0;

    EXPECT_EQ(2, clientM.getAll().size());

    clientM.remove(client1);

    EXPECT_EQ(1, clientM.getAll().size());
    EXPECT_TRUE(*client2 == *clientM.get(position));

    clientM.remove(client2);

    EXPECT_TRUE(clientM.getAll().empty());
    EXPECT_THROW(clientM.remove(client1), PersonDoesNotExist);
    EXPECT_THROW(clientM.remove(client2), PersonDoesNotExist);
}

TEST(ClientManager, remove_client_by_position){
    unsigned position = 1;
    ClientManager clientM;
    Client* client1 = clientM.add("Henrique Vaz");
    Client* client2 = clientM.add("Sofia Rebelo");

    EXPECT_EQ(2, clientM.getAll().size());

    clientM.remove(position);

    EXPECT_EQ(1, clientM.getAll().size());
    EXPECT_TRUE(*client1 == *(*clientM.getAll().begin()));
    EXPECT_THROW(clientM.remove(position++), InvalidPersonPosition);

    position = 0;
    clientM.remove(position);

    EXPECT_TRUE(clientM.getAll().empty());
    EXPECT_THROW(clientM.remove(position), InvalidPersonPosition);
}

TEST(WorkerManager, has_worker){
    Worker worker1("Francisco Ferreira", 948);
    Worker worker2("Margarida Ferraz", 849);
    WorkerManager wm;

    EXPECT_FALSE(wm.has(&worker1));
    EXPECT_FALSE(wm.has(&worker2));

    wm.add("Francisco Ferreira", 948);

    EXPECT_TRUE(wm.has(&worker1));
    EXPECT_FALSE(wm.has(&worker2));

    wm.add("Margarida Ferraz", 849);

    EXPECT_TRUE(wm.has(&worker1));
    EXPECT_TRUE(wm.has(&worker2));
}

TEST(WorkerManager, get_less_busy_worker){
    Store store("Aeda");
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Ricardo Macedo");
    Client* client2 = clientM.add("Joana Moreira");
    Worker* worker1 = workerM.add("Jose Figueiras", 890);
    Worker* worker2 = workerM.add("Madalena Faria", 980);

    EXPECT_EQ(0, worker1->getUndeliveredOrders());
    EXPECT_EQ(0, worker2->getUndeliveredOrders());
    EXPECT_TRUE(*worker1 == *(workerM.getLessBusyWorker()));

    Order* order1 = orderM.add(client1);

    EXPECT_EQ(1,worker1->getUndeliveredOrders());
    EXPECT_EQ(0, worker2->getUndeliveredOrders());
    EXPECT_TRUE(*worker2 == *(workerM.getLessBusyWorker()));

    Order* order2 = orderM.add(client2);

    EXPECT_EQ(1, worker1->getUndeliveredOrders());
    EXPECT_EQ(1, worker2->getUndeliveredOrders());
    EXPECT_TRUE(*worker1 == *(workerM.getLessBusyWorker()));
}

TEST(WorkerManager, change_salary){
    WorkerManager workerM;
    Worker* worker1 = workerM.add("Francisco Ferreira", 9665679,948);
    Worker* worker2 = workerM.add("Margarida Ferraz", 54498698,849);
    unsigned position = 0;

    EXPECT_FLOAT_EQ(948, workerM.get(position)->getSalary());
    EXPECT_FLOAT_EQ(849, workerM.get(++position)->getSalary());

    position = 0;
    workerM.setSalary(position, 900);
    workerM.setSalary(++position, 950);

    EXPECT_THROW(workerM.setSalary(++position, 950), InvalidPersonPosition);
    EXPECT_THROW(workerM.setSalary(++position, 950), InvalidPersonPosition);
    EXPECT_FLOAT_EQ(900, worker1->getSalary());
    EXPECT_FLOAT_EQ(950, worker2->getSalary());
}

TEST(WorkerManager, add_worker){
    Worker w1("Francisco Ferreira", 999999999,948);
    Worker w2("Joana Teixeira", 999999999, 892);
    Worker w3("Margarida Ferraz", 999999999, 849);
    WorkerManager workerM;
    unsigned position = 0;

    EXPECT_TRUE(workerM.getAll().empty());

    Worker* worker1 = workerM.add("Francisco Ferreira", 948);

    EXPECT_EQ(1, workerM.getAll().size());
    EXPECT_TRUE(*worker1 == *workerM.get(position));

    Worker* worker2 = workerM.add("Joana Teixeira", 999999999, 892);
    position = 0;

    EXPECT_EQ(2, workerM.getAll().size());
    EXPECT_TRUE(*worker1 == *workerM.get(position));
    EXPECT_TRUE(*worker2 == *workerM.get(++position));

    Worker* worker3 = workerM.add("Margarida Ferraz", 999999999, 849);
    position = 0;

    EXPECT_EQ(3, workerM.getAll().size());
    EXPECT_TRUE(*worker1 == *workerM.get(position));
    EXPECT_TRUE(*worker2 == *workerM.get(++position));
    EXPECT_TRUE(*worker3 == *workerM.get(++position));
    EXPECT_TRUE(workerM.getAll().size() == 3);
}

TEST(WorkerManager, remove_worker_by_pointer){
    WorkerManager workerM;
    Worker* worker1 = workerM.add("Francisco Ferreira", 999999999, 948);
    Worker* worker2 = workerM.add("Joana Teixeira", 999999999, 892);
    Worker* worker3 = workerM.add("Margarida Ferraz", 999999999, 849);
    unsigned position = 0;

    EXPECT_EQ(3, workerM.getAll().size());
    EXPECT_TRUE(*worker1 == *workerM.get(position));
    EXPECT_TRUE(*worker2 == *workerM.get(++position));
    EXPECT_TRUE(*worker3 == *workerM.get(++position));

    workerM.remove(worker1);
    position = 0;

    EXPECT_EQ(2, workerM.getAll().size());
    EXPECT_TRUE(*worker2 == *workerM.get(position));
    EXPECT_TRUE(*worker3 == *workerM.get(++position));

    workerM.remove(worker2);
    position = 0;

    EXPECT_EQ(1, workerM.getAll().size());
    EXPECT_TRUE(*worker3 == *workerM.get(position));

    workerM.remove(worker3);

    EXPECT_TRUE(workerM.getAll().empty());
    EXPECT_THROW(workerM.remove(worker1), PersonDoesNotExist);
    EXPECT_THROW(workerM.remove(worker2), PersonDoesNotExist);
    EXPECT_THROW(workerM.remove(worker3), PersonDoesNotExist);
}

TEST(WorkerManager, remove_worker_by_position){
    WorkerManager workerM;
    Worker* worker1 = workerM.add("Francisco Ferreira", 999999999, 948);
    Worker* worker2 = workerM.add("Joana Teixeira", 999999999, 892);
    Worker* worker3 = workerM.add("Margarida Ferraz", 999999999, 849);
    unsigned position = 0, positionToRemove = 0;

    EXPECT_EQ(3, workerM.getAll().size());
    EXPECT_THROW(workerM.remove(3), InvalidPersonPosition);
    EXPECT_TRUE(*worker1 == *workerM.get(position));
    EXPECT_TRUE(*worker2 == *workerM.get(++position));
    EXPECT_TRUE(*worker3 == *workerM.get(++position));

    workerM.remove(positionToRemove);
    position = 0;

    EXPECT_EQ(2, workerM.getAll().size());
    EXPECT_THROW(workerM.remove(2), InvalidPersonPosition);
    EXPECT_TRUE(*worker2 == *workerM.get(position));
    EXPECT_TRUE(*worker3 == *workerM.get(++position));


    workerM.remove(positionToRemove);
    position = 0;

    EXPECT_EQ(1, workerM.getAll().size());
    EXPECT_THROW(workerM.remove(1), InvalidPersonPosition);
    EXPECT_TRUE(*worker3 == *workerM.get(position));

    workerM.remove(positionToRemove);

    EXPECT_TRUE(workerM.getAll().empty());
}

TEST(ProductManager, add_bread) {
    ProductManager productM;

    EXPECT_EQ(0, productM.getAll().size());

    Bread hugeBread("Pao de sementes", 0.2, false);
    Bread* addedBread = productM.addBread("Pao de sementes", 0.2, false);
    unsigned position = 0;

    EXPECT_EQ(1, productM.getAll().size());
    EXPECT_EQ("Pao de sementes", productM.get(position)->getName());
    EXPECT_FLOAT_EQ(0.2, productM.get(position)->getPrice());
}

TEST(ProductManager, add_cake){
    ProductManager productM;

    EXPECT_EQ(0, productM.getAll().size());

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Cake* addedCake = productM.addCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    unsigned position = 0;

    EXPECT_EQ(1, productM.getAll().size());
    EXPECT_TRUE(meatCake == *addedCake);
    EXPECT_EQ("Bolo com molho de carne", productM.get(position)->getName());
    EXPECT_FLOAT_EQ(1, productM.get(position)->getPrice());
}

TEST(OrderManager, add_order){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);
    Client* client = clientM.add("Fernando Castro");
    Worker* worker = workerM.add("Josue Tome", 928);
    Order order(*client, *worker);

    EXPECT_TRUE(orderM.getAll().empty());

    Order* order1 = orderM.add(client);

    EXPECT_EQ(1, orderM.getAll().size());
    EXPECT_TRUE(order == *order1);
}

TEST(OrderManager, add_order_with_date){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);
    std::string location  = "Guarda"; locationM.add(location);
    Date date(16, 11, 2020, 2, 30);
    Client* client = clientM.add("Fernando Castro");
    Worker* worker = workerM.add("Josue Tome", 928);
    Order order(*client, *worker, location, date);

    EXPECT_TRUE(orderM.getAll().empty());

    Order* order1 = orderM.add(client, location, date);

    EXPECT_EQ(1, orderM.getAll().size());
    EXPECT_TRUE(order == *order1);
}

TEST(OrderManager, remove_order){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Adelaide Santos");
    Client* client2 = clientM.add("Bruno Mendes");
    Client* client3 = clientM.add("Ricardo Macedo");
    Client* client4 = clientM.add("Ze Manel");
    Worker* worker = workerM.add("Madalena Faria", 980);
    Order order(*client1, *worker);

    EXPECT_THROW(orderM.remove(&order), OrderDoesNotExist);

    Order* order1 = orderM.add(client1);
    Order* order2 = orderM.add(client2);
    Order* order3 = orderM.add(client3);
    orderM.remove(order1);
    unsigned position = 0;

    EXPECT_EQ(2, orderM.getAll().size());
    EXPECT_TRUE(*order2 == *orderM.get(position));
    EXPECT_TRUE(*order3 == *orderM.get(++position));

    orderM.remove(order2);
    position = 0;

    EXPECT_EQ(1, orderM.getAll().size());
    EXPECT_TRUE(*order3 == *orderM.get(position));

    orderM.remove(order3);
    position = 0;

    EXPECT_TRUE(orderM.getAll().empty());//Throw exception  for empty orders
}

TEST(OrderManager, sort_orders){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    std::string location = "Lisboar"; locationM.add(location);
    Date date2(25, 11, 2019, 3, 40);
    Date date1(16, 11, 2020, 2, 30);
    Client* client1 = clientM.add("Fernando Castro");
    Client* client2 = clientM.add("Catia Fernandes");
    Worker* worker = workerM.add("Josue Tome", 928);
    Order order1(*client1, *worker, location, date1);
    Order order2(*client2, *worker, location, date2);

    Order* order3 = orderM.add(client1, location, date1);
    Order* order4 = orderM.add(client2, location, date2);
    unsigned position = 0;

    EXPECT_TRUE(order1 == *order3);
    EXPECT_TRUE(*order3 == *orderM.get(position));
    EXPECT_TRUE(order2 == *order4);
    EXPECT_TRUE(*order4 == *orderM.get(++position));
}

TEST(OrderManager, get_order_by_position){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Ricardo Macedo");
    Client* client2 = clientM.add("Rosalia Martins");
    Worker* worker = workerM.add("Madalena Faria", 980);
    Order order1(*client1, *worker);
    Order order2(*client2, *worker);

    EXPECT_TRUE(orderM.getAll().empty());
    orderM.add(client1);
    unsigned position = 0;

    EXPECT_EQ(1, orderM.getAll().size());
    EXPECT_TRUE(order1 == *orderM.get(position));

    orderM.add(client2);

    EXPECT_EQ(2, orderM.getAll().size());
    EXPECT_TRUE(order1 == *orderM.get(position));
    EXPECT_TRUE(order2 == *orderM.get(++position));
    EXPECT_THROW(orderM.get(++position), InvalidOrderPosition);
}

TEST(OrderManager, get_client_orders){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Ricardo Macedo");
    Client client2("Bruno Mendes");
    Worker* worker = workerM.add("Madalena Faria", 980);
    Order order(*client1, *worker);

    EXPECT_TRUE(orderM.get(client1).empty());
    EXPECT_THROW(orderM.get(&client2), PersonDoesNotExist);

    Order* order1 = orderM.add(client1);

    EXPECT_EQ(1, orderM.get(client1).size());
    EXPECT_TRUE(order == *order1);

    Order* order2 = orderM.add(client1);

    EXPECT_EQ(2, orderM.get(client1).size());
    EXPECT_TRUE(order == *order2);
}

TEST(OrderManager, get_worker_orders){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client = clientM.add("Ricardo Macedo");
    Worker* worker1 = workerM.add("Madalena Faria", 980);
    Worker worker2("Rafael Macedo", 985);
    Order order(*client, *worker1);

    EXPECT_TRUE(orderM.get(worker1).empty());
    EXPECT_THROW(orderM.get(&worker2), PersonDoesNotExist);

    Order* order1 = orderM.add(client);

    EXPECT_EQ(1, orderM.get(worker1).size());
    EXPECT_TRUE(order == *order1);

    Order* order2 = orderM.add(client);

    EXPECT_EQ(2, orderM.get(worker1).size());
    EXPECT_TRUE(order == *order2);
}




