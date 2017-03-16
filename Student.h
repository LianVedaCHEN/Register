
#ifndef Student_h
#define Student_h
#include <stdio.h>
#include <string>
#include <cctype>
using std::string;
class Student{
public:
    Student();
    ~Student();
    Student(string id,string name,string year, string mf);
    Student(const Student& stu);
    Student& operator=(const Student& stu);
    bool isValidID(string id );
    void setID(string id);
    string getID() const;
    string getID() ;
    bool isValidName(string name );
    void setName(string name);
    string getName() const;
    string getName() ;
    bool isValidYear(string year1 );
    void setYear(string year1);
    string getYear() const;
    string getYear();
    bool isValidGender(string mf );
    void setGender(string mf);
    string getGender() const;
    bool operator<(const Student& stu) const;
    bool operator>(const Student& stu) const;
    bool operator<=(const Student& stu) const;
    bool operator>=(const Student& stu) const;
    bool operator==(const Student& stu) const;
    bool operator!=(const Student& stu) const;
private:
    
    string studentID;
    string studentName;
    string year;
    string gender;
    
};


#endif /* Student_h */
