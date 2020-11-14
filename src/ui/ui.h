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
    static std::string readCommand();
    static bool isValid(std::string input, const std::vector<std::string>& args, const std::string& cmd = {});
    static bool isValid(std::string input, const std::string& arg, const std::string& cmd = {});
    static bool isValid(std::string input, int maxIdxArg, const std::string& cmd = {});
    static void printOptions(const std::vector<std::string>& options, bool index = true);
    static void printError(bool index = true);
    static void printLogo();
    static const char* BACK;

    Store& _store;
};

#endif //FEUP_AEDA_PROJECT_UI_H
