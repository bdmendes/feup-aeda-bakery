//
// Created by Filipa on 10/25/2020.
//

#include <gtest/gtest.h>
#include <model/Person.h>
#include <model/Store.h>
#include <model/Order.h>
#include <model/Product.h>


using testing::Eq;

TEST(client, create_cliet){
    Client c1("Ana", 234567839, 0);
    EXPECT_EQ("Ana", c1.getName());
}