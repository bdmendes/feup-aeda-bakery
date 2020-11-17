//
// Created by bdmendes on 16/11/20.
//

#ifndef FEUP_AEDA_PROJECT_DASHBOARD_H
#define FEUP_AEDA_PROJECT_DASHBOARD_H


#include <ui/ui.h>

class Dashboard : public UI{
public:
    Dashboard(Store& store, Person* person);
    virtual ~Dashboard() = default;
    void show() override;

    void viewOrders(Client* client = nullptr, Worker* worker = nullptr);
    void expandOrder(Order* order);
    void editOrder(Order* order);

    void managePersonalData(Person* person);

    void manageStock();

    void printLogo(const std::string& detail) override;
protected:
    Person* _person;
private:
    static void changeCredential(Person* person);
    static void changeName(Person* person);
    void addBread();
    void addCake();
};


#endif //FEUP_AEDA_PROJECT_DASHBOARD_H
