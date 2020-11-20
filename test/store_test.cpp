
#include <gtest/gtest.h>
#include "model/store/store.h"
#include "model/store/location_manager.h"
#include "exception/file_exception.h"

#include <algorithm>

using testing::Eq;

TEST(Store, create_store){
    Store store1;

    EXPECT_EQ("Bakery Store", store1.getName());

    Store store2("Padaria Pao Quente");

    EXPECT_EQ("Padaria Pao Quente", store2.getName());
}

TEST(Store, set_name){
    Store store;
    store.setName("Padaria Doce Cereal");

    EXPECT_EQ("Padaria Doce Cereal", store.getName());

    store.setName("Padaria Diamante");

    EXPECT_EQ("Padaria Diamante", store.getName());
}

/*TEST(Store, get_evaluation){
    Boss boss("Boss to read");
    LocationManager locationM;
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);
    Store store;
    store.read("../data");
}

TEST(Store, get_profit){
    Store store;
    ProductManager productM; ClientManager clientM; WorkerManager workerM; LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);
    Client* client = clientM.add("Fernando Castro");
    Worker* worker = workerM.add("Josue Tome", 928);
    Cake* cake = productM.addCake("Bolo de chocolate", 3.2);
    Order* order1 = orderM.add(client, worker);
    order1->addProduct(cake, 10);
    order1->deliver(5);
    store.productManager = productM;
    store.clientManager =  clientM;
    store.workerManager = workerM;
    store.orderManager = orderM;
    store.locationManager = locationM;

    EXPECT_FLOAT_EQ(10*3.2, orderM.getAll().begin());

    client->addPoints(200);
    Order* order2 = orderM.add(client, worker);
    order2->addProduct(cake, 7);
    order2->deliver(4);

    EXPECT_FLOAT_EQ((10*3.2)+(7*3.2)*0.98, store.getProfit());
}*/

TEST(Store, read){
    Store store;
    std::string path = "../../data";
    std::string success = store.read(path);
    EXPECT_EQ("Import succeeded.", success);

    //Boss: Adelaide 3847565 adelaide adelaide123
    Boss boss = store.boss;
    Credential credential = {"adelaide", "adelaide123"};
    EXPECT_EQ("Adelaide", boss.getName());
    EXPECT_EQ(3847565, boss.getTaxId());
    EXPECT_TRUE(credential == boss.getCredential());

    //Locations: Head-Office; Lisboa
    std::set<std::string> locations = store.locationManager.getAll();
    EXPECT_EQ("Head Office", *locations.begin());
    EXPECT_EQ("Lisboa", *(++locations.begin()));

    //Cake: Bolo-crocante 15 Crunchy-Cake
    Cake* cake = *store.productManager.getCakes().begin();
    EXPECT_EQ("Bolo crocante", cake->getName());
    EXPECT_FLOAT_EQ(15, cake->getPrice());
    EXPECT_EQ(CakeCategory::CRUNCHY, cake->getCategory());

    //Bread: Pao-da-avo 1 big
    Bread* bread = *store.productManager.getBreads().begin();
    EXPECT_EQ("Pao da avo", bread->getName());
    EXPECT_FLOAT_EQ(1, bread->getPrice());
    EXPECT_FALSE(bread->isSmall());

    //Client: Alfredo-Machado 23554 basic 300 machado mymachado
    //Please note that because of the orders made by the client, the current points are set to 150
    Client client = *store.clientManager.get(0);
    credential = {"machado", "mymachado"};
    EXPECT_EQ("Alfredo Machado", client.getName());
    EXPECT_EQ(23554, client.getTaxId());
    EXPECT_FALSE(client.isPremium());
    EXPECT_EQ(150, client.getPoints());
    EXPECT_TRUE(credential == client.getCredential());

    //Worker: Julia-Mendes 2345 2001 julia sousenhora
    Worker* worker = store.workerManager.get(0);
    credential = {"julia", "sousenhora"};
    EXPECT_EQ("Julia Mendes", worker->getName());
    EXPECT_EQ(2345, worker->getTaxId());
    EXPECT_FLOAT_EQ(2001, worker->getSalary());
    EXPECT_TRUE(credential == worker->getCredential());

    //Order: 324564 32534 12/06/2020 18:34 Head-Office 5
    //Bolo-crocante 15 1
    //Pao-de-cereais 0.5 1
    Order* order = *store.orderManager.getAll().begin();
    EXPECT_EQ(324564, order->getClient()->getTaxId());
    EXPECT_EQ(32534, order->getWorker()->getTaxId());
    EXPECT_EQ("12/06/2020 18:34", order->getRequestDate().getCompleteDate());
    EXPECT_EQ("Head Office", order->getDeliverLocation());
    EXPECT_EQ("Bolo crocante", (order->getProducts().begin())->first->getName());
    EXPECT_FLOAT_EQ(15, (order->getProducts().begin())->first->getPrice());
    EXPECT_EQ(1, (order->getProducts().begin())->second);
    EXPECT_EQ("Pao de cereais", (++order->getProducts().begin())->first->getName());
    EXPECT_FLOAT_EQ(0.5, (++order->getProducts().begin())->first->getPrice());
    EXPECT_EQ(1, (++order->getProducts().begin())->second);

/*    EXPECT_FLOAT_EQ((15*1 + 0.5*1) + (3*1 + 25*1) + (15*1 + 0.5*1) + (3*1 + 25*1), store.getProfit());
    EXPECT_FLOAT_EQ((5+3+5+3)/4, store.getEvaluation());*/
}

TEST(Store, write){

}

TEST(ClientManager, has_client){
    ClientManager clientM;

    EXPECT_TRUE(clientM.getAll().empty());

    Client* client1 = clientM.add("Cristina Lopes");

    EXPECT_TRUE(clientM.has(client1));

    Client* client2 = clientM.add("Joao Manuel", false, 284917316, {"jonasManel", "joao123"});

    EXPECT_TRUE(clientM.has(client1));
    EXPECT_TRUE(clientM.has(client2));
}

