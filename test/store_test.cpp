//
// Created by bdmendes on 27/10/20.
//

#include <gtest/gtest.h>
#include "model/store/store.h"
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


