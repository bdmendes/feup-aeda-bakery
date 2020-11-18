//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_PERSON_H
#define FEUP_AEDA_PROJECT_PERSON_H

#include <exception/person_exception.h>

#include <string>
#include <stdexcept>
#include <set>

#include <iostream>

enum class PersonRole {
    WORKER,
    CLIENT,
    BOSS
};

/**
 *
 */
struct Credential {
    std::string username;
    std::string password;
    bool operator==(const Credential& c2) const{
        return username == c2.username && password == c2.password;
    }
    bool isReserved() const {
        return username == "back" || username == "exit"
        || password == "back" || password == "exit";
    }
};

/**
 *
 */
class Person {
public:
    /**
     * Creates a new person.
     *
     * @param name the name
     * @param taxID the taxpayer identification number
     * @param credential the access credentials (username and password)
     */
    Person(std::string name, int taxID, Credential credential, PersonRole role);

    /**
     * Destructs the person's object.
     */
    virtual ~Person() = default;

    /**
     * Gets the person's name.
     *
     * @return the name
     */
    std::string getName() const;

    /**
     * Gets the person's taxpayer identification number.
     *
     * @return the name
     */
    int getTaxId() const;

    /**
     * Gets the person's access credentials.
     *
     * @return the credentials
     */
    Credential getCredential() const;

    /**
     * Checks if the person is logged.
     *
     * @return true, if the person is logged; false, otherwise
     */
    bool isLogged() const;

    /**
     * Sets the person's log status.
     *
     * @param logged the log status
     */
    void setLogged(bool logged);

    /**
     * Sets the person's name.
     *
     * @param name the name
     */
    void setName(const std::string& name);

    /**
     * Sets the person's taxpayer identification number.
     *
     * @param taxID the taxpayer identification number
     */
    void setTaxID(int taxID);

    /**
     * Sets the person's access credentials.
     *
     * @param credential the credentials
     */
    void setCredential(const Credential& credential);

    /**
     * Less operator.
     *
     * @param p2 the person to compare with
     * @return true, if person is smaller than p2; false, otherwise.
     */
    bool operator<(const Person& p2) const;

    /**
     * Equality operator.
     *
     * @param p2 the person to compare with
     * @return true, if persons are equal; false, otherwise.
     */
    bool operator==(const Person& p2) const;

    /**
     * Gets the default access credentials.
     *
     * @return the default access credentials
     */
    virtual Credential getDefaultCredential() = 0;

    /**
     * The default taxpayer identification number.
     */

    PersonRole getRole();

    static const int DEFAULT_TAX_ID;

private:
    /**
     * The client's name.
     */
    std::string _name;

    /**
     * The client's taxpayer identification number.
     */
    int _taxID;

    /**
     * The client's access credentials.
     */
    Credential _credential;

    /**
     * The client's log status.
     */
    bool _logged;

protected:
    PersonRole _role;
};

/**
 *
 */
struct PersonSmaller{
    bool operator()(const Person* p1, const Person* p2) const{
        return *p1 < *p2;
    }
};

#endif //FEUP_AEDA_PROJECT_PERSON_H
