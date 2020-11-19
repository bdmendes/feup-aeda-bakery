
#ifndef FEUP_AEDA_PROJECT_CLIENT_H
#define FEUP_AEDA_PROJECT_CLIENT_H

#include "model/person/person.h"

#include <vector>
#include <string>

/**
 * Class relative to a store client.
 */
class Client : public Person {
public:

    /**
     * Creates a new client object.
     *
     * @param name the name
     * @param premium the subscription type (true, if it is premium; false, otherwise)
     * @param taxID the taxpayer identification number
     * @param credential the login credentials
     */
    explicit Client(std::string name, int taxID = Person::DEFAULT_TAX_ID, bool premium = false,
           Credential credential = {DEFAULT_USERNAME, DEFAULT_PASSWORD});

    /**
     * Checks if the client subscription type is premium.
     *
     * @return true, if the client subscription type is premium; false, otherwise
     */
    bool isPremium() const;

    /**
     * Gets the order mean evaluation given by the client.
     *
     * @return the order mean evaluation
     */
    float getMeanEvaluation() const;

    /**
     * Gets the client points.
     *
     * @return the client points
     */
    unsigned getPoints() const;

    /**
     * Sets the client subscription type.
     *
     * @param premium true to change client subscription type to premium; false, otherwise
     */
    void setPremium(bool premium);

    /**
     * Adds a certain number of points to the client's.
     *
     * @param points the points
     */
    void addPoints(unsigned points);

    /**
     * Removes a certain number of points from the client points.
     *
     * @param points the points
     */
    void removePoints(unsigned points);

    /**
     * Resets the client points.
     */
    void resetPoints();

    /**
     * Adds an order evaluation given by the client.
     *
     * @param evaluation the order evaluation
     */
    void addEvaluation(int evaluation);

    /**
     * Sets the client points.
     * Sets the client's subscription type.
     *
     * @param points the new points
     */
    void setPoints(unsigned points);

    /**
     * Prints the client data.
     *
     * @param os the output stream
     * @param showData if true, prints all data: name, taxpayer identification number, subscription type, accumulated
     * points and mean evaluation; otherwise, just prints the name, the taxpayer identification number and log status.
     */
    void print(std::ostream& os, bool showData = true);

    /**
     * Gets the client default login credentials.
     *
     * @return the login credentials
     */
    Credential getDefaultCredential() override;

    /**
     * The client default login username.
     */
    static const char* DEFAULT_USERNAME;

    /**
     * The client default login password.
     */
    static const char* DEFAULT_PASSWORD;
private:
    /**
     *The client subscription type.
     */
    bool _premium;

    /**
     * The client points.
     */
    unsigned _points;

    /**
     * The list of all order evaluations given by the client.
     */
    std::vector<int> _evaluations;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_H
