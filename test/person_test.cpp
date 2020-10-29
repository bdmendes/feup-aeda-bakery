//
// Created by bdmendes on 27/10/20.
//

#include <gtest/gtest.h>
#include "model/person/person/person.h"
#include "model/person/client/client.h"
#include "model/person/worker/worker.h"

using testing::Eq;

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
}