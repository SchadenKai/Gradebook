#ifndef TEACHER_H
#define TEACHER_H
#include "gradebook.h"
#include <string>
using namespace std;

class teacher
{
    public:
        teacher();
        ~teacher();
        void editing_grades(gradebook &grdobj);
        void editing_hps(gradebook &gobj);
        void simult_input_grades(gradebook &gobj);
    private:
        int *m_intpar1_p;
        int *m_intpar2_p;
        int *m_intpar3_p;
        double *m_doublepar1_p;
        string *m_stringpar1_p;
        char *m_back_p;
};


#endif // TEACHER_H
