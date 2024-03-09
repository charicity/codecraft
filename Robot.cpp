#include "Robot.h"

#include <iostream>

void Robot::input() {
  std::cin >> object_;
  pos_.input();
  std::cin >> status_;
}

void Robot::find_path() {
  int a, b;
  std::cin >> a >> b;
  
}