TEST(ClientManager, get_client_by_position){
    ClientManager clientM;
    Client* client1 = clientM.add("Alvaro Campos");
    Client* client2 = clientM.add("Henrique Vaz");
    Client* client3 = clientM.add("Sofia Rebelo");
    unsigned position = 0;

    EXPECT_TRUE(*client1 == *clientM.get(position));
    EXPECT_TRUE(*client2 == *clientM.get(++position));
    EXPECT_TRUE(*client3 == *clientM.get(++position));
}

TEST(ClientManager, get_client_by_taxID){
    ClientManager clientM;
    Client* client1 = clientM.add("Alvaro Campos", Person::DEFAULT_TAX_ID);
    Client* client2 = clientM.add("Henrique Vaz", 123812321);
    Client* client3 = clientM.add("Sofia Rebelo", 495483123);

    EXPECT_TRUE(*client1 == *clientM.getClient(Person::DEFAULT_TAX_ID));
    EXPECT_TRUE(*client2 == *clientM.getClient(123812321));
    EXPECT_TRUE(*client3 == *clientM.getClient(495483123));
}

TEST(ClientManager, add_client){
    unsigned position = 0;
    Client client1("Rodrigo Pereira");
    std::set<Client*, PersonSmaller> clients;
    ClientManager clientM;

    EXPECT_EQ(0, clientM.getAll().size());

    Client* getClient = clientM.add("Rodrigo Pereira");

    EXPECT_EQ(1, clientM.getAll().size());
    EXPECT_TRUE(client1 == *getClient);

    Client client2("Maria Joao", true, 174829123, {"mariaj", "123"});
    getClient = clientM.add("Maria Joao", true, 174829123, {"mariaj", "123"});

    EXPECT_EQ(2, clientM.getAll().size());
    EXPECT_TRUE(client2 == *getClient);
}

TEST(ClientManager, remove_client_by_pointer){
    ClientManager clientM;
    Client* client1 = clientM.add("Henrique Vaz");
    Client* client2 = clientM.add("Sofia Rebelo");
    unsigned position = 0;

    EXPECT_EQ(2, clientM.getAll().size());

    clientM.remove(client1);

    EXPECT_EQ(1, clientM.getAll().size());
    EXPECT_TRUE(*client2 == *clientM.get(position));

    clientM.remove(client2);

    EXPECT_TRUE(clientM.getAll().empty());
    EXPECT_THROW(clientM.remove(client1), PersonDoesNotExist);
    EXPECT_THROW(clientM.remove(client2), PersonDoesNotExist);
}

TEST(ClientManager, remove_client_by_position){
    unsigned position = 1;
    ClientManager clientM;
    Client* client1 = clientM.add("Henrique Vaz");
    Client* client2 = clientM.add("Sofia Rebelo");

    EXPECT_EQ(2, clientM.getAll().size());

    clientM.remove(position);

    EXPECT_EQ(1, clientM.getAll().size());
    EXPECT_TRUE(*client1 == *(*clientM.getAll().begin()));
    EXPECT_THROW(clientM.remove(position++), InvalidPersonPosition);

    position = 0;
    clientM.remove(position);

    EXPECT_TRUE(clientM.getAll().empty());
    EXPECT_THROW(clientM.remove(position), InvalidPersonPosition);
}

TEST(ClientManager, read){
    ClientManager clientM;

    EXPECT_THROW(clientM.read("/clients.txt"), FileNotFound);

    clientM.read("../../data/clients.txt");
    unsigned position = 0;
    Client* currentClient = clientM.get(position);

    //Alfredo-Machado 23554 basic 300 machado mymachado
    Credential credential = {"machado", "mymachado"};
    EXPECT_EQ("Alfredo Machado", currentClient->getName());
    EXPECT_EQ(23554, currentClient->getTaxId());
    EXPECT_FALSE(currentClient->isPremium());
    EXPECT_EQ(300, currentClient->getPoints());
    EXPECT_TRUE(credential == currentClient->getCredential());

    currentClient = clientM.get(++position);

    //Angela-Coelho 324564 premium 280 angela angela123
    credential = {"angela", "angela123"};
    EXPECT_EQ("Angela Coelho", currentClient->getName());
    EXPECT_EQ(324564, currentClient->getTaxId());
    EXPECT_TRUE(currentClient->isPremium());
    EXPECT_EQ(280, currentClient->getPoints());
    EXPECT_TRUE(credential == currentClient->getCredential());

    currentClient = clientM.get(++position);

    //Bruno-Mendes 879789 premium 280 bdmendes mendes
    credential = {"bdmendes", "mendes"};
    EXPECT_EQ("Bruno Mendes", currentClient->getName());
    EXPECT_EQ(879789, currentClient->getTaxId());
    EXPECT_TRUE(currentClient->isPremium());
    EXPECT_EQ(280, currentClient->getPoints());
    EXPECT_TRUE(credential == currentClient->getCredential());
}

TEST(ClientManager, write){
    const std::string path = "../../data/clients.txt";
    ClientManager clientMInitial;
    clientMInitial.read(path);
    ClientManager clientM;

    //EXPECT_THROW(clientM.write("/clients.txt"), FileNotFound);

    Client* client1 = clientM.add("Miguel Gomes", 4398331, false, {"miuelGom", "m123g"});
    client1->addPoints(80);
    Client* client2 = clientM.add("Joana Moreira", 38470348, true, {"juMoreira", "joanaMoreira"});
    client2->addPoints(130);
    Client* client3 = clientM.add("Ricardo Macedo", Person::DEFAULT_TAX_ID, false, {"ricM", "ricardo_948"});
    client3->addPoints(300);

    clientM.write(path);
    clientM.read(path);
    unsigned position = 0;
    Client* currentClient = clientM.get(position);

    //Miguel-Gomes 4398331 basic 80 miuelGom m123g
    Credential credential = {"miuelGom", "m123g"};
    EXPECT_EQ("Miguel Gomes", currentClient->getName());
    EXPECT_EQ(4398331, currentClient->getTaxId());
    EXPECT_FALSE(currentClient->isPremium());
    EXPECT_EQ(80, currentClient->getPoints());
    EXPECT_TRUE(credential == currentClient->getCredential());

    currentClient = clientM.get(++position);

    //Joana-Moreira 38470348 premium 130 juMoreira joanaMoreira
    credential = {"juMoreira", "joanaMoreira"};
    EXPECT_EQ("Joana Moreira", currentClient->getName());
    EXPECT_EQ(38470348, currentClient->getTaxId());
    EXPECT_TRUE(currentClient->isPremium());
    EXPECT_EQ(130, currentClient->getPoints());
    EXPECT_TRUE(credential == currentClient->getCredential());

    currentClient = clientM.get(++position);

    //Ricardo-Macedo 999999999 basic 300 ricM ricardo_948
    credential = {"ricM", "ricardo_948"};
    EXPECT_EQ("Ricardo Macedo", currentClient->getName());
    EXPECT_EQ(Person::DEFAULT_TAX_ID, currentClient->getTaxId());
    EXPECT_FALSE(currentClient->isPremium());
    EXPECT_EQ(300, currentClient->getPoints());
    EXPECT_TRUE(credential == currentClient->getCredential());

    clientMInitial.write(path);
}

