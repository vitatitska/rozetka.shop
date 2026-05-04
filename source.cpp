#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <locale>
using namespace std;
int main() {
    setlocale(LC_ALL, "ukr");
    //1. Видалити дублікати через set
    cout << "1. Видалення дублiкатiв\n";
    vector<int> arr = { 1, 2, 2, 3, 4, 4, 5, 6 };
    set<int> uniqueSet(arr.begin(), arr.end());
    cout << "Початковий масив: ";
    for (int x : arr) cout << x << " ";
    cout << "\nБез дублiкатiв: ";
    for (int x : uniqueSet) cout << x << " ";
    cout << "\n\n";
    //2. Словник оцінок через map 
    cout << "2. Словник оцiнок\n";
    map<string, int> grades;
    grades["Anna"] = 95;
    grades["Ivan"] = 88;
    grades["Oleh"] = 76;
    for (auto pair : grades) {
        cout << pair.first << " -> " << pair.second << endl;
    }
    cout << "\n";
    //3. Частота елементів через unordered_map 
    cout << "3. Частота елементiв\n";
    vector<int> nums = { 1, 2, 2, 3, 3, 3, 4, 8, 8, 9};
    unordered_map<int, int> freq;
    for (int x : nums) {
        freq[x]++;
    }
    cout << "Масив: ";
    for (int x : nums) 
        cout << x << " ";
    cout << "\nЧастоти:\n";
    for (auto pair : freq) {
        cout << pair.first << " зустрiчається " << pair.second << " раз(и)\n";
    }
    cout << "\n";
    //4. Автор -> книги через multimap
    cout << "4. Автори i книги\n";
    multimap<string, string> library;
    library.insert({ "Шевченко", "Кобзар" });
    library.insert({ "Шевченко", "Гайдамаки" });
    library.insert({ "Франко", "Захар Беркут" });
    library.insert({ "Франко", "Мойсей" });
    for (auto pair : library) {
        cout << pair.first << " -> " << pair.second << endl;
    }
    return 0;
}