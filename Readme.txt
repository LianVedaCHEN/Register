The whole program is made up by 8 .h files and 7 .cpp files.

Components:

Course.h
Course.cpp

Student.h
Student.cpp

CourseSelection.h
CourseSelection.h

HTMLgenerator.h
HTMLgenerator.cpp

System.h
System.cpp

Interface.h
Interface.cpp

hashTable.h

SDList.h

main.cpp

Introduction:
The .h and .cpp files of Student , Course and CourseSelection is used to provide three class whose object can be used
as record.

HTMLgenerator is used to generator the report. It can be developed into a more general report generator futher if some modifications
are added. But this one is enough in this project. It can let user program to set the title and the search key for list all courses for one student or 
all students for one course.

System is the core of the program. All the operation, like add/delete/modify student/couse/ selection record are implement by this one.
It also include the functions to save data and load data.

Interface provides interface for the user. Its functions include the display of menu etc. it also has a function called functionList(). This function map the
choice of user and the actual service provided by System. 

So if in the future, we want to add more functions for the program, we can add the actual action in System and register the map in Interface.

SDList.h is a template for sorted, doubly linked list. The way I implement it is to combine the STL::list with functions I need. For example, the sort is implemented 
in an insert sort way when the new element is added. The order of sort can be modified if the user input some compare function as a parameter of template.

hashTable is a (Separate Chaining) hash table which the SDList I implemented is used. It can be inputed a hash funtion as a parameter of constructor. I want it 
be as flexble as possible and it need the ability of fit several situation, so for some funtions,like remove and query, I overloaded several times and then later
user can choose the most convenient one to use. Because it is implemented by template, so it can fit with several situations, even the type of key can be defined
by user. I also overload the operator[] so user can find what they want very quick by inputting the key.

Problem I meet:
when I implement the save data function, I found my program may crush if I delete the Students or Records and then save. It is a quite strange problem.
After checking for long time, I found it is due to the broken link situation caused by call remove(). My remove is implemented with the help of STL::list::remove 
at that time. I searched on the internet and found there is a strange behavior of iterator of list when a remoev() is called. So later I modified my SDList and 
it works fine now.