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

    void viewOrders(Client* client = nullptr);
    void expandOrder(Order* order) const;
    void managePersonalData(Person* person);

    static void changeCredential(Person* person);
    static void changeName(Person* person);
    static void changeTaxID(Person* person);
protected:
    Person* _person;
};


#endif //FEUP_AEDA_PROJECT_DASHBOARD_H
