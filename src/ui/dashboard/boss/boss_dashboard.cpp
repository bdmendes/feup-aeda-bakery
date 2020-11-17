//
// Created by bdmendes on 14/11/20.
//

#include "boss_dashboard.h"

BossDashboard::BossDashboard(Store &store) : Dashboard(store, &store.boss), _boss(&store.boss) {
}



void BossDashboard::show() {
    //
}

void BossDashboard::addWorker() {

}

