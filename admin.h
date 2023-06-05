#ifndef ADMIN_H
#define ADMIN_H
#include "gradebook.h"
#include <string>
using namespace std;

class admin
{
    public:
        admin();
        ~admin();
        void func_studentinfo(gradebook &gobj);
        void edit_no_of_output(gradebook &gobj);
        void edit_course_name(gradebook &gobj);
        void releasing_grades(gradebook &gobj);
        void editing_student_info(gradebook &gobj);
        void editing_weight_per_component(gradebook &gobj);
        void studentinfo_settings(gradebook &gobj_studentinfo);
        void course_settings(gradebook &gobj_coursesettings);
        void setup_logininfo();
    private:
        char *m_back_p;
        string *m_stringpar1_p;
        string *m_stringpar2_p;
        int *m_intpar1_p;
        int *m_intpar2_p;
        char *m_charpar1_p;
};


#endif // ADMIN_H
