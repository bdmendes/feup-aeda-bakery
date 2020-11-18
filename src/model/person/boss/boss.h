
#ifndef FEUP_AEDA_PROJECT_BOSS_H
#define FEUP_AEDA_PROJECT_BOSS_H

#include <model/person/person.h>
#include <string>
#include <fstream>

/**
 * Class relative to the store boss.
 */
class Boss : public Person {
public:

    /**
     * Creates a new boss object.
     *
     * @param name the name
     * @param taxID the taxpayer identification number
     * @param credential the login credentials
     */
    explicit Boss(std::string name = "Boss", int taxID = Person::DEFAULT_TAX_ID, Credential credential = {DEFAULT_USERNAME, DEFAULT_PASSWORD});

    /**
     * Gets the default boss' login credentials.
     *
     * @return the default login credentials
     */
    Credential getDefaultCredential() override;

    /**
     * Reads a boss data (name, the taxpayer identification number and login credentials) from a file and creates a new
     * one with that data.
     *
     * @param path the file path
     */
    void read(const std::string& path);

    /**
     * Writes the boss data (name, the taxpayer identification number and login credentials) to a file.
     *
     * @param path the file path
     */
    void write(const std::string& path);

    /**
     * The default boss login username.
     */
    static const char* DEFAULT_USERNAME;

    /**
     *The default boss login password.
     */
    static const char* DEFAULT_PASSWORD;
};


#endif //FEUP_AEDA_PROJECT_BOSS_H
