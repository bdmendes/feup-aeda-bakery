//
// Created by bdmendes on 14/11/20.
//

#ifndef FEUP_AEDA_PROJECT_BOSS_H
#define FEUP_AEDA_PROJECT_BOSS_H

#include <model/person/person.h>
#include <string>


class Boss : public Person {
public:
    Boss(std::string name, int taxID, Credential credential = {DEFAULT_USERNAME, DEFAULT_PASSWORD});

    Credential getDefaultCredential() override;
    static const char* DEFAULT_USERNAME;
    static const char* DEFAULT_PASSWORD;

};


#endif //FEUP_AEDA_PROJECT_BOSS_H
