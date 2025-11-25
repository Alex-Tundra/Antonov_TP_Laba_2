#define _CRT_SECURE_NO_WARNINGS

#include "student.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

STUDENT::STUDENT() : name(nullptr), grades(nullptr), num_grades(0), subjects(nullptr), num_subjects(0) {
    std::cout << "Вызван конструктор STUDENT по умолчанию" << std::endl;
}

STUDENT::STUDENT(const char* name, const int* grades, int num_grades, char** subjects, int num_subjects) {
    std::cout << "Вызван конструктор STUDENT с параметрами" << std::endl;

    if (!name || num_grades < 0 || num_subjects < 0) {
        throw std::invalid_argument("Неверные параметры для конструктора STUDENT");
    }

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->num_grades = num_grades;
    if (num_grades > 0) {
        this->grades = new int[num_grades];
        for (int i = 0; i < num_grades; ++i) {
            if (grades[i] < 1 || grades[i] > 5) {
                throw std::invalid_argument("Оценка должна быть от 1 до 5");
            }
            this->grades[i] = grades[i];
        }
    }
    else {
        this->grades = nullptr;
    }

    this->num_subjects = num_subjects;
    if (num_subjects > 0) {
        this->subjects = new char* [num_subjects];
        for (int i = 0; i < num_subjects; ++i) {
            this->subjects[i] = new char[strlen(subjects[i]) + 1];
            strcpy(this->subjects[i], subjects[i]);
        }
    }
    else {
        this->subjects = nullptr;
    }
}

STUDENT::STUDENT(const STUDENT& other) {
    std::cout << "Вызван конструктор копирования STUDENT" << std::endl;

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    num_grades = other.num_grades;
    grades = new int[num_grades];
    for (int i = 0; i < num_grades; ++i) {
        grades[i] = other.grades[i];
    }

    num_subjects = other.num_subjects;
    subjects = new char* [num_subjects];
    for (int i = 0; i < num_subjects; ++i) {
        subjects[i] = new char[strlen(other.subjects[i]) + 1];
        strcpy(subjects[i], other.subjects[i]);
    }
}

STUDENT::~STUDENT() {
    std::cout << "Вызван деструктор STUDENT для " << (name ? name : "неизвестного студента") << std::endl;
    delete[] name;
    delete[] grades;
    for (int i = 0; i < num_subjects; ++i) {
        delete[] subjects[i];
    }
    delete[] subjects;
}

STUDENT& STUDENT::operator=(const STUDENT& other) {
    if (this == &other) return *this;

    delete[] name;
    delete[] grades;
    for (int i = 0; i < num_subjects; ++i) {
        delete[] subjects[i];
    }
    delete[] subjects;

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    num_grades = other.num_grades;
    grades = new int[num_grades];
    for (int i = 0; i < num_grades; ++i) {
        grades[i] = other.grades[i];
    }

    num_subjects = other.num_subjects;
    subjects = new char* [num_subjects];
    for (int i = 0; i < num_subjects; ++i) {
        subjects[i] = new char[strlen(other.subjects[i]) + 1];
        strcpy(subjects[i], other.subjects[i]);
    }

    return *this;
}

void STUDENT::setName(const char* name) {
    if (!name) throw std::invalid_argument("Имя не может быть пустым");
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void STUDENT::setGrades(const int* grades, int num_grades) {
    if (num_grades < 0) throw std::invalid_argument("Количество оценок не может быть отрицательным");

    delete[] this->grades;
    this->num_grades = num_grades;
    if (num_grades > 0) {
        this->grades = new int[num_grades];
        for (int i = 0; i < num_grades; ++i) {
            if (grades[i] < 1 || grades[i] > 5) {
                throw std::invalid_argument("Оценка должна быть от 1 до 5");
            }
            this->grades[i] = grades[i];
        }
    }
    else {
        this->grades = nullptr;
    }
}

void STUDENT::setSubjects(char** subjects, int num_subjects) {
    if (num_subjects < 0) throw std::invalid_argument("Количество предметов не может быть отрицательным");

    for (int i = 0; i < this->num_subjects; ++i) {
        delete[] this->subjects[i];
    }
    delete[] this->subjects;

    this->num_subjects = num_subjects;
    if (num_subjects > 0) {
        this->subjects = new char* [num_subjects];
        for (int i = 0; i < num_subjects; ++i) {
            this->subjects[i] = new char[strlen(subjects[i]) + 1];
            strcpy(this->subjects[i], subjects[i]);
        }
    }
    else {
        this->subjects = nullptr;
    }
}

char** STUDENT::getSubjects() const {
    char** copy = new char* [num_subjects];
    for (int i = 0; i < num_subjects; ++i) {
        copy[i] = new char[strlen(subjects[i]) + 1];
        strcpy(copy[i], subjects[i]);
    }
    return copy;
}

int STUDENT::getNumSubjects() const {
    return num_subjects;
}

double STUDENT::getAverage() const {
    if (num_grades == 0) return 0.0;
    int sum = 0;
    for (int i = 0; i < num_grades; ++i) {
        sum += grades[i];
    }
    return static_cast<double>(sum) / num_grades;
}

const char* STUDENT::getName() const {
    return name;
}

int STUDENT::getNumGrades() const {
    return num_grades;
}

const int* STUDENT::getGrades() const {
    return grades;
}

std::ostream& operator<<(std::ostream& os, const STUDENT& s) {
    os << s.name << " (Оценки: ";
    for (int i = 0; i < s.num_grades; ++i) {
        os << s.grades[i];
        if (i < s.num_grades - 1) os << ", ";
    }
    os << ", Средний балл: " << s.getAverage() << ")";
    return os;
}

std::istream& operator>>(std::istream& is, STUDENT& s) {
    char buffer[100];
    std::cout << "Введите ФИО студента: ";
    is.getline(buffer, 100);
    s.setName(buffer);

    int num_grades;
    std::cout << "Введите количество оценок: ";
    is >> num_grades;
    is.ignore();

    if (num_grades > 0) {
        int* grades = new int[num_grades];
        std::cout << "Введите оценки через пробел: ";
        for (int i = 0; i < num_grades; ++i) {
            is >> grades[i];
        }
        s.setGrades(grades, num_grades);
        delete[] grades;
    }
    is.ignore();

    char subs_input[200];
    std::cout << "Введите предметы через пробел: ";
    is.getline(subs_input, 200);

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
    s.setSubjects(subs, ns);

    for (int i = 0; i < ns; ++i) {
        delete[] subs[i];
    }
    delete[] subs;

    return is;
}