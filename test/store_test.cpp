//
// Created by bdmendes on 27/10/20.
//

#include <gtest/gtest.h>
#include "model/store/store.h"
#include "model/person/client/client_manager.h"
#include "model/person/worker/worker_manager.h"
#include "model/product/product_manager.h"
#include "model/order/order_manager.h"
#include <algorithm>
#include <map>

using testing::Eq;

TEST(Store, create_store){
    Store s1;

    EXPECT_EQ("Bakery Store", s1.getName());

    Store s2("Padaria Pao Quente");

    EXPECT_EQ("Padaria Pao Quente", s2.getName());
}

TEST(Store, set_name){
    Store store;
    store.setName("Padaria Doce Cereal");

    EXPECT_EQ("Padaria Doce Cereal", store.getName());

    store.setName("Padaria Diamante");

    EXPECT_EQ("Padaria Diamante", store.getName());
}

TEST(ClientManager, has_client){
    Client c1("Cristina Lopes");
    Client c2("Joao Manuel", false, 284917316, {"jonasManel", "joao123"});
    ClientManager cm;

    EXPECT_FALSE(cm.has(&c1));
    EXPECT_FALSE(cm.has(&c2));

    cm.add("Cristina Lopes");

    EXPECT_TRUE(cm.has(&c1));
    EXPECT_FALSE(cm.has(&c2));

    cm.add("Joao Manuel", false, 284917316, {"jonasManel", "joao123"});

    EXPECT_TRUE(cm.has(&c1));
    EXPECT_TRUE(cm.has(&c2));
}

TEST(ClientManager, add_client){
    unsigned position = 0;
    Client client1("Rodrigo Pereira");
    std::set<Client*, PersonSmaller> clients;
    ClientManager cm;

    EXPECT_EQ(0, cm.getAll().size());

    cm.add("Rodrigo Pereira");
    Client* getClient = cm.get(position);

    EXPECT_EQ(1, cm.getAll().size());
    EXPECT_TRUE(client1 == *getClient);

    Client client2("Maria Joao", true, 174829123, {"mariaj", "123"});
    cm.add("Maria Joao", true, 174829123, {"mariaj", "123"});
    getClient = cm.get(position++);

    EXPECT_EQ(2, cm.getAll().size());
    EXPECT_TRUE(client2 == *getClient);
    EXPECT_THROW(cm.add("Maria Joao", true, 174829123, {"mariaj", "123"}), PersonAlreadyExists);
}

TEST(ClientManager, remove_client_by_pointer){
    Client c1("Henrique Vaz");
    Client c2("Sofia Rebelo");
    ClientManager cm;
    cm.add("Henrique Vaz");
    cm.add("Sofia Rebelo");
    unsigned position = 0;

    EXPECT_EQ(2, cm.getAll().size());

    cm.remove(&c1);

    EXPECT_EQ(1, cm.getAll().size());
    EXPECT_TRUE(c2 == *cm.get(position));

    cm.remove(&c2);

    EXPECT_TRUE(cm.getAll().empty());
    EXPECT_THROW(cm.remove(&c1), PersonDoesNotExist);
    EXPECT_THROW(cm.remove(&c2), PersonDoesNotExist);
}

TEST(ClientManager, remove_client_by_position){
    unsigned position = 1;
    Client c1("Henrique Vaz");
    Client c2("Sofia Rebelo");
    ClientManager cm;
    cm.add("Henrique Vaz");
    cm.add("Sofia Rebelo");

    EXPECT_EQ(2, cm.getAll().size());

    cm.remove(position);

    EXPECT_EQ(1, cm.getAll().size());
    EXPECT_TRUE(c1 == *(*cm.getAll().begin()));
    EXPECT_THROW(cm.remove(position++), InvalidPersonPosition);

    position = 0;
    cm.remove(position);

    EXPECT_TRUE(cm.getAll().empty());
    EXPECT_THROW(cm.remove(position), InvalidPersonPosition);
}

