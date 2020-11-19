#ifndef FEUP_AEDA_PROJECT_LOGIN_MENU_H
#define FEUP_AEDA_PROJECT_LOGIN_MENU_H

#include "ui/ui.h"

class LoginMenu: public UI{
public:
    explicit LoginMenu(Store& store);
    void show() override;
    void selectPerson(bool client);
    void login(Person* person);
};

#endif //FEUP_AEDA_PROJECT_LOGIN_MENU_H
