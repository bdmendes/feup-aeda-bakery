//
// Created by bdmendes on 19/10/20.
//

#include <gtest/gtest.h>
#include <Person.h>
#include <Store.h>
#include <Order.h>
#include <Product.h>


using testing::Eq;

/*TEST(order, order_default_test){
    Person p("Alfredo",123,{"alfredo", "martins"});
    EXPECT_EQ(p.getCredential().password, "martins");
}*/

TEST(Client, create_client){
    Client c("Manel", 256789324, true);
    EXPECT_EQ(c.getName(), "Manel");
    EXPECT_EQ(c.getTributaryNumber(), 256789324);
    EXPECT_EQ(c.isPremium(), true);
}

TEST(Worker, create_worker){
    Worker w("Joao", 203574345, 600);
    EXPECT_EQ(w.getName(), "Joao");
    EXPECT_EQ(w.getTributaryNumber(), 203574345);
}

TEST(Boss, create_boss){
    Boss b("Marcelo Rebelo de Sousa", 294839201, 10000);
    EXPECT_EQ(b.getName(),"Marcelo Rebelo de Sousa");
    EXPECT_EQ(b.getTributaryNumber(), 294839201);
}

/*TEST(Products, creat_products){
    Product meatCake("Bolo com molho de carne", 1.20);
    EXPECT_EQ(meatCake.getName(), "Bolo com molho de carne");
    EXPECT_EQ(meatCake.getPrice(), 1.20);
}*/

TEST(Store, create_store){
    Boss b("Marcelo Rebelo de Sousa", 294839201, 10000);
    Store s("Barcelos", b);
    EXPECT_EQ(s.getLocation(),"Barcelos");
}

/*TEST(Order, create_order){
    Client c("Manel", 256789324, true);
    Worker w("Joao", 203574345, 600);
    Product meatCake("Bolo com molho de carne", 1.20);
    Product hugeBread("aquele pão gostoso", 0.15);
    std::map<Product, unsigned int> products;
    products.insert(std::pair<Product, unsigned int>(meatCake,2));
    products.insert(std::pair<Product, unsigned int>(hugeBread,3));
    Order o(products, c, w);
    EXPECT_EQ(o.getClient(), c);
    EXPECT_EQ(o.getWorker(), w);
    EXPECT_EQ(o.getTotalPrice(), 2.85);

}*/

