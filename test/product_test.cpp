//
// Created by laimi on 22/10/2020.
//

#include <gtest/gtest.h>
#include "../src/model/product.h"
#include <algorithm>

using testing::Eq;

TEST(Product, creat_product){
    Product meatCake("Bolo com molho de carne", 1.20);
    EXPECT_EQ(meatCake.getName(), "Bolo com molho de carne");
    EXPECT_EQ(meatCake.getPrice(), 1.20);
}

TEST(Cake, creat_cake){
    Cake cake("bolinho fofinho", 22.30, "Pie");
    EXPECT_EQ(cake.getName(), "bolinho fofinho");
    EXPECT_EQ(cake.getPrice(), 22.30);
    EXPECT_EQ(cake.getCategory(), "Pie");
}

TEST(Bread, creat_bread){
    Bread bread("pao da avo", 0.9, true);
    EXPECT_EQ(bread.getName(), "pao da avo");
    EXPECT_EQ(bread.getPrice(), 0.9);
    EXPECT_EQ(bread.isSmall(), true);
}

TEST(Cake, changeCategories){
    auto isPresent = [](const std::string &category) {
        return std::find_if(Cake::availableCategories.begin(), Cake::availableCategories.end(), [&category](const std::string& c){return (c==category);}) != Cake::availableCategories.end();
    };

    Cake::addCategory("Bolo de pedra");
    EXPECT_EQ(isPresent("Bolo de pedra"), true);
    Cake::removeCategory("Bolo de pedra");
    EXPECT_EQ(isPresent("Bolo de pedra"), false);
}

TEST(Product, equalProducts){
    Product meatCake("Bolo com molho de carne", 1.20);
    Product chocolateCake("Bolo de chocolate", 1.20);
    EXPECT_EQ(chocolateCake, meatCake);
}

TEST(Cake, equalProducts){
    Cake c1("Bolo da avo", 1.20, "Pie");
    Cake c2("Bolo da avo", 1.20, "Pie");
    EXPECT_EQ(c1,c2);
}

TEST(Bread, equalProducts){
    Bread b1("Pao da avo", 1.20, true);
    Bread b2("Cacete da avo", 1.20, true);
    EXPECT_EQ(b1, b2);
}