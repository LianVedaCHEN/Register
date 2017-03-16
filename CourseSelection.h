//
//  CourseSelection.h
//  project5
//
//  Created by Veda on 16/11/21.
//  Copyright © 2016年 Veda. All rights reserved.
//

#ifndef CourseSelection_h
#define CourseSelection_h
#include <stdio.h>
#include <string>
using std::string;
class CourseSelection{
public:
    CourseSelection();
    ~CourseSelection();
    CourseSelection(string id, string co, string mark);
    CourseSelection(const CourseSelection& cs);
    CourseSelection& operator=(const CourseSelection& cs);
    CourseSelection& operator=(CourseSelection& cs);
    bool isValidID(string id);
    void setID(string id);
    string getId() const;
    string getId() ;
    bool isValidCode(string co);
    void setCode(string co);
    string getCode() const;
     string getCode() ;
    bool isValidMark(string mark);
    void setMark(string mark);
    string getMark() const;
    string getMark() ;
    bool operator<(const CourseSelection& cs) const;
    bool operator<(const CourseSelection* cs) const;
    bool operator<=(const CourseSelection& cs) const;
    bool operator>(const CourseSelection& cs) const;
    bool operator>=(const CourseSelection& cs) const;
    bool operator==(const CourseSelection& cs) const;
    bool operator!=(const CourseSelection& cs) const;
private:
    string studentID;
    string code;
    string examMark;
};


#endif /* CourseSelection_h */