TEST(WorkerManager, has_worker){
    Worker worker1("Francisco Ferreira", 948);
    Worker worker2("Margarida Ferraz", 849);
    WorkerManager wm;

    EXPECT_FALSE(wm.has(&worker1));
    EXPECT_FALSE(wm.has(&worker2));

    wm.add("Francisco Ferreira", 948);

    EXPECT_TRUE(wm.has(&worker1));
    EXPECT_FALSE(wm.has(&worker2));

    wm.add("Margarida Ferraz", 849);

    EXPECT_TRUE(wm.has(&worker1));
    EXPECT_TRUE(wm.has(&worker2));
}

TEST(WorkerManager, get_worker_by_position){
    WorkerManager workerM;
    Worker* worker1 = workerM.add("Alvaro Campos");
    Worker* worker2 = workerM.add("Henrique Vaz");
    Worker* worker3 = workerM.add("Sofia Rebelo");
    unsigned position = 0;

    EXPECT_TRUE(*worker1 == *workerM.get(position));
    EXPECT_TRUE(*worker2 == *workerM.get(++position));
    EXPECT_TRUE(*worker3 == *workerM.get(++position));
}

TEST(WorkerManager, get_worker_by_taxID){
    WorkerManager workerM;
    Worker* worker1 = workerM.add("Alvaro Campos", Person::DEFAULT_TAX_ID);
    Worker* worker2 = workerM.add("Henrique Vaz", 123812321);
    Worker* worker3 = workerM.add("Sofia Rebelo", 495483123);

    EXPECT_TRUE(*worker1 == *workerM.getWorker(Person::DEFAULT_TAX_ID));
    EXPECT_TRUE(*worker2 == *workerM.getWorker(123812321));
    EXPECT_TRUE(*worker3 == *workerM.getWorker(495483123));
}

TEST(WorkerManager, get_less_busy_worker){
    Store store("Aeda");
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Ricardo Macedo");
    Client* client2 = clientM.add("Joana Moreira");
    Worker* worker1 = workerM.add("Jose Figueiras", 890);
    Worker* worker2 = workerM.add("Madalena Faria", 980);

    EXPECT_EQ(0, worker1->getUndeliveredOrders());
    EXPECT_EQ(0, worker2->getUndeliveredOrders());
    EXPECT_TRUE(*worker1 == *(workerM.getLessBusyWorker()));

    Order* order1 = orderM.add(client1);

    EXPECT_EQ(1,worker1->getUndeliveredOrders());
    EXPECT_EQ(0, worker2->getUndeliveredOrders());
    EXPECT_TRUE(*worker2 == *(workerM.getLessBusyWorker()));

    Order* order2 = orderM.add(client2);

    EXPECT_EQ(1, worker1->getUndeliveredOrders());
    EXPECT_EQ(1, worker2->getUndeliveredOrders());
    EXPECT_TRUE(*worker1 == *(workerM.getLessBusyWorker()));
}

TEST(WorkerManager, set_salary){
    WorkerManager workerM;
    Worker* worker1 = workerM.add("Francisco Ferreira", 9665679,948);
    Worker* worker2 = workerM.add("Margarida Ferraz", 54498698,849);
    unsigned position = 0;

    EXPECT_FLOAT_EQ(948, workerM.get(position)->getSalary());
    EXPECT_FLOAT_EQ(849, workerM.get(++position)->getSalary());

    position = 0;
    workerM.setSalary(position, 900);
    workerM.setSalary(++position, 950);

    EXPECT_THROW(workerM.setSalary(++position, 950), InvalidPersonPosition);
    EXPECT_THROW(workerM.setSalary(++position, 950), InvalidPersonPosition);
    EXPECT_FLOAT_EQ(900, worker1->getSalary());
    EXPECT_FLOAT_EQ(950, worker2->getSalary());
}

TEST(WorkerManager, add_worker){
    Worker w1("Francisco Ferreira", 999999999,948);
    Worker w2("Joana Teixeira", 999999999, 892);
    Worker w3("Margarida Ferraz", 999999999, 849);
    WorkerManager workerM;
    unsigned position = 0;

    EXPECT_TRUE(workerM.getAll().empty());

    Worker* worker1 = workerM.add("Francisco Ferreira", 948);

    EXPECT_EQ(1, workerM.getAll().size());
    EXPECT_TRUE(*worker1 == *workerM.get(position));

    Worker* worker2 = workerM.add("Joana Teixeira", 999999999, 892);
    position = 0;

    EXPECT_EQ(2, workerM.getAll().size());
    EXPECT_TRUE(*worker1 == *workerM.get(position));
    EXPECT_TRUE(*worker2 == *workerM.get(++position));

    Worker* worker3 = workerM.add("Margarida Ferraz", 999999999, 849);
    position = 0;

    EXPECT_EQ(3, workerM.getAll().size());
    EXPECT_TRUE(*worker1 == *workerM.get(position));
    EXPECT_TRUE(*worker2 == *workerM.get(++position));
    EXPECT_TRUE(*worker3 == *workerM.get(++position));
    EXPECT_TRUE(workerM.getAll().size() == 3);
}

