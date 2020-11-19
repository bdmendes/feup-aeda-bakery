#ifndef FEUP_AEDA_PROJECT_CLIENT_DASHBOARD_H
#define FEUP_AEDA_PROJECT_CLIENT_DASHBOARD_H


#include <ui/ui.h>
#include "ui/dashboard/dashboard.h"

/**
 * The client personal area.
 * Provides all functionality to allow him to perform his actions in the store.
 */
class ClientDashboard : public Dashboard {
public:
    /**
     * Create a new dashboard
     * @param store to which the client belongs
     * @param client who wants to access his personal area
     */
    ClientDashboard(Store& store, Client* client);

    /**
     * Show what the client can do and redirect to the chosen action.
     */
    void show() override;

private:
    /**
     * The client who's logged in.
     */
    Client* _client;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_DASHBOARD_H
