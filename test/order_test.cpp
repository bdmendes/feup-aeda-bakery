//
// Created by bdmendes on 19/10/20.
//

#include <gtest/gtest.h>

#include "model/order/order.h"
#include "model/product/product.h"
#include "model/person/client/client.h"
#include "model/person/worker/worker.h"

using testing::Eq;

TEST(Order, create_order){
    Client client("Alfredo Simões");
    Worker worker("Beatriz Silva",950);
    Date date(14, 11, 2020, 16, 30);
    Order order(client,worker, date);

    EXPECT_EQ(client, order.getClient());
    EXPECT_EQ(worker, order.getWorker());
    EXPECT_EQ(date, order.getRequestDate());
    EXPECT_FALSE(order.hasDiscount());
    EXPECT_FALSE(order.wasDelivered());
}

TEST(Order, add_product){
    Client client("Alfredo Simões");
    Worker worker("Beatriz Silva",950);
    Order order(client,worker);

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);
    order.addProduct(&meatCake, 5);
    order.addProduct(&hugeBread, 3);

    std::map<Product*, unsigned int, ProductSmaller> orderProducts;
    orderProducts[&meatCake] = 5;
    orderProducts[&hugeBread] = 3;

    EXPECT_EQ(2, order.getProducts().size());
    EXPECT_EQ(orderProducts, order.getProducts());
    EXPECT_FLOAT_EQ(5.6, order.getTotal());

    order.addProduct(&meatCake);
    orderProducts[&meatCake]++;

    EXPECT_EQ(2, order.getProducts().size());
    EXPECT_EQ(orderProducts, order.getProducts());
    EXPECT_FLOAT_EQ(6.6,order.getTotal());

    Cake chocolateCake("Bolo de chocolate", 0.8, CakeCategory::SPONGE);
    order.addProduct(&chocolateCake, 5);
    orderProducts[&chocolateCake] = 5;

    EXPECT_EQ(3, order.getProducts().size());
    EXPECT_EQ(orderProducts, order.getProducts());
    EXPECT_FLOAT_EQ(10.6, order.getTotal());

    Bread barleyBread("Pao de cevada", 0.4, false);
    order.deliver(4.3);

    EXPECT_THROW(order.addProduct(&barleyBread), OrderWasAlreadyDelivered);
}

TEST(Order, remove_product_quantity_by_pointer){
    Client client("Alfredo Simões");
    Worker worker("Beatriz Silva",950);
    Order order(client,worker);

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Cake chocolateCake("Bolo de chocolate", 0.8, CakeCategory::SPONGE);
    Bread hugeBread("Pao de sementes",0.2,false);
    Bread barleyBread("Pao de cevada", 0.4, false);
    order.addProduct(&meatCake, 5);
    order.addProduct(&chocolateCake, 7);
    order.addProduct(&hugeBread, 3);

    order.removeProduct(&meatCake, 3);
    std::map<Product*, unsigned int, ProductSmaller> orderProducts;
    orderProducts[&meatCake] = 2;
    orderProducts[&chocolateCake] = 7;
    orderProducts[&hugeBread] = 3;

    EXPECT_EQ(3, order.getProducts().size());
    EXPECT_EQ(orderProducts, order.getProducts());
    EXPECT_FLOAT_EQ(8.2, order.getTotal());

    order.removeProduct(&chocolateCake, 7);
    orderProducts.erase(&chocolateCake);

    EXPECT_EQ(2, order.getProducts().size());
    EXPECT_EQ(orderProducts, order.getProducts());
    EXPECT_FLOAT_EQ(2.6, order.getTotal());

    EXPECT_THROW(order.removeProduct(&barleyBread), ProductDoesNotExist);
}

