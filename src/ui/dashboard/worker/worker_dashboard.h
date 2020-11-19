#ifndef FEUP_AEDA_PROJECT_WORKER_DASHBOARD_H
#define FEUP_AEDA_PROJECT_WORKER_DASHBOARD_H

#include <ui/ui.h>
#include <ui/dashboard/dashboard.h>

/**
 * The worker personal area.
 * Provides all functionality to allow him to perform his actions in the store.
 */
class WorkerDashboard : public Dashboard {
public:
    /**
     * Create a new dashboard
     * @param store to which the worker belongs
     * @param worker who wants to access his personal area
     */
    WorkerDashboard(Store& store, Worker* worker);

    /**
     * Show what the worker can do, and redirect to the choosen action.
     */
    void show() override;

private:
    /**
     * The worker who's logged in.
     */
    Worker* _worker;
};


#endif //FEUP_AEDA_PROJECT_WORKER_DASHBOARD_H
