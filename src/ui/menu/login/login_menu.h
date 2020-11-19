#ifndef FEUP_AEDA_PROJECT_LOGIN_MENU_H
#define FEUP_AEDA_PROJECT_LOGIN_MENU_H

#include "ui/ui.h"

/**
 * Contains the functionality to allow the user to choose its role on the store,
 * select himself from the list and then login to his personal area with his credentials
 */
class LoginMenu: public UI{
public:
    /**
     * Create login menu
     * @param store from which to get the persons registered
     */
    explicit LoginMenu(Store& store);

    /**
     * The person role chooser page
     */
    void show() override;

    /**
     * List the persons associated with the given role in the store,
     * so that he can choose who he is.
     * @param role - the person role in the store
     */
    void selectPerson(PersonRole role);

    /**
     * Ask the user for its credential.
     * Instantiate respective dashboard if login successful (or already logged in) and show it.
     * @param person who wants to enter personal area
     */
    void login(Person* person);
};

#endif //FEUP_AEDA_PROJECT_LOGIN_MENU_H
