#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

void swapAdjacentWords() {
    std::string filename;
    std::cout << "Введите имя файла для обработки: ";
    std::getline(std::cin, filename);

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return;
    }

    std::string line;
    std::cout << "\nРезультат обработки (меняем местами каждые два соседних слова):\n";
    std::cout << "=========================================\n";

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> words;
        std::string word;

        // Читаем все слова из строки
        while (iss >> word) {
            words.push_back(word);
        }

        // Меняем местами каждые два соседних слова
        for (size_t i = 0; i + 1 < words.size(); i += 2) {
            std::swap(words[i], words[i + 1]);
        }

        // Выводим результат
        for (size_t i = 0; i < words.size(); ++i) {
            std::cout << words[i];
            if (i < words.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    inputFile.close();
    std::cout << "=========================================\n";
    std::cout << "Обработка завершена.\n";
}