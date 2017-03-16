//
//  CourseSelection.cpp
//  project5
//
//  Created by Veda on 16/11/21.
//  Copyright © 2016年 Veda. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "CourseSelection.h"
CourseSelection::CourseSelection():studentID("20130903"),code("COMP2012"),examMark("N/A"){}

CourseSelection::~CourseSelection(){}

CourseSelection::CourseSelection(string id, string co, string mark):studentID(id),code(co),examMark(mark){}

CourseSelection::CourseSelection(const CourseSelection& cs):studentID(cs.getId()),code(cs.getCode()),examMark(cs.getMark()){}

CourseSelection& CourseSelection::operator=(const CourseSelection& cs){
    studentID=cs.getId();
    code=cs.getCode();
    examMark=cs.getMark();
    return *this;
}

CourseSelection& CourseSelection::operator=(CourseSelection& cs){
    studentID=cs.getId();
    code=cs.getCode();
    examMark=cs.getMark();
    return *this;
}

bool CourseSelection::isValidID(string id){
    bool result=true;
    if(id.length()!=8) return false;
    for(std::string::iterator iter=id.begin();iter!=id.end();iter++)
    {
        if(!isdigit(*iter))
        {
            
            result=false;
            break;
        }
        
    }
    return result;
}

void CourseSelection::setID(string id){
       studentID=id;
}

string CourseSelection::getId()const{
    return studentID;
}

string CourseSelection::getId(){
    return studentID;
}

bool CourseSelection::isValidCode(string co){
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

void CourseSelection::setCode(string co){
    code=co;
}

string CourseSelection::getCode() const{
    return code;
}

string CourseSelection::getCode(){
    return code;
}

bool CourseSelection::isValidMark(string mark){
    if((mark.length()==3&&isdigit(mark[0])&&isdigit(mark[1])&&isdigit(mark[2]))||(mark.length()==2&&isdigit(mark[0])&&isdigit(mark[1]))||(mark.length()==1&&isdigit(mark[0]))){
        int temp=std::stoi(mark);
        if((temp>=0)&&(temp<=100)){
            return true;
        }
    }
    return false;

}

void CourseSelection::setMark(string mark){
    examMark=mark;
}

string CourseSelection::getMark() const{
    return examMark;
}

string CourseSelection::getMark(){
    return examMark;
}
bool CourseSelection::operator<(const CourseSelection& cs) const{
    return ((studentID==cs.getId())?(code<cs.getCode()):(studentID<cs.getId()));
}
bool CourseSelection::operator<(const CourseSelection* cs) const{
    return ((studentID==cs->getId())?(code<cs->getCode()):(studentID<cs->getId()));
}

bool CourseSelection::operator<=(const CourseSelection& cs) const{
    return ((studentID==cs.getId())?(code<=cs.getCode()):(studentID<=cs.getId()));
}

bool CourseSelection::operator>(const CourseSelection& cs) const{
    return ((studentID==cs.getId())?(code>cs.getCode()):(studentID>cs.getId()));
    
}

bool CourseSelection::operator>=(const CourseSelection& cs) const{
    return ((studentID==cs.getId())?(code>=cs.getCode()):(studentID>=cs.getId()));
}

bool CourseSelection::operator==(const CourseSelection& cs) const{
    return ((studentID==cs.getId())&&(code==cs.getCode())&&(examMark==cs.getMark()));
    
}
bool CourseSelection::operator!=(const CourseSelection& cs) const{
    return !(*this==cs);
}

