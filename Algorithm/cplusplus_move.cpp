//
//  cplusplus_move.cpp
//  cplusplus_test_ios
//
//  Created by tianqi on 2020/11/29.
//  Copyright © 2020 tianqi. All rights reserved.
//

#include "cplusplus_move.hpp"
#include <iostream>

using std::string;
using std::cout;

void move_local_variable(void) {
  std::string local = "I am local string";
  std::string other = std::move(local) + ".";
  std::cout << local <<std::endl;
}
