#ifndef SECURITY_H
#define SECURITY_H
#include <string>
using namespace std;

class security{
	private:
		string teacher_username[8] = {"comprog", "diffcal","numbertheory","pe","artappre","rph","filipino","rotc"};
		string teacher_password[8] = {"user123", "user123","user123","user123","user123","user123","user123","user123"};
		string student_username[60] =
		{"student1", "student2" ,"student3", "student4", "student5", "student6", "student7", "student8", "student9", "student10",
		"student11", "student12" ,"student13", "student14", "student15", "student16", "student17", "student18", "student19", "student20",
		"student21", "student22" ,"student23", "student24", "student25", "student26", "student27", "student28", "student29", "student30",
		"student31", "student32" ,"student33", "student34", "student35", "student36", "student37", "student38", "student39", "student40",
		"student41", "student42" ,"student43", "student44", "student45", "student46", "student47", "student48", "student49", "student50",
		"student51", "student52" ,"student53", "student54", "student55", "student56", "student57", "student58", "student59", "student60",
		};
		string student_password[60] =
		{"pass1", "pass2", "pass3", "pass4", "pass5", "pass6", "pass7", "pass8", "pass9", "pass10",
		"pass11", "pass12", "pass13", "pass14", "pass15", "pass16", "pass17", "pass18", "pass19", "pass20",
		"pass21", "pass22", "pass23", "pass24", "pass25", "pass26", "pass27", "pass28", "pass29", "pass30",
		"pass31", "pass32", "pass33", "pass34", "pass35", "pass36", "pass37", "pass38", "pass39", "pass40",
		"pass41", "pass42", "pass43", "pass44", "pass45", "pass46", "pass47", "pass48", "pass49", "pass50",
		"pass51", "pass52", "pass53", "pass54", "pass55", "pass56", "pass57", "pass58", "p	ass59", "pass60",
		};
		string admin_username = {"admin"};
		string admin_password = {"admin"};
		int usertype_indic;
		int checking_ind1 = 100;
	protected:
		string ui_username;
		string ui_password;
		char *m_back_p;
		int *m_intpar1_p;
	public:
		security(int);
		~security();
		char loop_back(int);
		void set_username(string, int);
		void set_password(string, int);
		int checking();
		void default_password();
		void ui_username_password();
		int return_indicator_login();
};

#endif
