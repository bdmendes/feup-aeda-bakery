//
// Created by bdmendes on 07/11/20.
//

#ifndef FEUP_AEDA_PROJECT_UI_H
#define FEUP_AEDA_PROJECT_UI_H

#include "model/store/store.h"
#include "util/util.h"

using namespace util;

class IntroMenu;

class UI {
public:
    explicit UI(Store& store);
    virtual void show() = 0;
protected:
    static std::string readCommand(bool lowCase = true);
    static bool isValid(std::string input, const std::vector<std::string>& args, const std::string& cmd = {});
    static bool isValid(std::string input, const std::string& arg, const std::string& cmd = {});
    static void printOptions(const std::vector<std::string>& options, bool index = false, std::string message = {});
    static void printError(bool index = false);
    static void printLogo();
    static const char* BACK;
    static const char* EXIT;
    Store& _store;
};

#endif //FEUP_AEDA_PROJECT_UI_H
