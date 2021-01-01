
#ifndef FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H
#define FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H

#include "product.h"
#include "util/bst.h"

/**
 * Class that encapsulates a Product* so that operator overloading is possible.
 */
class ProductEntry {
public:
    /**
     * Create a new null ProductEntry object.
     */
    ProductEntry() : _product(nullptr) {};
    /**
     * Create a new ProductEntry object.
     * @param product the product that shall be encapsulated
     */
    explicit ProductEntry(Product* product) : _product(product) {};
    /**
     * Get the product that the object encapsulates.
     * @return the product pointer
     */
    Product* getProduct() const { return _product; };
    /**
     * A comparison between two ProductEntry is based on the defined operators for Product.
     * @param rhs the product to be compared to
     * @return the product inequality
     */
    bool operator<(const ProductEntry& rhs) const{
        if (!getProduct() || !rhs.getProduct()) return false;
        return *getProduct() < *rhs.getProduct();
    }
    /**
     * A comparison between two ProductEntry is based on the defined operators for Product.
     * @param rhs the product to be compared to
     * @return the product equality
     */
    bool operator==(const ProductEntry& rhs) const {
        if (!getProduct() || !rhs.getProduct()) return false;
        return *getProduct() == *rhs.getProduct();
    }
private:
    /**
     * The pointer that the class encapsulates.
     */
    Product* _product;
};

/**
 * Struct to compare two product pointers.
 */
struct ProductSmaller{
    /**
     * Checks if a should be shown before another..
     *
     * @param p1 the first product to compare with
     * @param p2 the second product to compare with
     * @return true, if p1 is less than p2
     */
    bool operator()(const Product* p1, const Product* p2) const {
        return *p1 < *p2;
    }
};

/**
 * Class that manages the store products.
 */
class ProductManager {
public:
    /**
     * Creates a new ProductManager object.
     */
    ProductManager();

    /**
     * Destructs the ProductManager object.
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
    Product* get(unsigned long position);

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
    std::vector<Cake*> getCakes() const;

    /**
     * Gets all the breads on the products list.
     *
     * @return the breads on the products list
     */
    std::vector<Bread*> getBreads() const;

    /**
     * Gets all the products on the products list.
     *
     * @return the products list
     */
    std::vector<Product*> getAll() const;

    /**
     * Get the products that were ever included in orders.
     * @return the ever included products
     */
    std::vector<Product*> getUsed() const;

    /**
     * Get the products that were never included in orders.
     * @return the never included products
     */
    std::vector<Product*> getUnused() const;

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
     * Add a new product to the products BST.
     * @param product the product to be added
     * @return the added product
     */
    Product* add(Product* product);

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
    void remove(unsigned long position);

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
    void print(std::ostream& os, bool showInclusions = true) const;

private:
    /**
     * The list of all the products.
     */
    BST<ProductEntry> _products;
};

#endif //FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H
