
#include <gtest/gtest.h>
#include "model/order/order.h"
#include "model/product/product.h"
#include "model/person/client/client.h"
#include "model/person/worker/worker.h"

using testing::Eq;

TEST(Order, create_order){
    Client client("Alfredo Simoes");
    Worker worker("Beatriz Silva",950);
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
    Worker worker("Beatriz Silva",950);
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

TEST(Order, get_worker){
    Client client1("Alfredo Simoes");
    Worker worker1("Beatriz Silva",950);
    Order order1(client1, worker1);

    EXPECT_EQ(worker1, *order1.getWorker());

    Client client2("Carlos Monteiro");
    Worker worker2("Joana Figueiredo", 839);
    Order order2(client2, worker2);

    EXPECT_EQ(worker2, *order2.getWorker());
}

TEST(Order, get_client){
    Client client1("Alfredo Simoes");
    Worker worker1("Beatriz Silva",950);
    Order order1(client1, worker1);

    EXPECT_EQ(client1, *order1.getClient());

    Client client2("Carlos Monteiro");
    Worker worker2("Joana Figueiredo", 839);
    Order order2(client2, worker2);

    EXPECT_EQ(client2  , *order2.getClient());
}

TEST(Order, get_deliver_location){
    Client client1("Alfredo Simoes");
    Worker worker1("Beatriz Silva",950);
    Order order1(client1, worker1, "Matosinhos");

    EXPECT_EQ("Matosinhos", order1.getDeliverLocation());

    Client client2("Carlos Monteiro");
    Worker worker2("Joana Figueiredo", 839);
    Order order2(client2, worker2, "Vila do Conde");

    EXPECT_EQ("Vila do Conde", order2.getDeliverLocation());
}

TEST(Order, set_deliver_location){
    Client client("Alfredo Simoes");
    Worker worker("Beatriz Silva",950);
    Order order(client, worker);

    EXPECT_EQ(Order::DEFAULT_LOCATION, order.getDeliverLocation());

    order.setDeliverLocation("Porto");

    EXPECT_EQ("Porto", order.getDeliverLocation());

    order.setDeliverLocation("Felgueiras");

    EXPECT_EQ("Felgueiras", order.getDeliverLocation());
}

TEST(Order, get_products){
    Cake cake("Bolo de bolacha", 2.2);
    Bread bread("Pao de cereais", 0.8);
    Client client("Alfredo Simoes");
    Worker worker("Beatriz Silva",950);
    Order order(client, worker);

    EXPECT_TRUE(order.getProducts().empty());

    Product* product1 = order.addProduct(&cake, 10);

    EXPECT_EQ(1, order.getProducts().size());
    EXPECT_EQ(*product1, *(order.getProducts().begin()->first));
    EXPECT_EQ(10, order.getProducts().begin()->second);

    Product* product2 = order.addProduct(&bread, 7);

    EXPECT_EQ(2, order.getProducts().size());
    EXPECT_EQ(*product2, *((++order.getProducts().begin())->first));
    EXPECT_EQ(7, (++order.getProducts().begin())->second);
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

TEST(Order, get_request_date){
    Client client1("Alfredo Simoes");
    Worker worker1("Beatriz Silva",950);
    Date date1(23, 7, 2020, 14, 50);
    Order order1(client1, worker1, "Matosinhos", date1);

    EXPECT_TRUE(date1 == order1.getRequestDate());

    Client client2("Carlos Monteiro");
    Worker worker2("Joana Figueiredo", 839);
    Date date2(19, 8, 2019, 22, 30);
    Order order2(client2, worker2, "Vila do Conde", date2);

    EXPECT_TRUE(date2 == order2.getRequestDate());
}

TEST(Order, get_deliver_date){
    Client client1("Alfredo Simoes");
    Worker worker1("Beatriz Silva",950);
    Date date1(23, 7, 2020, 14, 50);
    Order order1(client1, worker1, "Matosinhos", date1);
    order1.deliver(5);
    date1.addMinutes(30);

    EXPECT_TRUE(date1 == order1.getDeliverDate());

    Client client2("Carlos Monteiro");
    Worker worker2("Joana Figueiredo", 839);
    Date date2(19, 8, 2019, 22, 30);
    Order order2(client2, worker2, "Vila do Conde", date2);
    order2.deliver(5, true, 20);
    date2.addMinutes(20);

    EXPECT_TRUE(date2 == order2.getDeliverDate());
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
    order.deliver(4);

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
    std::string location = "Felgueiras";
    Date date(14, 11, 2020, 16, 30);
    Client client("Alfredo Simões");
    client.addPoints(200);
    Worker worker("Beatriz Silva",950);
    Order order1(client,worker, location, date);

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);
    order1.addProduct(&meatCake, 5);
    order1.addProduct(&hugeBread, 3);

    EXPECT_FALSE(order1.wasDelivered());

    order1.deliver(3, true,20);
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

TEST(Order, equality_operator){
//    Client client1("Alfredo Simoes");
//    Client client2("Anotónio Pedroso");
//    Worker worker("Beatriz Silva",950);
//
//    Order order1(client1,worker);
//    Order order2(client1, worker);
//    Order order3(client1, worker);
//    Order order4(client2, worker);
//
//    EXPECT_TRUE(order1 == order2);
//
//    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
//    order1.addProduct(&meatCake, 5);
//
//    EXPECT_FALSE(order1 == order2);
//
//    order2.addProduct(&meatCake, 5);
//
//    EXPECT_TRUE(order1 == order2);
//    EXPECT_FALSE(order1 == order3);
//    EXPECT_FALSE(order2 == order3);
//    EXPECT_FALSE(order1 == order4);
//    EXPECT_FALSE(order2 == order4);
//    EXPECT_FALSE(order3 == order4);
//
//    order2.deliver(4.3);
//
//    EXPECT_FALSE(order1 == order2);
}

TEST(Order, less_than_operator){
    Client client("Alfredo Simoes");
    Worker worker("Beatriz Silva",950);
    std::string location = "Matosinhos";
    Date date1(13, 11, 2020, 16, 30);
    Date date2(14, 11, 2020, 16, 30);
    Date date3(14, 11, 2020, 16, 31);
    Order order1(client, worker, location, date1);
    Order order2(client, worker, location, date2);
    Order order3(client, worker, location, date3);

    EXPECT_TRUE(order1 < order2);
    EXPECT_TRUE(order1 < order3);
    EXPECT_TRUE(order2 < order3);
}
