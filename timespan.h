/**
 * @file TimeSpan.h
 * @brief header file for TimeSpan class
 * @author Braxton Goss
 */

#ifndef ASS2_TIMESPAN_H
#define ASS2_TIMESPAN_H

#include <iostream>
#include <string>

using namespace std;

class TimeSpan {
  friend ostream &operator<<(ostream &out, const TimeSpan &ts);

public:
  // constructor to handle default values of 0, full implementation in .cpp file
  explicit TimeSpan(double hour = 0, double minute = 0, double second = 0);

  // add two TimeSpans together
  TimeSpan operator+(const TimeSpan &ts) const;

  // subtract one TimeSpan from other TimeSpan
  TimeSpan operator-(const TimeSpan &ts) const;

  // add two TimeSpans together, shorthand
  TimeSpan &operator+=(const TimeSpan &ts);

  // subtract one TimeSpan from other TimeSpan, shorthand
  TimeSpan &operator-=(const TimeSpan &ts);

  // multiply timespan by an unsigned integer
  TimeSpan operator*(unsigned int number) const;

  // check equality between TimeSpans
  bool operator==(const TimeSpan &ts) const;

  // check if two TimeSpans are not equal
  bool operator!=(const TimeSpan &ts) const;

  // check if this TimeSpan is greater than other TimeSpan
  bool operator>(const TimeSpan &ts) const;

  // check if other TimeSpan is greater than this TimeSpan
  bool operator<(const TimeSpan &ts) const;

  // check if this TimeSpan is greater than or equal to other TimeSpan
  bool operator>=(const TimeSpan &ts) const;

  // check if other TimeSpan is greater than or equal to this TimeSpan
  bool operator<=(const TimeSpan &ts) const;

  // get hour component of timespan
  int getHour() const;

  // get minute component of timespan
  int getMinute() const;

  // get second component of timespan
  int getSecond() const;

  // true if timespan is 0 or larger
  bool isPositive() const;

private:
  int totalNumberOfSeconds; // all hours and minutes can be converted to
                            // seconds, this data value holds the entire span

  bool sign; // to make life easier for isPositive method and comparator
             // operators, sign (+ or -) of the span is held in bool (true =
             // positive, false = negative)

  bool getSign() const; // helper to reduce code repition when fetching sign for
                        // comparator (only accessible by class methods)

  void setSign(); // sign setter for constructor
};

#endif // ASS2_TIMESPAN_H
