//
// Created by bdmendes on 07/11/20.
//

#ifndef FEUP_AEDA_PROJECT_MENU_H
#define FEUP_AEDA_PROJECT_MENU_H

#include "../model/store/store.h"

namespace menu {
    void logo();
    void intro(const Store& store = {});

    void login();

    void bossPanel();
    void clientPanel();
    void workerPanel();

    void orderOverview(bool allowDeliver = false, bool allowEvaluate = false);
    void orderDetails();
    void clientOverview();
    void workerOverview();
}

#endif //FEUP_AEDA_PROJECT_MENU_H
