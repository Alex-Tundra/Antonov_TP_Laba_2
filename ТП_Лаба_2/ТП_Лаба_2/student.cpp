#define _CRT_SECURE_NO_WARNINGS  // Отключение предупреждений

#include "student.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

STUDENT::STUDENT() : name(nullptr), grades(nullptr), num_grades(0), subjects(nullptr), num_subjects(0) {}

STUDENT::STUDENT(const char* name, const int* grades, int num_grades, char** subjects, int num_subjects) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->num_grades = num_grades;
    this->grades = new int[num_grades];
    for (int i = 0; i < num_grades; ++i) {
        this->grades[i] = grades[i];
    }

    this->num_subjects = num_subjects;
    this->subjects = new char* [num_subjects];
    for (int i = 0; i < num_subjects; ++i) {
        this->subjects[i] = new char[strlen(subjects[i]) + 1];
        strcpy(this->subjects[i], subjects[i]);
    }
}

STUDENT::STUDENT(const STUDENT& other) {
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
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void STUDENT::setGrades(const int* grades, int num_grades) {
    delete[] this->grades;
    this->num_grades = num_grades;
    this->grades = new int[num_grades];
    for (int i = 0; i < num_grades; ++i) {
        this->grades[i] = grades[i];
    }
}

void STUDENT::setSubjects(char** subjects, int num_subjects) {
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

std::ostream& operator<<(std::ostream& os, const STUDENT& s) {
    os << s.name << " (Оценки: ";
    for (int i = 0; i < s.num_grades; ++i) {
        os << s.grades[i];
        if (i < s.num_grades - 1) os << ", ";
    }
    os << ")";
    return os;
}
