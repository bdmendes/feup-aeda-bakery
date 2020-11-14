//
// Created by bdmendes on 14/11/20.
//

#ifndef FEUP_AEDA_PROJECT_FILE_MENU_H
#define FEUP_AEDA_PROJECT_FILE_MENU_H


#include "ui/ui.h"

class FileMenu : public UI{
public:
    FileMenu(Store& store);
    void show() override;
private:
    void importFiles();
    void exportFiles();
};


#endif //FEUP_AEDA_PROJECT_FILE_MENU_H
