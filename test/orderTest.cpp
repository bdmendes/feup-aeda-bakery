//
// Created by bdmendes on 19/10/20.
//

#include <gtest/gtest.h>
#include <Person.h>

using testing::Eq;

TEST(order, order_default_test){
    Person p("Alfredo",123,{"alfredo", "martins"});
    EXPECT_EQ(p.getCredential().password, "martins");
}