TEST(WorkerManager, remove_worker_by_pointer){
    WorkerManager workerM;
    Worker* worker1 = workerM.add("Francisco Ferreira", 999999999, 948);
    Worker* worker2 = workerM.add("Joana Teixeira", 999999999, 892);
    Worker* worker3 = workerM.add("Margarida Ferraz", 999999999, 849);
    unsigned position = 0;

    EXPECT_EQ(3, workerM.getAll().size());
    EXPECT_TRUE(*worker1 == *workerM.get(position));
    EXPECT_TRUE(*worker2 == *workerM.get(++position));
    EXPECT_TRUE(*worker3 == *workerM.get(++position));

    workerM.remove(worker1);
    position = 0;

    EXPECT_EQ(2, workerM.getAll().size());
    EXPECT_TRUE(*worker2 == *workerM.get(position));
    EXPECT_TRUE(*worker3 == *workerM.get(++position));

    workerM.remove(worker2);
    position = 0;

    EXPECT_EQ(1, workerM.getAll().size());
    EXPECT_TRUE(*worker3 == *workerM.get(position));

    workerM.remove(worker3);

    EXPECT_TRUE(workerM.getAll().empty());
    EXPECT_THROW(workerM.remove(worker1), PersonDoesNotExist);
    EXPECT_THROW(workerM.remove(worker2), PersonDoesNotExist);
    EXPECT_THROW(workerM.remove(worker3), PersonDoesNotExist);
}

TEST(WorkerManager, remove_worker_by_position){
    WorkerManager workerM;
    Worker* worker1 = workerM.add("Francisco Ferreira", 999999999, 948);
    Worker* worker2 = workerM.add("Joana Teixeira", 999999999, 892);
    Worker* worker3 = workerM.add("Margarida Ferraz", 999999999, 849);
    unsigned position = 0, positionToRemove = 0;

    EXPECT_EQ(3, workerM.getAll().size());
    EXPECT_THROW(workerM.remove(3), InvalidPersonPosition);
    EXPECT_TRUE(*worker1 == *workerM.get(position));
    EXPECT_TRUE(*worker2 == *workerM.get(++position));
    EXPECT_TRUE(*worker3 == *workerM.get(++position));

    workerM.remove(positionToRemove);
    position = 0;

    EXPECT_EQ(2, workerM.getAll().size());
    EXPECT_THROW(workerM.remove(2), InvalidPersonPosition);
    EXPECT_TRUE(*worker2 == *workerM.get(position));
    EXPECT_TRUE(*worker3 == *workerM.get(++position));


    workerM.remove(positionToRemove);
    position = 0;

    EXPECT_EQ(1, workerM.getAll().size());
    EXPECT_THROW(workerM.remove(1), InvalidPersonPosition);
    EXPECT_TRUE(*worker3 == *workerM.get(position));

    workerM.remove(positionToRemove);

    EXPECT_TRUE(workerM.getAll().empty());
}

TEST(WorkerManager, read){
    WorkerManager workerM;

    EXPECT_THROW(workerM.read("/workers.txt"), FileNotFound);

    workerM.read("../../data/workers.txt");
    unsigned position = 0;
    Worker* currentWorker = workerM.get(position);

    //Julia-Mendes 2345 2001 julia sousenhora
    Credential credential = {"julia", "sousenhora"};
    EXPECT_EQ("Julia Mendes", currentWorker->getName());
    EXPECT_EQ(2345, currentWorker->getTaxId());
    EXPECT_EQ(2001, currentWorker->getSalary());
    EXPECT_TRUE(credential == currentWorker->getCredential());

    currentWorker = workerM.get(++position);

    //Maria-Gil 7978 2000 mg bolachas
    credential = {"mg", "bolachas"};
    EXPECT_EQ("Maria Gil", currentWorker->getName());
    EXPECT_EQ(7978, currentWorker->getTaxId());
    EXPECT_EQ(2000, currentWorker->getSalary());
    EXPECT_TRUE(credential == currentWorker->getCredential());

    currentWorker = workerM.get(++position);

    //Osvaldo-Ribeiro 32534 1500 osvaldo souoosvaldo
    credential = {"osvaldo", "souoosvaldo"};
    EXPECT_EQ("Osvaldo Ribeiro", currentWorker->getName());
    EXPECT_EQ(32534, currentWorker->getTaxId());
    EXPECT_EQ(1500, currentWorker->getSalary());
    EXPECT_TRUE(credential == currentWorker->getCredential());
}

TEST(WorkerManager, write){
    const std::string path = "../../data/workers.txt";
    WorkerManager workerMInitial;
    workerMInitial.read(path);
    WorkerManager workerM;

    EXPECT_THROW(workerM.write("/workers.txt"), FileNotFound);

    Worker* worker1 = workerM.add("Miguel Gomes", 4398331, 900, {"miuelGom", "m123g"});
    Worker* worker2 = workerM.add("Joana Moreira", 38470348, 1000, {"juMoreira", "joanaMoreira"});
    Worker* worker3 = workerM.add("Ricardo Macedo", Person::DEFAULT_TAX_ID, 870, {"ricM", "ricardo_948"});

    workerM.write(path);
    workerM.read(path);
    unsigned position = 0;
    Worker* currentWorker = workerM.get(position);

    //Miguel-Gomes 4398331 900 miuelGom m123g
    Credential credential = {"miuelGom", "m123g"};
    EXPECT_EQ("Miguel Gomes", currentWorker->getName());
    EXPECT_EQ(4398331, currentWorker->getTaxId());
    EXPECT_EQ(900, currentWorker->getSalary());
    EXPECT_TRUE(credential == currentWorker->getCredential());

    currentWorker = workerM.get(++position);

    //Joana-Moreira 38470348 1000 juMoreira joanaMoreira
    credential = {"juMoreira", "joanaMoreira"};
    EXPECT_EQ("Joana Moreira", currentWorker->getName());
    EXPECT_EQ(38470348, currentWorker->getTaxId());
    EXPECT_EQ(1000, currentWorker->getSalary());
    EXPECT_TRUE(credential == currentWorker->getCredential());

    currentWorker = workerM.get(++position);

    //Ricardo-Macedo 999999999 870 ricM ricardo_948
    credential = {"ricM", "ricardo_948"};
    EXPECT_EQ("Ricardo Macedo", currentWorker->getName());
    EXPECT_EQ(Person::DEFAULT_TAX_ID, currentWorker->getTaxId());
    EXPECT_EQ(870, currentWorker->getSalary());
    EXPECT_TRUE(credential == currentWorker->getCredential());

    workerMInitial.write(path);
}