TEST(WorkerManager, has_worker){
    Worker w1("Francisco Ferreira", 948);
    Worker w2("Margarida Ferraz", 849);
    WorkerManager wm;

    EXPECT_FALSE(wm.has(&w1));
    EXPECT_FALSE(wm.has(&w2));

    wm.add("Francisco Ferreira", 948);

    EXPECT_TRUE(wm.has(&w1));
    EXPECT_FALSE(wm.has(&w2));

    wm.add("Margarida Ferraz", 849);

    EXPECT_TRUE(wm.has(&w1));
    EXPECT_TRUE(wm.has(&w2));
}

TEST(WorkerManager, change_salary){
    WorkerManager wm;
    wm.add("Francisco Ferreira", 948);
    wm.add("Margarida Ferraz", 849);
    unsigned position = 0;

    EXPECT_FLOAT_EQ(948, wm.get(position)->getSalary());
    EXPECT_FLOAT_EQ(849, wm.get(++position)->getSalary());

    position = 0;
    wm.changeSalary(position, 900);
    wm.changeSalary(++position, 950);
    EXPECT_THROW(wm.changeSalary(++position, 950), InvalidPersonPosition);

    position = 0;
    EXPECT_FLOAT_EQ(900, wm.get(position)->getSalary());
    EXPECT_FLOAT_EQ(950, wm.get(++position)->getSalary());
}

TEST(WorkerManager, add_worker){
    Worker w1("Francisco Ferreira", 948);
    Worker w2("Joana Teixeira", 892);
    Worker w3("Margarida Ferraz", 849);
    WorkerManager wm;
    unsigned position = 0;

    EXPECT_TRUE(wm.getAll().empty());

    wm.add("Francisco Ferreira", 948);

    EXPECT_EQ(1, wm.getAll().size());
    EXPECT_TRUE(w1 == *wm.get(position));

    wm.add("Joana Teixeira", 892);

    position = 0;
    EXPECT_EQ(2, wm.getAll().size());
    EXPECT_TRUE(w1 == *wm.get(position));
    EXPECT_TRUE(w2 == *wm.get(++position));

    wm.add("Margarida Ferraz", 849);

    position = 0;
    EXPECT_EQ(3, wm.getAll().size());
    EXPECT_TRUE(w1 == *wm.get(position));
    EXPECT_TRUE(w2 == *wm.get(++position));
    EXPECT_TRUE(w3 == *wm.get(++position));

    EXPECT_THROW(wm.add("Francisco Ferreira", 948), PersonAlreadyExists);
    EXPECT_THROW(wm.add("Joana Teixeira", 892), PersonAlreadyExists);
    EXPECT_THROW(wm.add("Margarida Ferraz", 849), PersonAlreadyExists);
}

TEST(WorkerManager, remove_worker_by_pointer){
    Worker w1("Francisco Ferreira", 948);
    Worker w2("Joana Teixeira", 892);
    Worker w3("Margarida Ferraz", 849);
    WorkerManager wm;
    wm.add("Francisco Ferreira", 948);
    wm.add("Joana Teixeira", 892);
    wm.add("Margarida Ferraz", 849);
    unsigned position = 0;

    EXPECT_EQ(3, wm.getAll().size());
    EXPECT_TRUE(w1 == *wm.get(position));
    EXPECT_TRUE(w2 == *wm.get(++position));
    EXPECT_TRUE(w3 == *wm.get(++position));

    wm.remove(&w1);

    position = 0;
    EXPECT_EQ(2, wm.getAll().size());
    EXPECT_TRUE(w2 == *wm.get(position));
    EXPECT_TRUE(w3 == *wm.get(++position));

    wm.remove(&w2);

    position = 0;
    EXPECT_EQ(1, wm.getAll().size());
    EXPECT_TRUE(w3 == *wm.get(position));

    wm.remove(&w3);

    EXPECT_TRUE(wm.getAll().empty());
    EXPECT_THROW(wm.remove(&w1), PersonDoesNotExist);
    EXPECT_THROW(wm.remove(&w2), PersonDoesNotExist);
    EXPECT_THROW(wm.remove(&w3), PersonDoesNotExist);
}

