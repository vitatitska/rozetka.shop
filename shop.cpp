#include "shop.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

OrderManager::OrderManager() {
    status = "Очiкування";
    orderDate = "21/05/2026";
    discountPercentage = 0.0;
    appliedBonusType = "Немає";

    loadCatalog("catalog.txt");
}

void OrderManager::loadCatalog(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        catalog = {
            {1, "Ноутбук", 25000.0, "Електронiка"},
            {2, "Мишка", 650.0, "Електронiка"},
            {3, "Клавiатура", 1200.0, "Електронiка"}
        };
        ofstream out(filename);
        for (const auto& p : catalog) {
            out << p.id << "," << p.name << "," << p.price << "," << p.category << "\n";
        }
        return;
    }

    Product p;
    string priceStr, idStr;
    while (getline(file, idStr, ',') &&
        getline(file, p.name, ',') &&
        getline(file, priceStr, ',') &&
        getline(file, p.category)) {
        p.id = stoi(idStr);
        p.price = stod(priceStr);
        catalog.push_back(p);
    }
    file.close();
}

void OrderManager::displayCatalog() const {
    cout << "\n================ КАТАЛОГ ТОВАРIВ ================\n";
    cout << left << setw(5) << "ID"
        << setw(25) << "Назва"
        << setw(12) << "Цiна"
        << "Категорiя" << "\n";
    cout << "-------------------------------------------------\n";
    for (const auto& p : catalog) {
        cout << left << setw(5) << p.id
            << setw(25) << p.name
            << setw(12) << p.price
            << p.category << "\n";
    }
    cout << "=================================================\n";
}

void OrderManager::addToCart(int productId, int quantity) {
    if (quantity <= 0) return;

    for (const auto& p : catalog) {
        if (p.id == productId) {
            if (cart.find(productId) != cart.end()) {
                cart[productId].quantity += quantity;
            }
            else {
                cart[productId] = { p, quantity };
            }
            cout << "[ OK ] Товар '" << p.name << "' успiшно додано до кошика!\n";
            return;
        }
    }
    cout << "[ Помилка ] Товар з ID " << productId << " не знайдено.\n";
}

void OrderManager::removeFromCart(int productId) {
    if (cart.erase(productId)) {
        cout << "[ OK ] Товар видалено з кошика.\n";
    }
    else {
        cout << "[ Помилка ] Цього товару не було в кошику.\n";
    }
}

void OrderManager::updateQuantity(int productId, int newQuantity) {
    if (newQuantity <= 0) {
        removeFromCart(productId);
        return;
    }
    if (cart.find(productId) != cart.end()) {
        cart[productId].quantity = newQuantity;
        cout << "[ OK ] Кiлькiсть товару оновлено.\n";
    }
    else {
        cout << "[ Помилка ] Товар не знайдено в кошику.\n";
    }
}

void OrderManager::displayCart() const {
    if (cart.empty()) {
        cout << "\nВаш кошик порожнiй. Час щось купити!\n";
        return;
    }
    cout << "\n---------------- ВАШ КОШИК ----------------\n";
    for (const auto& item : cart) {
        const auto& p = item.second.product;
        int qty = item.second.quantity;
        cout << "- [" << p.id << "] " << p.name << " x" << qty
            << " = " << (p.price * qty) << " USD\n";
    }
    cout << "-------------------------------------------\n";
    cout << "Поточна сума (без знижок): " << calculateTotal() / (1.0 - discountPercentage) << " USD\n";
    if (discountPercentage > 0) {
        cout << "Застосовано бонус: " << appliedBonusType << " (-" << (discountPercentage * 100) << "%)\n";
        cout << "Сума до сплати: " << calculateTotal() << " USD\n";
    }
}

void OrderManager::setOrderDate(const string& date) {
    orderDate = date;
}

void OrderManager::setStatus(const string& newStatus) {
    status = newStatus;
}

void OrderManager::applyBirthdayDiscount(int birthMonth, int currentMonth) {
    if (birthMonth == currentMonth) {
        discountPercentage = 0.15;
        appliedBonusType = "День Народження";
        cout << "[ Вiтаємо ] Вам нараховано святкову знижку 15%!\n";
    }
    else {
        cout << "Цього мiсяця у вас немає Дня народження. Знижку не застосовано.\n";
    }
}

void OrderManager::applyPromoCode(const string& promo) {
    if (promo == "SPRING20") {
        discountPercentage = 0.20;
        appliedBonusType = "Промокод SPRING20";
        cout << "[ OK ] Промокод прийнято! Отримано 20% знижки!\n";
    }
    else if (promo == "STUDENT") {
        discountPercentage = 0.10;
        appliedBonusType = "Студентська знижка";
        cout << "[ OK ] Промокод прийнято! Отримано 10% знижки!\n";
    }
    else {
        cout << "[ Помилка ] Невiрний або застарілий промокод.\n";
    }
}

double OrderManager::calculateTotal() const {
    double total = 0.0;
    for (const auto& item : cart) {
        total += item.second.product.price * item.second.quantity;
    }
    return total * (1.0 - discountPercentage);
}

void OrderManager::saveReceipt(const string& filename) const {
    if (cart.empty()) return;

    ofstream out(filename);
    if (!out.is_open()) return;

    out << "===========================================\n";
    out << "             ФIСКАЛЬНИЙ ЧЕК               \n";
    out << "===========================================\n";
    out << "Дата замовлення: " << orderDate << "\n";
    out << "Статус: " << status << "\n";
    out << "-------------------------------------------\n";

    for (const auto& item : cart) {
        const auto& p = item.second.product;
        int qty = item.second.quantity;
        out << left << setw(20) << p.name
            << "x" << setw(3) << qty
            << right << setw(10) << (p.price * qty) << " USD\n";
    }

    out << "-------------------------------------------\n";
    if (discountPercentage > 0) {
        out << "Тип бонусу: " << appliedBonusType << "\n";
        out << "Знижка: " << (discountPercentage * 100) << "%\n";
    }
    out << "РАЗОМ ДО СПЛАТИ: " << calculateTotal() << " USD\n";
    out << "===========================================\n";
    out << "        Дякуємо за покупку в нашому магазинi!\n";

    out.close();
    cout << "[ OK ] Чек успiшно збережено у файл '" << filename << "'\n";
}