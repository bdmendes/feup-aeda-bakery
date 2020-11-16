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

    static bool validInput1Word(const std::string& input, bool digit = true);
    static bool validInput1Cmd(std::string input, const std::string &cmd);
    static bool validInput1Cmd1Arg(std::string input, const std::string &cmd, bool digitArg);
    static bool validInput1Cmd1Arg(std::string input, const std::string &cmd, const std::vector<std::string> &args);
    static bool validInput1Cmd1Arg(const std::string& input, const std::string &cmd, const std::string &arg);
    static bool validInput1Cmd2Args(const std::string& input, const std::string &cmd, const std::vector<std::string> &args1,
                                    const std::vector<std::string> &args2);

    static void printOptions(const std::vector<std::string>& options, std::string message = {}, bool index = false);
    static void printError(bool index = false);
    static void printLogo();
    static const char* BACK;
    static const char* EXIT;

    Store& _store;
};

#endif //FEUP_AEDA_PROJECT_UI_H
