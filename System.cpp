
#include <stdio.h>
#include <iostream>
#include "System.h"
#include <math.h>
#include <fstream>
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
int hashForStudent(const string& key,int size){
    // use the knowledge of discrete math that (a+b) mod c=((a mod c)+(b mod c)) mod c to prevent the overflow
    int sum=0;
    for(int i=0;i<key.length();i++){
	sum =((sum%size)+((key[i]*((int)(pow(10,i))))%size))%size;
        
    }
    return sum;

}
int hashForCourse(const string& key,int size){
   // use the knowledge of discrete math that (a+b) mod c=((a mod c)+(b mod c)) mod c to prevent the overflow
    int sum=0;
    for(int i=0;i<key.length();i++){
        //for input is alphabet
        if(isalpha(key[i])){
            short temp= key[i]-'A'+11;
            sum=((sum%size)+((temp*((int)(pow(10,i))))%size))%size;
        }
        else if(isdigit(key[i])){
	    // for input is number
            sum =((sum%size)+((key[i]*((int)(pow(10,i))))%size))%size;
        }
        
    }
    return sum;
}

RegisterSystem::RegisterSystem():StudentsRecords(hashForStudent,29),CoursesRecords(hashForCourse, 17),studentIndex(hashForStudent,29),courseIndex(hashForCourse, 17){}

RegisterSystem::RegisterSystem(const RegisterSystem& reg):StudentsRecords(reg.StudentsRecords),CoursesRecords(reg.CoursesRecords),studentIndex(reg.studentIndex),courseIndex(reg.courseIndex){}

RegisterSystem::~RegisterSystem(){}

void RegisterSystem::insertStudent(){
    string input;
    Student stuTemp;
    do{
        cout<<"Enter the student ID: ";
        getline(cin,input);
        if(isExistStudent(input)){
            cout << "Student already exist" << endl;
            break;
        }
        //finish asking only when the input is valid
        while(!stuTemp.isValidID(input)){
            cout << "Invalid input, re-enter again [student ID]: ";
              getline(cin,input);
        }
        stuTemp.setID(input);
        //finish asking only when the input is valid
        cout<<"Enter the student name: ";
        getline(cin,input);
        while(!stuTemp.isValidName(input)){
            cout << "Invalid input, re-enter again [student name]: ";
            getline(cin,input);
        }
        stuTemp.setName(input);
        
        
        //finish asking only when the input is valid
        cout<<"Enter the student year[1-3]: ";
        getline(cin,input);
        while(!stuTemp.isValidYear(input)){
            cout << "Invalid input, re-enter again [student year]: ";
            getline(cin,input);
            
        }
        stuTemp.setYear(input);
        //finish asking only when the input is valid
        cout<<"Enter the student gender [M,F]: ";
        getline(cin,input);
        while(!stuTemp.isValidGender(input)){
            cout << "Invalid input, re-enter again [M,F]: ";
            getline(cin,input);
        }
        stuTemp.setGender(input);
        //insert the student in the database
        StudentsRecords.insert(stuTemp.getID(), stuTemp);
        cout<<"Creation of student record successful"<<endl;
        
    

    }while(false);
}

