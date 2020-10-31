//
// Created by bdmendes on 27/10/20.
//

#include <gtest/gtest.h>
#include "model/person/person/person.h"
#include "model/person/client/client.h"
#include "model/person/worker/worker.h"

using testing::Eq;

TEST(Client, create_client){
    Credential credential;
    credential.username = "client";
    credential.password = "client";

    Client c1("Manuel Martins");

    EXPECT_EQ("Manuel Martins", c1.getName());
    EXPECT_EQ(999999999, c1.getTributaryNumber());
    EXPECT_EQ(credential, c1.getCredential());
    EXPECT_FLOAT_EQ(0, c1.getPoints());
    EXPECT_FALSE(c1.isPremium());

    credential.username = "AngelicaVieira";
    credential.password = "Angelica_8293";
    Client c2("Angelica Vieira", true, 287389139, credential);

    EXPECT_EQ("Angelica Vieira", c2.getName());
    EXPECT_EQ(287389139, c2.getTributaryNumber());
    EXPECT_EQ(credential, c2.getCredential());
    EXPECT_FLOAT_EQ(0, c2.getPoints());
    EXPECT_TRUE(c2.isPremium());
}

TEST(Client, change_name){
    Client c1("Ricardo Silva");
    c1.changeName("Ricardo Gomes");

    EXPECT_EQ("Ricardo Gomes", c1.getName());

    Client c2("Maria Rodrigues");
    c2.changeName("Sandra Rodrigues");

    EXPECT_EQ("Sandra Rodrigues", c2.getName());
}

TEST(Client, change_credential){


}


TEST(Client, add_points){

}

TEST(Client, remove_points){

}

TEST(Client, reset_poinst){

}





/*

TEST(Client, create_client){
    Client c("Manel", true, 256789324);
    EXPECT_EQ(c.getName(), "Manel");
    EXPECT_EQ(c.getTributaryNumber(), 256789324);
    EXPECT_EQ(c.isPremium(), true);
}

TEST(Client, change_points){
    Client c("Manel");
    c.addPoints(10);
    EXPECT_EQ(c.getPoints(),10);
    c.resetPoints();
    EXPECT_EQ(c.getPoints(),0);
}

TEST(Person, change_credential){
    Worker w("Emídio", 2930);
    Credential credential = {"worker", "worker"};
    EXPECT_EQ(w.getCredential(), credential);
    credential.password = "thealmighty";
    w.changeCredential(credential);
    EXPECT_EQ(w.getCredential().password, "thealmighty");
}

TEST(Worker, change_salary){
    Worker w("Alfredo",5420);
    w.setSalary(1300);
    EXPECT_EQ(w.getSalary(),1300);
}*/
