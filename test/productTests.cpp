//
// Created by laimi on 22/10/2020.
//

#include <gtest/gtest.h>
#include "../src/model/Person.h"
#include "../src/model/Store.h"
#include "../src/model/Order.h"
#include "../src/model/Product.h"


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

//for test purposes
bool isPresent(const std::string &category) {
    if(std::find_if(Cake::availableCategories.begin(), Cake::availableCategories.end(), [&category](const std::string& c){return (c==category);})!=Cake::availableCategories.end())
        return true;
}

TEST(Cake, changeCategories){
    Cake::addCategory("Bolo de pedra");
    EXPECT_EQ(isPresent("Bolo de pedra"), true);
    Cake::removeCategory("Bolo de pedra");
    EXPECT_EQ(isPresent("Bolo de pedra"), false);
}

//for test purposes
bool areEqualProducts(const Product& p1, const Product& p2){
    return (p1==p2);
}

TEST(Product, equalProducts){
    Product meatCake("Bolo com molho de carne", 1.20);
    Product chocolateCake("Bolo de chocolate", 1.20);
    EXPECT_EQ(areEqualProducts(meatCake, chocolateCake), false);
}

//for test purposes
bool areEqualCakes(const Cake &c1, const Cake &c2){
    return (c1==c2);
}

TEST(Cake, equalProducts){
    Cake c1("Bolo da avo", 1.20, "Pie");
    Cake c2("Bolo da avo", 1.20, "Pie");
    EXPECT_EQ(areEqualCakes(c1, c2), true);
}

//for test purposes
bool areEqualBreads(const Bread &b1, const Bread &b2){
    return (b1==b2);
}

TEST(Cake, equalProducts){
    Bread b1("Pao da avo", 1.20, true);
    Bread b2("Cacete da avo", 1.20, true);
    EXPECT_EQ(areEqualBreads(b1, b2), false);
}