void RegisterSystem::modifyStudent(){
    string input;
    Student* stuTemp;
    do{
        cout<<"Enter the student ID: ";
        getline(cin,input);
        while(!stuTemp->isValidID(input)){
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin,input);
        }
        //check whether the student record has exist
        if(!isExistStudent(input)){
            cout << "Student not exist" << endl;
            break;
        }
        if(stuTemp->isValidID(input)){
            stuTemp=(StudentsRecords[input]);
        }
        string id=input;
        stuTemp->setID(input);
        
        //finish asking only when the input is valid
        cout<<"Enter the student name [";
        cout<<stuTemp->getName()<<"]: ";
        getline(cin,input);
        while(!stuTemp->isValidName(input)){
            cout << "Invalid input, re-enter again [";
            cout<<stuTemp->getName()<<"]: ";
            getline(cin,input);
        }
        stuTemp->setName(input);
        //finish asking only when the input is valid
        cout<<"Enter the student year [";
        cout<<stuTemp->getYear()<<"]: ";
        getline(cin,input);
        while(!stuTemp->isValidYear(input)){
            cout << "Invalid input, re-enter again [";
            cout<<stuTemp->getYear()<<"]: ";
            getline(cin,input);
            
        }
        
        stuTemp->setYear(input);
        //finish asking only when the input is valid
        cout<<"Enter the student gender ["<<stuTemp->getGender()<<"]: ";
        getline(cin,input);
        while(!stuTemp->isValidGender(input)){
            cout << "Invalid input, re-enter again ["<<stuTemp->getGender()<<"]: ";
            getline(cin,input);
        }
        stuTemp->setGender(input);
        
        cout<<"Modification of student record successful"<<endl;
        
        
    }while(false);
}

void RegisterSystem::deleteStudent(){
    string input;
    Student* stuTemp;
    do{ //finish asking only when the input is valid
        cout<<"Enter the student ID: ";
        getline(cin,input);
        while(!stuTemp->isValidID(input)){
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin,input);
        }
        //check whether teh student record exist or not
        if(!isExistStudent(input)){
            cout << "Student not exist" << endl;
            break;
        }
        StudentsRecords.remove(input);
       int count=0;
       for(SDList<CourseSelection>::iterator itr=SelectionRecords.begin();itr!=SelectionRecords.end();itr++){
	  if((*itr).getId()==input){
	  count++;
	  }
	 
       }
       // when a student record is deleted, it will evoke below part to delete all selectionrecords about this student
       while(count!=0){
	  for(SDList<CourseSelection>::iterator itr=SelectionRecords.begin();itr!=SelectionRecords.end();itr++){
	      if((*itr).getId()==input){
		CourseSelection* tempPtr;
		string id=input;
		string code=(*itr).getCode();

		if(isCourseRegistered(code,tempPtr,id)){
		SelectionRecords.remove(*tempPtr);
		courseIndex.remove(code);
		studentIndex.remove(id);
		count--;
		break;
		}
	      }
	 
	  }
       }
        
        cout<<"Deletion of student record successful"<<endl;
    }while(false);
    
}

void RegisterSystem::queryStudent(){
    string input;
    Student* stuTemp;
    do{ //finish asking only when the input is valid
        cout<<"Enter the student ID: ";
        getline(cin,input);
        while(!stuTemp->isValidID(input)){
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin,input);
        }
        if(!isExistStudent(input)){
            cout << "Student not exist" << endl;
            break;
        }
        if(stuTemp->isValidID(input)){
            stuTemp=(StudentsRecords[input]);
        }
        cout<<"\nID:      "<<stuTemp->getID()<<endl;
        cout<<"Name:    "<<stuTemp->getName()<<endl;
        cout<<"Year:    "<<stuTemp->getYear()<<endl;
        cout<<"Gender : "<<stuTemp->getGender()<<"\n"<<endl;
        
    }while(false);
    
}

void RegisterSystem::insertCourse(){
    string input;
    Course courseTemp;
    do{ //finish asking only when the input is valid
        cout<<"Enter the course code: ";
        getline(cin,input);
        if(isExistCourse(input)){
            cout << "Course already exist\n" << endl;
            break;
        }
        while(!courseTemp.isValidCode(input)){
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin,input);
        }
        courseTemp.setCode(input);
        //finish asking only when the input is valid
        cout<<"Enter the course name:  ";
        getline(cin,input);
        while(!courseTemp.isValidCourse(input)){
            cout << "Invalid input, re-enter again [course name]: ";
            getline(cin,input);
        }
        courseTemp.setCourseName(input);
        //finish asking only when the input is valid
        cout<<"Enter the course credit [0-5]: ";
        getline(cin,input);
        while(!courseTemp.isValidCredit(input)){
            cout << "Invalid input, re-enter again [course credit]: ";
            getline(cin,input);
        }
        courseTemp.setCredit(input);
	//insert a new course record into the database
        CoursesRecords.insert(courseTemp.getCode(), courseTemp);
        cout<<"Creation of course record successful"<<endl;
        
    }while(false);
}

