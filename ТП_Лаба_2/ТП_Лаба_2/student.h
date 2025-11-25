#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <stdexcept>

class STUDENT {
private:
    char* name;
    int* grades;
    int num_grades;
    char** subjects;
    int num_subjects;

public:
    STUDENT();
    STUDENT(const char* name, const int* grades, int num_grades, char** subjects, int num_subjects);
    STUDENT(const STUDENT& other);
    ~STUDENT();
    STUDENT& operator=(const STUDENT& other);

    void setName(const char* name);
    void setGrades(const int* grades, int num_grades);
    void setSubjects(char** subjects, int num_subjects);
    char** getSubjects() const;
    int getNumSubjects() const;
    double getAverage() const;
    const char* getName() const;
    int getNumGrades() const;
    const int* getGrades() const;

    friend std::ostream& operator<<(std::ostream& os, const STUDENT& s);
    friend std::istream& operator>>(std::istream& is, STUDENT& s);
};

#endif