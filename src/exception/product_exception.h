
#ifndef FEUP_AEDA_PROJECT_PRODUCTEXCEPTIONS_H
#define FEUP_AEDA_PROJECT_PRODUCTEXCEPTIONS_H

#include <string>
#include <iostream>

/**
 * Class relative to the exception of a nonexistent product.
 */
class ProductDoesNotExist : public std::invalid_argument{
public:
    /**
     * Creates a new ProductDoesNotExist object.
     *
     * @param name the name
     * @param price the price
     */
    ProductDoesNotExist(const std::string& name, float price);

    /**
     * Creates a new ProductDoesNotExist object.
     *
     * @param name the name
     */
    explicit ProductDoesNotExist(const std::string& name);

    /**
     * Creates a new ProductDoesNotExist object.
     *
     * @param price the price
     */
    explicit ProductDoesNotExist(float price);
};

/**
 * Class relative to the exception of an invalid product position on some list.
 */
class InvalidProductPosition : public std::invalid_argument{
public:
    /**
     * Creates a new InvalidProductPosition object.
     *
     * @param position the position
     * @param size the products list size
     */
    InvalidProductPosition(unsigned position, unsigned long size);
};


#endif //FEUP_AEDA_PROJECT_PRODUCTEXCEPTIONS_H
