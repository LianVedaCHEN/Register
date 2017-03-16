//
//  Interface.hpp
//  project5
//
//  Created by Veda on 16/11/26.
//  Copyright © 2016年 Veda. All rights reserved.
//

#ifndef Interface_h
#define Interface_h

#include <stdio.h>
#include <iostream>
#include "System.h"
using std::cin;
class Interface{
public:
    Interface();
    ~Interface();
    void start();
private:
    RegisterSystem sys;
    void displayMenu(int i);// display the menu of different level
    void functionList(int &menuLevel,int choice);//store therelation between the choice and correspond functions 
    bool inputCheck(int menuLevel,string input);// check whether the input is valid or not
    int numOfChoice(int level);// return the number of choice in the level
    void wait();// let the program continue only when the user hit the enter
};

#endif /* Interface_hpp */
