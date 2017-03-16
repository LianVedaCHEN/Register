
#ifndef System_h
#define System_h
#include <string>
#include "hashTable.h"
#include "Student.h"
#include "Course.h"
#include "CourseSelection.h"
#include "SDList.h"
#include "HTMLgenerator.h"
using std::string;
class HTMLgenerator;
class RegisterSystem{
public:
    RegisterSystem();
    ~RegisterSystem();
    RegisterSystem(const RegisterSystem& reg);
    void insertStudent();// after evoking, it will let user to input relative information of student and then add it into hash table
    void modifyStudent();// after evoking, it will let user to input relative information of student to modify it 
    void deleteStudent();// after evoking, it will let user to input relative information of student and then delte the one satisfying the requirement
    void queryStudent();// after evoking, it will let user to input relative information of student and search it for user
    
    void insertCourse();// after evoking, it will let user to input relative information of course and then add it into hash table
    void modifyCourse();//after evoking, it will let user to input relative information of course to modify it 
    void deleteCourse();//after evoking, it will let user to input relative information of course and then delte the one satisfying the requirement
    void queryCourse();// after evoking, it will let user to input relative information of course and search it for user
    
    void addSelection();// after evoking, it will let user to input relative information of course records and then add it 
    void modifyMark();// after evoking, it will let user to input the mark of the course for the student
    void dropSelection();// after evoking, it will let user to input relative information of selection record and then delte the one satisfying the requirement
    void querySelection();// after evoking, it will let user to input relative information of course selection records and search it for user
    
    void reportAllStudents();// list the information of all students
    void reportAllCourses();// list the information of all courses
    void reportCourses();//list the course taken by the stuent user want ot know
    void reportStudents();//list all the students taking the course the user wnat to know
    
    void saveData();//save the data 
    void loadData();//load the data 
    
    HashTable<string,Student> StudentsRecords;//database for strudent information
    HashTable<string,Course> CoursesRecords;//database for course information
    SDList<CourseSelection> SelectionRecords;//database for selection records
    
    typedef HashTable<string,CourseSelection*> indexHash;
    indexHash studentIndex;// store the pointer of records in order of student ID
    indexHash courseIndex;// store the pointer of records in order of course code
    friend class HTMLgenerator;
private:
    bool isExistStudent(string s);
    bool isExistCourse(string s);
    bool isCourseRegistered(string code,CourseSelection*& tempPtr,string stuID="-1");
    bool isCourseRegistered(string code="-1",string stuID="-1");


    
};
int hashForCourse(const string& key,int size);//hash function for course
int hashForStudent(const string& key,int size);//hash function for student
#endif /* System_h */