TEST(ProductManager, has){
    Bread bread("Pao de alfarroba", 1.20, false);
    Cake cake("Bolo de chocolate", 1, CakeCategory::SPONGE);
    ProductManager productM;
    Bread* bread1 = productM.addBread("Pao de sementes", 0.8, true);
    Cake* cake1 = productM.addCake("Tarte de bolacha", 3.40, CakeCategory::PIE);

    EXPECT_FALSE(productM.has(&bread));
    EXPECT_TRUE(productM.has(bread1));
    EXPECT_FALSE(productM.has(&cake));
    EXPECT_TRUE(productM.has(cake1));
}

TEST(ProductManager, get_by_position){
    ProductManager productM;
    Bread* bread = productM.addBread("Pao de sementes", 0.8, true);
    Cake* cake = productM.addCake("Tarte de bolacha", 3.40, CakeCategory::PIE);
    unsigned position = 0; Product* currentProduct = productM.get(position);

    EXPECT_TRUE(*static_cast<Product*>(bread) == *currentProduct);

    currentProduct = productM.get(++position);

    EXPECT_TRUE(*static_cast<Product*>(cake) == *currentProduct);
}

TEST(ProductManager, get_by_string_and_price){
    ProductManager productM;
    Bread* bread = productM.addBread("Pao de sementes", 0.8, true);
    Cake* cake = productM.addCake("Tarte de bolacha", 3.40, CakeCategory::PIE);

    Product* currentProduct = productM.get("Pao de sementes", 0.8);
    EXPECT_TRUE(*static_cast<Product*>(bread) == *currentProduct);

    currentProduct = productM.get("Tarte de bolacha", 3.40);
    EXPECT_TRUE(*static_cast<Product*>(cake) == *currentProduct);
}

TEST(ProductManager, add_bread) {
    ProductManager productM;

    EXPECT_EQ(0, productM.getAll().size());

    Bread hugeBread("Pao de sementes", 0.2, false);
    Bread* addedBread = productM.addBread("Pao de sementes", 0.2, false);
    unsigned position = 0;

    EXPECT_EQ(1, productM.getAll().size());
    EXPECT_EQ("Pao de sementes", productM.get(position)->getName());
    EXPECT_FLOAT_EQ(0.2, productM.get(position)->getPrice());
}

TEST(ProductManager, add_cake){
    ProductManager productM;

    EXPECT_EQ(0, productM.getAll().size());

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Cake* addedCake = productM.addCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    unsigned position = 0;

    EXPECT_EQ(1, productM.getAll().size());
    EXPECT_TRUE(meatCake == *addedCake);
    EXPECT_EQ("Bolo com molho de carne", productM.get(position)->getName());
    EXPECT_FLOAT_EQ(1, productM.get(position)->getPrice());
}

TEST(ProductManager, remove_by_pointer){
    Bread bread1("Pao de cereais", 0.9, false);
    ProductManager productM;
    Bread* bread = productM.addBread("Pao de sementes", 0.8, true);
    Cake* cake = productM.addCake("Tarte de bolacha", 3.40, CakeCategory::PIE);

    EXPECT_EQ(1, productM.getBreads().size());
    EXPECT_EQ(1, productM.getCakes().size());
    EXPECT_EQ(2, productM.getAll().size());

    productM.remove(bread);

    EXPECT_TRUE(productM.getBreads().empty());
    EXPECT_EQ(1, productM.getCakes().size());
    EXPECT_EQ(1, productM.getAll().size());
    EXPECT_TRUE(*cake == **productM.getCakes().begin());

    productM.remove(cake);

    EXPECT_TRUE(productM.getBreads().empty());
    EXPECT_TRUE(productM.getCakes().empty());
    EXPECT_TRUE(productM.getAll().empty());

    EXPECT_THROW(productM.remove(&bread1), ProductDoesNotExist);
}

TEST(ProductManager, remove_by_position){
    ProductManager productM;
    Bread* bread = productM.addBread("Pao de sementes", 0.8, true);
    Cake* cake = productM.addCake("Tarte de bolacha", 3.40, CakeCategory::PIE);
    unsigned position = 0;

    EXPECT_EQ(1, productM.getBreads().size());
    EXPECT_EQ(1, productM.getCakes().size());
    EXPECT_EQ(2, productM.getAll().size());

    productM.remove(position);

    EXPECT_TRUE(productM.getBreads().empty());
    EXPECT_EQ(1, productM.getCakes().size());
    EXPECT_EQ(1, productM.getAll().size());
    EXPECT_TRUE(*cake == **productM.getCakes().begin());

    productM.remove(position);

    EXPECT_TRUE(productM.getBreads().empty());
    EXPECT_TRUE(productM.getCakes().empty());
    EXPECT_TRUE(productM.getAll().empty());
}

TEST(ProductManager, read){
    ProductManager productM;

    EXPECT_THROW(productM.read("/products.txt"), FileNotFound);

    productM.read("../../data/products.txt");
    unsigned position = 0;
    Cake* cake = *productM.getCakes().begin();

    //Bolo-crocante 15 Crunchy-Cake
    EXPECT_EQ("Bolo crocante", cake->getName());
    EXPECT_FLOAT_EQ(15, cake->getPrice());
    EXPECT_EQ(CakeCategory::CRUNCHY, cake->getCategory());

    Bread* bread = *productM.getBreads().begin();

    //Pao-da-avo 1 big
    EXPECT_EQ("Pao da avo", bread->getName());
    EXPECT_FLOAT_EQ(1, bread->getPrice());
    EXPECT_FALSE(bread->isSmall());
}

