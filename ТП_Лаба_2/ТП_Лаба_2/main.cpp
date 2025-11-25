#define _CRT_SECURE_NO_WARNINGS  // Отключение предупреждений

#include "group.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <locale>

void sortGroups(GROUP** groups, int num_groups) {
    for (int i = 0; i < num_groups - 1; ++i) {
        for (int j = 0; j < num_groups - i - 1; ++j) {
            if (groups[j]->getGroupNumber() > groups[j + 1]->getGroupNumber()) {
                GROUP* temp = groups[j];
                groups[j] = groups[j + 1];
                groups[j + 1] = temp;
            }
        }
    }
}

void performTask(GROUP** groups, int num_groups) {
    std::cout << "Студенты с средним баллом > 4.0:" << std::endl;
    for (int i = 0; i < num_groups; ++i) {
        for (int j = 0; j < groups[i]->getNumStudents(); ++j) {
            STUDENT* s = groups[i]->getStudent(j);
            if (s && s->getAverage() > 4.0) {
                std::cout << "Группа " << groups[i]->getGroupNumber() << ": " << *s << std::endl;
            }
        }
    }
}

int main() {
    system("chcp 1251 > nul");  // Устанавливает кодовую страницу консоли на CP1251
    setlocale(LC_ALL, "Russian");  // Устанавливает локаль программы на русский

    GROUP** groups = nullptr;
    int num_groups = 0;
    int capacity = 10;
    groups = new GROUP * [capacity];

    int choice;
    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Создать группу\n";
        std::cout << "2. Добавить студента в группу\n";
        std::cout << "3. Удалить студента из группы\n";
        std::cout << "4. Редактировать студента\n";
        std::cout << "5. Изменить номер группы\n";
        std::cout << "6. Удалить группу\n";
        std::cout << "7. Показать все группы и студентов\n";
        std::cout << "8. Выполнить задачу (студенты с баллом > 4.0)\n";
        std::cout << "9. Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore();

        try {
            switch (choice) {
            case 1: {
                if (num_groups >= capacity) {
                    capacity *= 2;
                    GROUP** new_groups = new GROUP * [capacity];
                    for (int i = 0; i < num_groups; ++i) {
                        new_groups[i] = groups[i];
                    }
                    delete[] groups;
                    groups = new_groups;
                }
                int g_num;
                std::cout << "Введите номер группы: ";
                std::cin >> g_num;
                std::cin.ignore();
                char subs_input[200];
                std::cout << "Введите предметы через пробел: ";
                std::cin.getline(subs_input, 200);
                char** subs = nullptr;
                int ns = 0;
                char* token = strtok(subs_input, " ");
                while (token) {
                    char** temp = new char* [ns + 1];
                    for (int i = 0; i < ns; ++i) {
                        temp[i] = subs[i];
                    }
                    temp[ns] = new char[strlen(token) + 1];
                    strcpy(temp[ns], token);
                    delete[] subs;
                    subs = temp;
                    ++ns;
                    token = strtok(nullptr, " ");
                }
                groups[num_groups] = new GROUP(g_num, subs, ns);
                ++num_groups;
                sortGroups(groups, num_groups);
                for (int i = 0; i < ns; ++i) {
                    delete[] subs[i];
                }
                delete[] subs;
                std::cout << "Группа создана." << std::endl;
                break;
            }
            case 2: {
                int g_idx;
                std::cout << "Введите индекс группы (0-" << num_groups - 1 << "): ";
                std::cin >> g_idx;
                std::cin.ignore();
                if (g_idx < 0 || g_idx >= num_groups) {
                    std::cout << "Неверный индекс группы." << std::endl;
                    break;
                }
                char name[100];
                std::cout << "Введите ФИО студента: ";
                std::cin.getline(name, 100);
                int num_grades;
                std::cout << "Введите количество оценок: ";
                std::cin >> num_grades;
                std::cin.ignore();
                int* grades = new int[num_grades];
                std::cout << "Введите оценки через пробел: ";
                for (int i = 0; i < num_grades; ++i) {
                    std::cin >> grades[i];
                }
                std::cin.ignore();
                char subs_input[200];
                std::cout << "Введите предметы через пробел: ";
                std::cin.getline(subs_input, 200);
                char** subs = nullptr;
                int ns = 0;
                char* token = strtok(subs_input, " ");
                while (token) {
                    char** temp = new char* [ns + 1];
                    for (int i = 0; i < ns; ++i) {
                        temp[i] = subs[i];
                    }
                    temp[ns] = new char[strlen(token) + 1];
                    strcpy(temp[ns], token);
                    delete[] subs;
                    subs = temp;
                    ++ns;
                    token = strtok(nullptr, " ");
                }
                STUDENT s(name, grades, num_grades, subs, ns);
                groups[g_idx]->addStudent(s);
                delete[] grades;
                for (int i = 0; i < ns; ++i) {
                    delete[] subs[i];
                }
                delete[] subs;
                std::cout << "Студент добавлен." << std::endl;
                break;
            }
            case 3: {
                int g_idx, s_idx;
                std::cout << "Введите индекс группы (0-" << num_groups - 1 << "): ";
                std::cin >> g_idx;
                std::cin.ignore();
                if (g_idx < 0 || g_idx >= num_groups) {
                    std::cout << "Неверный индекс группы." << std::endl;
                    break;
                }
                std::cout << "Введите индекс студента (0-" << groups[g_idx]->getNumStudents() - 1 << "): ";
                std::cin >> s_idx;
                std::cin.ignore();
                groups[g_idx]->removeStudent(s_idx);
                std::cout << "Студент удален." << std::endl;
                break;
            }
            case 4: {
                int g_idx, s_idx;
                std::cout << "Введите индекс группы (0-" << num_groups - 1 << "): ";
                std::cin >> g_idx;
                std::cin.ignore();
                if (g_idx < 0 || g_idx >= num_groups) {
                    std::cout << "Неверный индекс группы." << std::endl;
                    break;
                }
                std::cout << "Введите индекс студента (0-" << groups[g_idx]->getNumStudents() - 1 << "): ";
                std::cin >> s_idx;
                std::cin.ignore();
                STUDENT* s = groups[g_idx]->getStudent(s_idx);
                if (!s) {
                    std::cout << "Студент не найден." << std::endl;
                    break;
                }
                char name[100];
                std::cout << "Введите новые ФИО: ";
                std::cin.getline(name, 100);
                s->setName(name);
                int num_grades;
                std::cout << "Введите новое количество оценок: ";
                std::cin >> num_grades;
                std::cin.ignore();
                int* grades = new int[num_grades];
                std::cout << "Введите новые оценки через пробел: ";
                for (int i = 0; i < num_grades; ++i) {
                    std::cin >> grades[i];
                }
                std::cin.ignore();
                s->setGrades(grades, num_grades);
                delete[] grades;
                char subs_input[200];
                std::cout << "Введите новые предметы через пробел: ";
                std::cin.getline(subs_input, 200);
                char** subs = nullptr;
                int ns = 0;
                char* token = strtok(subs_input, " ");
                while (token) {
                    char** temp = new char* [ns + 1];
                    for (int i = 0; i < ns; ++i) {
                        temp[i] = subs[i];
                    }
                    temp[ns] = new char[strlen(token) + 1];
                    strcpy(temp[ns], token);
                    delete[] subs;
                    subs = temp;
                    ++ns;
                    token = strtok(nullptr, " ");
                }
                s->setSubjects(subs, ns);
                for (int i = 0; i < ns; ++i) {
                    delete[] subs[i];
                }
                delete[] subs;
                std::cout << "Студент отредактирован." << std::endl;
                break;
            }
            case 5: {
                int g_idx, new_num;
                std::cout << "Введите индекс группы (0-" << num_groups - 1 << "): ";
                std::cin >> g_idx;
                std::cin.ignore();
                if (g_idx < 0 || g_idx >= num_groups) {
                    std::cout << "Неверный индекс группы." << std::endl;
                    break;
                }
                std::cout << "Введите новый номер группы: ";
                std::cin >> new_num;
                std::cin.ignore();
                groups[g_idx]->setGroupNumber(new_num);
                sortGroups(groups, num_groups);
                std::cout << "Номер группы изменен." << std::endl;
                break;
            }
            case 6: {
                int g_idx;
                std::cout << "Введите индекс группы для удаления (0-" << num_groups - 1 << "): ";
                std::cin >> g_idx;
                std::cin.ignore();
                if (g_idx < 0 || g_idx >= num_groups) {
                    std::cout << "Неверный индекс группы." << std::endl;
                    break;
                }
                delete groups[g_idx];
                for (int i = g_idx; i < num_groups - 1; ++i) {
                    groups[i] = groups[i + 1];
                }
                --num_groups;
                std::cout << "Группа удалена." << std::endl;
                break;
            }
            case 7: {
                for (int i = 0; i < num_groups; ++i) {
                    std::cout << "Группа " << groups[i]->getGroupNumber() << ":" << std::endl;
                    for (int j = 0; j < groups[i]->getNumStudents(); ++j) {
                        STUDENT* s = groups[i]->getStudent(j);
                        if (s) {
                            std::cout << *s << std::endl;
                        }
                    }
                }
                break;
            }
            case 8: {
                performTask(groups, num_groups);
                break;
            }
            case 9: {
                std::cout << "Выход." << std::endl;
                break;
            }
            default: {
                std::cout << "Неверный выбор." << std::endl;
                break;
            }
            }
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    } while (choice != 9);

    for (int i = 0; i < num_groups; ++i) {
        delete groups[i];
    }
    delete[] groups;

    return 0;
}
