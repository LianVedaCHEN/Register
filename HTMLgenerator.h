//
//  HTMLgenerator.hpp
//  project5
//
//  Created by Veda on 16/11/27.
//  Copyright © 2016年 Veda. All rights reserved.
//

#ifndef HTMLgenerator_h
#define HTMLgenerator_h

#include <stdio.h>
#include "hashTable.h"
#include "Student.h"
#include "Course.h"
#include "CourseSelection.h"
#include "System.h"
#include <fstream>
using std::ofstream;
class RegisterSystem;
class HTMLgenerator{
public:
    typedef HashTable<string,CourseSelection*> indexHash;
    HTMLgenerator();
    ~HTMLgenerator();
    HTMLgenerator(RegisterSystem* sis );
    bool generate();//generate the HTMl
    void setFile(string);//set the name of html
    void setSysName(string);
    void setTitle(string);// set the title of html
    void setKind(int);// for use to set the kind of html
    void setKey(string);// for use to set the search key
private:
    string file;
    string systemName;
    string title;
    void flexWrite(ofstream& os);
    RegisterSystem* sys; //the source of html which is the system
    int tableKind;
    string searchKey;
    void choice1(ofstream& os);//list all students information
    void choice2(ofstream& os);//list all courses information
    void choice3(ofstream& os);//list the courses of one student
    void choice4(ofstream& os);//list all the students taking one particular course
};


#endif /* HTMLgenerator_h */
