//
// Created by bdmendes on 07/11/20.
//

#ifndef FEUP_AEDA_PROJECT_UI_H
#define FEUP_AEDA_PROJECT_UI_H

#include "model/store/store.h"
#include "util/util.h"

using namespace util;

class UI {
public:
    explicit UI(Store& store);
    virtual void show() = 0;
protected:
    static std::string readCommand(bool lowCase = true);

    static bool validInput1Cmd(const std::string& input, const std::string &cmd);
    static bool validInput1Cmd1ArgDigit(const std::string& input, const std::string &cmd, bool acceptFloat = false);
    static bool validInput1Cmd1Arg(const std::string& input, const std::string &cmd, const std::string &arg);
    static bool validInput1Cmd2ArgsDigit(const std::string& input, const std::string &cmd, bool acceptFloatArg2 = false);

    static void printOptions(const std::vector<std::string>& options, std::string message = {});
    static void printError();

    virtual void printLogo(const std::string& detail);

    static const char* BACK;
    static const char* EXIT;

    Store& _store;
};

#endif //FEUP_AEDA_PROJECT_UI_H
