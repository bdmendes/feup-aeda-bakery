//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_CLIENT_H
#define FEUP_AEDA_PROJECT_CLIENT_H

#include "model/person/person.h"

#include <vector>
#include <string>

class Client : public Person {
public:

    /**
     * Creates a new client.
     *
     * @param name the name
     * @param premium the subscription type (basic or premium)
     * @param taxID the taxpayer identification number
     * @param credential the credentials
     */
    explicit Client(std::string name, int taxID = Person::DEFAULT_TAX_ID, bool premium = false,
           Credential credential = {DEFAULT_USERNAME, DEFAULT_PASSWORD});

    /**
     *Cheks if the client's subscription type is premium.
     *
     * @return true, if the client is premium; false, otherwise
     */
    bool isPremium() const;

    /**
     *Gets the order's mean evaluation given by the client.
     *
     * @return the order's mean evaluation
     */
    float getMeanEvaluation() const;

    /**
     * Gets the client points.
     *
     * @return the client's points
     */
    unsigned getPoints() const;

    /**
     *Gets the list of all order's evaluation given by the client.
     *
     * @return the list of order's evaluation
     */
    std::vector<int> getEvaluations() const;

    /**
     *Sets the client's subscription type.
     *
     * @param premium
     */
    void setPremium(bool premium);

    /**
     *Adds certain points to the client's.
     *
     * @param points the points
     */
    void addPoints(unsigned points);

    /**
     * Removes certain points of the client's points.
     *
     * @param points the points
     */
    void removePoints(unsigned points);

    /**
     * Resets the client's points.
     */
    void resetPoints();
  
    /**
     * Adds an order evaluation given by the client.
     *
     * @param evaluation the order evaluation
     */
    void addEvaluation(int evaluation);
  
    void setPoints(unsigned points);

    /**
     * Prints
     *
     * @param os the output stream
     * @param showData
     */
    void print(std::ostream& os, bool showData = true);

    /**
     * Gets the default access credentials.
     *
     * @return the access credentials
     */
    Credential getDefaultCredential() override;

    /**
     * The client's default username.
     */
    static const char* DEFAULT_USERNAME;

    /**
     * The client's default password.
     */
    static const char* DEFAULT_PASSWORD;
private:
    /**
     *
     */
    bool _premium;

    /**
     * The client's points.
     */
    unsigned _points;

    /**
     * The client's evaluations.
     */
    std::vector<int> _evaluations;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_H
