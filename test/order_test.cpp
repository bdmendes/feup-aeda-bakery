//
// Created by bdmendes on 19/10/20.
//

#include <gtest/gtest.h>

#include "model/person/person/person.h"
#include "model/order/order.h"
#include "model/product/product.h"
#include "model/person/client/client.h"
#include "model/person/worker/worker.h"

using testing::Eq;

TEST(Order, create_order){
    Client client("Alfredo");
    Worker worker("Beatriz",950);

    Cake meatCake("Bolo com molho de carne", 1.20, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao grande de cementes",0.2,false);
    std::vector<Product*> elements;
    elements.push_back(&meatCake);
    elements.push_back(&hugeBread);

    Order order(client,worker);
    order.addProduct(&meatCake,2);
    order.addProduct(&hugeBread,3);
    EXPECT_FLOAT_EQ(order.getFinalPrice(),2*1.20+3*0.2);
    EXPECT_EQ(order.getClient(),client);
    EXPECT_EQ(order.getWorker(),worker);
}

TEST(Order,create_order_premium_discount){
    Client client("Alfredo",true);
    client.addPoints(100);
    Worker worker("Beatriz",950);

    Cake meatCake("Bolo com molho de carne", 1.20);
    Bread hugeBread("Pao grande de cementes",0.2);

    std::vector<Product*> elements;
    elements.push_back(&meatCake);
    elements.push_back(&hugeBread);

    Order order(client,worker);
    order.addProduct(&meatCake,2);
    order.addProduct(&hugeBread,3);
    EXPECT_TRUE(order.hasDiscount());
    EXPECT_FLOAT_EQ(order.getFinalPrice(),0.95*(2*1.20+3*0.2));
    client.setPremium(false);
    EXPECT_FLOAT_EQ(order.getFinalPrice(),1*(2*1.20+3*0.2));
    client.addPoints(100);
    EXPECT_FLOAT_EQ(order.getFinalPrice(),0.98*(2*1.20+3*0.2));
    client.setPremium(true);
    EXPECT_FLOAT_EQ(order.getFinalPrice(),0.95*(2*1.20+3*0.2));
    EXPECT_FALSE(client.getPoints() == 0); // only after delivering!
}

TEST(Order,add_products){

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao grande de cementes",0.2,false);

    Client client("Alfredo",true);
    Worker worker("Beatriz",950);

    std::vector<Product*> elements;
    elements.push_back(&meatCake);
    elements.push_back(&hugeBread);

    Order order(client,worker);
    order.addProduct(&meatCake,5);
    order.addProduct(&hugeBread, 3);

    std::map<Product*,unsigned> elements2;
    elements2[&meatCake] = 5;
    elements2[&hugeBread] = 3;

    EXPECT_EQ(order.getProducts(),elements2);
    EXPECT_FLOAT_EQ(order.getTotal(),5.6);
    order.addProduct(&meatCake);
    EXPECT_FLOAT_EQ(order.getTotal(),6.6);
    EXPECT_EQ(order.getProducts()[&meatCake],6);
}

/*

TEST(Order,remove_products){

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao grande de cementes",0.2,false);
    Bread hugeBread2("Pao grande de centeio",0.2,false);

    Client client("Alfredo",true);
    Worker worker("Beatriz",950);

    Order order(client,worker);
    order.addProduct(&meatCake,5);
    order.addProduct(&hugeBread, 3);
    EXPECT_FLOAT_EQ(order.getTotal(),5.6);
    order.removeProduct(&hugeBread,1);
    EXPECT_FLOAT_EQ(order.getTotal(),5.4);

    EXPECT_EQ(order.getProducts()[&hugeBread],2);
    order.removeProduct(&hugeBread);
    EXPECT_FALSE(order.hasProduct((&hugeBread)));
    EXPECT_THROW(order.removeProduct(&hugeBread2),ProductDoesNotExist);
}

TEST(Order,deliver_noreset){
    Cake meatCake("Bolo com molho de carne", 1);
    Bread hugeBread("Pao grande de cementes",0.1);
    Client client("Alfredo",true);
    Worker worker("Beatriz",950);

    Order order(client,worker);
    EXPECT_EQ(client.getPoints(),0);

    order.addProduct(&meatCake,8);
    order.addProduct(&hugeBread, 10);
    EXPECT_EQ(client.getPoints(),0);

    EXPECT_THROW(order.deliver(7),InvalidOrderEvaluation);
    order.deliver(4);
    EXPECT_EQ(client.getPoints(),90);
    EXPECT_THROW(order.deliver(3),OrderWasAlreadyDelivered);
    EXPECT_THROW(order.addProduct(&meatCake),OrderWasAlreadyDelivered);
    EXPECT_THROW(order.removeProduct(&meatCake),OrderWasAlreadyDelivered);
}

TEST(Order,deliver_reset){
    Cake meatCake("Bolo com molho de carne", 1);
    Bread hugeBread("Pao grande de cementes",0.1);
    Client client("Alfredo",true);
    Worker worker("Beatriz",950);

    Order order(client,worker);
    EXPECT_EQ(client.getPoints(),0);
    order.addProduct(&meatCake,10);
    EXPECT_EQ(client.getPoints(),0);
    EXPECT_FALSE(order.hasDiscount());
    order.deliver(4);
    EXPECT_EQ(client.getPoints(),100); // points accumulate after deliver; will reset next order

    Order order2(client,worker);
    order2.addProduct(&meatCake,1);
    EXPECT_TRUE(order.hasDiscount());
    order2.deliver(2);
    EXPECT_EQ(client.getPoints(),10);
}

TEST(Order,evaluations){
    Client client("Alfredo",true);
    Worker worker("Beatriz",950);

    Order order1(client,worker);
    Order order2(client,worker);
    EXPECT_THROW(order1.getClientEvaluation(),OrderWasNotDeliveredYet);
    order1.deliver(2);
    order2.deliver(4);
    EXPECT_FLOAT_EQ(order1.getClientEvaluation(),2);
    EXPECT_FLOAT_EQ(client.getMeanEvaluation(),3);
}

 */