TEST(ProductManager, write){
    std::string path = "../../data/products.txt";
    ProductManager productMInitial; productMInitial.read(path);
    ProductManager productM;
    Bread* bread = productM.addBread("Pao de sementes", 0.8, true);
    Cake* cake = productM.addCake("Tarte de bolacha", 3.40, CakeCategory::PIE);

    EXPECT_THROW(productM.read("/products.txt"), FileNotFound);

    productM.write(path);
    productM.read(path);
    unsigned position = 0;
    Cake* cake1 = *productM.getCakes().begin();

    //Tarte-de-bolacha 3.40 Pie
    EXPECT_EQ("Tarte de bolacha", cake1->getName());
    EXPECT_FLOAT_EQ(3.4, cake1->getPrice());
    EXPECT_EQ(CakeCategory::PIE, cake1->getCategory());

    Bread* bread1 = *productM.getBreads().begin();

    //Pao-de-sementes 0.8 small
    EXPECT_EQ("Pao de sementes", bread1->getName());
    EXPECT_FLOAT_EQ(0.8, bread1->getPrice());
    EXPECT_TRUE(bread1->isSmall());

    productMInitial.write(path);
}

TEST(OrderManager, has){
    ProductManager productM; ClientManager clientM; WorkerManager workerM; LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);
    Worker* worker = workerM.add("Josue Tome", 928);

    Client* client1 = clientM.add("Carlos Caetano");
    Date date1(10, 4, 2020, 19, 30);
    Order order1(*client1, *worker, Order::DEFAULT_LOCATION, date1);

    Client* client2 = clientM.add("Fernando Castro");
    Date date2(23, 7, 2020, 12, 30);
    Order* order2 = orderM.add(client2, worker, Order::DEFAULT_LOCATION, date2);

    EXPECT_FALSE(orderM.has(&order1));
    EXPECT_TRUE(orderM.has(order2));
}

TEST(OrderManager, get_by_position_client_and_worker){
    ProductManager productM; ClientManager clientM; WorkerManager workerM; LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);
    Worker* worker = workerM.add("Josue Tome", 928);

    Client* client1 = clientM.add("Carlos Caetano");
    Date date1(10, 4, 2020, 19, 30);
    Order* order1 = orderM.add(client1, worker, Order::DEFAULT_LOCATION, date1);
    Date date2(23, 7, 2020, 12, 30);
    Order* order2 = orderM.add(client1, worker, Order::DEFAULT_LOCATION, date2);

    EXPECT_TRUE(*order1 == *orderM.get(0, client1));
    EXPECT_TRUE(*order2 == *orderM.get(1, client1));
    EXPECT_TRUE(*order1 == *orderM.get(0, nullptr, worker));
    EXPECT_TRUE(*order2 == *orderM.get(1, nullptr, worker));
}

TEST(OrderManager, get_client_orders){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Ricardo Macedo");
    Client client2("Bruno Mendes");
    Worker* worker = workerM.add("Madalena Faria", 980);
    Order order(*client1, *worker);

    EXPECT_TRUE(orderM.get(client1).empty());
    EXPECT_THROW(orderM.get(&client2), PersonDoesNotExist);

    Order* order1 = orderM.add(client1);

    EXPECT_EQ(1, orderM.get(client1).size());
    EXPECT_TRUE(order == *order1);

    Order* order2 = orderM.add(client1);

    EXPECT_EQ(2, orderM.get(client1).size());
    EXPECT_TRUE(order == *order2);
}

TEST(OrderManager, get_worker_orders){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client = clientM.add("Ricardo Macedo");
    Worker* worker1 = workerM.add("Madalena Faria", 980);
    Worker worker2("Rafael Macedo", 985);
    Order order(*client, *worker1);

    EXPECT_TRUE(orderM.get(worker1).empty());
    EXPECT_THROW(orderM.get(&worker2), PersonDoesNotExist);

    Order* order1 = orderM.add(client);

    EXPECT_EQ(1, orderM.get(worker1).size());
    EXPECT_TRUE(order == *order1);

    Order* order2 = orderM.add(client);

    EXPECT_EQ(2, orderM.get(worker1).size());
    EXPECT_TRUE(order == *order2);
}

TEST(OrderManager, get_location_orders){
    ProductManager productM; ClientManager clientM; WorkerManager workerM; LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);
    std::string location = "Gaia";
    locationM.add(location);

    Client* client = clientM.add("Ricardo Macedo");
    Worker* worker = workerM.add("Madalena Faria", 980);
    Date date1(19, 10, 2020, 17, 30);
    Order* order1 = orderM.add(client, worker, location, date1);
    Date date2(21, 10, 2020, 18, 10);
    Order* order2 = orderM.add(client, worker, location, date2);
    unsigned position = 0;

    EXPECT_EQ(2, orderM.get(location).size());
    EXPECT_TRUE(*order1 == *orderM.get(location).at(position));
    EXPECT_TRUE(*order2 == *orderM.get(location).at(++position));
}

TEST(OrderManager, add_order){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);
    Client* client = clientM.add("Fernando Castro");
    Worker* worker = workerM.add("Josue Tome", 928);
    Order order(*client, *worker);

    EXPECT_TRUE(orderM.getAll().empty());

    Order* order1 = orderM.add(client);

    EXPECT_EQ(1, orderM.getAll().size());
    EXPECT_TRUE(order == *order1);
}

TEST(OrderManager, add_order_with_worker){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);
    std::string location  = "Guarda"; locationM.add(location);
    Date date(16, 11, 2020, 2, 30);
    Client* client = clientM.add("Fernando Castro");
    Worker* worker = workerM.add("Josue Tome", 928);
    Order order(*client, *worker, location, date);

    EXPECT_TRUE(orderM.getAll().empty());

    Order* order1 = orderM.add(client, location, date);

    EXPECT_EQ(1, orderM.getAll().size());
    EXPECT_TRUE(order == *order1);
}