TEST(Order, remove_product_by_pointer){
    Client client("Alfredo Simões");
    Worker worker("Beatriz Silva",950);
    Order order(client,worker);

    Bread hugeBread("Pao de sementes",0.2,false);
    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Cake chocolateCake("Bolo de chocolate", 0.8, CakeCategory::SPONGE);

    order.addProduct(&meatCake, 5);
    order.addProduct(&hugeBread, 3);

    order.removeProduct(&meatCake);
    std::map<Product*, unsigned int, ProductSmaller> orderProducts;
    orderProducts[&hugeBread] = 3;

    EXPECT_EQ(1, order.getProducts().size());
    EXPECT_EQ(orderProducts, order.getProducts());
    EXPECT_FLOAT_EQ(0.6, order.getTotal());

    EXPECT_THROW(order.removeProduct(&chocolateCake), ProductDoesNotExist);
}

TEST(Order, remove_product_quantity_by_position){
    Client client("Alfredo Simões");
    Worker worker("Beatriz Silva",950);
    Order order(client,worker);

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Cake chocolateCake("Bolo de chocolate", 0.8, CakeCategory::SPONGE);
    Bread hugeBread("Pao de sementes",0.2,false);
    Bread barleyBread("Pao de cevada", 0.4, false);
    order.addProduct(&meatCake, 5);
    order.addProduct(&chocolateCake, 7);
    order.addProduct(&hugeBread, 3);

    order.removeProduct(1, 3);
    std::map<Product*, unsigned int, ProductSmaller> orderProducts;
    orderProducts[&meatCake] = 5;
    orderProducts[&chocolateCake] = 4;
    orderProducts[&hugeBread] = 3;

    EXPECT_EQ(3, order.getProducts().size());
    EXPECT_EQ(orderProducts, order.getProducts());
    EXPECT_FLOAT_EQ(8.8, order.getTotal());

    order.removeProduct(2, 3);
    orderProducts.erase(&hugeBread);

    EXPECT_EQ(2, order.getProducts().size());
    EXPECT_EQ(orderProducts, order.getProducts());
    EXPECT_FLOAT_EQ(8.2, order.getTotal());

    EXPECT_THROW(order.removeProduct(2), InvalidProductPosition);
}

TEST(Order, remove_product_by_position){
    Client client("Alfredo Simões");
    Worker worker("Beatriz Silva",950);
    Order order(client,worker);

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Cake chocolateCake("Bolo de chocolate", 0.8, CakeCategory::SPONGE);
    Bread hugeBread("Pao de sementes",0.2,false);
    Bread barleyBread("Pao de cevada", 0.4, false);
    order.addProduct(&meatCake, 5);
    order.addProduct(&chocolateCake, 7);
    order.addProduct(&hugeBread, 3);

    unsigned position = 2;
    order.removeProduct(position);
    std::map<Product*, unsigned int, ProductSmaller> orderProducts;
    orderProducts[&meatCake] = 5;
    orderProducts[&chocolateCake] = 7;

    EXPECT_EQ(2, order.getProducts().size());
    EXPECT_EQ(orderProducts, order.getProducts());
    EXPECT_FLOAT_EQ(10.6, order.getTotal());

    position = 0;
    order.removeProduct(position);
    orderProducts.erase(&meatCake);

    EXPECT_EQ(1, order.getProducts().size());
    EXPECT_EQ(orderProducts, order.getProducts());
    EXPECT_FLOAT_EQ(5.6, order.getTotal());

    EXPECT_THROW(order.removeProduct(1), InvalidProductPosition);
}

TEST(Order, deliver){
    Date date(14, 11, 2020, 16, 30);
    Client client("Alfredo Simões");
    client.addPoints(200);
    Worker worker("Beatriz Silva",950);
    Order order1(client,worker, date);

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);
    order1.addProduct(&meatCake, 5);
    order1.addProduct(&hugeBread, 3);

    EXPECT_FALSE(order1.wasDelivered());

    order1.deliver(3.4, 20);
    date.addMinutes(20);

    EXPECT_TRUE(order1.wasDelivered());
    EXPECT_EQ(date, order1.getDeliverDate());
    EXPECT_EQ(50, client.getPoints()); // Resets points after delivering and adds 10 for each euro
    EXPECT_FLOAT_EQ(3.4, order1.getClientEvaluation());

    client.setPremium(true);
    client.resetPoints();
    client.addPoints(100);
    Order order2(client, worker);

    EXPECT_FALSE(order2.wasDelivered());

    order2.deliver(4.1);

    EXPECT_TRUE(order2.wasDelivered());
    EXPECT_EQ(0, client.getPoints());
    EXPECT_FLOAT_EQ(4.1, order2.getClientEvaluation());

    EXPECT_THROW(order2.deliver(2.3), OrderWasAlreadyDelivered);

    Order order3(client, worker);

    EXPECT_THROW(order3.deliver(5.3), InvalidOrderEvaluation);
}

