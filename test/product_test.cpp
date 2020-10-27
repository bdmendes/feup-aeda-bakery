//
// Created by laimi on 22/10/2020.
//

#include <gtest/gtest.h>
#include "../src/model/product.h"
#include <algorithm>

using testing::Eq;

TEST(Product, creat_product){
    Cake meatCake("Bolo com molho de carne", 1.20, CakeCategory::PUFF_PASTRY);
    EXPECT_EQ(meatCake.getName(), "Bolo com molho de carne");
    EXPECT_FLOAT_EQ(meatCake.getPrice(), 1.20);
}

TEST(Cake, creat_cake){
    Cake cake("bolinho fofinho", 22.30, CakeCategory::PIE);
    EXPECT_EQ(cake.getName(), "bolinho fofinho");
    EXPECT_FLOAT_EQ(cake.getPrice(), 22.30);
    EXPECT_EQ(cake.getCategory(), CakeCategory::PIE);
}

TEST(Bread, creat_bread){
    Bread bread("pao da avo", 0.9, true);
    EXPECT_EQ(bread.getName(), "pao da avo");
    EXPECT_FLOAT_EQ(bread.getPrice(), 0.9);
    EXPECT_EQ(bread.isSmall(), true);
}

TEST(Product, equalProducts){
    Cake meatCake("Bolo com molho de carne", 1.20, CakeCategory::PUFF_PASTRY);
    Cake chocolateCake("Bolo de chocolate", 1.20, CakeCategory::PUFF_PASTRY);
    EXPECT_FALSE(chocolateCake == meatCake);
}

TEST(Cake, equalProducts){
    Cake c1("Bolo da avo", 1.20, CakeCategory::PIE);
    Cake c2("Bolo da avo", 1.20, CakeCategory::PIE);
    EXPECT_TRUE(c1 == c2);
}

TEST(Bread, equalProducts){
    Bread b1("Pao da avo", 1.20, true);
    Bread b2("Cacete da avo", 1.20, true);
    EXPECT_FALSE(b1 == b2);
}