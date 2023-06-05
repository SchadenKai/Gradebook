#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include "gradebook.h"
#include "security.h"
#include "student.h"
#include "teacher.h"
#include "admin.h"
using namespace std;

// global variables
char *back_p;           // back pointer (for user controlled looping)
int *option_p;          // main menu options pointer
// objects
gradebook *grdbookptr1 = new gradebook;
gradebook *grdbookptr2 = new gradebook;
gradebook *grdbookptr3 = new gradebook;
gradebook *grdbookptr4 = new gradebook;
gradebook *grdbookptr5 = new gradebook;
gradebook *grdbookptr6 = new gradebook;
gradebook *grdbookptr7 = new gradebook;
gradebook *grdbookptr8 = new gradebook;
admin adminobj;
teacher teacherobj;
student studentobj;
security admin_login(3);
security student_login(2);
security teacher_login(1);

// GRADEBOOK
gradebook::gradebook(string name)
: m_back_p(new char), m_intpar1_p(new int), m_intpar2_p(new int),m_intpar3_p(new int)
{
    setcourseName(name);
}
gradebook::gradebook(){             // constructor
    default_data();
    courseName = "Undefined Course Name";
}
gradebook::~gradebook(){            // destructor
    cout << "Releasing memory from gradebook class..." << endl;
    delete m_back_p;
    delete m_intpar1_p;
    delete m_intpar2_p;
    delete m_intpar3_p;
}
// default member functions
void gradebook::setcourseName(string name){
    if(name.length()<=25)
        courseName = name ;
    if(name.length()>25){
        courseName = name.substr(0, 25);
        cout << "Course Name: " << name << " exceeds maximum length of 25 characters" << endl;
    }
}
string gradebook::getcourseName()const {
    return courseName;
}
void gradebook::message()const{
    cout << "STUDENT GRADEBOOK: " <<getcourseName() << endl;
}
// added member functions
void gradebook::student_grade_list(){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << setw(25) << "STUDENT NAME" << setw(3) << " |   " << setw(7) << "SRCODE" << "  |    ";
        for(int k = 0; k < no_output_written; k++){
                    cout << setw(4) << "WW" << setw(3)<< "   ";
        }
        for(int k = 0; k < no_output_performance; k++){
                    cout << setw(4) << "PT" << setw(3)<< "   ";
        }
        for(int k = 0; k < no_output_exams; k++){
                    cout << setw(4) << "ME" << setw(3)<< "   ";
        }
        cout << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    for (int i = 0; i < no_of_students; i++){
    cout << setw(25) << student_name[i] << setw(3) << " |   " << setw(7) << sr_code[i] << "  |    ";
        for (int j = 0; j < 3; j++){
            if(j == 0){
                for(int k = 0; k < no_output_written; k++){
                    cout << setw(4) << indiv_grades[i][j][k]<< setw(3)<< "   ";
                }
            }
            if(j == 1){
                for(int k = 0; k < no_output_performance; k++){
                    cout << setw(4) << indiv_grades[i][j][k]<< setw(3)<< "   ";
                }
            }
            if(j == 2){
                for(int k = 0; k < no_output_exams; k++){
                    cout << setw(4) << indiv_grades[i][j][k]<< setw(3)<< "   ";
                }
            }
        }
    cout << endl;
    }
}
void gradebook::setStudentinfo(string name, int sr, int indic){
    student_name[indic] = name;
    sr_code[indic] = sr;
}
void gradebook::getStudentinfo(int ind1)const{         // polymorphism
        cout << "Name: " << student_name[ind1] << endl;
        cout << "SR CODE: " << sr_code[ind1] << endl;
}
void gradebook::student_list(){
    for(int i = 0; i < no_of_students ; i++){
        cout << student_name[i] << " :   " << sr_code[i] << "  |    " << endl;
    }
}
void gradebook::setIndiv_grades(int ind1, int ind2, int ind3, double grade){    // [student][component][output]
    indiv_grades[ind1][ind2][ind3] = grade;
}
int gradebook::get_indiv_grade(int ind1, int ind2, int ind3)const{
return indiv_grades[ind1][ind2][ind3];
}
void gradebook::get_indiv_student(int ind1)const{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
    cout << "Student name: " << student_name[ind1] << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
double gradebook::getpercentage_written(int ind1){
    int n = 0;
    int *m_intpar1_p = 0;
    int sum = 0;
    for (int i = 0; i < no_output_written; i++){
        *m_intpar1_p = *m_intpar1_p + written_works[i];
    }
    for (int i = 0; i < no_output_written; i++){
        sum = sum + indiv_grades[ind1][0][i];
        n = sum/ *m_intpar1_p;
        percentage_written[ind1] = n*weight_written;
    }
return percentage_written[ind1];
}
double gradebook::getpercentage_performance(int ind1){
    int n = 0;
    int *m_intpar1_p = 0;
    int sum = 0;
    for (int i = 0; i < no_output_performance; i++){
        *m_intpar1_p = *m_intpar1_p + performance_task[i];
    }
    for (int i = 0; i < no_output_performance; i++){
        sum = sum + indiv_grades[ind1][1][i];
        n = sum/ *m_intpar1_p;
        percentage_performance[ind1] = n*weight_performance;
    }
return percentage_performance[ind1];
}
double gradebook::getpercentage_exams(int ind1){
    int n = 0;
    int *m_intpar1_p = 0;
    int sum = 0;
    for (int i = 0; i < no_output_exams; i++){
        *m_intpar1_p = *m_intpar1_p + examination[i];
    }
    for (int i = 0; i < no_output_exams; i++){
        sum = sum + indiv_grades[ind1][2][i];
        n = sum/ *m_intpar1_p;
        percentage_exams[ind1] = n*weight_exams;
    }
return percentage_exams[ind1];
}
int gradebook::getaverage_grade(int ind1){
    getpercentage_exams(ind1);
    getpercentage_performance(ind1);
    getpercentage_written(ind1);
return average[ind1] = percentage_written[ind1]+percentage_exams[ind1]+percentage_performance[ind1];;
}
void gradebook::set_hps(int ind1, int component, int new_var){
        if(component == 1){
            written_works[ind1] = new_var;
        }
        else if(component == 2){
            performance_task[ind1] = new_var;
        }
        else if(component == 3){
            examination[ind1] = new_var;
        }
}
int gradebook::released_grades(int ind1){
    int num;
    if(release_grades == true){
        num = average[ind1]*100;
    }
    else{
        num = 0;
    }
return num;
}
void gradebook::setreleasing_grades(char x){
    if(x == 'Y' || x == 'y'){
        release_grades = true;
    }
    else if (x == 'n' || x == 'N'){
        release_grades = false;
    }
}
void gradebook::get_hps(){
    cout << setw(38) << "Highest Possible Score" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << "------------------ Written works ----------------- " << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            for(int i = 0; i < no_output_written; i++){
                cout << setw(10) << "Output no." << i+1 << setw(10)<< "  |  " << setw(10)<< written_works[i] << endl;
            }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout <<"------------------- Performance Task --------------" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            for(int i = 0; i < no_output_performance; i++){
                cout << setw(10)<< "Output no." << i+1 << setw(10)<< "  |  " << setw(10)<< performance_task[i] << endl;
            }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout <<"-------------------- Major Examination ------------"<< endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            for(int i = 0; i < no_output_exams; i++){
                cout << setw(10)<< "Output no." << i+1 << setw(10)<< "  |  " << setw(10)<< examination[i] << endl;
            }
}
void gradebook::edit_no_of_output(int ind1, int ind2){
    if (ind2 == 1){
        no_output_written = ind1;
    }
    else if (ind2 == 2){
        no_output_performance = ind1;
    }
    else if (ind2 == 3){
        no_output_exams = ind1;
    }
}
void gradebook::edit_weightcomponent(int ind1, int ind2){
    if (ind2 == 1){
        weight_written = ind1/100;
    }
    else if (ind2 == 2){
        weight_performance = ind1/100;
    }
    else if (ind2 == 3){
        weight_exams = ind1/100;
    }
}
void gradebook::set_count_students(int ind1){
    no_of_students = ind1;
}
void gradebook::display_count_output()const{
    cout << "[WW] Count of Written Works: "<< no_output_written << endl;
    cout << "[PT] Count of Performance Task: "<< no_output_performance << endl;
    cout << "[ME] Count of Major Exams: "<< no_output_exams << endl;
}
void gradebook::get_weight_component()const{
    cout << "[WW] Current weight for Written works: " << weight_written << endl;
    cout << "[PT] Current weight for Performance Task: " << weight_performance << endl;
    cout << "[ME] Current weight for Major Examinations: " << weight_exams << endl << endl;
}
int gradebook::get_no_of_students()const{
return no_of_students;
}
int gradebook::get_percentage(int ind1,int ind2)const{
    int num;
    if(ind1 == 1){
        num =  percentage_written[ind2];
    }
    else if(ind1 == 2){
        num =  percentage_performance[ind2];
    }
    else if(ind1 == 3){
        num =  percentage_exams[ind2];
    }
return num;
}
double gradebook::get_weight_value(int ind1)const{
    double num;
    if(ind1 == 1){
        num =  weight_written;
    }
    else if(ind1 == 2){
        num =  weight_performance;
    }
    else if(ind1 == 3){
        num =  weight_exams;
    }
return num;
}
int gradebook::get_output_per_component(int ind1)const{
    int num;
    if(ind1 == 1){
        num = no_output_written;
    }
    else if(ind1 == 2){
        num = no_output_performance;
    }
    else if(ind1 == 3){
        num = no_output_exams;
    }
return num;
}
int gradebook::get_hps_per_component(int ind1, int ind2)const{
    int num;
    if(ind1 == 1){
        num =  written_works[ind2];
    }
    else if(ind1 == 2){
        num = performance_task[ind2];
    }
    else if(ind1 == 3){
        num = examination[ind2];
    }
return num;
}
char gradebook::loop_back(int ind1){
char back;

if (ind1 == 1){
    cout << "Go back to Menu? [Y / Menu]: ";
}
if (ind1 == 2){
    cout << "Continue? [Y / N]: ";
}
if (ind1 == 3){
    cout << "Go back to Main menu? [Y / Exit Program]: ";
}
if (ind1 == 4){
    cout << "Go back to Student Menu? [Y / Exit Program]: ";
}
cin >> back;
    if(!(back == 'Y' || back == 'y' || back == 'n' || back == 'N')){
        cout << "ERROR: 95 - Invalid Answer" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        system("pause");
    }
    if(cin.fail()){
        cout << "ERROR: 95 - Invalid Answer"<< endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        system("pause");
    }
    cin.ignore(INT_MAX, '\n');
return back;
}
void gradebook::default_data(){
    /*string str;
    int num1, num2, num3;
    ifstream default_data("default_data.csv", ios::app);
    while(default_data >> student_name[i] >> sr_code[i] >> num2 >> num3){
        getline(default_data, student_name[0], ',');
*/

    // sr code;
    // indiv grades;
    // no_of_student;
    //_no_of_output_written, performance, exams
    // written works;
    // performane task
    // examination
    //weight written , performance, exams
}
// ADMIN
admin::admin()
:m_back_p(new char), m_stringpar1_p(new string), m_stringpar2_p(new string),
m_intpar1_p(new int), m_intpar2_p(new int), m_charpar1_p(new char)
{
}
admin::~admin(){
    cout << "Releasing memory from admin class..." << endl;
    delete m_back_p;
    delete m_stringpar1_p;
    delete m_stringpar2_p;
    delete m_intpar1_p;
    delete m_intpar2_p;
    delete m_charpar1_p;
}
void admin::func_studentinfo(gradebook &gobj){
    do{
    system ("CLS");
    cout << "\t\t Student Information" << endl << endl;
    string stu_name;
    int sr_code;
    gobj.student_grade_list();
    cout << "Enter number of students: ";
    cin >> setw(2) >> *m_intpar1_p ;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = gobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
    gobj.set_count_students(*m_intpar1_p );
    for (int i = 0; i < *m_intpar1_p ; i++){
        cout << "Student name no. " << i+1 << ": ";
        getline(cin,stu_name,'\n');
        cout << "Sr code (7 - digit): ";
        cin >> setw(7) >> sr_code;
            if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = gobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
        gobj.setStudentinfo(stu_name, sr_code, i);
    }
    *m_back_p = gobj.loop_back(2);
    }
    while (*m_back_p == 'Y' || *m_back_p == 'y');
}
void admin::edit_no_of_output(gradebook &gobj){
    do{
    system("CLS");
    cout << "\t\tEDIT NUMBER OF OUTPUTS - " << gobj.getcourseName() << endl << endl;
    gobj.display_count_output();
    cout << endl << "Choose component to change: ";
    cin >> setw(2) >> *m_stringpar1_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = gobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
        if (*m_stringpar1_p == "WW" || *m_stringpar1_p == "ww"){
            *m_intpar1_p = 1;
        }
        else if (*m_stringpar1_p == "PT" || *m_stringpar1_p == "pt"){
            *m_intpar1_p = 2;
        }
        else if (*m_stringpar1_p == "ME" || *m_stringpar1_p == "me"){
            *m_intpar1_p = 3;
        }
        else{
            cout << "ERROR: INVALID INPUT - Not inside the choices " << endl << endl;
            *m_back_p = gobj.loop_back(3);
            break;

        }
    cout << "Number of outputs: ";
    cin >> setw(2) >> *m_intpar2_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = gobj.loop_back(2);
            continue;
        }
        else{
        cin.ignore(INT_MAX, '\n');
        gobj.edit_no_of_output(*m_intpar2_p, *m_intpar1_p);
        }
    *m_back_p = gobj.loop_back(2);
    }
    while(*m_back_p == 'y' || *m_back_p == 'Y');
}
void admin::edit_course_name(gradebook &gobj){
    do{
    system("CLS");
    cout << "\t\t Edit Course Name" << endl << endl;
    cout << "Edit course name: ";
    getline(cin, *m_stringpar1_p, '\n');
    gobj.setcourseName(*m_stringpar1_p);
    cout << endl << "Successfully changed!! - NEW COURSE NAME:" <<gobj.getcourseName() << endl << endl;
    *m_back_p = gobj.loop_back(2);
    }
    while(*m_back_p == 'y' || *m_back_p == 'Y');
}
void admin::releasing_grades(gradebook &gobj){
    do{
        system("CLS");
        cout << "\t\t RELEASING OF GRADES - " << gobj.getcourseName() << endl << endl;
        gobj.student_grade_list();
        cout << endl;
        cout << "Release the grades [Y/N]: ";
        cin >> setw(1) >> *m_charpar1_p;
            if (cin.fail()){
                cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                *m_back_p = gobj.loop_back(2);
                continue;
            }
            else{
                cin.ignore(INT_MAX, '\n');
                gobj.setreleasing_grades(*m_charpar1_p);
            }
    }
    while(*m_back_p == 'y' || *m_back_p == 'Y');
}
void admin::editing_student_info(gradebook &gobj){
    do{
    system("CLS");
    cout << "\t\t EDITING OF STUDENT INFORMATION " << gobj.getcourseName() << endl;
    gobj.student_grade_list();
    cout << endl << "Enter Number of Student to Edit: ";
    cin >> *m_intpar1_p;
    cin.ignore(INT_MAX, '\n');
    cout << "New Student name: ";
    getline(cin,*m_stringpar1_p, '\n');
    cout << "New SR Code: ";
    cin >> *m_intpar2_p;
    gobj.setStudentinfo(*m_stringpar1_p,*m_intpar2_p,*m_intpar1_p-1);
    *m_back_p = gobj.loop_back(2);
    }
    while(*m_back_p == 'y' || *m_back_p == 'Y');
}
void admin::editing_weight_per_component(gradebook &gobj){
    do{
    system("CLS");
    cout << "\t\tEDITING WEIGHT PER COMPONENT for " << gobj.getcourseName() << endl << endl;
    gobj.get_weight_component();
    cout << "Choose component: ";
    cin >> setw(2)>> *m_stringpar1_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = gobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
        if (*m_stringpar1_p == "WW" || *m_stringpar1_p == "ww"){
            *m_intpar1_p = 1;
        }
        else if (*m_stringpar1_p == "PT" || *m_stringpar1_p == "pt"){
            *m_intpar1_p = 2;
        }
        else if (*m_stringpar1_p == "ME" || *m_stringpar1_p == "me"){
            *m_intpar1_p = 3;
        }
    cout << "Enter new weight(by whole number): ";
    cin >> setw(4) >> *m_intpar2_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = gobj.loop_back(2);
            continue;
        }
        else{
            cin.ignore(INT_MAX, '\n');
            gobj.edit_weightcomponent(*m_intpar2_p, *m_intpar1_p);
        }
    *m_back_p = gobj.loop_back(2);
    }
    while(*m_back_p == 'y' || *m_back_p == 'Y');
}
void admin::setup_logininfo(){
	do{
	system("CLS");
	cout << "\t\t CHOOSE USER TYPE TO SETUP LOGIN INFO" << endl << endl;
	cout << "Teacher    [1]" << endl;
	cout << "Student    [2]" << endl;
	cout << "Admin      [3]" << endl << endl;
	cout << "Choose user: ";
	cin >> *m_intpar1_p;
		cin.ignore(INT_MAX, '\n');
		if (*m_intpar1_p == 1){
			cout << "Enter new username: ";
			getline(cin, *m_stringpar2_p , '\n');
			cout << "Choose subject (1-8): ";
			cin >> *m_intpar2_p ;
				cin.ignore(INT_MAX, '\n');
			teacher_login.set_username(*m_stringpar2_p, *m_intpar2_p);
			cout << "Enter new password: ";
			getline(cin, *m_stringpar1_p, '\n');
			teacher_login.set_password(*m_stringpar1_p, *m_intpar2_p);
		}
		else if (*m_intpar1_p == 2){
			cout << "Enter new username: ";
			getline(cin, *m_stringpar2_p, '\n');
			cout << "Choose student account (1-60): ";
			cin >> *m_intpar2_p ;
				cin.ignore(INT_MAX, '\n');
			student_login.set_username(*m_stringpar2_p, *m_intpar2_p);
			cout << "Enter new password: ";
			getline(cin, *m_stringpar1_p, '\n');
			student_login.set_password(*m_stringpar1_p, *m_intpar2_p);
		}
		else if (*m_intpar1_p == 3){
			cout << "Enter new username: ";
			getline(cin, *m_stringpar2_p, '\n');
			admin_login.set_username(*m_stringpar2_p, 0);
			cout << "Enter new password: ";
			getline(cin, *m_stringpar1_p, '\n');
			admin_login.set_password(*m_stringpar1_p, 0);
		}
	*m_back_p = grdbookptr1->loop_back(2);
	}
	while(*m_back_p == 'Y'|| *m_back_p == 'y');

}
// SECURITY
security::security(int ui_indic)
:usertype_indic(ui_indic), m_back_p(new char), m_intpar1_p(new int)
{}
security::~security(){
    cout << "Releasing memory for security class..." << endl;
    delete m_back_p;
    delete m_intpar1_p;
}
char security::loop_back(int ind1){
char back;
if (ind1 == 1){
    cout << "Go back to Menu? [Y / Menu]: ";
}
if (ind1 == 2){
    cout << "Continue? [Y / N]: ";
}
if (ind1 == 3){
    cout << "Go back to Main menu? [Y / Exit Program]: ";
}
if (ind1 == 4){
    cout << "Go back to Student Menu? [Y / Exit Program]: ";
}
cin >> back;
    if(!(back == 'Y' || back == 'y' || back == 'n' || back == 'N')){
        cout << "ERROR: 95 - Invalid Answer" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        system("pause");
    }
    if(cin.fail()){
        cout << "ERROR: 95 - Invalid Answer"<< endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        system("pause");
    }
    cin.ignore(INT_MAX, '\n');
return back;
}
void security::set_username(string un, int indic){
	if(usertype_indic == 1){
		teacher_username[indic] = un;
	}
	else if(usertype_indic == 2){
		student_username[indic] = un;
	}
	else if(usertype_indic == 3){
		admin_username = un;
	}
}
void security::set_password(string p, int indic){
	if(usertype_indic == 1){
		teacher_password[indic] = p;
	}
	else if(usertype_indic == 2){
		student_password[indic] = p;
	}
	else if(usertype_indic == 3){
		admin_password = p;
	}
}
int security::checking(){
    int indicator_login;
	if(usertype_indic == 1){
		for(int i = 0; i < 8; i++){					 // TEACHER  [8]
        	if(ui_username == teacher_username[i]){
            checking_ind1 = i;
            break;
        	}
    	}
    	if(checking_ind1 < 9){
        	if(teacher_password[checking_ind1] == ui_password){
            indicator_login = checking_ind1;
        	}
    	}
    	if(checking_ind1 > 9){
    		indicator_login = checking_ind1;
		}
	}
	else if(usertype_indic == 2){				// STUDENT  [60]
		for(int i = 0; i < 60; i++){
        	if(ui_username == student_username[i]){
            checking_ind1 = i;
            break;
        	}
    	}
    	if(checking_ind1 < 60){
        	if(student_password[checking_ind1] == ui_password){
            indicator_login = checking_ind1;
        	}
    	}
    	else{
    		indicator_login = checking_ind1;
		}
	}
	else if(usertype_indic == 3){					// ADMIN
		if(ui_username == admin_username && ui_password == admin_password){
			indicator_login = 1;
		}
		else{
			indicator_login = checking_ind1;
		}
	}
return indicator_login;
}
void security::ui_username_password(){
	cout << endl << "\t\t Please Login " << endl << endl;
	cout << "\t\t Username: " ;
	cin  >> setw(25)>> ui_username;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        cin.ignore(INT_MAX, '\n');
	cout << "\t\t Password: ";
	cin  >> setw(25)>> ui_password;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        cin.ignore(INT_MAX, '\n');

}
// STUDENT
student::student()
:m_intpar1_p(new int), m_back_p(new char)
{
}
student::~student(){
    cout << "Releasing memory for student class... " << endl;
    delete m_intpar1_p;
    delete m_back_p;
}
void student::viewing_grades(int indic){     //STUDENT
    do{
    m_back_p = new char;
	system("CLS");
	cout << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << setw(30)<< "COURSE SUBJECT " << " | " << setw(5) << "AVERAGE GRADE" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << setw(30)<< grdbookptr1->getcourseName() << " | " << setw(5)<< grdbookptr1->released_grades(indic) << "         [1]"<<endl;
	cout << setw(30)<< grdbookptr2->getcourseName() << " | " << setw(5)<<  grdbookptr2->released_grades(indic) << "         [2]"<< endl;        // new source code for average
	cout << setw(30)<< grdbookptr3->getcourseName() << " | " << setw(5)<<  grdbookptr3->released_grades(indic) << "         [3]"<< endl;
	cout << setw(30)<< grdbookptr4->getcourseName() << " | " << setw(5)<<  grdbookptr4->released_grades(indic) << "         [4]"<< endl;
	cout << setw(30)<< grdbookptr5->getcourseName() << " | " << setw(5)<<  grdbookptr5->released_grades(indic) << "         [5]"<< endl;
	cout << setw(30)<< grdbookptr6->getcourseName() << " | " << setw(5)<<  grdbookptr6->released_grades(indic) << "         [6]"<< endl;
	cout << setw(30)<< grdbookptr7->getcourseName() << " | " << setw(5)<<  grdbookptr7->released_grades(indic) << "         [7]"<< endl;
	cout << setw(30)<< grdbookptr8->getcourseName() << " | " << setw(5)<<  grdbookptr8->released_grades(indic) << "         [8]"<< endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << endl << "Back to Student menu   [9]" << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Enter action: ";
	cin >> setw(1) >> *m_intpar1_p;
        if (cin.fail()){
                cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                *m_back_p = grdbookptr1->loop_back(2);
                continue;
        }
        cin.ignore(INT_MAX, '\n');
        switch(*m_intpar1_p){
            case 1:
                grade_details(*grdbookptr1, indic);
                *m_back_p = grdbookptr1->loop_back(2);
                break;
            case 2:
                grade_details(*grdbookptr2, indic);
                *m_back_p = grdbookptr2->loop_back(2);
                break;
            case 3:
                grade_details(*grdbookptr3, indic);
                *m_back_p = grdbookptr3->loop_back(2);
                break;
            case 4:
                grade_details(*grdbookptr4, indic);
                *m_back_p = grdbookptr4->loop_back(2);
                break;
            case 5:
                grade_details(*grdbookptr5, indic);
                *m_back_p = grdbookptr5->loop_back(2);
                break;
            case 6:
                grade_details(*grdbookptr6, indic);
                *m_back_p = grdbookptr6->loop_back(2);
                break;
            case 7:
                grade_details(*grdbookptr7, indic);
                *m_back_p = grdbookptr7->loop_back(2);
                break;
            case 8:
                grade_details(*grdbookptr8, indic);
                *m_back_p = grdbookptr8->loop_back(2);
                break;
            case 9:
                break;
                break;
            default:
                cout << "ERR0R: NOT IN THE GIVEN OPTIONS" << endl << endl;
                *m_back_p = grdbookptr1->loop_back(2);
                break;
        }
	}
	while(*m_back_p == 'Y'|| *m_back_p == 'y');
}
void student::grade_details(gradebook &gobj, int ind1){

    cout << "GRADE DETAILS : " << gobj.getcourseName() << endl << endl;
    cout << " |    OUTPUTS        |     HIGHEST POSSIBLE SCORE   |" << endl;
    cout << " | WRITTEN WORKS: "<< gobj.get_percentage(1, ind1)*100 << "/" <<gobj.get_weight_value(1)*100<< " -----------------------------|" << endl;
        for (int i = 0; i < gobj.get_output_per_component(1); i++){
            cout << " | " << setw(10) <<  gobj.get_indiv_grade(ind1,0,i) << "        | " << setw(20) << gobj.get_hps_per_component(1, i) << setw(2)<< "         |" << endl;
        }
    cout << " | --------- PERFORMANCE TASK: "<< gobj.get_percentage(2, ind1)*100 << "/" <<gobj.get_weight_value(2)*100 << " ----------------|" << endl;
        for (int i = 0; i < gobj.get_output_per_component(2); i++){
            cout << " | " << setw(10) << gobj.get_indiv_grade(ind1,1,i) << "         | " << setw(20) << gobj.get_hps_per_component(2, i) << setw(2)<< "         |" << endl;
        }
    cout << " | --------- MAJOR EXAMINATIONS: "<< gobj.get_percentage(3, ind1)*100 << "/" <<gobj.get_weight_value(3)*100<< " ---------------|" << endl;
        for (int i = 0; i < gobj.get_output_per_component(3); i++){
            cout << " | " << setw(10) << gobj.get_indiv_grade(ind1,2,i) << "         | " << setw(20) << gobj.get_hps_per_component(3, i) << setw(2)<< "        |" << endl;
        }
}
// TEACHER
teacher::teacher()
: m_intpar1_p(new int), m_intpar2_p(new int), m_intpar3_p(new int),
m_doublepar1_p(new double), m_stringpar1_p(new string), m_back_p(new char)
{
}
teacher::~teacher(){
    cout << "Releasing memory for teacher class... " << endl;
        delete m_intpar1_p;
        delete m_intpar2_p;
        delete m_intpar3_p;
        delete m_doublepar1_p;
        delete m_stringpar1_p;
        delete m_back_p;
}
void teacher::editing_grades(gradebook &grdobj){
    do{
    system("CLS");
    cout << "\t\t EDITING OF GRADES - GRADEBOOK: " << grdobj.getcourseName() << endl << endl;
    grdobj.student_grade_list();
    cout << endl << "Number of student: ";
    cin >> *m_intpar1_p;
    grdobj.get_indiv_student(*m_intpar1_p);
    cout << "Enter output component [WW / PT / ME]: ";
    cin >> setw(2) >> *m_stringpar1_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = grdobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
            if (*m_stringpar1_p == "WW" || *m_stringpar1_p == "ww"){
                *m_intpar3_p = 1;
            }
            else if (*m_stringpar1_p == "PT" || *m_stringpar1_p == "pt"){
                *m_intpar3_p = 2;
            }
            else if (*m_stringpar1_p == "ME" || *m_stringpar1_p == "me"){
                *m_intpar3_p = 3;
            }
    cout << "Number of output: ";
    cin >> setw(2) >> *m_intpar2_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = grdobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
    cout << "New Grade: ";
    cin >> *m_doublepar1_p;
        try{
        if (*m_doublepar1_p > grdobj.get_hps_per_component(*m_intpar3_p, *m_intpar2_p)){
            throw string("ERROR: Grade input greater than the highest possible score");
        }
        if (cin.fail()){
            throw string ("ERROR: Invalid Input - You may have input character or special character");
        }
        }
        catch(string x){
            cout << x << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = grdobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
    grdobj.setIndiv_grades(*m_intpar1_p-1, *m_intpar3_p-1, *m_intpar2_p-1, *m_doublepar1_p);
    *m_back_p = grdobj.loop_back(2);
    }
    while(*m_back_p == 'Y' || *m_back_p == 'y');
}
void teacher::editing_hps(gradebook &gobj){
    do{
    system("CLS");
    cout << "EDITING HIGHGEST POSSIBLE SCORE " << endl << endl;
    gobj.get_hps();
    cout << endl << "Choose assessment component [WW | PT | ME]: ";
    cin >> setw(2) >> *m_stringpar1_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = gobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
            if (*m_stringpar1_p == "WW" || *m_stringpar1_p == "ww"){
                *m_intpar2_p = 1;
            }
            else if (*m_stringpar1_p == "PT" || *m_stringpar1_p == "pt"){
                *m_intpar2_p = 2;
            }
            else if (*m_stringpar1_p == "ME" || *m_stringpar1_p == "me"){
                *m_intpar2_p = 3;
            }
            else{
                cout << "ERROR: Invalid Input - Input not in scope" << endl;
                *m_back_p = gobj.loop_back(2);
                continue;
            }
    cout << "Choose output to edit: ";
    cin >> setw (2) >>*m_intpar1_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = gobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
    cout << "Set new highest possible score: ";
    cin >> setw(2) >> *m_intpar3_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = gobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
    gobj.set_hps(*m_intpar1_p-1, *m_intpar2_p, *m_intpar3_p);
    *m_back_p = gobj.loop_back(2);
    }
    while(*m_back_p == 'Y' || *m_back_p == 'y');
}
void teacher::simult_input_grades(gradebook &gobj){
    do{
    system("CLS");
    cout << "\t\tINPUT OF GRADES - " << gobj.getcourseName() << endl << endl;
    gobj.student_grade_list();
    cout << endl;
    cout << "Enter component [WW | PT | ME]: ";    // one lang mag rurun
    cin >> setw(2) >> *m_stringpar1_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = gobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
            if (*m_stringpar1_p == "WW" || *m_stringpar1_p == "ww"){
                *m_intpar1_p = 0;
            }
            else if (*m_stringpar1_p == "PT" || *m_stringpar1_p == "pt"){
                *m_intpar1_p = 1;
            }
            else if (*m_stringpar1_p == "ME" || *m_stringpar1_p == "me"){
                *m_intpar1_p = 2;
            }
            else{
                cout << "ERROR: INVALID INPUT - Not inside the choices " << endl << endl;
                *m_back_p = gobj.loop_back(3);
                break;
            }
    cout << "Select output number: ";
    cin >> *m_intpar3_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *m_back_p = gobj.loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
    for (int i = 0; i <= gobj.get_no_of_students() ; i++){
        system("CLS");
        cout << "\t\tINPUT OF GRADES - " << gobj.getcourseName() << endl << endl;
        gobj.student_grade_list();
        cout << endl;
        if (i < gobj.get_no_of_students()){
        cout << "Enter Grade: ";
        cin >> *m_intpar2_p;
            try{
                if (*m_intpar2_p > gobj.get_hps_per_component(*m_intpar1_p, *m_intpar3_p)){
                    throw string("ERROR: Grade input greater than the highest possible score");
                }
                if (cin.fail()){
                    throw string ("ERROR: Invalid Input - You may have input character or special character");
                }
            }
            catch(string x){
                cout << x << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                *m_back_p = gobj.loop_back(2);
                continue;
            }
            cin.ignore(INT_MAX, '\n');
        gobj.setIndiv_grades(i, *m_intpar1_p, *m_intpar3_p-1, *m_intpar2_p);
        }
    }
    cout << endl;
    *m_back_p = gobj.loop_back(2);
    }
    while(*m_back_p == 'y' || *m_back_p == 'Y');
}
// OTHER FUNCTIONS
char loop_back(int ind1){
char back;

if (ind1 == 1){
    cout << "Go back to Menu? [Y / Menu]: ";
}
if (ind1 == 2){
    cout << "Continue? [Y / N]: ";
}
if (ind1 == 3){
    cout << "Go back to Main menu? [Y / Exit Program]: ";
}
if (ind1 == 4){
    cout << "Go back to Student Menu? [Y / Exit Program]: ";
}
cin >> back;
    if(!(back == 'Y' || back == 'y' || back == 'n' || back == 'N')){
        cout << "ERROR: 95 - Invalid Answer" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        system("pause");
    }
    if(cin.fail()){
        cout << "ERROR: 95 - Invalid Answer"<< endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        system("pause");
    }
    cin.ignore(INT_MAX, '\n');
return back;
}
void login_teacher(){
    option_p = new int;
    back_p = new char;
    int place_holder;
	do{			 // add exit function
    int teacher_option;
    int subject_indic;
    system("CLS");
    teacher_login.ui_username_password();
    *option_p = teacher_login.checking();
		if(teacher_login.checking() > 8){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << endl << "The username or password you entered is incorrect" << endl << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			*back_p = loop_back(2);
			continue;
		}
		else{
            if (*option_p == 0){
                teacher_main_menu(*grdbookptr1);
            }
            else if (*option_p == 1){
                teacher_main_menu(*grdbookptr2);
            }
            else if (*option_p == 2){
                teacher_main_menu(*grdbookptr3);
            }
            else if (*option_p == 3){
                teacher_main_menu(*grdbookptr4);
            }
            else if (*option_p == 4){
                teacher_main_menu(*grdbookptr5);
            }
            else if (*option_p == 5){
                teacher_main_menu(*grdbookptr6);
            }
            else if (*option_p == 6){
                teacher_main_menu(*grdbookptr7);
            }
            else if (*option_p == 7){
                teacher_main_menu(*grdbookptr8);
            }
		}
	*back_p == loop_back(2);
	}
	while(*back_p == 'y'|| *back_p == 'Y');
}
void admin_main_menu();
void teacher_main_menu(gradebook &gobj);
void student_main_menu(gradebook &gobj, int ind1);
void subject_option(int indic);
void studentinfo_settings(gradebook &gobj_studentinfo);
void course_settings(gradebook &gobj_coursesettings);
// MAIN
int main(){
    do{
    option_p = new int;
    back_p = new char;
    int place_holder1;
    bool login_success;
    login_success = false;
    system("title Gradebook - Batangas State University");
    system("CLS");
    cout << endl << endl << " \t\t ####   GRADEBOOK   ####" << endl << endl;
    cout << "Student [1]    |    Teacher [2]    |    Admin [3] " << endl << endl;
    cout << "Enter User Type: ";
    cin >> setw(1) >> *option_p;
        if (cin.fail()){
            cout << "ERROR: INVALID INPUT - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *back_p = loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
    	switch(*option_p){
    		case 1:             // student login -> student main menu
                do{
                system("CLS");
                *back_p = ' ';
                student_login.ui_username_password();
                place_holder1 = student_login.checking();
                    if(student_login.checking() >= 60){
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                        cout << endl << "The username or password you entered is incorrect" << endl << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                        login_success = false;
                        *back_p = loop_back(2);
                        continue;
                    }
                    else {
                        login_success = true;
                        break;
                    }
                }
                while(*back_p == 'Y' || *back_p == 'y');
    			if (login_success == true){
                    student_main_menu(*grdbookptr1, place_holder1);
    			}
    			*back_p = loop_back(3);
    			break;
    		case 2:             // teacher login -> teacher main menu
    			login_teacher();
    			*back_p = loop_back(3);
    			break;
    		case 3:             // admin login -> admin main menu
    		    do{
                    *back_p = ' ';
                    system("CLS");
                    admin_login.ui_username_password();
                        if(admin_login.checking() != 1){
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                        cout << endl << "The username or password you entered is incorrect" << endl << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                        login_success = false;
                        *back_p = loop_back(2);
                        continue;
                        }
                        else{
                            login_success = true;
                            break;
                        }
    		    }
    		    while(*back_p == 'Y' || *back_p == 'y');
    		    if (login_success == true){
                    admin_main_menu();;
    			}
    			*back_p = loop_back(3);
    			break;
            default:
                cout << "ERROR: INVALID INPUT - Not inside the choices " << endl << endl;
                *back_p = loop_back(3);
                break;
        }
    delete option_p;
    delete back_p;
    }
    while(*back_p == 'y' || *back_p == 'Y');
return 0;
}
void admin_main_menu(){
    do{
    option_p = new int;
    back_p = new char;
    system("CLS");
    cout << "\t\t ADMIN - GRADEBOOK " << endl << endl;
	cout << "Student Information Settings [1]" << endl;
	cout << "Course Settings              [2]" << endl;
	cout << "Log in Settings              [3]" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << endl << "Logout                       [9]" << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Enter option: ";
	cin >> setw(1) >> *option_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *back_p = loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
		switch(*option_p){
			case 1:
				subject_option(1);
				break;
			case 2:
                subject_option(2);
				break;
			case 3:
				adminobj.setup_logininfo();
				break;
            case 9:
                main();
		}
    }
    while(true);
}
void teacher_main_menu(gradebook &gobj){
    do{
    option_p = new int;
    back_p = new char;
    system("CLS");
    cout << "\t\tTEACHER MAIN MENU - " << gobj.getcourseName()<< endl << endl;
    cout << "Input of Grades                 [1]  " << endl;
    cout << "Editing of Grades               [2]" << endl;
    cout << "Editing Highest Possible Grade  [3]" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << endl << "Logout                          [9]" << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "Enter desired action: ";
    cin >> setw (1) >> *option_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *back_p = loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
   		switch(*option_p){
		case 1:
            teacherobj.simult_input_grades(gobj);
    		break;
        case 2:
            teacherobj.editing_grades(gobj);
            break;
        case 3:
            teacherobj.editing_hps(gobj);
            break;
        case 9:
            main();
        default:
            cout << "ERROR: INVALID INPUT - Not inside the choices " << endl << endl;
            *back_p = loop_back(3);
            break;
    	}
    }
    while(true);
}
void student_main_menu(gradebook &gobj, int ind1){
	do{
    option_p = new int;
    back_p = new char;
    system("CLS");
	cout << "\t\t STUDENT MENU " << endl << endl;
	gobj.getStudentinfo(ind1);
	cout << "View Grades      [1]   " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << endl << "Logout           [9]   " << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cin >> setw(1)>> *option_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *back_p = loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
		switch(*option_p){
			case 1:
			    cout << "wrokinh" << endl;
				studentobj.viewing_grades(ind1);
				*back_p = loop_back(4);
				cout << endl << endl;
				break;
			case 9:
                main();
			default:
				cout << "ERROR: Please select options that are available. " << endl;
				*back_p = loop_back(4);
				cout << endl << endl;
				break;
		}
	}
	while(true);
}
void course_settings(gradebook &gobj_coursesettings){        // ADMIN
	do{
    option_p = new int;
    back_p = new char;
	system("CLS");
	cout << "\t\t COURSE SETTINGS - " << gobj_coursesettings.getcourseName() << endl << endl;
	cout << "Changing Course name    [1] |  Change weight of output    [3] " << endl;
	cout << "Edit number of output   [2] |  Releasing of grades        [4]" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "Back to Admin Menu      [9]" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Enter option: ";
	cin >> setw(1) >> *option_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *back_p = loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
        switch(*option_p){
            case 1:
                adminobj.edit_course_name(gobj_coursesettings);
                break;
            case 2:
                adminobj.edit_no_of_output(gobj_coursesettings);
                break;
            case 3:
                adminobj.editing_weight_per_component(gobj_coursesettings);
                break;
            case 4:
                adminobj.releasing_grades(gobj_coursesettings);
                break;
            case 9:
                admin_main_menu();
        }
	}
	while(true);
}
void studentinfo_settings(gradebook &gobj_studentinfo){      // ADMIN
	do{
	option_p = new int;
	back_p = new char;
	system("CLS");
	cout << "\t\t STUDENT INFORMATION SETTINGS - " << gobj_studentinfo.getcourseName() << endl << endl;
	cout << "Input Student Information   [1]" << endl;
	cout << "Editing Student Information [2]" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "Back to Admin Main Menu     [9]" << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Enter option: ";
	cin >> setw(1) >>*option_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *back_p = loop_back(2);
            continue;
        }
        cin.ignore(INT_MAX, '\n');
		switch(*option_p){
			case 1:
				adminobj.func_studentinfo(gobj_studentinfo);
				break;
			case 2:
				adminobj.editing_student_info(gobj_studentinfo);
				break;
            case 9:
                admin_main_menu();
				break;
            default:
                cout << "ERROR: INVALID INPUT - Not inside the choices " << endl << endl;
    			*back_p = loop_back(2);
    			break;
		}
	}
	while(true);
}
void subject_option(int indic){
    system("CLS");
    option_p = new int;
    back_p = new char;
    bool fail = false;
    cout << "\t\tCHOOSE COURSE SUBJECT: " << endl << endl;
    cout << setw(24) << grdbookptr1->getcourseName() << " [1] " << setw(24) << grdbookptr2->getcourseName() <<" [2]" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 43);
    cout << setw(24) << grdbookptr3->getcourseName() << " [3] " << setw(24) << grdbookptr4->getcourseName() <<" [4]" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << setw(24) << grdbookptr5->getcourseName() << " [5] " << setw(24) << grdbookptr6->getcourseName() <<" [6]" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 43);
    cout << setw(24) << grdbookptr7->getcourseName() << " [7] " << setw(24) << grdbookptr8->getcourseName() <<" [8]" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    cout << "Choose course subject: ";
    cin >> setw(1) >>*option_p;
        if (cin.fail()){
            cout << "ERROR: Invalid Input - You may have input character or special character" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            *back_p = loop_back(2);
            fail = true;
        }
        cin.ignore(INT_MAX, '\n');
	if (fail == false){
        switch(*option_p){
            case 1:
                if (indic == 1){
                    studentinfo_settings(*grdbookptr1);
                }
                else if(indic == 2){
                    course_settings(*grdbookptr1);
                }
                break;
            case 2:
                if (indic == 1){
                    studentinfo_settings(*grdbookptr2);
                }
                else if (indic == 2){
                    course_settings(*grdbookptr2);
                }
                break;
            case 3:
                if (indic == 1){
                    studentinfo_settings(*grdbookptr3);
                }
                else if (indic ==2){
                    course_settings(*grdbookptr3);
                }
                break;
            case 4:
                if (indic == 1){
                    studentinfo_settings(*grdbookptr4);
                }
                else if (indic == 2){
                    course_settings(*grdbookptr4);
                }
                break;
            case 5:
                if (indic == 1){
                    studentinfo_settings(*grdbookptr5);
                }
                else if (indic == 2){
                    course_settings(*grdbookptr5);
                }
                break;
            case 6:
                if (indic == 1){
                    studentinfo_settings(*grdbookptr6);
                }
                else if (indic == 2){
                    course_settings(*grdbookptr6);
                }
                break;
            case 7:
                if (indic == 1){
                    studentinfo_settings(*grdbookptr7);
                }
                else if (indic == 2){
                    course_settings(*grdbookptr7);
                }
                break;
            case 8:
                if (indic == 1){
                    studentinfo_settings(*grdbookptr8);
                }
                else if (indic == 2){
                    course_settings(*grdbookptr8);
                }
                break;
            default:
                cout << "ERROR: Not in the given options" << endl << endl;
                break;
        }
	}
}