void RegisterSystem::modifyCourse(){
    string input;
    Course* courseTemp;
    do{ //finish asking only when the input is valid
        cout<<"Enter the course code: ";
        getline(cin,input);
        while(!courseTemp->isValidCode(input)){
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin,input);
        }
        
        if(!isExistCourse(input)){
            cout << "Course not exist" << endl;
            break;
        }
        if(courseTemp->isValidCode(input)){
            courseTemp=(CoursesRecords[input]);
        }
        string id=input;
        courseTemp->setCode(input);
        
        //finish asking only when the input is valid
        cout<<"Enter the course name [";
        cout<<courseTemp->getCourseName()<<"]: ";
        getline(cin,input);
        while(!courseTemp->isValidCourse(input)){
            cout << "Invalid input, re-enter again [";
            cout<<courseTemp->getCourseName()<<"]: ";
            getline(cin,input);
        }
        courseTemp->setCourseName(input);
        //finish asking only when the input is valid
        cout<<"Enter the course credit [";
        cout<<courseTemp->getCredit()<<"]: ";
        getline(cin,input);
        while(!courseTemp->isValidCredit(input)){
            cout << "Invalid input, re-enter again [";
            cout<<courseTemp->getCredit()<<"]: ";
            getline(cin,input);
            
        }
        
        courseTemp->setCredit(input);
        cout<<"Modification of course record successful"<<endl;
    }while(false);
}

void RegisterSystem::deleteCourse(){
    string input;
    Course* courseTemp;
    do{ //finish asking only when the input is valid
        cout<<"Enter the course code: ";
        getline(cin,input);
        while(!courseTemp->isValidCode(input)){
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin,input);
        }
        if(!isExistCourse(input)){
            cout << "Course not exist" << endl;
            break;
        }
        // this part check whether a register of the course exist. If so, the course can not be deleted
        if(isCourseRegistered(input,"-1")){
            cout << "Some students already registered in this course, deletion fail" << endl;
            break;
        }
        CoursesRecords.remove(input);
        cout<<"Deletion of course record successful"<<endl;
    }while(false);
    
}

void RegisterSystem::queryCourse(){
    string input;
    Course* courseTemp;
    do{
        cout<<"Enter the course code: ";
        getline(cin,input);
        while(!courseTemp->isValidCode(input)){
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin,input);
        }
        if(!isExistCourse(input)){
            cout << "Course not exist" << endl;
            break;
        }
        if(courseTemp->isValidCode(input)){
            courseTemp=(CoursesRecords[input]);
        }
        cout<<"\nCode:    "<<courseTemp->getCode()<<endl;
        cout<<"Name:    "<<courseTemp->getCourseName()<<endl;
        cout<<"Credit:  "<<courseTemp->getCredit()<<"\n"<<endl;
        
    }while(false);
}

void RegisterSystem::addSelection(){
    string input;
    CourseSelection selectionTemp;
    do{ //finish asking only when the input is valid
        cout<<"Enter the student ID: ";
        getline(cin,input);
        while(!selectionTemp.isValidID(input)){
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin,input);
        }
        string id=input;
        if(!isExistStudent(id)){
            cout<<"Student not exist"<<endl;
            break;
        }
        
        //finish asking only when the input is valid
        cout<<"Enter the course code:  ";
        getline(cin,input);
        while(!selectionTemp.isValidCode(input)){
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin,input);
        }
        string code=input;
        if(!isExistCourse(code)){
            cout<<"Course not exist"<<endl;
            break;
        }
        
        //if the record of register has existed, no need to insert the same one
        if(isCourseRegistered(code,id)){
            cout<<"The student already registered the course"<<endl;
            break;
        }
        selectionTemp.setID(id);
        selectionTemp.setCode(code);
        //insert the record to database. Also insert its two new pointer to the index hash table for further use
        CourseSelection* ptrRecoder=SelectionRecords.insert(selectionTemp);
        studentIndex.insert(id, ptrRecoder);
        courseIndex.insert(code, ptrRecoder);
       
        cout<<"Add course successful"<<endl;
        
    }while(false);
}

