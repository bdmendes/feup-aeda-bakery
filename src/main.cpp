#include <iostream>
#include <ui/menu/intro/intro_menu.h>

#include "model/store/store.h"
#include "ui/ui.h"

int main() {
    Store s;
    s.boss.setLogged(true);
    s.productManager.read("../../data/products.txt");
    s.productManager.write("../../data/written_products.txt");
    s.clientManager.read("../../data/clients.txt");
    s.clientManager.write("../../data/written_clients.txt");
    s.workerManager.read("../../data/workers.txt");
    s.workerManager.write("../../data/written_workers");
    s.orderManager.read("../../data/orders.txt");
    s.orderManager.write("../../data/written_orders.txt");
    IntroMenu menu(s);
    menu.show();
}
