
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

/*TEST(Order, less_than_operator){
    Client client("Alfredo Simoes");
    Worker worker("Head Office", "Beatriz Silva",950);
    std::string location = "Matosinhos";
    Date date1(13, 11, 2020, 16, 30);
    Date date2(14, 11, 2020, 16, 30);
    Date date3(14, 11, 2020, 16, 31);
    Order order1(client, worker, location, date1);
    Order order2(client, worker, location, date2);
    Order order3(client, worker, location, date3);

    EXPECT_TRUE(order2 < order1);
    EXPECT_TRUE(order1 < order3);
    EXPECT_TRUE(order2 < order3);
}*/
