#include <iostream>
#include <ui/menu/intro/intro_menu.h>

#include "model/store/store.h"
#include "ui/ui.h"

int main() {
    Store s;

    // some filling to debug
    s.workerManager.add("Alfredo",2000,923747);
    Worker* retiros = s.workerManager.add("Retiros",8950,394858);
    s.clientManager.add("Alface",true);
    Client* osvaldo = s.clientManager.add("Osvaldo",false,2389474);
    Product* bolo = s.productManager.addCake("Bolo ligeiro",2.20);
    Product* pao = s.productManager.addBread("Pao muito branco",0.12);
    Order* pedidoDoOsvaldo = s.orderManager.add(osvaldo);
    pedidoDoOsvaldo->addProduct(bolo,2);
    pedidoDoOsvaldo->addProduct(pao);

    IntroMenu menu(s);
    menu.show();
}
