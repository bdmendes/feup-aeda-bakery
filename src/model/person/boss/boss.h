//
// Created by bdmendes on 14/11/20.
//

#ifndef FEUP_AEDA_PROJECT_BOSS_H
#define FEUP_AEDA_PROJECT_BOSS_H

#include <model/person/person.h>
#include <string>

/**
 *
 */
class Boss : public Person {
public:

    /**
     * Creates a new boss.
     *
     * @param name the name
     * @param taxID the taxpayer identification number
     * @param credential the access credentials
     */
    Boss(std::string name, int taxID, Credential credential = {DEFAULT_USERNAME, DEFAULT_PASSWORD});

    /**
     * Gets the default boss' access credentials.
     *
     * @return the default access credentials
     */
    Credential getDefaultCredential() override;

    /**
     * The default boss' access username.
     */
    static const char* DEFAULT_USERNAME;

    /**
     *The default boss' access password.
     */
    static const char* DEFAULT_PASSWORD;

};


#endif //FEUP_AEDA_PROJECT_BOSS_H
