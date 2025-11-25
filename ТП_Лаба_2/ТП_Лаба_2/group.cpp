#define _CRT_SECURE_NO_WARNINGS

#include "group.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

GROUP::GROUP() : group_number(0), students(nullptr), num_students(0), capacity(0), subjects(nullptr), num_subjects(0) {
    std::cout << "Вызван конструктор GROUP по умолчанию" << std::endl;
}

GROUP::GROUP(int group_number, char** subjects, int num_subjects) : group_number(group_number), num_students(0), capacity(10) {
    std::cout << "Вызван конструктор GROUP с параметрами для группы " << group_number << std::endl;

    if (group_number <= 0) {
        throw std::invalid_argument("Номер группы должен быть положительным");
    }

    students = new STUDENT[capacity];

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

GROUP::GROUP(const GROUP& other) {
    std::cout << "Вызван конструктор копирования GROUP для группы " << other.group_number << std::endl;

    group_number = other.group_number;
    num_students = other.num_students;
    capacity = other.capacity;
    students = new STUDENT[capacity];
    for (int i = 0; i < num_students; ++i) {
        students[i] = other.students[i];
    }

    num_subjects = other.num_subjects;
    subjects = new char* [num_subjects];
    for (int i = 0; i < num_subjects; ++i) {
        subjects[i] = new char[strlen(other.subjects[i]) + 1];
        strcpy(subjects[i], other.subjects[i]);
    }
}

GROUP::~GROUP() {
    std::cout << "Вызван деструктор GROUP для группы " << group_number << std::endl;
    delete[] students;
    for (int i = 0; i < num_subjects; ++i) {
        delete[] subjects[i];
    }
    delete[] subjects;
}

GROUP& GROUP::operator=(const GROUP& other) {
    if (this == &other) return *this;

    delete[] students;
    for (int i = 0; i < num_subjects; ++i) {
        delete[] subjects[i];
    }
    delete[] subjects;

    group_number = other.group_number;
    num_students = other.num_students;
    capacity = other.capacity;
    students = new STUDENT[capacity];
    for (int i = 0; i < num_students; ++i) {
        students[i] = other.students[i];
    }

    num_subjects = other.num_subjects;
    subjects = new char* [num_subjects];
    for (int i = 0; i < num_subjects; ++i) {
        subjects[i] = new char[strlen(other.subjects[i]) + 1];
        strcpy(subjects[i], other.subjects[i]);
    }

    return *this;
}

void GROUP::setGroupNumber(int group_number) {
    if (group_number <= 0) {
        throw std::invalid_argument("Номер группы должен быть положительным");
    }
    this->group_number = group_number;
}

void GROUP::resize(int new_capacity) {
    if (new_capacity <= capacity) return;
    STUDENT* new_students = new STUDENT[new_capacity];
    for (int i = 0; i < num_students; ++i) {
        new_students[i] = students[i];
    }
    delete[] students;
    students = new_students;
    capacity = new_capacity;
}

void GROUP::addStudent(const STUDENT& student, int position) {
    if (num_students >= capacity) {
        resize(capacity * 2);
    }
    if (position == -1 || position >= num_students) {
        students[num_students] = student;
    }
    else {
        if (position < 0) {
            throw std::out_of_range("Позиция не может быть отрицательной");
        }
        for (int i = num_students; i > position; --i) {
            students[i] = students[i - 1];
        }
        students[position] = student;
    }
    ++num_students;
}

void GROUP::removeStudent(int index) {
    if (index < 0 || index >= num_students) {
        throw std::out_of_range("Индекс студента вне диапазона");
    }
    for (int i = index; i < num_students - 1; ++i) {
        students[i] = students[i + 1];
    }
    --num_students;
}

STUDENT* GROUP::getStudent(int index) const {
    if (index < 0 || index >= num_students) {
        throw std::out_of_range("Индекс студента вне диапазона");
    }
    return &students[index];
}

int GROUP::getNumStudents() const {
    return num_students;
}

int GROUP::getGroupNumber() const {
    return group_number;
}

char** GROUP::getSubjects() const {
    char** copy = new char* [num_subjects];
    for (int i = 0; i < num_subjects; ++i) {
        copy[i] = new char[strlen(subjects[i]) + 1];
        strcpy(copy[i], subjects[i]);
    }
    return copy;
}

int GROUP::getNumSubjects() const {
    return num_subjects;
}

void GROUP::setSubjects(char** subjects, int num_subjects) {
    for (int i = 0; i < this->num_subjects; ++i) {
        delete[] this->subjects[i];
    }
    delete[] this->subjects;

    this->num_subjects = num_subjects;
    this->subjects = new char* [num_subjects];
    for (int i = 0; i < num_subjects; ++i) {
        this->subjects[i] = new char[strlen(subjects[i]) + 1];
        strcpy(this->subjects[i], subjects[i]);
    }
}

double GROUP::getGroupAverage() const {
    if (num_students == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < num_students; ++i) {
        sum += students[i].getAverage();
    }
    return sum / num_students;
}