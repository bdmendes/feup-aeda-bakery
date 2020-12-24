
#ifndef SRC_PRODUCT_H
#define SRC_PRODUCT_H

#include <string>
#include <map>
#include <set>

#include "exception/product_exception.h"
#include <vector>

/**
 * The enum with the available cake categories.
 */
enum class CakeCategory {
    GENERAL, PIE, SPONGE, PUFF_PASTRY, CRUNCHY
};

/**
 * Class relative to a store product.
 */
class Product {
public:
    /**
     * Creates a new Product object.
     *
     * @param name the name
     * @param price the price
     */
    Product(std::string name, float price);

    virtual ~Product() = default;

    /**
     * Get textual description of the product category.
     */
    virtual std::string getCategory() const = 0;

    bool operator==(const Product& rhs) const;

    bool operator<(const Product& rhs) const;

    unsigned getTimesIncluded() const;
    void addInclusion();
    void removeInclusion();

    /**
     * Gets the product name.
     *
     * @return the name
     */
    std::string getName() const;

    /**
     * Gets the product price.
     *
     * @return the price
     */
    float getPrice() const;

    /**
     * Prints all the product data.
     *
     * @param os the output stream
     */
    void print(std::ostream& os, bool showInclusions = false) const;

protected:
    /**
     * The product name.
     */
    std::string _name;

    /**
     * The product price.
     */
    float _price;

    /**
     * Total times the product was included in an order.
     */
    unsigned _timesIncluded;
};

/**
 * The class relative to a specific type of product: bread.
 */
class Bread : public Product{
public:
    /**
     * Creates a new Bread object.
     *
     * @param name the name
     * @param price the price
     * @param small true, if it is small; false, otherwise
     */
    Bread(std::string name, float price, bool small = true);

    /**
     * Get bread size as a string.
     */
    std::string getCategory() const override;

    bool isSmall() const;

private:
    /**
     * The bread size.
     */
    bool _small;
};

/**
 * The class relative to a specific type of products: cake.
 */
class Cake : public Product{
public:
    /**
     * Creates a new Cake object
     *
     * @param name the name
     * @param price the price
     * @param category the category
     */
    Cake(std::string name, float price, CakeCategory category = CakeCategory::GENERAL);

    /**
     * Get cake category string.
     * @return _categoryStr
     */
    std::string getCategory() const override;

    /**
     * All the possible cakes categories as a string.
     */
    static const char* categoryStr[5];

    /**
     * Gets the list of all available cakes categories as strings.
     *
     * @return the list of all available cake categories as strings
     */
    static std::vector<std::string> getCategories();

private:
    /**
     * The cake category.
     */
    CakeCategory _category;

    /**
     * The cake category as a string.
     */
    const char* _categoryStr;
};

#endif //SRC_PRODUCT_H
