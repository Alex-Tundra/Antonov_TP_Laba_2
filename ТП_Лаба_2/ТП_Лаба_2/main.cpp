#include <iostream>
#include <limits>
#include <windows.h>
#include <locale>
#include <clocale>

int main() {
    // Установка русской локали
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::setlocale(LC_ALL, "Russian");

    return 0;
}