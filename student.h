#ifndef STUDENT_H
#define STUDENT_H
#include "gradebook.h"
#include <string>
using namespace std;

class student
{
    public:
        student();
        ~student();
        void grade_details(gradebook &gobj, int);
        void viewing_grades(int indic);
    private:
        int *m_intpar1_p;
        char *m_back_p;
};

#endif // STUDENT_H
