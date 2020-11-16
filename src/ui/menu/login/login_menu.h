//
// Created by bdmendes on 14/11/20.
//

#ifndef FEUP_AEDA_PROJECT_LOGIN_MENU_H
#define FEUP_AEDA_PROJECT_LOGIN_MENU_H

#include "ui/ui.h"

class BossDashboard;
class ClientDashboard;
class WorkerDashboard;

enum class PersonToShow {
    WORKER,
    CLIENT
};

class LoginMenu: public UI{
public:
    LoginMenu(Store& store);
    void show() override;
    void showPersons(PersonToShow person);
    void login(Person* person);
private:
    std::vector<Person*> _persons;
};


#endif //FEUP_AEDA_PROJECT_LOGIN_MENU_H
