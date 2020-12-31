
#include <gtest/gtest.h>
#include "model/person/person.h"
#include "model/person/client/client.h"
#include "model/person/worker/worker.h"
#include "model/person/boss/boss.h"
#include "exception/file_exception.h"

using testing::Eq;

TEST(Client, create_client){
    EXPECT_THROW(Client("Maria Luisa", 293847162, false, {"back", "luisa"}), InvalidCredential);
    EXPECT_THROW(Client("Maria Luisa", 293847162, false, {"luisa", "exit"}), InvalidCredential);

    Client client1("Manuel Martins");

    EXPECT_EQ("Manuel Martins", client1.getName());
    EXPECT_EQ(Person::DEFAULT_TAX_ID, client1.getTaxId());
    EXPECT_TRUE(client1.getDefaultCredential() == client1.getCredential());
    EXPECT_FLOAT_EQ(0, client1.getPoints());
    EXPECT_FALSE(client1.isPremium());
    EXPECT_FALSE(client1.isLogged());

    Client client2("Angelica Vieira", 287389139, true,{"AngelicaVieira", "Angelica_8293"});
    Credential credential = {"AngelicaVieira", "Angelica_8293"};

    EXPECT_EQ("Angelica Vieira", client2.getName());
    EXPECT_EQ(287389139, client2.getTaxId());
    EXPECT_TRUE(credential == client2.getCredential());
    EXPECT_FLOAT_EQ(0, client2.getPoints());
    EXPECT_TRUE(client2.isPremium());
    EXPECT_FALSE(client2.isLogged());
}

TEST(Worker, create_worker){
    EXPECT_THROW(Worker("Head Office", "Maria Luisa", 293847162, 900, {"back", "luisa"}), InvalidCredential);
    EXPECT_THROW(Worker("Head Office", "Maria Luisa", 293847162, 900, {"luisa", "exit"}), InvalidCredential);

    Worker worker1("Head Office", "Joao Filipe", Person::DEFAULT_TAX_ID,950);
    Credential credential = {"worker", "worker"};

    EXPECT_EQ("Head Office", worker1.getLocation());
    EXPECT_EQ("Joao Filipe", worker1.getName());
    EXPECT_FLOAT_EQ(950, worker1.getSalary());
    EXPECT_EQ(Person::DEFAULT_TAX_ID, worker1.getTaxId());
    EXPECT_EQ("worker", worker1.getCredential().username);
    EXPECT_EQ("worker", worker1.getCredential().password);
    EXPECT_EQ(0, worker1.getUndeliveredOrders());
    EXPECT_TRUE(worker1.getCredential() == credential);
    EXPECT_FLOAT_EQ(950, worker1.getSalary());

    Worker worker2("Lisboa", "Filipa Ribeiro",  293013289, 893,{"FilipaRibeiro","filipaRibeiro_9201"});
    credential = {"FilipaRibeiro", "filipaRibeiro_9201"};

    EXPECT_EQ("Lisboa", worker2.getLocation());
    EXPECT_EQ("Filipa Ribeiro", worker2.getName());
    EXPECT_FLOAT_EQ(893,worker2.getSalary());
    EXPECT_EQ(293013289, worker2.getTaxId());
    EXPECT_EQ("FilipaRibeiro", worker2.getCredential().username);
    EXPECT_EQ("filipaRibeiro_9201", worker2.getCredential().password);
    EXPECT_EQ(0, worker2.getUndeliveredOrders());
    EXPECT_TRUE(worker2.getCredential() == credential);
    EXPECT_FLOAT_EQ(893,worker2.getSalary());
}

