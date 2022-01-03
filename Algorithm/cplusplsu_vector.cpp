//
//  cplusplsu_vector.cpp
//  cplusplus_test_ios
//
//  Created by tianqi on 2020/2/7.
//  Copyright © 2020 tianqi. All rights reserved.
//

#include "cplusplsu_vector.hpp"
#include <condition_variable>
#include <iostream>
#include <thread>
#include <future>
#include <exception>
#include <unistd.h>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::move;

static int g_i = 0;
/*
 Class
 */
class TestMutex {
public:
  std::mutex mutex0;
};

class StringWrapper final {
public:
  StringWrapper(const char* s) {
    if (s == nullptr) {
      return;
    }
    std::size_t n = std::strlen(s) + 1;
    for (int i = 0; i < n; i++) {
      data.push_back(s[i]);
    }
  }
  std::vector<char> data;
};

class A {
public:
  A():m_ptr{new int(0)}{
    printf("default construct\n");
  };
  A(const A& a):m_ptr{new int(*a.m_ptr)} {
    printf("copy construct\n");
  }
  A(A&& a){
    printf("move construct\n");
    if (this != &a) {
      m_ptr = a.m_ptr;
      a.m_ptr = nullptr;
    }
  }
  A& operator=(const A& a){
    if (this != &a){
      delete m_ptr;
      this->m_ptr = new int(*a.m_ptr);
    }
    printf("copy assign operator\n");
    return *this;
  }
  ~A(){
    printf("deconstruct\n");
    if (m_ptr!=nullptr) {
      delete m_ptr;
    }
    m_ptr = nullptr;
  }
private:
  int *m_ptr;
};

A getItem(bool tag) {
  A a,b;
  if (tag) {
    return a;
  } else {
    return b;
  }
  
}

/*
 Functions
 */
void vector_reserve() {
  printf("//****//vector_reserve\n");
  std::vector<int>::size_type sz;
  std::vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  std::vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
}

void vector_resize() {
  printf("//****//vector_resize\n");
  std::vector<int> myvector;

  // set some initial content:
  for (int i=1;i<10;i++) myvector.push_back(i);

  myvector.resize(5);
  myvector.resize(8,100);
  myvector.resize(12);

  std::cout << "myvector contains:";
  for (int i=0;i<myvector.size();i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}

void vector_shrink_to_fit() {
  printf("//****//vector_shrink_to_fit\n");
  std::vector<int> myvector (101);
  myvector.push_back(5);
  std::cout << "1. capacity of myvector: " << myvector.capacity() << '\n';

  myvector.resize(10);
  std::cout << "2. capacity of myvector: " << myvector.capacity() << '\n';

  myvector.shrink_to_fit();
  std::cout << "3. capacity of myvector: " << myvector.capacity() << '\n';
}

void vector_operator_assign(){
  printf("//****//vector_operator_assign\n");
  std::vector<int> foo (3,0);
  std::vector<int> bar (5,0);


  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

void vector_begin_end() {
  printf("//****//vector_begin_end\n");
  std::vector<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void vector_at() {
  printf("//****//vector_at\n");
  std::vector<int> myvector (10);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;
  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';
}

void vector_assign() {
  printf("//****//vector_assign\n");
  std::vector<int> first;
  std::vector<int> second;
  std::vector<int> third;

  first.assign (7,100);             // 7 ints with a value of 100

  std::vector<int>::iterator it;
  it=first.begin()+1;

  second.assign (it,first.end()-1); // the 5 central values of first

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';
}

void vector_insert() {
  printf("//****//vector_insert\n");
  std::vector<int> myvector (3,100);
  std::vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  std::vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void vector_erase() {
  printf("//****//vector_erase\n");
  std::vector<int> myvector;

  // set some values (from 1 to 10)
  for (int i=1; i<=10; i++) myvector.push_back(i);

  // erase the 6th element
  myvector.erase (myvector.begin()+5);

  // erase the first 3 elements:
  myvector.erase (myvector.begin(),myvector.begin()+3);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}

void vector_swap() {
  printf("//****//vector_swap\n");
  std::vector<int> foo (3,100);   // three ints with a value of 100
  std::vector<int> bar (5,200);   // five ints with a value of 200

  foo.swap(bar);

  std::cout << "foo contains:";
  for (unsigned i=0; i<foo.size(); i++)
    std::cout << ' ' << foo[i];
  std::cout << '\n';

  std::cout << "bar contains:";
  for (unsigned i=0; i<bar.size(); i++)
    std::cout << ' ' << bar[i];
  std::cout << '\n';
}

void vector_move() {
  printf("//****//vector_move\n");
  std::string foo = "foo-string";
  std::string bar = "bar-string";
  std::vector<std::string> myvector;

  myvector.push_back (foo);                    // copies
  myvector.push_back (std::move(bar));         // moves

  std::cout << "myvector contains:";
  for (std::string& x:myvector) std::cout << ' ' << x <<'\n';
  std::cout << '\n';
}

void vector_move2() {
  printf("//vector_move2\n");
  A a = getItem(false);
//  A b;
//  b = a;
}

void vector_simple_copy() {
  //调用默认构造函数
  StringWrapper wrapper{"hello"};
  //调用copy构造函数，若未定义copy构造函数，系统构造默认copy构造函数，进行浅copy。由于data并非指针类型，copy效果与深copy相同。
  StringWrapper wrapper2{wrapper};
  wrapper2.data[0] = 'H';
  int i = 0;
  i++;
}

void vector_other() {
  int i = 0;
  int64_t i_64 = 0;
  void *ptr = 0;
  int a[10];
  std::cout << "vector_other:sizeof(i) = " << sizeof(i) << "," << "sizeof (ptr) = " << sizeof(ptr) <<",a[] = "<<sizeof(a)<<'\n';
}
