//
//  Interface.cpp
//  project5
//
//  Created by Veda on 16/11/26.
//  Copyright © 2016年 Veda. All rights reserved.
//

#include "Interface.h"
using std::cin;
Interface::Interface(){}

Interface::~Interface(){}

int Interface::numOfChoice(int level){
    int numMax=0;
    switch(level){
        case 0:{numMax=6;break;}
        case 1:{numMax=5;break;}
        case 2:{numMax=5;break;}
        case 3:{numMax=5;break;}
        case 4:{numMax=5;break;}
        case 5:{numMax=3;break;}
    }
    return numMax;
}
bool Interface::inputCheck(int level, string s){
    int numMax=numOfChoice(level);
        if(s.length()==1&&isdigit(s[0])){
        int temp=std::stoi(s);
        if((temp>=1)&&(temp<=numMax)){
            return true;
        }
        
    }
    
    
    return false;
}

void Interface::displayMenu(int i){
    //display the menu. The level 0 is the main menu 
    switch(i){
        case 0:{
            cout<<"HKUST Course Registration System"<<endl;
            cout<<"--------------------------------\n"<<endl;
            cout<<"1. Student Management"<<endl;
            cout<<"2. Course Management"<<endl;
            cout<<"3. Course Registration"<<endl;
            cout<<"4. Report Management"<<endl;
            cout<<"5. File Management"<<endl;
            cout<<"6. Exit\n"<<endl;
            break;
            
        }
        case 1:{
            cout<<"HKUST Course Registration System  (Student Menu)"<<endl;
            cout<<"------------------------------------------------\n"<<endl;
            cout<<"1. Insert Student Record"<<endl;
            cout<<"2. Modify Student Record"<<endl;
            cout<<"3. Delete Student Record"<<endl;
            cout<<"4. Query Student Record"<<endl;
            cout<<"5. Go back to main menu\n"<<endl;
            break;
        }
        case 2:{
            cout<<"HKUST Course Registration System  (Course Menu)"<<endl;
            cout<<"-----------------------------------------------\n"<<endl;
            cout<<"1. Insert Course Record"<<endl;
            cout<<"2. Modify Course Record"<<endl;
            cout<<"3. Delete Course Record"<<endl;
            cout<<"4. Query Course Record"<<endl;
            cout<<"5. Go back to main menu\n"<<endl;
            break;

        }
        case 3:{
            cout<<"HKUST Course Registration System  (Registration Menu)"<<endl;
            cout<<"-----------------------------------------------------\n"<<endl;
            cout<<"1. Add Course"<<endl;
            cout<<"2. Drop Course"<<endl;
            cout<<"3. Modify Exam Mark"<<endl;
            cout<<"4. Query Registration"<<endl;
            cout<<"5. Go back to main menu\n"<<endl;
            break;

        }

        case 4:{
            cout<<"HKUST Course Registration System  (Report Generation Menu)"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"1. List all student information"<<endl;
            cout<<"2. List all course information"<<endl;
            cout<<"3. List all courses of a student"<<endl;
            cout<<"4. List all students of a course"<<endl;
            cout<<"5. Go back to main menu\n"<<endl;
            break;

        }
        case 5:{
            cout<<"HKUST Course Registration System  (File Menu)"<<endl;
            cout<<"---------------------------------------------"<<endl;
            cout<<"1. Save Database"<<endl;
            cout<<"2. Load Database"<<endl;
            cout<<"3. Go back to main menu\n"<<endl;
            break;

        }
    }
}

void Interface::functionList(int &menuLevel,int choice){
    switch(menuLevel){
        case 0:{
            if(choice!=6){
                menuLevel=choice;}
            else exit(0);
            break;
        }
        case 1:{
            switch(choice){
                case 1: {sys.insertStudent();wait();menuLevel=0;break;}
                case 2: {sys.modifyStudent();wait();menuLevel=0;break;}
                case 3: {sys.deleteStudent();wait();menuLevel=0;break;}
                case 4: {sys.queryStudent();wait();menuLevel=0;break;}
                case 5: {menuLevel=0;break;}
            }
            break;
        }
        case 2:{
            switch (choice){
                case 1:{sys.insertCourse();wait(); menuLevel=0;break;}
                case 2:{sys.modifyCourse();wait();menuLevel=0;break;}
                case 3:{sys.deleteCourse();wait();menuLevel=0;break;}
                case 4:{sys.queryCourse(); wait();menuLevel=0;break;}
                case 5:{menuLevel=0;break;}
                    
            }
            break;
        }
        case 3:{
            switch (choice){
                case 1:{sys.addSelection(); wait();menuLevel=0;break;}
                case 2:{sys.dropSelection(); wait();menuLevel=0;break;}
                case 3:{sys.modifyMark() ;wait();menuLevel=0;break;}
                case 4:{sys.querySelection();wait();menuLevel=0;break;}
                case 5:{menuLevel=0;break;}
                    
            }
            break;
        }
        case 4:{
            switch (choice){
                case 1:{sys.reportAllStudents();wait();menuLevel=0; break;}
                case 2:{sys.reportAllCourses(); wait();menuLevel=0;break;}
                case 3:{sys.reportCourses();wait();menuLevel=0;break;}
                case 4:{sys.reportStudents();wait();menuLevel=0;break;}
                case 5:{menuLevel=0;break;}
                    
            }
            break;
        }
        case 5:{
            switch (choice){
                case 1:{sys.saveData();wait();menuLevel=0;break;}
                case 2:{sys.loadData();wait();menuLevel=0;break;}
                case 3:{menuLevel=0;break;}
                    
            }
            break;

        }
    }

}
void Interface::start(){
    bool end=false;
    int menuLevel=0;
    string input;
    int choice=0;
    do{ system("clear");
        displayMenu(menuLevel);
        cout<<"Enter you choice(1-"<<numOfChoice(menuLevel)<<"): ";
        getline(cin,input);
        while(!inputCheck(menuLevel, input)){
            cout << "Invalid input, re-enter again (1-"<<numOfChoice(menuLevel)<<"): ";
            getline(cin,input);
        }
        functionList(menuLevel, std::stoi(input));

        

        
        
        
    }while(!end);
}

void Interface::wait(){
    //use to implement the effect that the program only continue when the user hit ENTER
    string tmp;
    cout << "\nHit ENTER to continue... \n";
    getline(cin, tmp);
}
