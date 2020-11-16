//
// Created by bdmendes on 14/11/20.
//

#ifndef FEUP_AEDA_PROJECT_CLIENT_DASHBOARD_H
#define FEUP_AEDA_PROJECT_CLIENT_DASHBOARD_H


#include <ui/ui.h>
#include "ui/dashboard/dashboard.h"

class ClientDashboard : public Dashboard {
public:
    ClientDashboard(Store& store, Client* client);
    void show() override;

    void addOrder();
private:
    Client* _client;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_DASHBOARD_H
