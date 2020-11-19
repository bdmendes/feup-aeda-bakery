
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

    /**
     * Destructs the Product object.
     */
    virtual ~Product() = default;

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
     * Equality operator.
     *
     * @param p the product to compare with
     * @return true, if the products are equal; false, otherwise
     */
    virtual bool operator== (const Product& p) const;

    /**
     * Less than operator.
     *
     * @param p the product to compare with
     * @return true, if the product is less than p, according to alphabetical order; false, otherwise
     */
    bool operator<(const Product& p) const;

    /**
     * Prints all the product data.
     *
     * @param os the output stream
     */
    virtual void print(std::ostream& os) const = 0;
protected:
    /**
     * The product name.
     */
    std::string _name;

    /**
     * The product price.
     */
    float _price;
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
     * Checks if the bread is small.
     *
     * @return true, if it is small; false, otherwise
     */
    bool isSmall() const;

    /**
     * Equality operator.
     *
     * @param bread the bread to compare with
     * @return
     */
    virtual bool operator==(const Bread& bread) const;

    /**
     * Prints all the bread data (name, size and price).
     *
     * @param os the output stream
     */
    void print(std::ostream& os) const override;
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
     * Gets the cake category.
     *
     * @return the cake category
     */
    CakeCategory getCategory() const;

    /**
     * Equality operator
     *
     * @param cake the cake to compare with
     * @return true, if the cakes are equal; false, otherwise
     */
    virtual bool operator==(const Cake& cake) const;

    /**
     * Prints all the bread data (name, category and price).
     *
     * @param os the output stream
     */
    void print(std::ostream& os) const override;

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
