#ifndef FEUP_AEDA_PROJECT_WORKER_DASHBOARD_H
#define FEUP_AEDA_PROJECT_WORKER_DASHBOARD_H

#include <ui/ui.h>
#include <ui/dashboard/dashboard.h>

class WorkerDashboard : public Dashboard {
public:
    WorkerDashboard(Store& store, Worker* worker);
    void show() override;
private:
    Worker* _worker;
};


#endif //FEUP_AEDA_PROJECT_WORKER_DASHBOARD_H