TEST(OrderManager, remove_order){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Adelaide Santos");
    Client* client2 = clientM.add("Bruno Mendes");
    Client* client3 = clientM.add("Ricardo Macedo");
    Client* client4 = clientM.add("Ze Manel");
    Worker* worker = workerM.add("Madalena Faria", 980);
    Order order(*client1, *worker);

    EXPECT_THROW(orderM.remove(&order), OrderDoesNotExist);

    Order* order1 = orderM.add(client1);
    Order* order2 = orderM.add(client2);
    Order* order3 = orderM.add(client3);
    orderM.remove(order1);
    unsigned position = 0;

    EXPECT_EQ(2, orderM.getAll().size());
    EXPECT_TRUE(*order2 == *orderM.get(position));
    EXPECT_TRUE(*order3 == *orderM.get(++position));

    orderM.remove(order2);
    position = 0;

    EXPECT_EQ(1, orderM.getAll().size());
    EXPECT_TRUE(*order3 == *orderM.get(position));

    orderM.remove(order3);
    position = 0;

    EXPECT_TRUE(orderM.getAll().empty());//Throw exception  for empty orders
}

TEST(OrderManager, sort_orders){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    std::string location = "Lisboar"; locationM.add(location);
    Date date2(25, 11, 2019, 3, 40);
    Date date1(16, 11, 2020, 2, 30);
    Client* client1 = clientM.add("Fernando Castro");
    Client* client2 = clientM.add("Catia Fernandes");
    Worker* worker = workerM.add("Josue Tome", 928);
    Order order1(*client1, *worker, location, date1);
    Order order2(*client2, *worker, location, date2);

    Order* order3 = orderM.add(client1, location, date1);
    Order* order4 = orderM.add(client2, location, date2);
    unsigned position = 0;

    EXPECT_TRUE(order1 == *order3);
    EXPECT_TRUE(*order3 == *orderM.get(position));
    EXPECT_TRUE(order2 == *order4);
    EXPECT_TRUE(*order4 == *orderM.get(++position));
}

TEST(OrderManager, get_order_by_position){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Ricardo Macedo");
    Client* client2 = clientM.add("Rosalia Martins");
    Worker* worker = workerM.add("Madalena Faria", 980);
    Order order1(*client1, *worker);
    Order order2(*client2, *worker);

    EXPECT_TRUE(orderM.getAll().empty());
    orderM.add(client1);
    unsigned position = 0;

    EXPECT_EQ(1, orderM.getAll().size());
    EXPECT_TRUE(order1 == *orderM.get(position));

    orderM.add(client2);

    EXPECT_EQ(2, orderM.getAll().size());
    EXPECT_TRUE(order1 == *orderM.get(position));
    EXPECT_TRUE(order2 == *orderM.get(++position));
    EXPECT_THROW(orderM.get(++position), InvalidOrderPosition);
}

TEST(OrderManager, read){
    std::string path = "../../data/orders.txt";
    ProductManager productM; ClientManager clientM; WorkerManager workerM; LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    EXPECT_THROW(orderM.read("/orders.txt"), FileNotFound);
    EXPECT_THROW(orderM.read(path), PersonDoesNotExist);

    productM.read("../../data/products.txt");
    clientM.read("../../data/clients.txt");
    workerM.read("../../data/workers.txt");
    locationM.read("../../data/locations.txt");
    orderM.read(path);
    unsigned position = 0;
    Order* currentOrder = orderM.getAll().at(position);

    //324564 32534 12/06/2020 18:34 Head-Office 5
    //Bolo-crocante 15 1
    //Pao-de-cereais 0.5 1
    EXPECT_EQ(324564, currentOrder->getClient()->getTaxId());
    EXPECT_EQ(32534, currentOrder->getWorker()->getTaxId());
    EXPECT_EQ("12/06/2020 18:34", currentOrder->getRequestDate().getCompleteDate());
    EXPECT_EQ("Head Office", currentOrder->getDeliverLocation());
    EXPECT_TRUE(currentOrder->wasDelivered());
    EXPECT_EQ(5, currentOrder->getClientEvaluation());
    EXPECT_EQ("Bolo crocante", (currentOrder->getProducts().begin())->first->getName());
    EXPECT_FLOAT_EQ(15, (currentOrder->getProducts().begin())->first->getPrice());
    EXPECT_EQ(1, (currentOrder->getProducts().begin())->second);
    EXPECT_EQ("Pao de cereais", (++currentOrder->getProducts().begin())->first->getName());
    EXPECT_FLOAT_EQ(0.5, (++currentOrder->getProducts().begin())->first->getPrice());
    EXPECT_EQ(1, (++currentOrder->getProducts().begin())->second);

    currentOrder = orderM.getAll().at(++position);

    //324564 32534 12/12/2020 14:45 Lisboa
    //Bolo-esponja 30 1
    //Pao-da-avo 1 1
    //Pao-de-sementes 0.8 1
    EXPECT_EQ(324564, currentOrder->getClient()->getTaxId());
    EXPECT_EQ(32534, currentOrder->getWorker()->getTaxId());
    EXPECT_EQ("12/12/2020 14:45", currentOrder->getRequestDate().getCompleteDate());
    EXPECT_EQ("Lisboa", currentOrder->getDeliverLocation());
    EXPECT_FALSE(currentOrder->wasDelivered());
    EXPECT_EQ("Bolo esponja", (currentOrder->getProducts().begin())->first->getName());
    EXPECT_FLOAT_EQ(30, (currentOrder->getProducts().begin())->first->getPrice());
    EXPECT_EQ(1, (currentOrder->getProducts().begin())->second);
    EXPECT_EQ("Pao da avo", (++currentOrder->getProducts().begin())->first->getName());
    EXPECT_FLOAT_EQ(1, (++currentOrder->getProducts().begin())->first->getPrice());
    EXPECT_EQ(1, (++currentOrder->getProducts().begin())->second);
}

