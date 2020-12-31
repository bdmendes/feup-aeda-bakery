
#include <gtest/gtest.h>
#include "model/product/product.h"

#include <iostream>

using testing::Eq;

TEST(Bread, create_bread){
    Bread bread1("Pao de cereais", 0.7);

    EXPECT_EQ("Pao de cereais", bread1.getName());
    EXPECT_FLOAT_EQ(0.7, bread1.getPrice());
    EXPECT_TRUE(bread1.isSmall());

    Bread bread2("Pao da avo", 0.9, false);

    EXPECT_EQ("Pao da avo", bread2.getName());
    EXPECT_FLOAT_EQ( 0.9, bread2.getPrice());
    EXPECT_FALSE(bread2.isSmall());
}

TEST(Cake, create_cake){
    Cake cake1("Pao de lo", 17.30);

    EXPECT_EQ("Pao de lo", cake1.getName());
    EXPECT_FLOAT_EQ(17.30, cake1.getPrice());
    EXPECT_EQ("General", cake1.getCategory());

    Cake cake2("Bolinho fofinho", 22.30, CakeCategory::PIE);

    EXPECT_EQ("Bolinho fofinho", cake2.getName());
    EXPECT_FLOAT_EQ(22.30,cake2.getPrice());
    EXPECT_EQ("Pie" ,cake2.getCategory());
}

TEST(Product, less_than_operator){
    Bread bread1("Pao de alfarroba", 0.6);
    Bread bread2("Pao de agua", 0.45);
    Cake cake1("Bolo de amendoa", 1.2);
    Cake cake2("Bolo de arroz", 1);

    EXPECT_TRUE(cake1 < bread1);
    EXPECT_TRUE(cake1 < bread2);
    EXPECT_TRUE(cake2 < bread1);
    EXPECT_TRUE(cake2 < bread2);
}

TEST(Bread, less_than_operator){
    Bread bread1("Pao de agua", 0.45);
    Bread bread2("Pao de alfarroba", 0.6);
    Bread bread3("Pao normal", 0.1);

    EXPECT_TRUE(bread1 < bread2);
    EXPECT_TRUE(bread1 < bread3);
    EXPECT_TRUE(bread2 < bread3);
}

TEST(Bread, equality_operator){
    Bread bread1("Pao de sementes", 0.8);
    Bread bread2("Pao de sementes", 0.8);
    Bread bread3("Pao de sementes", 0.8, false);

    EXPECT_TRUE(bread1==bread2);
    EXPECT_FALSE(bread1==bread3);
    EXPECT_FALSE(bread2==bread3);
}

TEST(Cake, less_than_operator){
    Cake cake1("Bolo de amendoa", 1.2);
    Cake cake2("Bolo de arroz", 1);
    Cake cake3("Bolo de chocolate", 0.9);

    EXPECT_TRUE(cake1 < cake2);
    EXPECT_TRUE(cake1 < cake3);
    EXPECT_TRUE(cake2 < cake3);
}

TEST(Cake, equality_operator){
    Cake cake1("Tarte de bolacha", 13.2);
    Cake cake2("Tarte de bolacha", 13.2);
    Cake cake3("Tarte de bolacha", 13.2, CakeCategory::CRUNCHY);

    EXPECT_TRUE(cake1==cake2);
    EXPECT_FALSE(cake1==cake3);
    EXPECT_FALSE(cake2==cake3);
}

