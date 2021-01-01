#ifndef FEUP_AEDA_PROJECT_BOSS_DASHBOARD_H
#define FEUP_AEDA_PROJECT_BOSS_DASHBOARD_H


#include <ui/ui.h>
#include "ui/dashboard/dashboard.h"

/**
 * The boss personal area.
 * Contains all functionality he needs to perform his actions, including special ones:
 * manage clients, manage store delivery locations, view quick stats
 */
class BossDashboard : public Dashboard {
public:
    /**
     * Create the dashboard
     * @param store which the boss runs
     */
    explicit BossDashboard(Store& store);

    /**
     * Shows what the boss can do and redirect to the chosen action.
     */
    void show() override;

private:
    /**
     * Show store workers.
     * Add new ones or fire current ones, provided they haven't been assigned to any order yet.
     * Change salaries.
     * @param location the location to be highlighted; if none, no highlight will be shown
     */
    void manageStaff(std::string location = {});

    /**
     * Ask which location to highlight (may be used for order and worker highlighting for the provided location)
     * @return the user input location
     */
    std::string askLocationHighlight() const;

    /**
     * Add new worker: provide name, taxID and salary.
     */
    void addWorker();

    /**
     * Show store delivery locations.
     * Add new ones or remove old ones (except the Head Office which must exist)
     */
    void manageLocations();

    /**
     * Add new store delivery location: provide name.
     */
    void addLocation();

    /**
     * Show total revenue, and the store mean client evaluation.
     */
    void showStats() const;

    /**
     * The boss who's logged in.
     */
    Boss* _boss;
};

#endif //FEUP_AEDA_PROJECT_BOSS_DASHBOARD_H