TEST(Boss, create_boss){
    EXPECT_THROW(Boss("Maria Luisa", 293847162, {"back", "luisa"}), InvalidCredential);
    EXPECT_THROW(Boss("Maria Luisa", 293847162, {"luisa", "exit"}), InvalidCredential);

    Boss boss1("Manuel Martins");

    EXPECT_EQ("Manuel Martins", boss1.getName());
    EXPECT_EQ(Person::DEFAULT_TAX_ID, boss1.getTaxId());
    EXPECT_TRUE(boss1.getDefaultCredential() == boss1.getCredential());
    EXPECT_FALSE(boss1.isLogged());

    Boss boss2("Angelica Vieira", 287389139, {"AngelicaVieira", "Angelica_8293"});
    Credential credential = {"AngelicaVieira", "Angelica_8293"};

    EXPECT_EQ("Angelica Vieira", boss2.getName());
    EXPECT_EQ(287389139, boss2.getTaxId());
    EXPECT_TRUE(credential == boss2.getCredential());
    EXPECT_FALSE(boss2.isLogged());
}

TEST(Person, set_logged){
    Client client("Joao Martins");
    client.setLogged(true);

    EXPECT_TRUE(client.isLogged());

    Worker worker("Head Office", "Manuel Miranda");
    worker.setLogged(true);

    EXPECT_TRUE(worker.isLogged());

    Boss boss("Joaquim Felix");
    boss.setLogged(true);

    EXPECT_TRUE(boss.isLogged());
}

TEST(Person, set_name){
    Client client("Ricardo Silva");
    client.setName("Ricardo Gomes");

    EXPECT_EQ("Ricardo Gomes", client.getName());
    client.setName("Filipe Gomes");
    EXPECT_EQ("Filipe Gomes", client.getName());

    Worker worker("Head Office", "Maria Rodrigues", 790);
    worker.setName("Sandra Rodrigues");

    EXPECT_EQ("Sandra Rodrigues", worker.getName());
    worker.setName("Sandra Silva");
    EXPECT_EQ("Sandra Silva", worker.getName());

    Boss boss("Fabiana Silva");
    boss.setName("Luisa Silva");

    EXPECT_EQ("Luisa Silva", boss.getName());
    boss.setName("Luisa Gomes");
    EXPECT_EQ("Luisa Gomes", boss.getName());
}

TEST(Person, set_tax_id){
    Client client("Joao Manuel");
    client.setTaxID(2138329);

    EXPECT_EQ(2138329, client.getTaxId());

    Worker worker("Head Office", "Goncalo Oliveira");
    worker.setTaxID(9482371);

    EXPECT_EQ(9482371, worker.getTaxId());

    Boss boss("Bruno Luis");
    boss.setTaxID(1231289);

    EXPECT_EQ(1231289, boss.getTaxId());
}

TEST(Person, set_credential){
    Client client("Rui Macedo");
    Credential clientCredential = {"Ruimacedo", "macedo@123"};
    client.setCredential(clientCredential);

    EXPECT_TRUE(client.getCredential() == clientCredential);

    clientCredential.username = "ruimacedo";
    client.setCredential(clientCredential);

    EXPECT_TRUE(client.getCredential() == clientCredential);

    clientCredential.password = "back";
    EXPECT_THROW(client.setCredential(clientCredential),InvalidCredential);

    clientCredential.username = "exit";
    EXPECT_THROW(client.setCredential({"exit","123"}),InvalidCredential);

    Worker worker("Head Office", "Luis Figo", 920);
    Credential workerCredential = {"figoLuis13", "921-figo"};
    worker.setCredential(workerCredential);

    EXPECT_TRUE(worker.getCredential() == workerCredential);
    workerCredential.password = "senha321";
    worker.setCredential(workerCredential);

    EXPECT_TRUE(worker.getCredential() == workerCredential);

    workerCredential.password = "back";
    EXPECT_THROW(worker.setCredential(workerCredential),InvalidCredential);

    workerCredential.username = "exit";
    EXPECT_THROW(worker.setCredential({"exit","123"}),InvalidCredential);

    Boss boss("Ricardo Macedo");
    Credential bossCredential = {"Ricardinho", "macedo@123"};
    boss.setCredential(bossCredential);

    EXPECT_TRUE(boss.getCredential() == bossCredential);

    bossCredential.username = "ruimacedo";
    boss.setCredential(bossCredential);

    EXPECT_TRUE(boss.getCredential() == bossCredential);

    bossCredential.password = "back";
    EXPECT_THROW(boss.setCredential(bossCredential),InvalidCredential);

    bossCredential.username = "exit";
    EXPECT_THROW(boss.setCredential({"exit","123"}),InvalidCredential);
}