void RegisterSystem::dropSelection(){
    string input;
    CourseSelection* selectionTemp;
    do{
        cout<<"Enter the student ID: ";
        getline(cin,input);
        while(!selectionTemp->isValidID(input)){
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin,input);
        }
        string id=input;
        if(!isExistStudent(id)){
            cout<<"Student not exist"<<endl;
            break;
        }
        
        
        cout<<"Enter the course code:  ";
        getline(cin,input);
        while(!selectionTemp->isValidCode(input)){
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin,input);
        }
        string code=input;
        if(!isExistCourse(code)){
            cout<<"Course not exist"<<endl;
            break;
        }
        //delete only when the record exists
        if(isCourseRegistered(code,selectionTemp,id)){
            SelectionRecords.remove(selectionTemp);
            courseIndex.remove(code, selectionTemp);
            studentIndex.remove(id, selectionTemp);
            cout<<"Deletion of registration record successful"<<endl;
        }
        else {
            cout<<"The registration record not exist"<<endl;
            break;
        }
        
    }while(false);
}

void RegisterSystem::modifyMark(){
    string input;
    CourseSelection* selectionTemp;
    do{ //finish asking only when the input is valid
        cout<<"Enter the student ID: ";
        getline(cin,input);
        while(!selectionTemp->isValidID(input)){
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin,input);
        }
        string id=input;
        if(!isExistStudent(id)){
            cout<<"Student not exist"<<endl;
            break;
        }
        
        //finish asking only when the input is valid
        cout<<"Enter the course code:  ";
        getline(cin,input);
        while(!selectionTemp->isValidCode(input)){
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin,input);
        }
        string code=input;
        if(!isExistCourse(code)){
            cout<<"Course not exist"<<endl;
            break;
        }
        //only whenthe record exist you can modify the exam mark
        if(isCourseRegistered(code,selectionTemp,id)){
            cout<<"Enter the exam mark [N/A]: ";
            getline(cin,input);
            while(!selectionTemp->isValidMark(input)){
                cout << "Invalid input, re-enter again [exam mark]: ";
                getline(cin,input);
            }
            selectionTemp->setMark(input);
            cout<<"Modification of exam mark successful"<<endl;
        }
        else{
	    cout<<"The registration record not exist"<<endl;
            break;
	}
        
        
    }while(false);
    
}

void RegisterSystem::querySelection(){
    string input;
    CourseSelection* selectionTemp;
    do{ //finish asking only when the input is valid
        cout<<"Enter the student ID: ";
        getline(cin,input);
        while(!selectionTemp->isValidID(input)){
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin,input);
        }
        string id=input;
        if(!isExistStudent(id)){
            cout<<"Student not exist"<<endl;
            break;
        }
        
        //finish asking only when the input is valid
        cout<<"Enter the course code:  ";
        getline(cin,input);
        while(!selectionTemp->isValidCode(input)){
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin,input);
        }
        string code=input;
        if(!isExistCourse(code)){
            cout<<"Course not exist"<<endl;
            break;
        }
        
        if(isCourseRegistered(code,selectionTemp,id)){
            cout<<"\nstudent ID:    "<<selectionTemp->getId()<<endl;
            cout<<"Course Code:    "<<selectionTemp->getCode()<<endl;
            cout<<"Exam Mark:      "<<selectionTemp->getMark()<<"\n"<<endl;

        }
        else{
            cout<<"The registration record not exist"<<endl;
            break;
        }
    }while(false);

}