TEST(OrderManager, write){
    std::string path = "../../data/orders.txt";
    ProductManager productMInit; ClientManager clientMInit; WorkerManager workerMInit; LocationManager locationMInit;
    OrderManager orderMInit(&productMInit, &clientMInit, &workerMInit, &locationMInit);
    productMInit.read("../../data/products.txt");
    clientMInit.read("../../data/clients.txt");
    workerMInit.read("../../data/workers.txt");
    locationMInit.read("../../data/locations.txt");
    orderMInit.read(path);

    ProductManager productM; ClientManager clientM; WorkerManager workerM; LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);
    Client* client = clientM.add("Joao Miguel", 123823);
    Worker* worker = workerM.add("Mario Cordeiro", 823823);
    Cake* cake = productM.addCake("Bolo de arroz", 1);
    Date date(23, 5, 2019, 21, 30);
    locationM.add("Porto");
    Order* order = orderM.add(client, worker, "Porto", date);
    order->addProduct(cake, 1);

    EXPECT_THROW(orderM.write("l/orders.txt"), FileNotFound);

    orderM.write(path);
    orderM.read(path);
    unsigned position = 0;
    Order* currentOrder = orderM.getAll().at(position);

    //123823 823823 23/05/2019 21:30 Porto
    //Bolo-de-arroz 1 1
    EXPECT_EQ(123823, currentOrder->getClient()->getTaxId());
    EXPECT_EQ(823823, currentOrder->getWorker()->getTaxId());
    EXPECT_EQ("23/05/2019 21:30", currentOrder->getRequestDate().getCompleteDate());
    EXPECT_EQ("Porto", currentOrder->getDeliverLocation());
    EXPECT_FALSE(currentOrder->wasDelivered());
    EXPECT_EQ("Bolo de arroz", (currentOrder->getProducts().begin())->first->getName());
    EXPECT_FLOAT_EQ(1, (currentOrder->getProducts().begin())->first->getPrice());
    EXPECT_EQ(2, (currentOrder->getProducts().begin())->second);

    //Rests orders.txt
    orderMInit.write(path);
}

TEST(LocationManager, has){
    LocationManager locationM;
    std::string location1 = "Braga";
    locationM.add(location1);
    std::string location2 = "Gaia";

    EXPECT_TRUE(locationM.has(location1));
    EXPECT_FALSE(locationM.has(location2));
}

TEST(LocationManager, add){
    LocationManager locationM;

    EXPECT_EQ(1, locationM.getAll().size());
    EXPECT_EQ(Order::DEFAULT_LOCATION, *locationM.getAll().begin());

    locationM.add("Braga");

    EXPECT_EQ(2, locationM.getAll().size());
    EXPECT_EQ("Braga", *(locationM.getAll().begin()));
}

TEST(LocationManager, remove_by_string){
    LocationManager locationM;

    EXPECT_THROW(locationM.remove("Braga"), LocationDoesNotExist);
    EXPECT_EQ(1, locationM.getAll().size());
    EXPECT_EQ(Order::DEFAULT_LOCATION, *locationM.getAll().begin());

    locationM.add("Aveiro");
    locationM.add("Braga");
    locationM.remove("Braga");

    EXPECT_EQ(2, locationM.getAll().size());
    EXPECT_EQ("Aveiro", *locationM.getAll().begin());
}

TEST(LocationManager, remove_by_position){
    LocationManager locationM;

    EXPECT_THROW(locationM.remove("Braga"), LocationDoesNotExist);
    EXPECT_EQ(1, locationM.getAll().size());
    EXPECT_EQ(Order::DEFAULT_LOCATION, *locationM.getAll().begin());

    locationM.add("Aveiro");
    locationM.add("Braga");
    locationM.remove(1);

    EXPECT_EQ(2, locationM.getAll().size());
    EXPECT_EQ("Aveiro", *locationM.getAll().begin());
}

TEST(LocationManager, read){
    LocationManager locationM;
    locationM.read("../../data/locations.txt");

    //Head-Office
    //Lisboa
    EXPECT_EQ("Head Office", *locationM.getAll().begin());
    EXPECT_EQ("Lisboa", *(++locationM.getAll().begin()));
}

TEST(LocationManager, write){
    std::string path = "../../data/locations.txt";
    LocationManager locationMInit;
    locationMInit.read(path);

    LocationManager locationM;
    locationM.add("Guarda");
    locationM.write(path);
    locationM.read(path);

    //Guarda
    //Head-Office
    EXPECT_EQ(2, locationM.getAll().size());
    EXPECT_EQ("Guarda", *locationM.getAll().begin());
    EXPECT_EQ("Head Office", *(++locationM.getAll().begin()));

    locationMInit.write(path);
}

TEST(OrderManager, sortByClient){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;
    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Ricardo Macedo");
    Client* client2 = clientM.add("Rosalia Martins");
    Client* client3 = clientM.add("Beatriz Mendes");

    Worker* worker1 = workerM.add("Madalena Faria", 980);
    Worker* worker2 = workerM.add("Maria Miguel", 980);
    Worker* worker3 = workerM.add("Ana Santos", 980);

    orderM.add(client1, worker1);
    orderM.add(client2,worker2);
    orderM.add(client3, worker3);
    orderM.sortByClient();
    EXPECT_EQ("Beatriz Mendes", orderM.getAll().at(0)->getClient()->getName());
}

TEST(OrderManager, sortByWorker){
    ProductManager productM;
    ClientManager clientM;
    WorkerManager workerM;
    LocationManager locationM;

    OrderManager orderM(&productM, &clientM, &workerM, &locationM);

    Client* client1 = clientM.add("Ricardo Macedo");
    Client* client2 = clientM.add("Rosalia Martins");
    Client* client3 = clientM.add("Beatriz Mendes");

    Worker* worker1 = workerM.add("Madalena Faria", 980);
    Worker* worker2 = workerM.add("Maria Miguel", 980);
    Worker* worker3 = workerM.add("Ana Santos", 980);

    orderM.add(client1, worker1);
    orderM.add(client2,worker2);
    orderM.add(client3, worker3);
    orderM.sortByWorker();
    EXPECT_EQ("Ana Santos", orderM.getAll().at(0)->getWorker()->getName());
}

