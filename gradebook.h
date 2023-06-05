#ifndef GRADEBOOK_H
#define GRADEBOOK_H
#include <string>
using namespace std;

class gradebook
{
    public:
        gradebook();
        gradebook(string);
        ~gradebook();
        // default codes
        void setcourseName(string);
        string getcourseName()const;
        void message()const;
        // added member functions
        void student_grade_list();
        void setStudentinfo(string , int, int);
        void getStudentinfo(int)const;          // polymorphism
        void student_list();
        void setIndiv_grades(int, int, int, double);
        int get_indiv_grade(int, int, int)const;
        void get_indiv_student(int)const;
        int getaverage_grade(int);
        void set_hps(int, int, int);
        int released_grades(int);
        void setreleasing_grades(char);
        void get_hps();
        double getpercentage_written(int);
        double getpercentage_performance(int);
        double getpercentage_exams(int);
        void edit_no_of_output(int, int);
        void edit_weightcomponent(int ,int );
        void set_count_students(int);
        void display_count_output()const;
        void get_weight_component()const;
        int get_no_of_students()const;
        int get_percentage(int, int)const;
        double get_weight_value(int)const;
        int get_output_per_component(int)const;
        int get_hps_per_component(int, int)const;
        char loop_back(int);
        void default_data();
        // friend class
        friend class admin;
        friend class teacher;
        friend class student;
        friend void teacher_main_menu(gradebook &gobj);
        friend void student_main_menu(gradebook &gobj, int);
        friend void studentinfo_settings(gradebook &gobj_studentinfo);
        friend void course_settings(gradebook &gobj_coursesettings);
        //
    private:
        string courseName;
        string student_name[60];
        int sr_code[60];
        double indiv_grades[60][3][100] = { {{0,0,0,0,0},{0,0,0},{0,0}}  };
        int no_of_students = 5;
        int no_output_written = 5;
        int no_output_performance = 3;
        int no_output_exams = 2;
        bool release_grades = false;
        int average[60];
        int scores[100];
        // highest possible grade
        int written_works[60] = {10,10,10,10,10};
        int performance_task[60] = {50, 50, 50, 50, 50};
        int examination[60] = {100, 100, 100};
        //
        double weight_written = 0.30;
        double weight_performance = 0.50;
        double weight_exams = 0.20;
        double percentage_written[100];
        double percentage_performance[100];
        double percentage_exams[100];
        char *m_back_p;
        int *m_intpar1_p;
        int *m_intpar2_p;
        int *m_intpar3_p;
};


#endif // GRADEBOOK_H