TEST(Person, less_than_operator){
    Client client1("Beatriz Duarte");
    Client client2("Joana Fernandes");
    Client client3("Joao Martins");

    EXPECT_TRUE(client1 < client2);
    EXPECT_TRUE(client2 < client3);
    EXPECT_FALSE(client3 < client1);

    Worker worker1("Head Office", "Cristina Martins", 184391272);
    Worker worker2 ("Head Office", "Cristina Martins");
    Worker worker3("Head Office", "Sara Ribeiro", 249123948);
    Worker worker4("Head Office", "Sara Couto");

    EXPECT_TRUE(worker1 < worker2);
    EXPECT_TRUE(worker1 < worker3);
    EXPECT_TRUE(worker1 < worker4);
    EXPECT_TRUE(worker3 < worker2);
    EXPECT_TRUE(worker2 < worker4);
    EXPECT_TRUE(worker3 < worker4);

    Boss boss1("Beatriz Duarte");
    Boss boss2("Joana Fernandes");
    Boss boss3("Joao Martins");

    EXPECT_TRUE(boss1 < boss2);
    EXPECT_TRUE(boss2 < boss3);
    EXPECT_FALSE(boss3 < boss1);

}

TEST(Person, equality_operator){
    Client client1("Cristina Lopes");
    Client client2("Cristina Lopes", Person::DEFAULT_TAX_ID, false, {"client", "client"});
    Client client3("Cristina Figueiredo");
    Client client4("Joao Manuel", 284917316,false, {"jonasManel", "joao123"});

    EXPECT_TRUE(client1==client2);
    EXPECT_FALSE(client1==client3);
    EXPECT_FALSE(client2==client3);
    EXPECT_FALSE(client1==client4);

    Worker worker1("Head Office", "Luis Miguel", Person::DEFAULT_TAX_ID,950);
    Worker worker2("Head Office", "Luis Miguel",  Person::DEFAULT_TAX_ID,950, {"worker", "worker"});
    Worker worker3("Head Office", "Luis Filipe", 890);
    Worker worker4("Head Office", "Joao Manuel", 284917316,950, {"jonasManel", "joao123"});

    EXPECT_TRUE(worker1==worker2);
    EXPECT_FALSE(worker1==worker3);
    EXPECT_FALSE(worker2==worker3);
    EXPECT_FALSE(worker1==worker4);

    Boss boss1("Cristina Lopes");
    Boss boss2("Cristina Lopes", Person::DEFAULT_TAX_ID, {"client", "client"});
    Boss boss3("Cristina Figueiredo");
    Boss boss4("Joao Manuel", 284917316, {"jonasManel", "joao123"});

    EXPECT_TRUE(boss1==boss2);
    EXPECT_FALSE(boss1==boss3);
    EXPECT_FALSE(boss2==boss3);
    EXPECT_FALSE(boss1==boss4);
}

TEST(Client, add_discount){
    Client client("Joana Ferraz");
    EXPECT_EQ(0, client.getNumDiscounts());

    client.addDiscount();
    EXPECT_EQ(1, client.getNumDiscounts());

    client.addDiscount();
    client.addDiscount();
    client.addDiscount();
    EXPECT_EQ(4, client.getNumDiscounts());
}