TEST(WorkerManager, remove_worker_by_position){
    Worker w1("Francisco Ferreira", 948);
    Worker w2("Joana Teixeira", 892);
    Worker w3("Margarida Ferraz", 849);
    WorkerManager wm;
    wm.add("Francisco Ferreira", 948);
    wm.add("Joana Teixeira", 892);
    wm.add("Margarida Ferraz", 849);
    unsigned position = 0, positionToRemove = 0;

    EXPECT_EQ(3, wm.getAll().size());
    EXPECT_THROW(wm.remove(3), InvalidPersonPosition);
    EXPECT_TRUE(w1 == *wm.get(position));
    EXPECT_TRUE(w2 == *wm.get(++position));
    EXPECT_TRUE(w3 == *wm.get(++position));

    wm.remove(positionToRemove);

    position = 0;
    EXPECT_EQ(2, wm.getAll().size());
    EXPECT_THROW(wm.remove(2), InvalidPersonPosition);
    EXPECT_TRUE(w2 == *wm.get(position));
    EXPECT_TRUE(w3 == *wm.get(++position));


    wm.remove(positionToRemove);

    position = 0;
    EXPECT_EQ(1, wm.getAll().size());
    EXPECT_THROW(wm.remove(1), InvalidPersonPosition);
    EXPECT_TRUE(w3 == *wm.get(position));

    wm.remove(positionToRemove);

    EXPECT_TRUE(wm.getAll().empty());
}

TEST(ProductManager, create_product_manager){
    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);
    std::set<Product*, ProductSmaller> stock;
    stock.insert(&meatCake);
    stock.insert(&hugeBread);
    ProductManager pm(stock);

    EXPECT_EQ(stock, pm.getAll());
}

TEST(ProductManager, has_product){
    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);
    std::set<Product*, ProductSmaller> stock;
    stock.insert(&meatCake);
    ProductManager pm(stock);

    EXPECT_TRUE(pm.has(&meatCake));
    EXPECT_FALSE(pm.has(&hugeBread));
}

TEST(ProductManager, get_product_by_position){
    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);

    std::set<Product*, ProductSmaller> stock;
    stock.insert(&meatCake);
    stock.insert(&hugeBread);
    ProductManager pm(stock);

    unsigned position = 0;
    EXPECT_EQ(&meatCake, pm.get(position));
    EXPECT_EQ(&hugeBread, pm.get(++position));

    EXPECT_THROW(pm.get(++position), InvalidProductPosition);
}

TEST(ProductManager, add_bread) {
    ProductManager pm;

    EXPECT_EQ(0, pm.getAll().size());

    Bread hugeBread("Pao de sementes", 0.2, false);
    pm.addBread("Pao de sementes", 0.2, false);

    EXPECT_EQ(1, pm.getAll().size());
    EXPECT_EQ("Pao de sementes", (*pm.getAll().begin())->getName());
    EXPECT_FLOAT_EQ(0.2, (*pm.getAll().begin())->getPrice());
}

TEST(ProductManager, add_cake){
    ProductManager pm;

    EXPECT_EQ(0, pm.getAll().size());

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    pm.addCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);

    EXPECT_EQ(1, pm.getAll().size());
    EXPECT_EQ("Bolo com molho de carne", (*pm.getAll().begin())->getName());
    EXPECT_FLOAT_EQ(1, (*pm.getAll().begin())->getPrice());
}

TEST(ProductManager, remove_product){
    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);

    std::set<Product*, ProductSmaller> stock;
    stock.insert(&meatCake);
    stock.insert(&hugeBread);
    ProductManager pm(stock);

    EXPECT_EQ(2, pm.getAll().size());

    pm.remove(&hugeBread);

    EXPECT_EQ(1, pm.getAll().size());
    EXPECT_EQ("Bolo com molho de carne", (*pm.getAll().begin())->getName());
    EXPECT_FLOAT_EQ(1, (*pm.getAll().begin())->getPrice());

    pm.remove(&meatCake);

    EXPECT_EQ(0, pm.getAll().size());

    EXPECT_THROW(pm.remove(&meatCake), ProductDoesNotExist);
}




