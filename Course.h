
#ifndef Course_h
#define Course_h
#include <stdio.h>
#include <string>
#include <cctype>
using std::string;
class Course{
public:
    Course();
    ~Course();
    Course(string c,string name,string cred);
    Course(const Course& course);
    Course& operator=(const Course& cou);
    bool isValidCode(string co);//check whether the couse code is valid
    void setCode(string co);
    string getCode() const;
     string getCode();
    bool isValidCourse(string name);//check whether the couse name is valid
    void setCourseName(string name);
    string getCourseName() const;
    string getCourseName();
    bool isValidCredit(string cre);//check whether the couse credit is valid
    void setCredit(string cre);
    string getCredit() const;
    string getCredit();
    bool operator<(const Course& cou) const;
    bool operator<=(const Course& cou) const;
    bool operator>(const Course& cou) const;
    bool operator>=(const Course& cou) const;
    bool operator==(const Course& cou) const;
    bool operator!=(const Course& cou) const;
private:
    string code;
    string courseName;
    string credit;
    
};


#endif /* Course_h */
