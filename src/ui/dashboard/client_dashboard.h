//
// Created by bdmendes on 14/11/20.
//

#ifndef FEUP_AEDA_PROJECT_CLIENT_DASHBOARD_H
#define FEUP_AEDA_PROJECT_CLIENT_DASHBOARD_H


#include <ui/ui.h>

class ClientDashboard : public UI{
public:
    ClientDashboard(Store& store, Client* client);
    void show() override;
private:
    Client* _client;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_DASHBOARD_H
