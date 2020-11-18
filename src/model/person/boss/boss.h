//
// Created by bdmendes on 14/11/20.
//

#ifndef FEUP_AEDA_PROJECT_BOSS_H
#define FEUP_AEDA_PROJECT_BOSS_H

#include <model/person/person.h>
#include <string>
#include <fstream>

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
    explicit Boss(std::string name = "Boss", int taxID = Person::DEFAULT_TAX_ID,
                  Credential credential = {DEFAULT_USERNAME, DEFAULT_PASSWORD});

    void read(const std::string& path);
    void write(const std::string& path);

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