TEST(Client, remove_discount){
    Client client("Joana Ferraz");
    client.addDiscount();
    client.addDiscount();
    client.addDiscount();
    client.addDiscount();

    client.removeDiscount();
    EXPECT_EQ(3, client.getNumDiscounts());

    client.removeDiscount();
    client.removeDiscount();
    client.removeDiscount();
    EXPECT_EQ(0, client.getNumDiscounts());
}

TEST(Client, set_premium){
    Client client("Joel Lopes", 599596,true);
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

TEST(Client, set_points){
    Client client("Joao Manuel");
    client.setPoints(50);

    EXPECT_EQ(50, client.getPoints());

    client.setPoints(18);

    EXPECT_EQ(18, client.getPoints());
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

TEST(Client, add_evaluation){
    Client client("Rodrigo Machado");

    EXPECT_FLOAT_EQ(0, client.getMeanEvaluation());

    client.addEvaluation(4);

    EXPECT_FLOAT_EQ(4, client.getMeanEvaluation());

    client.addEvaluation(3);
    client.addEvaluation(2);
    client.addEvaluation(5);

    EXPECT_FLOAT_EQ((float)(4+3+2+5)/4, client.getMeanEvaluation());
}

TEST(Worker, set_salary){
    Worker worker("Head Office", "Miguel Filipe", 830);
    worker.setSalary(920);

    EXPECT_FLOAT_EQ(920, worker.getSalary());

    worker.setSalary(892.3);

    EXPECT_FLOAT_EQ(892.3, worker.getSalary());
}

TEST(Worker, add_order_to_deliver){
    Worker worker("Head Office", "Afonso Duarte", 923);
    worker.addOrderToDeliver();
    worker.addOrderToDeliver();

    EXPECT_EQ(2, worker.getUndeliveredOrders());
}

TEST(Worker, remove_order_to_deliver){
    Worker worker("Head Office", "Rafael Simao", 872);
    worker.addOrderToDeliver();
    worker.addOrderToDeliver();
    worker.addOrderToDeliver();
    worker.removeOrderToDeliver();
    worker.removeOrderToDeliver();

    EXPECT_EQ(1, worker.getUndeliveredOrders());
}

TEST(Worker, add_evaluation){
    Worker worker("Head Office", "Rodrigo Machado");

    EXPECT_FLOAT_EQ(0, worker.getMeanEvaluation());

    worker.addEvaluation(4);

    EXPECT_FLOAT_EQ(4, worker.getMeanEvaluation());

    worker.addEvaluation(3);
    worker.addEvaluation(2);
    worker.addEvaluation(5);

    EXPECT_FLOAT_EQ((float)(4+3+2+5)/4, worker.getMeanEvaluation());
}

TEST(Boss, read){
    //Adelaide 3847565 adelaide adelaide123
    Boss boss("To read");

    EXPECT_THROW(boss.read("/boss.txt"), FileNotFound);

    boss.read("../../data/boss.txt");

    Credential credential = {"adelaide", "adelaide123"};
    EXPECT_EQ("Adelaide", boss.getName());
    EXPECT_EQ(3847565, boss.getTaxId());
    EXPECT_TRUE(credential == boss.getCredential());
}

TEST(Boss, write){
    Boss initialBoss("Initial Boss");
    initialBoss.read("../../data/boss.txt");

    //Joel-Miranda 213138 jeel jeelmir194
    Boss writeBoss("Joel Miranda", 213138, {"jeel", "jeelmir194"});
    Boss readBoss("Boss to read");

    EXPECT_THROW(writeBoss.write("/boss.txt"), FileNotFound);

    writeBoss.write("../../data/boss.txt");
    writeBoss.read("../../data/boss.txt");

    Credential credential = {"jeel", "jeelmir194"};
    EXPECT_EQ("Joel Miranda", writeBoss.getName());
    EXPECT_EQ(213138, writeBoss.getTaxId());
    EXPECT_TRUE(credential == writeBoss.getCredential());

    //Resets file
    initialBoss.write("../../data/boss.txt");
}