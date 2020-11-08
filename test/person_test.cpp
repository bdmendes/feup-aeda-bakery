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
    Credential credential = {"client", "client"};

    EXPECT_EQ("Manuel Martins", c1.getName());
    EXPECT_EQ(999999999, c1.getTaxId());
    EXPECT_EQ("client", c1.getCredential().username);
    EXPECT_EQ("client", c1.getCredential().password);
    EXPECT_FLOAT_EQ(0, c1.getPoints());
    EXPECT_FALSE(c1.isPremium());
    EXPECT_FLOAT_EQ(0, c1.getPoints());

    Client c2("Angelica Vieira", true, 287389139, {"AngelicaVieira", "Angelica_8293"});
    credential = {"AngelicaVieira", "Angelica_8293"};

    EXPECT_EQ("Angelica Vieira", c2.getName());
    EXPECT_EQ(287389139, c2.getTaxId());
    EXPECT_EQ("AngelicaVieira", c2.getCredential().username);
    EXPECT_EQ("Angelica_8293", c2.getCredential().password);
    EXPECT_FLOAT_EQ(0, c2.getPoints());
    EXPECT_TRUE(c2.isPremium());
    EXPECT_FLOAT_EQ(0, c2.getPoints());
}

TEST(Worker, create_worker){
    Worker w1("Joao Filipe", 950);
    Credential credential = {"worker", "worker"};

    EXPECT_EQ("Joao Filipe", w1.getName());
    EXPECT_FLOAT_EQ(950, w1.getSalary());
    EXPECT_EQ(999999999, w1.getTaxId());
    EXPECT_EQ("worker", w1.getCredential().username);
    EXPECT_EQ("worker", w1.getCredential().password);
    EXPECT_EQ(0, w1.getOrders());
    EXPECT_TRUE(w1.getCredential() == credential);
    EXPECT_FLOAT_EQ(950, w1.getSalary());

    Worker w2("Filipa Ribeiro", 893, 293013289, {"FilipaRibeiro","filipaRibeiro_9201"});
    credential = {"FilipaRibeiro", "filipaRibeiro_9201"};

    EXPECT_EQ("Filipa Ribeiro", w2.getName());
    EXPECT_FLOAT_EQ(893,w2.getSalary());
    EXPECT_EQ(293013289, w2.getTaxId());
    EXPECT_EQ("FilipaRibeiro", w2.getCredential().username);
    EXPECT_EQ("filipaRibeiro_9201", w2.getCredential().password);
    EXPECT_EQ(0, w2.getOrders());
    EXPECT_TRUE(w2.getCredential() == credential);
    EXPECT_FLOAT_EQ(893,w2.getSalary());
}

TEST(Person, change_name){
    Client client("Ricardo Silva");
    client.changeName("Ricardo Gomes");

    EXPECT_EQ("Ricardo Gomes", client.getName());
    EXPECT_THROW(client.changeName("Ricardo Gomes"), InvalidPersonNameChange);

    client.changeName("Filipe Gomes");

    EXPECT_EQ("Filipe Gomes", client.getName());

    Worker worker("Maria Rodrigues", 790);
    worker.changeName("Sandra Rodrigues");

    EXPECT_EQ("Sandra Rodrigues", worker.getName());
    EXPECT_THROW(worker.changeName("Sandra Rodrigues"), InvalidPersonNameChange);

    worker.changeName("Sandra Silva");

    EXPECT_EQ("Sandra Silva", worker.getName());
}

TEST(Person, change_credential){
    Client client("Rui Macedo");
    Credential clientCredential = {"Ruimacedo", "macedo@123"};
    client.changeCredential(clientCredential);

    EXPECT_TRUE(client.getCredential() == clientCredential);
    EXPECT_THROW(client.changeCredential(clientCredential), InvalidPersonCredentialChange);

    clientCredential.username = "ruimacedo";
    client.changeCredential(clientCredential);

    EXPECT_TRUE(client.getCredential() == clientCredential);

    Worker worker("Luis Figo", 920);
    Credential workerCredential = {"figoLuis13", "921-figo"};
    worker.changeCredential(workerCredential);

    EXPECT_TRUE(worker.getCredential() == workerCredential);
    EXPECT_THROW(worker.changeCredential(workerCredential), InvalidPersonCredentialChange);

    workerCredential.password = "senha321";
    worker.changeCredential(workerCredential);

    EXPECT_TRUE(worker.getCredential() == workerCredential);
}

