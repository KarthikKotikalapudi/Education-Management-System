#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;


class admin{
    private:
    string password;
    public:
    string admin_id;
    admin(string id, string pwd){
        admin_id = id;
        password = pwd;
    }
    void check_password(){
        while(1){
            cout<<"Enter password: ";
            string pwd;
            cin>>pwd;
            if(pwd != password){
                cout<<"Wrong password"<<endl;
                cout<<"Please Try again"<<endl;
                continue;
            }
            else break;
        }
    }
    void change_password(string npwd){
        password = npwd;
    }
};

class faculty{
    private:
    string password;
    public:
    string faculty_id;
    faculty(string id, string pwd){
        faculty_id = id;
        password = pwd;
    }
    void check_password(){
        while(1){
            cout<<"Enter password: ";
            string pwd;
            cin>>pwd;
            if(pwd != password){
                cout<<"Wrong password"<<endl;
                cout<<"Please Try again"<<endl;
                continue;
            }
            else break;
        }
    }
    void change_password(string npwd){
        password = npwd;
    }
};

class course{
    private:
    int floating;
    int graded;
    public:
    string course_id;
    string faculty_id;
    vector<pair<string,string>> vec;
    course(string s, string ins){
        course_id = s;
        faculty_id = ins;
        floating = 0;
        graded = 0;
    }
    course(string id, string ins, int f, int g, vector<pair<string,string>> v){
        course_id = id;
        faculty_id = ins;
        floating = f;
        graded = g;
        vec = v;
    }
    void On_floating(){
        floating = 1;
    }
    void Off_floating(){
        floating = 0;
    }
    int show_floating_stat(){
        return floating;
    }
    int show_grading_stat(){
        return graded;
    }
    void add_student(string s){      
        vec.push_back(make_pair(s,"ungraded"));
    }
    void delete_student(string s){
        for(long long unsigned int i=0; i<vec.size(); i++){
            if(vec[i].first == s){
                vec.erase(vec.begin()+i);
            }
        }
    }
    int user_found(string s){
        for(long long unsigned int i=0; i<vec.size(); i++){
            if(vec[i].first == s){
                return 1;
            }
        }
        return 0;
    }
    string grade(string s){
        for(long long unsigned int i=0; i<vec.size(); i++){
            if(vec[i].first == s){
                return vec[i].second;
            }
        }
        return "Course not found";
    }
    void show_students(){
        for(long long unsigned int i=0; i<vec.size(); i++){
            cout<<vec[i].first<<endl;
        }
    }
    void Grade_students(){
        string grade;
        for(long long unsigned int i=0; i<vec.size(); i++){
            cout<<"Enter grade for "<<vec[i].first<<": ";
            cin>>grade;
            vec[i].second = grade;
        }
    }
    void Grading_done(){
        graded = 1;
    }
    
};

class student{
    private:
    string name;
    string roll_no;
    string password;
    public:
    string student_id;
    student(string s_id, string nm, string rno){
        student_id = s_id;
        //Setting password as "studentpassword" initially
        password = "studentpassword";
        name = nm;
        roll_no = rno;
    }
    student(string s_id, string nm, string rno, string pwd){
        student_id = s_id;
        password = pwd;
        name = nm;
        roll_no = rno;
    }
    void reg_course(string courseid, vector<course*> avail_courses){
        int count = 0;
        for(long long unsigned int i=0;i<avail_courses.size(); i++){
            if(avail_courses[i]->course_id == courseid){
                if(avail_courses[i]->show_floating_stat() == 0 || avail_courses[i]->show_grading_stat() != 0){
                    cout<<"Course not available for registration."<<endl;
                    break;
                }
                else{
                    avail_courses[i]->add_student(student_id);
                }
                count=1;
                break;
            }
        }
        if(count==0){
            cout<<"No course with that id is found"<<endl;
            return;
        }
    }
    void drop_course(string courseid, vector<course*> avail_courses){
        int count = 0;
        for(long long unsigned int i=0;i<avail_courses.size(); i++){
            if(avail_courses[i]->course_id == courseid){
                if(avail_courses[i]->show_grading_stat() != 0){
                    cout<<"Course not available for de-registration."<<endl;
                    break;
                }
                else{
                    avail_courses[i]->delete_student(student_id);
                }
                count=1;
                break;
            }
        }
        if(count==0){
            cout<<"No course with that id is found"<<endl;
            return;
        }
    }
    void check_password(){
        while(1){
            cout<<"Enter password: ";
            string pwd;
            cin>>pwd;
            if(pwd != password){
                cout<<"Wrong password"<<endl;
                cout<<"Please Try again"<<endl;
                continue;
            }
            else break;
        }
    }
    void change_password(string npwd){
        password = npwd;
    }
};

