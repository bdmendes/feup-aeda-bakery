//
// Created by bdmendes on 27/10/20.
//

#include <gtest/gtest.h>
#include "../src/model/store.h"
#include <algorithm>
#include <map>

using testing::Eq;

TEST(Store, create_store){
    Store store1("Padaria Diamante");
    Store store2("Padaria Pão Quente");

    EXPECT_EQ(store1.getName(), "Padaria Diamante");
    EXPECT_EQ(store2.getName(), "Padaria Pão Quente");
}

TEST(Store, hire_worker){
    Store store("Padaria Diamante");

    Worker worker1("Maria João", 970, 253579503);
    Worker worker2("Rodrigo Soares", 890);
    Worker worker3("Manuel Faria", 900);

    store.hireWorker(&worker1);
    store.hireWorker(&worker2);
    store.hireWorker(&worker3);

    EXPECT_THROW(store.hireWorker(&worker1), PersonAlreadyExists);
    EXPECT_THROW(store.hireWorker(&worker2), PersonAlreadyExists);
}

TEST(Store, fire_worker){
    Store store("Padaria Pão Quente");

    Worker worker1("Maria João", 970, 253579503);
    Worker worker2("Rodrigo Soares", 890);
    Worker worker3("Manuel Faria", 900);
    Worker worker4("Juliana Fernandes", 960, 567432890);

    EXPECT_THROW(store.fireWorker(&worker1), StoreHasNoWorkers);

    store.hireWorker(&worker1);
    store.hireWorker(&worker2);

    EXPECT_THROW(store.fireWorker(&worker3), PersonDoesNotExist);
    EXPECT_THROW(store.fireWorker(&worker4), PersonDoesNotExist);
}

TEST(Store, has_worker){
    Store store("Padaria Pão Quente");

    Worker worker1("Mariana Simões", 970, 253579503);
    Worker worker2("Joana Faria", 890);
    Worker worker3("Miguel Gomes", 900, 289304093);
    Worker worker4("Júlio Domingos", 960);

    store.hireWorker(&worker1);
    store.hireWorker(&worker2);

    EXPECT_TRUE(store.hasWorker("Mariana Simões"));
    EXPECT_TRUE(store.hasWorker("Joana Faria"));
    EXPECT_TRUE(store.hasWorker(253579503));
    EXPECT_TRUE(store.hasWorker(&worker1));
    EXPECT_TRUE(store.hasWorker(&worker2));

    EXPECT_FALSE(store.hasWorker("Miguel Gomes"));
    EXPECT_FALSE(store.hasWorker("Júlio Domingos"));
    EXPECT_FALSE(store.hasWorker(289304093));
    EXPECT_FALSE(store.hasWorker(&worker3));
    EXPECT_FALSE(store.hasWorker(&worker4));
}

TEST(Store, has_client){
    Store store("Padaria Pão Quente");

    Client client1("João Martins");
    Client client2("Madalena Lopes", true, 289456094);
    Client client3("Luís Ferreira", false,289345874);

    Worker worker1("Margarida Azevedo",  830);
    Worker worker2("João Gomes", 990, 278917902);

    store.hireWorker(&worker1);
    store.hireWorker(&worker2);

    Bread cerealBread("Pão de cereais", 0.80, false);
    Cake chocolateCake("Bolo de Chocolate", 1.20, CakeCategory::CRUNCHY);

    std::map<Product*, unsigned int> breadProducts;
    breadProducts[&cerealBread] = 3;

    EXPECT_THROW(store.addOrder(breadProducts, client1),PersonDoesNotExist);
    store.addClient(&client1);
    store.addClient(&client2);
    store.addOrder(breadProducts, client1);

    std::map<Product*, unsigned int> cakeProducts;
    cakeProducts[&chocolateCake] = 2;
    store.addOrder(cakeProducts, client2);

    EXPECT_TRUE(store.hasClient("João Martins"));
    EXPECT_TRUE(store.hasClient(&client1));
    EXPECT_TRUE(store.hasClient("Madalena Lopes"));
    EXPECT_TRUE(store.hasClient(289456094));
    EXPECT_TRUE(store.hasClient(&client2));

    EXPECT_FALSE(store.hasClient("Luís Ferreira"));
    EXPECT_FALSE(store.hasClient(278917902));
    EXPECT_FALSE(store.hasClient(&client3));
}

TEST(Store, change_worker_salary){
    Store store("Pão Quente");
    Worker worker1("João Miguel", 950, 267892019);
    store.hireWorker(&worker1);

    store.changeWorkerSalary(&worker1, 900);
    EXPECT_FLOAT_EQ(worker1.getSalary(), 900);

    store.changeWorkerSalary(&worker1, 970);
    EXPECT_FLOAT_EQ(worker1.getSalary(), 970);
}

TEST(Store, add_product){
    Store store("Pão Quente");

    Bread cerealBread("Pão de cereais", 0.80, false);
    Cake chocolateCake("Bolo de Chocolate", 1.20, CakeCategory::CRUNCHY);

    store.addProduct(&cerealBread);
    store.addProduct(&chocolateCake);

    EXPECT_THROW(store.addProduct(&cerealBread), ProductAlreadyExists);
    EXPECT_THROW(store.addProduct(&chocolateCake), ProductAlreadyExists);
}

TEST(Store, remove_product){
    Store store("Pão Quente");

    Bread cerealBread("Pão de cereais", 0.80, false);
    Cake chocolateCake("Bolo de Chocolate", 1.20, CakeCategory::CRUNCHY);
    Cake nutCake("Tarte de noz", 1.50, CakeCategory::PIE);

    store.addProduct(&cerealBread);
    store.addProduct(&chocolateCake);
    EXPECT_THROW(store.removeProduct(&nutCake), ProductDoesNotExist);
    store.removeProduct(&cerealBread);
    EXPECT_THROW(store.removeProduct(&cerealBread), ProductDoesNotExist);
    store.removeProduct(&chocolateCake);
    EXPECT_THROW(store.removeProduct(&nutCake), ProductDoesNotExist);
}

TEST(Store, get_mean_evaluation){
    Store store("Padaria Pão Quente");

    Client client1("João Martins");
    Client client2("Madalena Lopes", true, 289456094);
    Client client3("Luís Ferreira", false,289345874);

    Worker worker1("Margarida Azevedo",  830);
    store.hireWorker(&worker1);

    Bread cerealBread("Pão de cereais", 0.80, false);
    Cake chocolateCake("Bolo de Chocolate", 1.20, CakeCategory::CRUNCHY);

    std::map<Product*, unsigned int> products;
    products[&cerealBread] = 3;
    products[&chocolateCake] = 2;

    store.addClient(&client1);
    store.addClient(&client2);
    store.addClient(&client3);
    store.addOrder(products, client1);
    store.addOrder(products, client2);
    store.addOrder(products, client3);

    (store.getClientOrders(client1))[0]->deliver(3.6);
    EXPECT_FLOAT_EQ(3.6, store.getMeanEvaluation());
    (store.getClientOrders(client2))[0]->deliver(4.8);
    EXPECT_FLOAT_EQ((3.6+4.8)/2, store.getMeanEvaluation());
    (store.getClientOrders(client3))[0]->deliver(4.2);
    EXPECT_FLOAT_EQ((3.6+4.8+4.2)/3, store.getMeanEvaluation());
}






