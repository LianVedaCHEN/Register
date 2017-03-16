//
//  Student.cpp
//  project5
//
//  Created by Veda on 16/11/21.
//  Copyright © 2016年 Veda. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Student.h"
Student::Student():studentID("20130903"),studentName("Mitsuha"),year("2"),gender("female"){}

Student::Student(string id,string name,string year1, string mf):studentID(id),studentName(name),year(year1),gender(mf){}

Student::Student(const Student& stu):studentID(stu.studentID),studentName(stu.studentName),year(stu.year),gender(stu.gender){}

Student::~Student(){}


Student& Student::operator=(const Student& stu){
    studentID=stu.getID();
    studentName=stu.getName();
    year=stu.getYear();
    gender =stu.gender;
    return (*this);
}

bool Student::isValidID(string id ){
    if(id.length()!=8) return false;
    for(std::string::iterator iter=id.begin();iter!=id.end();iter++)
    {
        if(!isdigit(*iter))
        {
            
            return false;
        }
        
    }
    return true;
}

void Student::setID(string id){
       studentID=id;
    
}

string Student::getID() const{
    return studentID;
}

string Student::getID() {
    string temp=studentID;
    return temp;
}

bool Student::isValidName(string name){
    if((name.length()>=1)&&(name.length()<=32)){
        return true;
    }
    return false;
}


void Student::setName(string name){
            studentName=name;
}

string Student::getName() const{
    return studentName;
}

string Student::getName() {
    return studentName;
}

bool Student::isValidYear(string  year1){
    if(year1.length()==1&&isdigit(year1[0])){
        int temp=std::stoi(year1);
        if((temp>=1)&&(temp<=3)){
            return true;
        }

        
    }

        return false;
}

void Student::setYear(string year1){
        year =year1;
}

string Student::getYear() const{
    return year;
}

string Student::getYear() {
    return year;
}

bool Student::isValidGender(string mf){
    //input is M or F but the output will change to Male or female
    if(mf=="M"||mf=="F"){
        return true;
    }
    return false;
}

void Student::setGender(string mf){
           gender=mf;
}

string Student::getGender() const{
    return gender;
}

bool Student::operator<(const Student& stu) const{
    return (studentID<stu.getID());
}

bool Student::operator>(const Student& stu) const{
    return (studentID>stu.getID());
}

bool Student::operator<=(const Student& stu) const{
    return (studentID<=stu.getID());
}

bool Student::operator>=(const Student& stu) const{
    return (studentID>=stu.getID());
}

bool Student::operator==(const Student& stu) const{
    return (studentID==stu.getID());
}

bool Student::operator!=(const Student& stu) const{
    return !(studentID==stu.getID());
}