TEST(Order,evaluations){
    Client client("Alfredo Simões",true);
    Worker worker("Beatriz Silva",950);

    Order order1(client,worker);
    Order order2(client,worker);

    EXPECT_THROW(order1.getClientEvaluation(),OrderWasNotDeliveredYet);

    order1.deliver(2);
    order2.deliver(4);

    EXPECT_FLOAT_EQ(order1.getClientEvaluation(),2);
    EXPECT_FLOAT_EQ(client.getMeanEvaluation(),3);
}

TEST(Order, get_final_price){
    Client client("Alfredo Simões", true);
    client.addPoints(100);
    Worker worker("Beatriz Silva",950);
    Order order(client,worker);

    Cake meatCake("Bolo com molho de carne", 1.20);
    Bread hugeBread("Pao grande de cementes",0.2);

    std::map<Product*, unsigned int, ProductSmaller> orderProducts;
    orderProducts[&meatCake] = 2;
    orderProducts[&hugeBread] = 3;

    order.addProduct(&meatCake,2);
    order.addProduct(&hugeBread,3);

    EXPECT_TRUE(order.hasDiscount());
    EXPECT_FLOAT_EQ(0.95*(2*1.20+3*0.2), order.getFinalPrice());

    client.setPremium(false);

    EXPECT_FALSE(order.hasDiscount());
    EXPECT_FLOAT_EQ(order.getFinalPrice(),1*(2*1.20+3*0.2));

    client.addPoints(100); //Client has now 200 points

    EXPECT_FLOAT_EQ(order.getFinalPrice(),0.98*(2*1.20+3*0.2));

    client.setPremium(true);

    EXPECT_TRUE(order.hasDiscount());
    EXPECT_FLOAT_EQ(order.getFinalPrice(),0.95*(2*1.20+3*0.2));
    EXPECT_FALSE(client.getPoints() == 0); // only after delivering!
}

TEST(Order, equal_orders){
    Client client1("Alfredo Simões");
    Client client2("Anotónio Pedroso");
    Worker worker("Beatriz Silva",950);

    Order order1(client1,worker);
    Order order2(client1, worker);
    Order order3(client1, worker);
    Order order4(client2, worker);

    EXPECT_TRUE(order1 == order2);

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    order1.addProduct(&meatCake, 5);

    EXPECT_FALSE(order1 == order2);

    order2.addProduct(&meatCake, 5);

    EXPECT_TRUE(order1 == order2);
    EXPECT_FALSE(order1 == order3);
    EXPECT_FALSE(order2 == order3);
    EXPECT_FALSE(order1 == order4);
    EXPECT_FALSE(order2 == order4);
    EXPECT_FALSE(order3 == order4);

    order2.deliver(4.3);

    EXPECT_FALSE(order1 == order2);
}

TEST(Order, sort_orders){
    Client client("Alfredo Simões");
    Worker worker("Beatriz Silva",950);
    Date date1(13, 11, 2020, 16, 30);
    Date date2(14, 11, 2020, 16, 30);
    Date date3(14, 11, 2020, 16, 31);
    Order order1(client, worker, date1);
    Order order2(client, worker, date2);
    Order order3(client, worker, date3);

    EXPECT_TRUE(order1 < order2);
    EXPECT_TRUE(order1 < order3);
    EXPECT_TRUE(order2 < order3);

}