TEST(Person, equal_person){
    Credential credential={"client", "client"};
    Client c1("Cristina Lopes");
    Client c2("Cristina Lopes", false, 999999999, credential);
    Client c3("Cristina Figueiredo");

    EXPECT_TRUE(c1==c2);
    EXPECT_FALSE(c1==c3);
    EXPECT_FALSE(c2==c3);

    credential = {"worker", "worker"};
    Worker w1("Luis Miguel", 950);
    Worker w2("Luis Miguel", 950, 999999999, credential);
    Worker w3("Luis Filipe", 890);

    EXPECT_TRUE(w1==w2);
    EXPECT_FALSE(w1==w3);
    EXPECT_FALSE(w2==w3);
}

TEST(Client, set_premium){
    Client client("Joel Lopes", true);
    client.setPremium(false);

    EXPECT_FALSE(client.isPremium());

    client.setPremium(true);

    EXPECT_TRUE(client.isPremium());
}

TEST(Client, add_points){
    Client client("Joao Manuel");
    client.addPoints(50);

    EXPECT_EQ(50, client.getPoints());

    client.addPoints(18);

    EXPECT_EQ(68, client.getPoints());

}

TEST(Client, remove_points){
    Client client("Marta Fonseca");
    client.addPoints(43);
    client.removePoints(3);

    EXPECT_EQ(40, client.getPoints());

    client.addPoints(17); //Points = 57
    client.removePoints(10);

    EXPECT_EQ(47, client.getPoints());
}

TEST(Client, reset_poinst){
    Client client("Fabio Fernandes");
    client.addPoints(26);
    client.removePoints(13);
    client.resetPoints();

    EXPECT_EQ(0, client.getPoints());
}

//Note that evaluations are going to be validated in class Order
TEST(Client, add_evaluation){
    Client client("Jose Manuel");
    client.addEvaluation(3.7);
    client.addEvaluation(2.9);

    std::vector<float> evaluations = {3.7, 2.9};

    EXPECT_EQ(evaluations, client.getEvaluations());

    client.addEvaluation(4.5);
    evaluations.push_back(4.5);

    EXPECT_EQ(evaluations, client.getEvaluations());
}

TEST(Client, get_mean_evaluation){
    Client client("Joao Lima");
    client.addEvaluation(3.5);
    client.addEvaluation(2.7);

    EXPECT_FLOAT_EQ((3.5+2.7)/2, client.getMeanEvaluation());

    client.addEvaluation(4.73);
    client.addEvaluation(3.3);

    EXPECT_FLOAT_EQ((3.5+2.7+4.73+3.3)/4, client.getMeanEvaluation());
}

TEST(Client, create_client){
    Client c("Manel", true, 256789324);
    EXPECT_EQ(c.getName(), "Manel");
    EXPECT_EQ(c.getTaxId(), 256789324);
    EXPECT_EQ(c.isPremium(), true);
}

TEST(Worker, set_salary){
    Worker worker("Miguel Filipe", 830);
    worker.setSalary(920);

    EXPECT_FLOAT_EQ(920, worker.getSalary());

    worker.setSalary(892.3);

    EXPECT_FLOAT_EQ(892.3, worker.getSalary());
}

TEST(Worker, add_order){
    Worker worker("Afonso Duarte", 923);
    worker.addOrder();
    worker.addOrder();

    EXPECT_EQ(2, worker.getOrders());
}

TEST(Worker, remove_order){
    Worker worker("Rafael Simao", 872);
    worker.addOrder();
    worker.addOrder();
    worker.addOrder();
    worker.removeOrder();
    worker.removeOrder();

    EXPECT_EQ(1, worker.getOrders());
}

