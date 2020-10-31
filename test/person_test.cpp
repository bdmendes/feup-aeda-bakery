//
// Created by bdmendes on 27/10/20.
//

#include <gtest/gtest.h>
#include "model/person/person/person.h"
#include "model/person/client/client.h"
#include "model/person/worker/worker.h"

using testing::Eq;

TEST(Client, create_client){
    Client c1("Manuel Martins");

    EXPECT_EQ("Manuel Martins", c1.getName());
    EXPECT_EQ(999999999, c1.getTributaryNumber());
    EXPECT_EQ("client", c1.getCredential().username);
    EXPECT_EQ("client", c1.getCredential().password);
    EXPECT_FLOAT_EQ(0, c1.getPoints());
    EXPECT_FALSE(c1.isPremium());

    Credential credential;
    credential.username = "AngelicaVieira";
    credential.password = "Angelica_8293";
    Client c2("Angelica Vieira", true, 287389139, credential);

    EXPECT_EQ("Angelica Vieira", c2.getName());
    EXPECT_EQ(287389139, c2.getTributaryNumber());
    EXPECT_EQ("AngelicaVieira", c2.getCredential().username);
    EXPECT_EQ("Angelica_8293", c2.getCredential().password);
    EXPECT_FLOAT_EQ(0, c2.getPoints());
    EXPECT_TRUE(c2.isPremium());
}

TEST(Worker, create_worker){
    Worker w1("Joao Filipe", 950);

    EXPECT_EQ("Joao Filipe", w1.getName());
    EXPECT_FLOAT_EQ(950, w1.getSalary());
    EXPECT_EQ(999999999, w1.getTributaryNumber());
    EXPECT_EQ("worker", w1.getCredential().username);
    EXPECT_EQ("worker", w1.getCredential().password);
    EXPECT_EQ(0, w1.getOrders());

    Credential credential;
    credential.username = "FilipaRibeiro";
    credential.password = "filipaRibeiro_9201";
    Worker w2("Filipa Ribeiro", 893, 293013289, credential);

    EXPECT_EQ("Filipa Ribeiro", w2.getName());
    EXPECT_FLOAT_EQ(893,w2.getSalary());
    EXPECT_EQ(293013289, w2.getTributaryNumber());
    EXPECT_EQ("FilipaRibeiro", w2.getCredential().username);
    EXPECT_EQ("filipaRibeiro_9201", w2.getCredential().password);
    EXPECT_EQ(0, w2.getOrders());
}


TEST(Person, change_name){
    Client client("Ricardo Silva");
    client.changeName("Ricardo Gomes");

    EXPECT_EQ("Ricardo Gomes", client.getName());

    client.changeName("Filipe Gomes");

    EXPECT_EQ("Filipe Gomes", client.getName());

    Worker worker("Maria Rodrigues", 790);
    worker.changeName("Sandra Rodrigues");

    EXPECT_EQ("Sandra Rodrigues", worker.getName());

    worker.changeName("Sandra Costa");

    EXPECT_EQ("Sandra Costa", worker.getName());
}

TEST(Person, change_credential){
    Client client("Rui Macedo");
    Credential clientCredential;
    clientCredential.username = "Ruimacedo";
    clientCredential.password = "macedo@123";
    client.changeCredential(clientCredential);

    EXPECT_EQ("Ruimacedo", client.getCredential().username);
    EXPECT_EQ("macedo@123", client.getCredential().password);

    clientCredential.username = "ruiMacedo";
    client.changeCredential(clientCredential);

    EXPECT_EQ("ruiMacedo", client.getCredential().username);
    EXPECT_EQ("macedo@123", client.getCredential().password);

    Worker worker("Luis Figo", 920);
    Credential workerCredential;
    workerCredential.username = "figoLuis13";
    workerCredential.password= "921-figo";
    worker.changeCredential(workerCredential);

    EXPECT_EQ("figoLuis13", worker.getCredential().username);
    EXPECT_EQ("921-figo", worker.getCredential().password);

    workerCredential.password = "figoluis_921";
    worker.changeCredential(workerCredential);

    EXPECT_EQ("figoLuis13", worker.getCredential().username);
    EXPECT_EQ("figoluis_921", worker.getCredential().password);
}

TEST(Person, equal_person){
    Client c1("Cristina Lopes");
    Client c2("Cristina Lopes");
    Client c3("Cristina Figueiredo");

    EXPECT_TRUE(c1==c2);
    EXPECT_TRUE(c2==c1);
    EXPECT_FALSE(c1==c3);
    EXPECT_FALSE(c2==c3);

    Worker w1("Luis Miguel", 950);

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
