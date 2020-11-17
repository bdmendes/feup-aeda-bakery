//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_PERSON_H
#define FEUP_AEDA_PROJECT_PERSON_H

#include <exception/person_exception.h>

#include <string>
#include <stdexcept>
#include <set>

struct Credential {
    std::string username;
    std::string password;
    bool operator==(const Credential& c2) const{
        return username == c2.username && password == c2.password;
    }
};

class Person {
public:
    Person(std::string name, int taxID, Credential credential);
    virtual ~Person() = default;

    std::string getName() const;
    int getTaxId() const;
    Credential getCredential() const;

    bool isLogged() const;
    void setLogged(bool logged);

    void setName(const std::string& name);
    void setTaxID(int taxID);
    void setCredential(const Credential& credential);

    bool operator<(const Person& p2) const;
    bool operator==(const Person& p2) const;

    virtual Credential getDefaultCredential() = 0;
    static const int DEFAULT_TAX_ID;
private:
    std::string _name;
    int _taxId;
    Credential _credential;
    bool _logged;
};

struct PersonSmaller{
    bool operator()(const Person* p1, const Person* p2) const{
        return *p1 < *p2;
    }
};

#endif //FEUP_AEDA_PROJECT_PERSON_H
