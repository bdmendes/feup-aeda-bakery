//
// Created by bdmendes on 14/11/20.
//

#ifndef FEUP_AEDA_PROJECT_BOSS_DASHBOARD_H
#define FEUP_AEDA_PROJECT_BOSS_DASHBOARD_H


#include <ui/ui.h>

class BossDashboard : public UI {
public:
    explicit BossDashboard(Store& store);
    void show() override;
};


#endif //FEUP_AEDA_PROJECT_BOSS_DASHBOARD_H
