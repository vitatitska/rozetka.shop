#include <iostream>
#include <windows.h>
#include "shop.h"

using namespace std;

void printMenu() {
        cout << "\n----------- ГОЛОВНЕ МЕНЮ -----------\n";
        cout << "1. Показати каталог товарiв\n";         
        cout << "2. Додати товар до кошика\n";
        cout << "3. Видалити товар з кошика\n";
        cout << "4. Змiнити кiлькiсть товару в кошику\n";
        cout << "5. Переглянути кошик та суму\n";
        cout << "6. Застосувати промокод\n";
        cout << "7. Перевiрити знижку\n";                
        cout << "8. Налаштувати дату замовлення\n";
        cout << "9. Завершити замовлення\n";
        cout << "0. Вихiд\n";                               
        cout << "------------------------------------\n";
        cout << "Оберiть дiю: ";                          
}

int main() {
    setlocale(LC_ALL, "Ukrainian");

    cout << "=============================================\n";
    cout << "   ВIТАЄМО В НАШОМУ МАГАЗИНI РОЗЕТКА!     \n";
    cout << "=============================================\n";

    OrderManager manager;
    int choice = -1;

    while (choice != 0) {
        printMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Будь ласка, введiть число!\n";
            continue;
        }

        switch (choice) {
        case 1:
            manager.displayCatalog();
            break;
        case 2: {
            int id, qty;
            cout << "Введiть ID товару: ";
            cin >> id;
            cout << "Введiть кiлькiсть: ";
            cin >> qty;

            manager.addToCart(id, qty);
            manager.displayCart(); // Автоматичний вивiд кошика
            break;
        }
        case 3: {
            int id;
            cout << "Введiть ID товару для видалення: ";
            cin >> id;

            manager.removeFromCart(id);
            manager.displayCart(); // Автоматичний вивiд кошика
            break;
        }
        case 4: {
            int id, qty;
            cout << "Введiть ID товару: ";
            cin >> id;
            cout << "Введiть нову кiлькiсть: ";
            cin >> qty;

            manager.updateQuantity(id, qty);
            manager.displayCart(); // Автоматичний вивiд кошика
            break;
        }
        case 5:
            manager.displayCart();
            break;
        case 6: {
            string code;
            cout << "Введiть промокод (SPRING20 або STUDENT): ";
            cin >> code;
            manager.applyPromoCode(code);
            break;
        }
        case 7: {
            int birthMonth, currentMonth;
            cout << "Введiть мiсяць вашого народження (1-12): ";
            cin >> birthMonth;
            cout << "Введiть поточний мiсяць (1-12): ";
            cin >> currentMonth;
            manager.applyBirthdayDiscount(birthMonth, currentMonth);
            break;
        }
        case 8: {
            string date, userStatus;
            cout << "Введiть дату замовлення (ДД/ММ/РРРР): ";
            cin >> date;
            manager.setOrderDate(date);

            cout << "Введiть статус замовлення (наприклад: Очiкується, Обробляється): ";
            cin.ignore();
            getline(cin, userStatus);
            manager.setStatus(userStatus);

            cout << "Данi успiшно оновлено.\n";
            break;
        }
        case 9:
            cout << "\nОформлення фiнального замовлення...\n";
            manager.setStatus("Завершено");
            manager.saveReceipt("receipt.txt");
            cout << "Дякуємо! Програму завершено, чек сформовано в файлi receipt.txt.\n";
            return 0;
        case 0:
            cout << "Дякуємо, що завiтали! До побачення!\n";
            break;
        default:
            cout << "Невiрний пункт меню, спробуйте ще раз.\n";
        }
    }

    return 0;
}