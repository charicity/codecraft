#include<iostream>
#include "Robot.h"

void Robot::input(){
    std::cin>>object_;
    pos_.input();
    std::cin>>status_;
}