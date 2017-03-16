
#include "HTMLgenerator.h"
#include "SDList.h"
#include <vector>
#include <algorithm>
#include <fstream>
using std::ofstream;
HTMLgenerator::HTMLgenerator(){}

HTMLgenerator::~HTMLgenerator(){
    sys=NULL;
    
}

HTMLgenerator::HTMLgenerator(RegisterSystem* sis):sys(sis){}

void HTMLgenerator::setFile(string fileName){
    file=fileName;
}

void HTMLgenerator::setSysName(string sysName){
    systemName=sysName;
}

void HTMLgenerator::setTitle(string title1){
    title=title1;
}

void HTMLgenerator::setKind(int tabletype){
    tableKind=tabletype;
}

void HTMLgenerator::setKey(string key){
    searchKey=key;
}

bool HTMLgenerator::generate(){
    ofstream output;
    output.open(file);
    if(output.is_open()){
        //this part is responsible for the fixed part like the header and the end
        output<<"<HTML>\n<HEAD>\n<HEAD>\n<TITLE>"<<title<<"</TITLE>\n</HEAD>\n";
        output<<"<BODY bgColor=#ffffcc>\n<H1><FONT color=#6600ff>"<<systemName<<"</FONT></H1>\n";
        flexWrite(output);
        output<<"\n</P>\n</BODY>\n</HTML>"<<std::flush;
        output.close();
        return true;
    }
    return false;
}

void HTMLgenerator::flexWrite(ofstream& os){
    //this part is responsible for the flexible part which can change according to the user's input
    switch(tableKind){
        case 1: {choice1(os);break;}
        case 2: {choice2(os);break;}
        case 3: {choice3(os);break;}
        case 4: {choice4(os);break;}
    }
}

void HTMLgenerator::choice1(ofstream& os){
    os<<"<H2>All Students List</H2>\n<P>\n";
        if(sys->StudentsRecords.begin()==sys->StudentsRecords.end()){
        os<<"No student found";
    }
    else{
        vector<Student> stuV;
        os<<"<TABLE cellSpacing=1 cellPadding=1 border=1>\n\n<TR>\n<TD>Student ID</TD>\n<TD>Student Name</TD>\n<TD>Year</TD>\n<TD>Gender</TD>\n</TR>\n\n";
        for(HashTable<string, Student>::iterator itr=sys->StudentsRecords.begin();itr!=sys->StudentsRecords.end();itr++){
	Student tempStu=*itr;  
	stuV.push_back(tempStu);
        }
        //sort according to the id
        sort(stuV.begin(),stuV.end());
        for(vector<Student>::iterator itr=stuV.begin();itr!=stuV.end();itr++){
	    os<<"<TR>\n<TD>"<<(*itr).getID()<<"</TD>\n<TD>"<<(*itr).getName()<<"</TD>\n<TD>"<<(*itr).getYear()<<"</TD>\n<TD>"<<(((*itr).getGender()=="M")?"Male":"Female")<<"</TD>\n</TR>\n\n";
	}
        os<<"</TABLE>";
    }
}

void HTMLgenerator::choice2(ofstream& os){
    os<<"<H2>All Course List</H2>\n<P>\n";
    if(sys->CoursesRecords.begin()==sys->CoursesRecords.end()){
        os<<"No course found";
    }
    else{
        vector<Course> couV;
        os<<"<TABLE cellSpacing=1 cellPadding=1 border=1>\n\n<TR>\n<TD>Course Code</TD>\n<TD>Course Name</TD>\n<TD>Credit</TD>\n</TR>\n\n";
        for(HashTable<string, Course>::iterator itr=sys->CoursesRecords.begin();itr!=sys->CoursesRecords.end();itr++){
	    Course couTemp=*itr;
	    couV.push_back(couTemp);  
        }
        //sort according to the code
        sort(couV.begin(),couV.end());
        for(vector<Course>::iterator itr=couV.begin();itr!=couV.end();itr++){
	    os<<"<TR>\n<TD>"<<(*itr).getCode()<<"</TD>\n<TD>"<<(*itr).getCourseName()<<"</TD>\n<TD>"<<(*itr).getCredit()<<"</TD>\n</TR>\n\n";
	}
        os<<"</TABLE>";
    }
}

void HTMLgenerator::choice3(ofstream& os){
    string stuId=sys->StudentsRecords[searchKey]->getID();
    string stuName=sys->StudentsRecords[searchKey]->getName();
    
    os<<"<H2>Course Records for Student: "<<stuName<<" ("<<stuId<<")</H2>\n<P>\n";

    if(!sys->isCourseRegistered("-1",searchKey)){
        os<<"No course taken ";
    }
    else{
        //since my SDList is a sorted doubly linked list so when teh element is inserted, they has been sorted
        os<<"<TABLE cellSpacing=1 cellPadding=1 border=1>\n\n<TR>\n<TD>Course Code</TD>\n<TD>Course Name</TD>\n<TD>Credit</TD>\n<TD>Exam Mark</TD>\n</TR>\n\n";
        for(SDList<CourseSelection>::iterator itr=sys->SelectionRecords.begin();itr!=sys->SelectionRecords.end();itr++){
        if((*itr).getId()==searchKey){
            string code=(*itr).getCode();
            os<<"<TR>\n<TD>"<<sys->CoursesRecords[code]->getCode()<<"</TD>\n<TD>"<<sys->CoursesRecords[code]->getCourseName()<<"</TD>\n<TD>"<<sys->CoursesRecords[code]->getCredit()<<"</TD>\n<TD>"<<(*itr).getMark()<<"</TD>\n</TR>\n\n";
        		
	  
	}
    }
    os<<"</TABLE>";
    }
}

void HTMLgenerator::choice4(ofstream& os){
    
    string cName=sys->CoursesRecords[searchKey]->getCourseName();
    string cCode=sys->CoursesRecords[searchKey]->getCode();
    os<<"<H2>Course Records for Course: "<<cName<<" ("<<cCode<<")</H2>\n<P>\n";
    if(!sys->isCourseRegistered(searchKey,"-1")){os<<"No student takes this course";}
    else{
        //since my SDList is a sorted doubly linked list so when teh element is inserted, they has been sorted
        os<<"<TABLE cellSpacing=1 cellPadding=1 border=1>\n\n<TR>\n<TD>Student ID</TD>\n<TD>Student Name</TD>\n<TD>Year</TD>\n<TD>Gender</TD>\n<TD>Exam Mark</TD>\n</TR>\n\n";
        for(SDList<CourseSelection>::iterator itr=sys->SelectionRecords.begin();itr!=sys->SelectionRecords.end();itr++){
	 
            if((*itr).getCode()==searchKey){
              string id= (*itr).getId();
               os<<"<TR>\n<TD>"<<sys->StudentsRecords[id]->getID()<<"</TD>\n<TD>"<<sys->StudentsRecords[id]->getName()<<"</TD>\n<TD>"<<sys->StudentsRecords[id]->getYear()<<"</TD>\n<TD>"<<((sys->StudentsRecords[id]->getGender()=="M")?"Male":"Female")<<"</TD>\n<TD>"<<(*itr).getMark()<<"</TD>\n</TR>\n\n";
	      
	    }
       }
       os<<"</TABLE>";
    }
}