//Function to find if a file exists
int file_exists(string f){
    ifstream ifile;
    ifile.open(f);
    if(ifile) {
      return 1;
    }
    return 0;
}
class user{
    public:
    // Function which runs if the person who logged in is an admin
    void Admin_func(vector<course*> avail_courses, vector<student*> avail_students, vector<admin*> avail_admins, int k){
        avail_admins[k]->check_password();
        while(1){
            int num;
            cout << "Enter what you want to do(Press the number in bracket): "<<endl;
            cout << "Add course(1)    Delete course(2)    On floating(3)    Off floating(4)" << endl;
            cout << "Add student(5)    Delete student(6)    Change Password(7)    Logout(8)" << endl;
            cin>>num;
            //Adds course
            if(num == 1){
                string courseid, ins;
                cout<<"Floating will be off and there will be no students intially"<<endl;
                cout << "Enter course id: ";
                cin >> courseid;
                cout << "Enter instructor id: ";
                cin >> ins;
                course *crs = new course(courseid, ins);
                avail_courses.push_back(crs);
                int c = file_exists("Courses.csv");
                fstream fout;
                fout.open("Courses.csv", ios::out | ios::app);
                if(c != 0) fout<<"\n";
                fout<<courseid<<","<<ins<<","<<0<<","<<0;

                fout.close();
            }
            //Deletes course
            else if(num == 2){
                string courseid;
                cout << "Enter course id:"<<endl;
                cin >> courseid;
                int count=0;
                for(long long unsigned int i=0;i<avail_courses.size(); i++){
                    if(avail_courses[i]->course_id == courseid){
                        avail_courses.erase(avail_courses.begin()+i);
                        count=1;
                        break;
                    }
                }
                if(count==0){
                    cout<<"No course with that id is found"<<endl;
                    continue;
                }
                int l = 1, sz = avail_courses.size();
                
                fstream fin, fout;
                fin.open("Courses.csv", ios::in);
                fout.open("Coursesnew.csv", ios::out);
                string line, word;
                vector<string> row;
                while (!fin.eof()) {
                    row.clear();
                    getline(fin, line);
                    stringstream s(line);
                    while (getline(s, word, ',')) {
                        row.push_back(word);
                    }
                    if(row[0] == courseid){
                        continue;
                    }
                    for(long long unsigned int j=0; j < row.size()-1; j++){
                        fout<<row[j]<<",";
                    }
                    if(l<sz) fout<<row[row.size()-1]<<"\n";
                    else fout<<row[row.size()-1];
                    l++;
                }
                fin.close();
                fout.close();

                remove("Courses.csv");
                rename("Coursesnew.csv", "Courses.csv");
            }
            //On floating
            else if(num == 3){
                string courseid;
                cout << "Enter course id"<<endl;
                cin >> courseid;
                int count=0;
                for(long long unsigned int i=0;i<avail_courses.size(); i++){
                    if(avail_courses[i]->course_id == courseid){
                        avail_courses[i]->On_floating();
                        count=1;
                        break;
                    }
                }
                if(count==0) cout<<"No course with that id is found"<<endl;
            }
            //Off floating
            else if(num == 4){
                string courseid;
                cout << "Enter course id: ";
                cin >> courseid;
                int count=0;
                for(long long unsigned int i=0;i<avail_courses.size(); i++){
                    if(avail_courses[i]->course_id == courseid){
                        avail_courses[i]->Off_floating();
                        count=1;
                        break;
                    }
                }
                if(count==0) cout<<"No course with that id is found"<<endl;
            }
            //Adds student
            else if(num == 5){
                string studentid, studentname, rollno;
                cout << "Enter student id: ";
                cin >> studentid;
                cout << "Enter student name: ";
                cin >> studentname;
                cout << "Enter student roll no: ";
                cin >> rollno;
                student *stdnt = new student(studentid, studentname, rollno);
                avail_students.push_back(stdnt);
                
                int c = file_exists("Students.csv");
                fstream fout;
                fout.open("Students.csv", ios::out | ios::app);
                if(c != 0) fout<<"\n";
                fout<<studentid<<","<<studentname<<","<<rollno<<","<<"studentpassword";
                fout.close();

            }
            //Deletes Student
            else if(num == 6){
                string studentid;
                cout << "Enter student id"<<endl;
                cin >> studentid;
                long long unsigned int i,count = 0;
                for(i=0;i<avail_students.size(); i++){
                    if(avail_students[i]->student_id == studentid){
                        avail_students.erase(avail_students.begin()+i);
                        count=1;
                        break;
                    }
                }
                if(count==0){
                    cout<<"No student with that id is found"<<endl;
                    continue;
                }
                int l = 1, sz = avail_students.size();
                
                fstream fin, fout;
                fin.open("Students.csv", ios::in);
                fout.open("Studentsnew.csv", ios::out);
                string line, word;
                vector<string> row;
                while (!fin.eof()) {
                    row.clear();
                    getline(fin, line);
                    stringstream s(line);
                    while (getline(s, word, ',')) {
                        row.push_back(word);
                    }
                    if(row[0] == avail_students[i]->student_id){
                        continue;
                    }
                    for(long long unsigned int j=0; j < row.size()-1; j++){
                        fout<<row[j]<<",";
                    }
                    if(l<sz) fout<<row[row.size()-1]<<"\n";
                    else fout<<row[row.size()-1];
                    l++; 
                }
                fin.close();
                fout.close();

                remove("Students.csv");
                rename("Studentsnew.csv", "Students.csv");
            }
            //Changes password
            else if(num == 7){
                string npwd;
                cout << "Enter new password: ";
                cin >> npwd;
                avail_admins[k]->change_password(npwd);
    
                fstream fin, fout;
                fin.open("Admins.csv", ios::in);
                fout.open("Adminsnew.csv", ios::out);
                string line, word;
                vector<string> row;
                while (!fin.eof()) {
                    row.clear();
                    getline(fin, line);
                    stringstream s(line);
                    while (getline(s, word, ',')) {
                        row.push_back(word);
                    }
                    if(row[0] == avail_admins[k]->admin_id){
                        row[1] = npwd;
                    }
                    for(long long unsigned int i=0; i < row.size()-1; i++){
                        fout<<row[i]<<",";
                    }
                    fout<<row[row.size()-1]<<"\n";
                }
                fin.close();
                fout.close();
                
                remove("Admins.csv");
                rename("Adminsnew.csv", "Admins.csv");
            }
            //Logout
            else if(num == 8){
                break;
            }
            //Wrong number pressed
            else{
                cout<<"Wrong choice. Please try again."<<endl;
                break;
            }
            cout<<"Done"<<endl;
        }
    }
    // Function which runs if the person who logged in is a student
    void Student_func(vector<course*> avail_courses, vector<student*> avail_students, int i){
        avail_students[i]->check_password();
        while(1){
            int num, count;
            cout << "Enter what you want to do(Press the number in bracket): "<<endl;
            cout << "Register course(1)    Drop course(2)    Show courses(3)    Show grades(4)    Change password(5)    Logout(6)" << endl;
            cin >> num;
            //Registers to the course
            if(num == 1){
                string courseid;
                cout << "Enter course id: ";
                cin >> courseid;
                int count = 0;
                for(long long unsigned int k = 0; k < avail_courses.size(); k++){
                    if(avail_courses[k]->course_id == courseid){
                        for(long long unsigned int l = 0; l<avail_courses[k]->vec.size(); l++){
                            if(avail_courses[k]->vec[l].first == avail_students[i]->student_id){
                                count=1;
                            }
                        }
                    }
                }
                if(count == 1){
                    cout<<"Already registered."<<endl;
                    continue;
                }
                avail_students[i]->reg_course(courseid, avail_courses);
                int l = 1, sz = avail_courses.size();
                
                fstream fin, fout;
                fin.open("Courses.csv", ios::in);
                fout.open("Coursesnew.csv", ios::out);
                string line, word;
                vector<string> row;
                while (!fin.eof()) {
                    row.clear();
                    getline(fin, line);
                    stringstream s(line);
                    while (getline(s, word, ',')) {
                        row.push_back(word);
                    }
                    if(row[0] == courseid){
                        row.push_back(avail_students[i]->student_id);
                        row.push_back("ungraded");
                    }
                    for(long long unsigned int j=0; j < row.size()-1; j++){
                        fout<<row[j]<<",";
                    }
                    if(l<sz) fout<<row[row.size()-1]<<"\n";
                    else fout<<row[row.size()-1];
                    l++;
                }
                fin.close();
                fout.close();

                remove("Courses.csv");
                rename("Coursesnew.csv", "Courses.csv");
            }
            //De-registers the course
            else if(num == 2){
                string courseid;
                cout << "Enter course id: ";
                cin >> courseid;
                avail_students[i]->drop_course(courseid, avail_courses);
                int l = 1, sz = avail_courses.size();

                fstream fin, fout;
                fin.open("Courses.csv", ios::in);
                fout.open("Coursesnew.csv", ios::out);
                string line, word;
                vector<string> row;
                while (!fin.eof()) {
                    row.clear();
                    getline(fin, line);
                    stringstream s(line);
                    while (getline(s, word, ',')) {
                        row.push_back(word);
                    }
                    long long unsigned int count = 0;
                    if(row[0] == courseid){
                        for(long long unsigned int j=0; j < row.size(); j++){
                            if(row[j] == avail_students[i]->student_id){
                                j++;
                                continue;
                            }
                            else{
                                count++;
                                if(count<row.size()-2)
                                fout<<row[j]<<",";
                                else{
                                    if(l<sz) fout<<row[j]<<"\n";
                                    else fout<<row[j];
                                }
                            }
                            
                        }
                        l++;
                        continue;
                    }
                    for(long long unsigned int j=0; j < row.size()-1; j++){
                        fout<<row[j]<<",";
                    }
                    if(l<sz) fout<<row[row.size()-1]<<"\n";
                    else fout<<row[row.size()-1];
                    l++;
                }
                fin.close();
                fout.close();

                remove("Courses.csv");
                rename("Coursesnew.csv", "Courses.csv");
            }
            //Shows registered courses
            else if(num == 3){
                for(long long unsigned int j=0; j < avail_courses.size(); j++){
                    if(avail_courses[j]->user_found(avail_students[i]->student_id) == 1){
                        cout<<avail_courses[j]->course_id<<endl;
                        count = 1;
                    }
                }
                if(count != 1){
                    cout<<"No courses found"<<endl;
                    continue;
                }
            }
            //Shows grades
            else if(num == 4){
            for(long long unsigned int j=0; j < avail_courses.size(); j++){
                    if(avail_courses[j]->user_found(avail_students[i]->student_id) == 1){
                        cout<<avail_courses[j]->course_id<<"    "<<avail_courses[j]->grade(avail_students[i]->student_id)<<endl;
                        count = 1;
                    }
                } 
                if(count != 1){
                    cout<<"No courses found"<<endl;
                    continue;
                }
            }
            //Changes password
            else if(num == 5){
                string npwd;
                cout<<"Enter new password: ";
                cin>>npwd;
                avail_students[i]->change_password(npwd);
                
                fstream fin, fout;
                fin.open("Students.csv", ios::in);
                fout.open("Studentsnew.csv", ios::out);
                string line, word;
                vector<string> row;
                while (!fin.eof()) {
                    row.clear();
                    getline(fin, line);
                    stringstream s(line);
                    while (getline(s, word, ',')) {
                        row.push_back(word);
                    }
                    if(row[0] == avail_students[i]->student_id){
                        row[1] = npwd;
                    }
                    for(long long unsigned int j=0; j < row.size()-1; j++){
                        fout<<row[j]<<",";
                    }
                    fout<<row[row.size()-1]<<"\n";
                }
                fin.close();
                fout.close();

                remove("Students.csv");
                rename("Studentsnew.csv", "Students.csv");
            }
            //Logs out
            else if(num == 6){
                break;
            }
            //Wrong key pressed
            else{
                cout<<"Wrong choice. Please try again."<<endl;
                break;
            }
            cout<<"Done"<<endl;
        }
    }
    // Function which runs if the person who logged in is Faculty
    void Faculty_func(vector<course*>avail_courses, vector<faculty*> avail_faculty, int i){
        avail_faculty[i]->check_password();
        while(1){
            int num;
            cout << "Enter what you want to do(Press the number in bracket): "<<endl;
            cout << "Grade course(1)    Show students(2)    Change password(3)    Logout(4)" << endl;
            cin >> num;
            int count;
            //Grades course
            if(num == 1){
                string courseid;
                cout << "Enter course id: ";
                cin >> courseid;
                for(long long unsigned int j=0; j < avail_courses.size(); j++){
                    if(avail_courses[j]->course_id == courseid && avail_courses[j]->faculty_id == avail_faculty[i]->faculty_id){
                        avail_courses[j]->Grade_students();
                        avail_courses[j]->Grading_done();
                        count = 1;
                        break;
                    }
                }
                if(count != 1){
                    cout<<"Course not found"<<endl;
                    continue;
                }
                int l = 1, sz = avail_courses.size();
                
                fstream fin, fout;
                fin.open("Courses.csv", ios::in);
                fout.open("Coursesnew.csv", ios::out);
                string line, word;
                vector<string> row;
                while (!fin.eof()) {
                    row.clear();
                    getline(fin, line);
                    stringstream s(line);
                    while (getline(s, word, ',')) {
                        row.push_back(word);
                    }
                    int j=0;
                    if(row[0] == courseid){
                        for(long long unsigned int k = 5; k < row.size(); k += 2){
                            row[k] = avail_courses[i]->vec[j].second;
                            j++; 
                        }
                    }
                    
                    for(long long unsigned int j=0; j < row.size()-1; j++){
                        fout<<row[j]<<",";
                    }
                    if(l<sz) fout<<row[row.size()-1]<<"\n";
                    else fout<<row[row.size()-1];
                    l++;
                }
                fin.close();
                fout.close();

                remove("Courses.csv");
                rename("Coursesnew.csv", "Courses.csv");
            }
            //Shows students
            else if(num == 2){
                string courseid;
                int count;
                cout << "Enter course id: ";
                cin >> courseid;
                for(long long unsigned int j=0; j < avail_courses.size(); j++){
                    if(avail_courses[j]->course_id == courseid && avail_courses[j]->faculty_id == avail_faculty[i]->faculty_id){
                        avail_courses[j]->show_students();
                        count = 1;
                        break;
                    }
                }
                if(count != 1){
                    cout<<"Course not found"<<endl;
                    continue;
                }
            }
            //Changes password
            else if(num == 3){
                string npwd;
                cout<<"Enter new password: ";
                cin>>npwd;
                avail_faculty[i]->change_password(npwd);
                
                fstream fin, fout;
                fin.open("Faculty.csv", ios::in);
                fout.open("Facultynew.csv", ios::out);
                string line, word;
                vector<string> row;
                while (!fin.eof()) {
                    row.clear();
                    getline(fin, line);
                    stringstream s(line);
                    while (getline(s, word, ',')) {
                        row.push_back(word);
                    }
                    if(row[0] == avail_faculty[i]->faculty_id){
                        row[1] = npwd;
                    }
                    for(long long unsigned int j=0; j < row.size()-1; j++){
                        fout<<row[j]<<",";
                    }
                    fout<<row[row.size()-1]<<"\n";
                }
                fin.close();
                fout.close();

                remove("Faculty.csv");
                rename("Facultynew.csv", "Faculty.csv");
            }
            //Logs out
            else if(num == 4){
                break;
            }
            //Wrong number pressed
            else{
                cout<<"Wrong choice. Please try again."<<endl;
                break;
            }
            cout<<"Done"<<endl;
        }
    }
};
//Reads the data from the file which stored the admin data
vector<admin*> Admin_data(vector<admin*> avail_admins){
    
    fstream fin;
    fin.open("Admins.csv", ios::in);
    string id, pwd, line, word;
    vector<string> row;
    while(!fin.eof()){
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while(getline(s, word, ',')){
            row.push_back(word);
        }
        id = row[0];
        pwd = row[1];
        admin*admin_new = new admin(id, pwd);
        avail_admins.push_back(admin_new);
    }
    fin.close();
    return avail_admins;
}
//Reads the data from the file which stored the faculty data
vector<faculty*> Faculty_data(vector<faculty*> avail_faculty){
    
    fstream fin;
    fin.open("Faculty.csv", ios::in);
    string id, pwd, line, word;
    vector<string> row;
    while(!fin.eof()){
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while(getline(s, word, ',')){
            row.push_back(word);
        }
        id = row[0];
        pwd = row[1];
        faculty*faculty_new = new faculty(id, pwd);
        avail_faculty.push_back(faculty_new);
    }
    fin.close();
    return avail_faculty;
}
//Reads the data from the file which stored the student data
vector<student*> Student_data(vector<student*> avail_students){
    
    fstream fin;
    fin.open("Students.csv", ios::in);
    string id, pwd, line, word, nm, rno;
    vector<string> row;
    while(!fin.eof()){
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while(getline(s, word, ',')){
            row.push_back(word);
        }
        id = row[0];
        pwd = row[1];
        nm = row[2];
        rno = row[3];
        student*student_new = new student(id, pwd, nm, rno);
        avail_students.push_back(student_new);
    }
    fin.close();
    return avail_students;
}
//Reads the data from the file which stored the course data
vector<course*> Course_data(vector<course*> avail_courses){
    
    fstream fin;
    fin.open("Courses.csv", ios::in);
    string id, ins, line, word;
    int fltng, grd;
    vector<pair<string,string>> stdnt_grds;
    vector<string> row;
    while(!fin.eof()){
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while(getline(s, word, ',')){
            row.push_back(word);
        }
        id = row[0];
        ins = row[1];
        fltng = stoi(row[2]);
        grd = stoi(row[3]);
        int j = 0;
        long long unsigned int i = 4;
        if(row.size() < 5){
            course*course_new = new course(id, ins, fltng, grd, stdnt_grds);
            avail_courses.push_back(course_new);
            continue;
        }
        while(i < row.size()){
            stdnt_grds.push_back(make_pair(row[i],row[i+1]));
            i+=2;
            j++;
        }
        course*course_new = new course(id, ins, fltng, grd, stdnt_grds);
        avail_courses.push_back(course_new);
    }
    fin.close();
    return avail_courses;
}

