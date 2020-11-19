#ifndef FEUP_AEDA_PROJECT_INTRO_MENU_H
#define FEUP_AEDA_PROJECT_INTRO_MENU_H

#include "ui/ui.h"

/**
 * The first UI page. Allows importing/exporting data and entering the store management
 */
class IntroMenu : public UI {
public:
    /**
     * Create menu to show the main page
     * @param s store which info gets accessed and manipulated
     */
    explicit IntroMenu(Store& s);

    /**
     * Show the main menu and command handler
     */
    void show() override;

    /**
     * Asks the user for the "data" folder path from which to import the store data
     */
    void importData();

    /**
     * Asks the user for the "data" folder to which the store data will get exported
     */
    void exportData();
};

#endif //FEUP_AEDA_PROJECT_INTRO_MENU_H
