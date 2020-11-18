
#ifndef FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H
#define FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H

#include "product.h"
#include <set>

/**
 * Struct to compare two product pointers.
 */
struct ProductSmaller{
    bool operator()(const Product* p1, const Product* p2) {
        return *p1 < *p2;
    }
};

/**
 * Class that manages the store products.
 */
class ProductManager {
public:
    /**
     * Creates a new product manager object.
     */
    ProductManager();

    /**
     * Destructs the product manager object.
     */
    ~ProductManager();

    /**
     * Checks if the product is on the products list of the product manager.
     *
     * @param product the product
     * @return true, if the product is on products list; false, otherwise
     */
    bool has(Product* product) const;

    /**
     * Gets the product on the products list of the product manager at a certain position.
     *
     * @param position the position
     * @return the product at that position
     */
    Product* get(unsigned position);

    /**
     * Gets the product on the products list with a certain name and price.
     *
     * @param name the name
     * @param price the price
     * @return the product with that name and price
     */
    Product* get(const std::string &name, float price);

    /**
     * Gets all the cakes on the products list.
     *
     * @return the cakes on products list
     */
    std::set<Cake*, ProductSmaller> getCakes() const;

    /**
     * Gets all the breads on the products list.
     *
     * @return the breads on the products list
     */
    std::set<Bread*, ProductSmaller> getBreads() const;

    /**
     * Gets all the products on the products list.
     *
     * @return the products list
     */
    std::set<Product*, ProductSmaller> getAll();

    /**
     * Adds a bread to the product list.
     *
     * @param name the name
     * @param price the price
     * @param small the size
     * @return the bread added to the products list
     */
    Bread* addBread(std::string name, float price, bool small = true);

    /**
     * Adds a cake to the products list.
     *
     * @param name the name
     * @param price the price
     * @param category the category
     * @return the cake added to the products list
     */
    Cake* addCake(std::string name, float price, CakeCategory category = CakeCategory::GENERAL);

    /**
     * Removes a product from the products list.
     *
     * @param product the product
     */
    void remove(Product* product);

    /**
     * Removes a product from the products list at a certain position.
     *
     * @param position the position
     */
    void remove(unsigned position);

    /**
     * Reads all the products data (name, price, size if it is a bread and category if it is a cake) from a file and
     * creates news ones with that data.
     *
     * @param path the file path
     */
    void read(const std::string& path);

    /**
     * Writes the all the products data that are on the products list (name, price, size if it is a bread and category
     * if it is a cake) to a file.
     *
     * @param path the file path
     */
    void write(const std::string& path) const;

    /**
     * Prints all the products data (name, price, size if it is a bread and category if it is a cake).
     *
     * @param os the output stream
     */
    void print(std::ostream& os) const;
private:
    /**
     * The list of all the products.
     */
    std::set<Product*, ProductSmaller> _products;
};


#endif //FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H