void create_admin(){

}

int main(){
    string userid;
    vector<admin*> avail_admins;
    vector<faculty*> avail_faculty;
    vector<student*> avail_students;
    vector<course*> avail_courses;

    int found;
    found = file_exists("Admins.csv");
    if(found != 1){
        cout<<"Files containing information of existing Admins not found"<<endl;
        cout<<"Do you want to create a completely new database by storing new admin and faculty details and deleting previous ones?(Press Y if yes)"<<endl;
        string Response;
        cin>>Response;
        if(Response == "Y" || "y"){
            remove("Admins.csv");
            remove("Faculty.csv");
            remove("Courses.csv");
            remove("Students.csv");

            while(1){
                cout<<"Whom do you want to add? Press number in the bracket"<<endl;
                cout<<"Admin(1)     Faculty(2)      exit(3)"<<endl;
                int num;
                cin>>num;
                //Adds admin
                if(num == 1){
                    cout<<"Intially password for admins will be set as 'adminpassword'. Enter the new admin id"<<endl;
                    string id;
                    cin>>id;

                    int c = file_exists("Admins.csv");
                    fstream fout;
                    fout.open("Admins.csv", ios::out | ios::app);
                    if(c != 0) fout<<"\n";
                    fout<<id<<","<<"adminpassword";
                    fout.close();
                }
                //Adds faculty member
                else if(num == 2){
                    cout<<"Intially password for faculty will be set as 'facultypassword'. Enter the new faculty id"<<endl;
                    string id;
                    cin>>id;
                    
                    int c = file_exists("Faculty.csv");
                    fstream fout;
                    fout.open("Faculty.csv", ios::out | ios::app);
                    if(c != 0) fout<<"\n";
                    fout<<id<<","<<"facultypassword";
                    fout.close();
                }
                //exits
                else if(num == 3){
                    break;
                }
                else{
                    cout<<"Wrong option. Please try again."<<endl;
                    continue;
                }

            }
        }
    }

    while(1){
        avail_admins.clear();
        avail_faculty.clear();
        avail_students.clear();
        avail_courses.clear();

        avail_admins = Admin_data(avail_admins);
        avail_faculty = Faculty_data(avail_faculty);
        if(file_exists("Students.csv") == 1) avail_students = Student_data(avail_students);
        if(file_exists("Courses.csv") == 1) avail_courses = Course_data(avail_courses);
        
        user User;
        cout<<"Login"<<endl;
        cout<<"Enter 'exit' to exit"<<endl;
        cout<<"Enter user id: ";
        cin>>userid;
        if(userid == "exit") return 0;
        int count = 0;
        for(long long unsigned int i=0;i<avail_admins.size(); i++){
            if(avail_admins[i]->admin_id == userid){
                User.Admin_func(avail_courses, avail_students, avail_admins, i);
                count = 1;
                break;
            }
        }
        for(long long unsigned int i=0;i<avail_students.size(); i++){
            if(avail_students[i]->student_id == userid){
                User.Student_func(avail_courses, avail_students, i);
                count = 1;
                break;
            }
        }
        for(long long unsigned int i=0;i<avail_faculty.size(); i++){
            if(avail_faculty[i]->faculty_id == userid){
                User.Faculty_func(avail_courses, avail_faculty, i);
                count = 1;
                break;
            }
        }
        if(count == 0) cout<<"User id not found. Try again"<<endl;
    }
    return 0;
}