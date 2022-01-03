//
//  cplusplus_utility.cpp
//  cplusplus_test_ios
//
//  Created by tianqi on 2020/5/16.
//  Copyright © 2020 tianqi. All rights reserved.
//

#include "cplusplus_utility.hpp"
#include <utility>
#include <iostream>

using std::cout;
using std::move;

void utility_rvalue() {
  int i=42;
  int &r=i;   //正确，r引用i
  int &&r1 = move(i);   //正确，可以将一个右值引用绑定到一个右值上
  int &&r2 = move(r1);  //同上
  const int &r3=i*2;  //正确，我们可以将一个const的引用绑定到一个右值上
  int &&r4=i*2; //正确，将rr2绑定到乘法结果上
  cout << "r = " << r << '\n';
  cout << "r1 = " << r1 << '\n';
  cout << "r2 = " << r2 << '\n';
  cout <<"r3 = " << r3 << '\n';
  cout <<"r4 = " << r4 << '\n';
}

void overloaded (const int& x) {std::cout << "[lvalue]";}
void overloaded (int&& x) {std::cout << "[rvalue]";}
template <class T> void fn (T&& x) {//万能引用
  overloaded (x);                   // always an lvalue
  overloaded (std::forward<T>(x));  // rvalue if argument is rvalue
}
void utility_forward() {
  int a;
  // function with lvalue and rvalue reference overloads:
  std::cout << "calling fn with lvalue: ";
  fn (a);
  std::cout << '\n';

  std::cout << "calling fn with rvalue: ";
  fn (0);
  std::cout << '\n';
}
