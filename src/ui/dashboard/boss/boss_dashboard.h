//
// Created by bdmendes on 14/11/20.
//

#ifndef FEUP_AEDA_PROJECT_BOSS_DASHBOARD_H
#define FEUP_AEDA_PROJECT_BOSS_DASHBOARD_H


#include <ui/ui.h>
#include "ui/dashboard/dashboard.h"

class BossDashboard : public Dashboard {
public:
    explicit BossDashboard(Store& store);
    void show() override;
private:
    void manageStaff();
    void addWorker();
    void showStats();
    Boss* _boss;
};


#endif //FEUP_AEDA_PROJECT_BOSS_DASHBOARD_H
