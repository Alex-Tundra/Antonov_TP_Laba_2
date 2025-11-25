#ifndef GROUP_H
#define GROUP_H

#include "student.h"

class GROUP {
private:
    int group_number;
    STUDENT* students;
    int num_students;
    int capacity;
    char** subjects;
    int num_subjects;

public:
    GROUP();
    GROUP(int group_number, char** subjects, int num_subjects);
    GROUP(const GROUP& other);
    ~GROUP();
    GROUP& operator=(const GROUP& other);

    void setGroupNumber(int group_number);
    void resize(int new_capacity);
    void addStudent(const STUDENT& student, int position = -1);
    void removeStudent(int index);
    STUDENT* getStudent(int index) const;
    int getNumStudents() const;
    int getGroupNumber() const;
    char** getSubjects() const;
    int getNumSubjects() const;
    void setSubjects(char** subjects, int num_subjects);
};

#endif
