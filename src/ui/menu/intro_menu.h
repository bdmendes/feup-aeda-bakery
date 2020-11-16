//
// Created by bdmendes on 14/11/20.
//

#ifndef FEUP_AEDA_PROJECT_INTRO_MENU_H
#define FEUP_AEDA_PROJECT_INTRO_MENU_H

#include "ui/ui.h"

class LoginMenu;
class FileImportMenu;

class IntroMenu : public UI {
public:
    IntroMenu(Store& s);
    void show() override;
};


#endif //FEUP_AEDA_PROJECT_INTRO_MENU_H
