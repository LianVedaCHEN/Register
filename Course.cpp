//
//  Course.cpp
//  project5
//
//  Created by Veda on 16/11/21.
//  Copyright © 2016年 Veda. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Course.h"
Course::Course():code("COMP2012"),courseName("OOP"),credit("5"){}

Course::~Course(){}

Course::Course(string c,string name,string cred):code(c),courseName(name),credit(cred){}

Course::Course(const Course& course):code(course.getCode()),courseName(course.getCourseName()),credit(course.getCredit()){}

Course& Course::operator=(const Course& cou){
    code=cou.getCode();
    courseName=cou.getCourseName();
    credit=cou.getCredit();
    return *this;
}
bool Course::isValidCode(string co){
    long strl=co.length();
    if((strl>=7)&&(strl<=8)){
        
        string prefix=co.substr(0,4);
        for(std::string::iterator iter=co.begin();iter!=co.end();iter++)
        {
            if(!(isalpha(*iter)||isdigit(*iter)))
            {
                
                return false;
                
            }
            
        }
        //check the whether the first 4 are upper case alphabet
        for(std::string::iterator iter=prefix.begin();iter!=prefix.end();iter++)
        {
            if(!isalpha(*iter)||!isupper(*iter))
            {
                
                return false;
            }
            
        }
         //check the whether the 8th (if any) are upper case alphabet
        if(strl==8&&isalpha(co[7])&&!isupper(co[7])){
	  return false;
	}
        return true;
    }
    return false;

}
void Course::setCode(string co){
            code=co;
}

string Course::getCode() const{
    return code;
}

string Course::getCode(){
    return code;
}

bool Course::isValidCourse(string name){
    if((name.length()>=1)&&(name.length()<=50)){
        return true;
    }
    return false;

}

void Course::setCourseName(string name){
    courseName=name;
}

string Course::getCourseName() const{
    return courseName;
}

string Course::getCourseName(){
    return courseName;
}

bool Course::isValidCredit(string cre){
   if(cre.length()==1&&isdigit(cre[0])){

       int temp= std::stoi(cre);
       if((temp>=0)&&(temp<=5)){
           return true;
       }
   }
    return false;

}
void Course::setCredit(string cre){
    credit=cre;
}

string Course::getCredit() const{
    return credit;
}

string Course::getCredit(){
    return credit;
}

bool Course::operator<(const Course& cou) const{
    return (code<cou.getCode());
}

bool Course::operator<=(const Course& cou) const{
    return (code<=cou.getCode());
}

bool Course::operator>(const Course& cou) const{
    return (code>cou.getCode());
}

bool Course::operator>=(const Course& cou) const{
    return (code>=cou.getCode());
}
bool Course::operator==(const Course& cou) const{
    return (code==cou.getCode());
}
bool Course::operator!=(const Course& cou) const{
    return (code!=cou.getCode());
}

