/**
 * @file main.cpp
 * @brief driver file for timespan implementation, including added tests using
 * cassert and stringstream
 * @author Braxton Goss
 */

#include <cassert>
#include <iostream>
#include <sstream>

#include "timespan.h"

using namespace std;

// testing constructor
void test1() {

  TimeSpan ts1{}; // curly braces used for object initialization with no
                  // parameters, using Object Foo(); causes the compiler to
                  // treat it like a function declaration
  stringstream ss;
  ss << ts1;
  assert(ss.str() ==
         "0:00:00"); // test empty timespan creation for default values

  TimeSpan ts(1, 20, 30);
  ss.str("");
  ss << ts;
  assert(ss.str() == "1:20:30"); // test normal entry

  TimeSpan ts2(4, -20, -90);
  ss.str("");
  ss << ts2;
  assert(ss.str() == "3:38:30"); // test negative minutes and seconds

  TimeSpan ts3(1.5, 30.5, -90);
  ss.str("");
  ss << ts3;
  assert(ss.str() ==
         "1:59:00"); // test decimal hours, decimal minutes, negative seconds

  TimeSpan ts4(0, 0.07, 0);
  ss.str("");
  ss << ts4;
  assert(ss.str() == "0:00:04"); // test decimal minutes

  TimeSpan ts5(1, 800, 15);
  ss.str("");
  ss << ts5;
  assert(ss.str() == "14:20:15"); // test large minutes converted to hours

  TimeSpan ts6(0, 0, 6000000);
  ss.str("");
  ss << ts6;
  assert(ss.str() == "1666:40:00"); // test huge seconds value for conversion

  TimeSpan ts7(0, 0, -6000000);
  ss.str("");
  ss << ts7;
  assert(ss.str() ==
         "-1666:40:00"); // test huge negative seconds for conversion

  cout << "test1 complete" << endl;
}

// testing equality, addition, subtraction, multiplication
void test2() {
  TimeSpan ts(1, 20, 30);
  TimeSpan ts2(1, 20, 30);
  TimeSpan ts3(0, 0, 0);
  TimeSpan ts4(4, 1, 30);

  assert(ts == ts2);
  assert(!(ts != ts2));
  assert(ts != ts3);
  assert((ts + ts + ts) == ts4);
  assert((ts + ts + ts) == (ts2 * 3));
  assert((ts * 5) == (ts2 * 4) + ts2);
  assert((ts * 5) == (ts2 * 6) - ts2);
  assert((ts + ts - ts) == ((ts2 * 2) - ts));
  assert((ts - ts2) == ts3);
  assert((ts3 * 5) == ts3);
  cout << "test2 complete" << endl;
}

void test3() {
  TimeSpan ts0(0, 0, 0);
  TimeSpan ts1(0, 0, 10);
  TimeSpan ts2 = ts0 - ts1;
  assert(ts0.isPositive());
  assert(ts1.isPositive() && !ts2.isPositive());
  stringstream ss;
  ss << ts2;
  assert(ss.str() == "-0:00:10");
  cout << "test3 complete" << endl;
}

int main() {
  test1();
  test2();
  test3();
  cout << "Done." << std::endl;
  return 0;
}