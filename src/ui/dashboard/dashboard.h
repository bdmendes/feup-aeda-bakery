#ifndef FEUP_AEDA_PROJECT_DASHBOARD_H
#define FEUP_AEDA_PROJECT_DASHBOARD_H

#include <ui/ui.h>

/**
 * The interface from which all roles' dashboards derive.
 * Provides the functionality at least two different roles need to perform their actions:
 * -> All: edit account details, logout, manage associated orders
 * -> Worker, boss: manage stock, manage clients, manage orders
 */
class Dashboard : public UI{
public:
    /**
     * Create dashboard for the given person
     * @param store to which the person is associated
     * @param person who desires to enter personal area
     */
    Dashboard(Store& store, Person* person);

    /**
     * Destruct the dashboard
     */
    virtual ~Dashboard() = default;

    /**
     * Print store logo and known person info
     */
    void show() override;

    /**
     * Common to all dashboards; allows order condensed and expanded view and editing
     * @param client to which the orders are associated; if nullptr, all orders are shown
     * @param worker to which the orders are associated; if nullpter, all orders are shown
     */
    void manageOrders(Client* client = nullptr, Worker* worker = nullptr);

    /**
     * View order details: client, worker, request and deliver dates, deliver location, products and final price.
     * @param order from which to view details
     */
    void expandOrder(Order* order) const;

    /**
     * View order details and current store stock, to allow adding new products and removing old ones.
     * One can also change the deliver location.
     * @param order
     */
    void editOrder(Order* order);

    /**
     * Set order delivery location
     * @param order from which location to change
     */
    void setOrderLocation(Order* order);

    /**
     * Edit account details: name, taxID and credential.
     * If person is a client, allow also to change the premium state
     * @param person which data to change
     */
    void managePersonalData(Person* person);

    /**
     * Common to the boss and the workers.
     * View current stock, create new cake/bread or remove current ones.
     */
    void manageStock();

    /**
     * Common to the boss and the workers.
     * Register a new client to the store or kick a current one, providing he has never requested any order.
     */
    void manageClients();

    /**
     * Print uppercased blue store logo, followed by an hyphen, "<personName>'s Personal Area", another hyphen, and detail
     * @param detail to be displayed after the dashboard indicative
     */
    void printLogo(const std::string& detail) const override;

protected:
    /**
     * The person who's logged in
     */
    Person* _person;

private:
    /**
     * Ask for new username, confirmation, new password and confirmation and sets them
     * @param person who wants to change credentials
     */
    static void changeCredential(Person* person);

    /**
     * Ask for new name and sets it
     * @param person who wants to change name
     */
    static void changeName(Person* person);

    /**
     * Ask for new taxID and sets it
     * @param person who wants to change taxID
     */
    static void changeTaxID(Person* person);

    /**
     * Add a new bread: provide name, unit price and small attribute
     */
    void addBread();

    /**
     * Add a new cake: provide name, unit price and cake caregory attribute
     */
    void addCake();

    /**
     * Add a new client: provide name and taxID
     */
    void addClient();
};


#endif //FEUP_AEDA_PROJECT_DASHBOARD_H
