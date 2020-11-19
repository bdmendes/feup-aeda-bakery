
#include <gtest/gtest.h>
#include "model/order/order.h"
#include "model/product/product.h"
#include "model/person/client/client.h"
#include "model/person/worker/worker.h"

using testing::Eq;

TEST(Order, create_order){
    Client client("Alfredo Simoes");
    Worker worker("Beatriz Silva",950);
    Date date(14, 11, 2020, 16, 30);
    Order order(client,worker, "Felgueiras", date);

    EXPECT_EQ(client, *order.getClient());
    EXPECT_EQ(worker, *order.getWorker());
    EXPECT_EQ(date, order.getRequestDate());
    EXPECT_FALSE(order.hasDiscount());
    EXPECT_FALSE(order.wasDelivered());
}

TEST(Order, has_discount){
    Client client1("Alfredo Simoes");
    Client client2("Alfredo Simoes");
    Client client3("Carlos Monteiro", 1238471736, true);
    Client client4("Carlos Monteiro", 1238471736, true);
    Worker worker("Beatriz Silva",950);
    Date date(14, 11, 2020, 16, 30);
    std::string location = "Porto";

    Order order1(client1,worker, location, date); client1.setPoints(200);
    Order order2(client2, worker, location, date);
    Order order3(client3, worker, location, date); client3.setPoints(100);
    Order order4(client4, worker, location, date);

    EXPECT_TRUE(order1.hasDiscount());
    EXPECT_FALSE(order2.hasDiscount());
    EXPECT_TRUE(order3.hasDiscount());
    EXPECT_FALSE(order4.hasDiscount());
    EXPECT_EQ(order1.getDeliverLocation(), "Porto");
}

TEST(Order, has_product){
    Cake cake1("Pao de lo", 3.20);
    Cake cake2("Bolo de chocolate", 1.20);
    Bread bread1("Pao de sementes", 0.8);
    Bread bread2("Pao simples", 0.2);
    Client client("Alfredo Simoes");
    Worker worker("Beatriz Silva",950);

    Order order(client,worker);
    order.addProduct(&cake1, 10);
    order.addProduct(&bread1, 8);

    EXPECT_TRUE(order.hasProduct(&cake1));
    EXPECT_FALSE(order.hasProduct(&cake2));
    EXPECT_TRUE(order.hasProduct(&bread1));
    EXPECT_FALSE(order.hasProduct(&bread2));
}

TEST(Order, was_delivered){
    Client client1("Alfredo Simoes");
    Client client2("Carlos Monteiro");
    Worker worker("Beatriz Silva",950);
    Order order1(client1, worker); order1.deliver(2);
    Order order2(client2, worker);

    EXPECT_TRUE(order1.wasDelivered());
    EXPECT_FALSE(order2.wasDelivered());
}

TEST(Order, get_client_evaluation){
    Client client("Alfredo Simoes",true);
    Worker worker("Beatriz Silva",950);

    Order order1(client,worker);
    Order order2(client,worker);

    EXPECT_THROW(order1.getClientEvaluation(),OrderWasNotDeliveredYet);

    order1.deliver(2);
    order2.deliver(4);

    EXPECT_FLOAT_EQ(order1.getClientEvaluation(),2);
}

TEST(Order, get_final_price){
    Client client("Alfredo Simoes", 5959,true);
    client.addPoints(100);
    Worker worker("Beatriz Silva",69696,950);
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

TEST(Order, get_total){
    Cake cake1("Pao de lo", 3.20);
    Cake cake2("Bolo de chocolate", 1.20);
    Bread bread1("Pao de sementes", 0.8);
    Bread bread2("Pao simples", 0.2);
    Client client("Alfredo Simoes");
    Worker worker("Beatriz Silva",950);
    Order order(client,worker);


    EXPECT_FLOAT_EQ(0, order.getTotal());

    order.addProduct(&cake1, 10);

    EXPECT_FLOAT_EQ(3.20*10, order.getTotal());

    order.addProduct(&cake2, 15);

    EXPECT_FLOAT_EQ((3.20*10)+(1.20*15), order.getTotal());

    order.addProduct(&bread1, 8);

    EXPECT_FLOAT_EQ((3.20*10)+(1.20*15)+(0.8*8), order.getTotal());

    order.addProduct(&bread2, 3);

    EXPECT_FLOAT_EQ((3.20*10)+(1.20*15)+(0.8*8)+(0.2*3), order.getTotal());
}

TEST(Order, add_product){
    Client client("Alfredo Simoes");
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

TEST(Order, remove_product_by_pointer){
    Client client("Alfredo Simoes");
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
    Order order1(client,worker, "Penafiel", date);

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);
    order1.addProduct(&meatCake, 5);
    order1.addProduct(&hugeBread, 3);

    EXPECT_FALSE(order1.wasDelivered());

    order1.deliver(3, 20);
    date.addMinutes(20);

    EXPECT_TRUE(order1.wasDelivered());
    EXPECT_EQ(date, order1.getDeliverDate());
    EXPECT_EQ(50, client.getPoints()); // Resets points after delivering and adds 10 for each euro
    EXPECT_EQ(3, order1.getClientEvaluation());

    client.setPremium(true);
    client.resetPoints();
    client.addPoints(100);
    Order order2(client, worker);

    EXPECT_FALSE(order2.wasDelivered());

    order2.deliver(4);

    EXPECT_TRUE(order2.wasDelivered());
    EXPECT_EQ(0, client.getPoints());
    EXPECT_EQ(4, order2.getClientEvaluation());
    EXPECT_THROW(order2.deliver(2), OrderWasAlreadyDelivered);

    Order order3(client, worker);

    EXPECT_THROW(order3.deliver(6), InvalidOrderEvaluation);
}

TEST(Order, equal_operator){
    Client client1("Alfredo Simoes");
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

TEST(Order, less_than_operator){
    Client client("Alfredo Simoes");
    Worker worker("Beatriz Silva",950);
    Date date1(13, 11, 2020, 16, 30);
    Date date2(14, 11, 2020, 16, 30);
    Date date3(14, 11, 2020, 16, 31);
    Order order1(client, worker, "Porto", date1);
    Order order2(client, worker, "Funchal", date2);
    Order order3(client, worker, "Vila do Conde", date3);

    EXPECT_TRUE(order1 < order2);
    EXPECT_TRUE(order1 < order3);
    EXPECT_TRUE(order2 < order3);
}

TEST(Order, print){
}