void RegisterSystem::reportAllStudents(){
    //the HTML generator will generator the report automatically
    HTMLgenerator reporter(this);
    reporter.setFile("Students.html");
    reporter.setKind(1);
    reporter.setTitle("All Students List");
    reporter.setSysName("HKUST Course Registration System");
    if(reporter.generate()){
        cout<<"Output Successful"<<endl;
    }
}

void RegisterSystem::reportAllCourses(){
    //the HTML generator will generator the report automatically
    HTMLgenerator reporter(this);
    reporter.setFile("Courses.html");
    reporter.setKind(2);
    reporter.setTitle("All Course List");
    reporter.setSysName("HKUST Course Registration System");
    if(reporter.generate()){
        cout<<"Output Successful"<<endl;}
    
}

void RegisterSystem::reportCourses(){
    //the HTML generator will generator the report automatically
    string input;
    CourseSelection* selectionTemp;
    do{
        cout<<"Enter the student ID: ";
        getline(cin,input);
        while(!selectionTemp->isValidID(input)){
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin,input);
        }
        string id=input;
        if(!isExistStudent(id)){
            cout<<"Student not exist"<<endl;
            break;
        }
        
        HTMLgenerator reporter(this);
        string tempstr=id+".html";
        reporter.setFile(tempstr);
        reporter.setKind(3);
        string tempstr2="Course Records for Student "+id;

        reporter.setTitle(tempstr2);
        reporter.setSysName("HKUST Course Registration System");
        reporter.setKey(id);
        if(reporter.generate()){
            cout<<"Output Successful"<<endl;}
        

    }while(false);
    
}

void RegisterSystem::reportStudents(){
    //the HTML generator will generator the report automatically
    string input;
    CourseSelection* selectionTemp;
    do{
        cout<<"Enter the course code: ";
        getline(cin,input);
        while(!selectionTemp->isValidCode(input)){
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin,input);
        }
        string code=input;
        if(!isExistCourse(code)){
            cout<<"Course not exist"<<endl;
            break;
        }
        
        HTMLgenerator reporter(this);
         reporter.setKey(code);
        string tempstr=code+".html";
        reporter.setFile(tempstr);
        reporter.setKind(4);
        string tempstr2="Course Records for Course "+code;
        
        reporter.setTitle(tempstr2);
        reporter.setSysName("HKUST Course Registration System");
        if(reporter.generate()){
            cout<<"Output Successful"<<endl;
	  
	}
        
        
    }while(false);
    
}

void RegisterSystem::saveData(){
    //save all the data with my format
    string input;
    cout<<"Enter the filename: ";
    getline(cin,input);
    if(input!=""){
	ofstream output;
	string tempStr=input;
	output.open(tempStr);
	//output the number of records to let the load process quick and correctly
	// save the data of students
	output<<StudentsRecords.size()<<"\n";
	for(HashTable<string, Student>::iterator itr=StudentsRecords.begin();itr!=StudentsRecords.end();itr++){
	  output<<(*itr).getID()<<"\n"<<(*itr).getName()<<"\n"<<(*itr).getYear()<<"\n"<<(*itr).getGender()<<"\n";
	}
	//output the number of records to let the load process quick and correctly
	// save the data of courses
        output<<CoursesRecords.size()<<"\n";
	for(HashTable<string, Course>::iterator itr=CoursesRecords.begin();itr!=CoursesRecords.end();itr++){
           output<<(*itr).getCode()<<"\n"<<(*itr).getCourseName()<<"\n"<<(*itr).getCredit()<<"\n";
        }
        //output the number of records to let the load process quick and correctly
        // save the data of courses selections
        output<<SelectionRecords.size()<<"\n";
	for(SDList<CourseSelection>::iterator itr=SelectionRecords.begin();itr!=SelectionRecords.end();itr++){
           output<<(*itr).getId()<<"\n"<<(*itr).getCode()<<"\n"<<(*itr).getMark()<<"\n";
        }
        output.close();
        cout<<"Saving Successful"<<endl;
    }
    else{
	cout<<"Error: Write File Error"<<endl;
    }
}

