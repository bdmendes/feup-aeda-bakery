//
// Created by bdmendes on 07/11/20.
//

#ifndef FEUP_AEDA_PROJECT_MENU_H
#define FEUP_AEDA_PROJECT_MENU_H

#include "../model/store/store.h"
#include "../util/util.h"

class Menu {
public:
    Menu(Store& store);
    void intro();
protected:
    static std::string readCommand(const std::string& message);
    static std::string isValid(const std::string& input,
                               const std::vector<std::string>& args, const std::string& cmd = "");
    static std::string isValid(const std::string& input,
                               const std::string& arg, const std::string& cmd = "");
    Store& _store;
    Person* _logged;
};

#endif //FEUP_AEDA_PROJECT_MENU_H
