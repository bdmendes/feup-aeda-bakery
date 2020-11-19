
#ifndef FEUP_AEDA_PROJECT_PERSON_H
#define FEUP_AEDA_PROJECT_PERSON_H

#include <exception/person_exception.h>

#include <string>
#include <stdexcept>
#include <set>

#include <iostream>

/**
 * Struct relative to the login credentials.
 */
struct Credential {
    /**
     * The login username.
     */
    std::string username;

    /**
     * The login password.
     */
    std::string password;

    /**
     * Equality operator.
     *
     * @param c2 the credentials to compare with
     * @return true, if credentials are equal; false, otherwise
     */
    bool operator==(const Credential& c2) const{
        return username == c2.username && password == c2.password;
    }

    /**
     * Checks if the login credentials are reserved to the current user.
     *
     * @return true, if the login credentials are reserved; false, otherwise
     */
    bool isReserved() const {
        return username == "back" || username == "exit"
        || password == "back" || password == "exit";
    }
};

/**
 * Class relative to a store user.
 */
class Person {
public:
    /**
     * Creates a new person object.
     *
     * @param name the name
     * @param taxID the taxpayer identification number
     * @param credential the login credentials (username and password)
     */
    Person(std::string name, int taxID, Credential credential);

    /**
     * Destructs the person object.
     */
    virtual ~Person() = default;

    /**
     * Gets the person name.
     *
     * @return the name
     */
    std::string getName() const;

    /**
     * Gets the person taxpayer identification number.
     *
     * @return the taxpayer identification number
     */
    int getTaxId() const;

    /**
     * Gets the person login credentials.
     *
     * @return the login credentials
     */
    Credential getCredential() const;

    /**
     * Checks if the person is logged in.
     *
     * @return true, if the person is logged in; false, otherwise
     */
    bool isLogged() const;

    /**
     * Sets the person log status.
     *
     * @param logged the log status (true, if it is logged int; false, otherwise)
     */
    void setLogged(bool logged);

    /**
     * Sets the person name.
     *
     * @param name the name
     */
    void setName(const std::string& name);

    /**
     * Sets the person taxpayer identification number.
     *
     * @param taxID the taxpayer identification number
     */
    void setTaxID(int taxID);

    /**
     * Sets the person login credentials.
     *
     * @param credential the login credentials
     */
    void setCredential(const Credential& credential);

    /**
     * Less than operator.
     *
     * @param p2 the person to compare with
     * @return true, if person is less than p2, according to alphabetical order ; false, otherwise.
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
     * Gets the default login credentials.
     *
     * @return the default login credentials
     */
    virtual Credential getDefaultCredential() = 0;

    /**
     * The default taxpayer identification number.
     */
    static const int DEFAULT_TAX_ID;

private:
    /**
     * The person name.
     */
    std::string _name;

    /**
     * The person taxpayer identification number.
     */
    int _taxID;

    /**
     * The person login credentials.
     */
    Credential _credential;

    /**
     * The person log status.
     */
    bool _logged;
};

/**
 * Struct to compare two persons pointers.
 */
struct PersonSmaller{
    /**
     * Checks if a person is smaller than other.
     *
     * @param p1 the first person to compare with
     * @param p2 the second person to compare with
     * @return true, if p1 is less than p2, according to alphabetical order; false, otherwise
     */
    bool operator()(const Person* p1, const Person* p2) const{
        return *p1 < *p2;
    }
};

#endif //FEUP_AEDA_PROJECT_PERSON_H
