//
// Created by laimi on 22/10/2020.
//

#include <gtest/gtest.h>
#include "model/product/product.h"
#include <algorithm>

using testing::Eq;

TEST(Bread, create_bread){
    Bread b1("Pao de cereais", 0.7);

    EXPECT_EQ("Pao de cereais", b1.getName());
    EXPECT_FLOAT_EQ(0.7, b1.getPrice());
    EXPECT_TRUE(b1.isSmall());

    Bread b2("Pao da avo", 0.9, false);

    EXPECT_EQ("Pao da avo", b2.getName());
    EXPECT_FLOAT_EQ( 0.9, b2.getPrice());
    EXPECT_FALSE(b2.isSmall());
}

TEST(Cake, create_cake){
    Cake c1("Pao de lo", 17.30);

    EXPECT_EQ("Pao de lo", c1.getName());
    EXPECT_FLOAT_EQ(17.30, c1.getPrice());
    EXPECT_EQ(CakeCategory::GENERAL, c1.getCategory());

    Cake c2("Bolinho fofinho", 22.30, CakeCategory::PIE);

    EXPECT_EQ("Bolinho fofinho", c2.getName());
    EXPECT_FLOAT_EQ(22.30,c2.getPrice());
    EXPECT_EQ(CakeCategory::PIE,c2.getCategory());
}

TEST(Product, product_equal){
    Bread b1("Pao de sementes", 0.8);
    Bread b2("Pao de sementes", 0.8);
    Bread b3("Pao de alfarroba", 0.8);
    Bread b4("Pao de sementes", 1);

    EXPECT_TRUE(b1==b2);
    EXPECT_FALSE(b1==b3);
    EXPECT_FALSE(b1==b4);
    EXPECT_FALSE(b2==b3);
    EXPECT_FALSE(b2==b4);

    Cake c1("Tarte de bolacha", 13.2);
    Cake c2("Tarte de bolacha", 13.2);
    Cake c3("Tarte de fruta", 13.2);
    Cake c4("Tarte de bolacha", 14.5);

    EXPECT_TRUE(c1==c2);
    EXPECT_FALSE(c1==c3);
    EXPECT_FALSE(c1==c4);
    EXPECT_FALSE(c2==c3);
    EXPECT_FALSE(c2==c4);
}

TEST(Bread, bread_equal){
    Bread b1("Pao de sementes", 0.8);
    Bread b2("Pao de sementes", 0.8);
    Bread b3("Pao de sementes", 0.8, false);

    EXPECT_TRUE(b1==b2);
    EXPECT_FALSE(b1==b3);
    EXPECT_FALSE(b2==b3);
}

TEST(Cake, cake_equal){
    Cake c1("Bolo de chocolate", 15.60);
    Cake c2("Bolo de chocolate", 15.60);
    Cake c3("Bolo de chocolate", 15.60, CakeCategory::SPONGE);

    EXPECT_TRUE(c1==c2);
    EXPECT_FALSE(c1==c3);
    EXPECT_FALSE(c2==c3);
}

