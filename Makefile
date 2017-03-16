CPP = g++

Register: main.o Interface.o System.o HTMLgenerator.o Student.o CourseSelection.o Course.o
	$(CPP) -std=c++11 -o Register main.o Interface.o System.o HTMLgenerator.o Student.o CourseSelection.o Course.o
main.o: main.cpp SDList.h hashTable.h Course.h Student.h System.h Interface.h
	$(CPP) -std=c++11 -c main.cpp
Interface.o: Interface.h Interface.cpp System.h
	$(CPP) -std=c++11 -c Interface.cpp
System.o: System.cpp System.h hashTable.h Student.h Course.h CourseSelection.h HTMLgenerator.h SDList.h
	$(CPP) -std=c++11 -c System.cpp
HTMLgenerator.o: HTMLgenerator.cpp HTMLgenerator.h CourseSelection.h System.h Student.h Course.h hashTable.h
	$(CPP) -std=c++11 -c HTMLgenerator.cpp
Student.o: Student.cpp Student.h
	$(CPP) -std=c++11 -c Student.cpp 	
CourseSelection.o: CourseSelection.cpp CourseSelection.h
	$(CPP) -std=c++11 -c CourseSelection.cpp 
Course.o: Course.cpp Course.h
	$(CPP) -std=c++11 -c Course.cpp 
clean: 
	rm -f *.o Register 
version:
	$(CPP) -v