void RegisterSystem::loadData(){
    string input;
    cout<<"Enter the filename: ";
    getline(cin,input);
    ifstream inFile;
    inFile.open(input);
    if(inFile.is_open()){
      //clear the old database
      StudentsRecords.clear();
      CoursesRecords.clear();
      SelectionRecords.clear();
      courseIndex.clear();
      studentIndex.clear();
      //load the data of students
      string stuNo="-1";
      inFile>>stuNo;
      if(stuNo!="0"){
	int sNo=std::stoi(stuNo);
	string stuId="";
	string stuName="";
	string stuYear="";
	string stuGender="";
	for(int i=0;i<sNo;i++){
	  inFile>>stuId;
	  inFile>>stuName;
	  inFile>>stuYear;
	  inFile>>stuGender;
	  Student temp1(stuId,stuName,stuYear,stuGender);
	  StudentsRecords.insert(stuId,temp1);
	}
      }
      //load the data of courses
      string couNo="-1";
      inFile>>couNo;
      if(couNo!="0"){
	int cNo=std::stoi(couNo);
	string couCode="";
	string couName="";
	string couCre="";
	for(int i=0;i<cNo;i++){
	 inFile>>couCode;
	  inFile>>couName;
	  inFile>>couCre;
	  Course temp2(couCode,couName,couCre);
	  CoursesRecords.insert(couCode,temp2);
	}
      }
      //load the data of courses selections
      string seNo="-1";
      inFile>>seNo;
      if(seNo!="0"){
	int sNo=std::stoi(seNo);
	string seId="";
	string seCode="";
	string seMark="";
	for(int i=0;i<sNo;i++){
	  inFile>>seId;
	  inFile>>seCode;
	  inFile>>seMark;
	  CourseSelection temp3(seId,seCode,seMark);
	  CourseSelection* tempPtr;
	  tempPtr=SelectionRecords.insert(temp3);
	  studentIndex.insert(seId,tempPtr);
	  courseIndex.insert(seCode,tempPtr);
	}
      }
      inFile.close();
      cout<<"Loading Successful"<<endl;
    }
    else cout<<"Error: Load File Error (File not exist / File Corrupted / Incorrect Format"<<endl;
}

bool RegisterSystem::isExistStudent(string s){
    return StudentsRecords.query(s);
}

bool RegisterSystem::isExistCourse(string s){
    return CoursesRecords.query(s);
}
typedef CourseSelection* CSptr;
bool RegisterSystem::isCourseRegistered(string code,CSptr& tempPtr,string stuID){
    //check the recordes of selections according to the user input
    if(stuID=="-1"){
        return courseIndex.query(code);
	//if user only input code, he may wants to check the infomation of student
    }
    else if(code=="-1"){
        return studentIndex.query(stuID);
	//if user only input id, he may wants to check the infomation of course
    }
    else{
      //if user input code and id, he may wants to get the record so the pointer input will get the object of the record
        for(typename list<CourseSelection>::iterator itr=SelectionRecords.begin();itr!=SelectionRecords.end();itr++){
            if((*itr).getCode()==code&&(*itr).getId()==stuID){
                tempPtr=&((*itr));
                return true;
            }
        }
           
    }
    return false;
}


bool RegisterSystem::isCourseRegistered(string code,string stuID){
    if(stuID=="-1"){
        return courseIndex.query(code);
	//if user only input code, he may wants to check the infomation of student
    }
    else if(code=="-1"){
        return studentIndex.query(stuID);
	//if user only input code, he may wants to check the infomation of student
    }
    else{
	//if user input code and id, he may not wants to get the record so only return whether the record exits or not
	for(typename list<CourseSelection>::iterator itr=SelectionRecords.begin();itr!=SelectionRecords.end();itr++){
            if((*itr).getCode()==code&&(*itr).getId()==stuID){
                return true;
            }
        }
    }
    return false;
}

