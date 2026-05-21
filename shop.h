#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
struct Product {
    int id;
    string name;
    double price;
    string category;
};

struct CartItem {
    Product product;
    int quantity;
};

class OrderManager {
private:
    vector<Product> catalog;
    map<int, CartItem> cart;
    string status;
    string orderDate;
    double discountPercentage;
    string appliedBonusType;
    void loadCatalog(const string& filename);
public:
    OrderManager();
    void displayCatalog() const;
    void addToCart(int productId, int quantity);
    void removeFromCart(int productId);
    void updateQuantity(int productId, int newQuantity);
    void displayCart() const;
    void setOrderDate(const string& date);
    void setStatus(const string& newStatus);
    void applyBirthdayDiscount(int birthMonth, int currentMonth);
    void applyPromoCode(const string& promo);
    double calculateTotal() const;
    void saveReceipt(const string& filename) const;
};