/**
 * @file TimeSpan.cpp
 * @brief Implementation of TimeSpan class
 * @author Braxton Goss
 */

#include "timespan.h"
#include <cmath>

TimeSpan::TimeSpan(double hour, double minute, double second) {
  double temp_total = 0;

  temp_total += (hour * 3600);
  temp_total += (minute * 60);
  temp_total += second;

  totalNumberOfSeconds = round(
      temp_total); // round after setting to account for total seconds that may
                   // have been lost when multiplying hours and minutes

  setSign();

  // stil keep sign of total seconds but takes the sign using setSign()
  // therefore the totalNumberOfSeconds can be always positive
  totalNumberOfSeconds = abs(totalNumberOfSeconds);
}

// hour component
int TimeSpan::getHour() const { return (totalNumberOfSeconds / 3600); }

// minute component
int TimeSpan::getMinute() const {
  int hours = getHour();
  int temp_seconds_remaining = totalNumberOfSeconds - (3600 * hours);
  return (temp_seconds_remaining / 60);
}

// second component
int TimeSpan::getSecond() const {
  int hoursInSeconds = getHour() * 3600;
  int minutesInSeconds = getMinute() * 60;
  return (totalNumberOfSeconds - hoursInSeconds - minutesInSeconds);
}

// true if timespan is 0 or larger
bool TimeSpan::isPositive() const { return sign; }

// add two TimeSpans together
TimeSpan TimeSpan::operator+(const TimeSpan &ts) const {
  TimeSpan tsSum(getHour() + ts.getHour(), getMinute() + ts.getMinute(),
                 getSecond() + ts.getSecond());
  return tsSum;
}

// subtract one TimeSpan from other TimeSpan
TimeSpan TimeSpan::operator-(const TimeSpan &ts) const {
  TimeSpan tsSub(getHour() - ts.getHour(), getMinute() - ts.getMinute(),
                 getSecond() - ts.getSecond());
  return tsSub;
}
// add two TimeSpans together, shorthand
TimeSpan &TimeSpan::operator+=(const TimeSpan &ts) {
  totalNumberOfSeconds += ts.totalNumberOfSeconds;
  setSign();
  return *this;
}

// subtract one TimeSpan from other TimeSpan, shorthand
TimeSpan &TimeSpan::operator-=(const TimeSpan &ts) {
  totalNumberOfSeconds -= ts.totalNumberOfSeconds;
  setSign();
  return *this;
}

// multiply with an integer
TimeSpan TimeSpan::operator*(unsigned int number) const {
  TimeSpan tsLarge(getHour() * number, getMinute() * number,
                   getSecond() * number);
  return tsLarge;
}

// equality ==, check if this sign is the same as other sign AND they are same
// value.
bool TimeSpan::operator==(const TimeSpan &ts) const {
  return ((sign == ts.sign) &&
          (totalNumberOfSeconds == ts.totalNumberOfSeconds));
}

// inequality !=, check if values are not the same
bool TimeSpan::operator!=(const TimeSpan &ts) const {
  return (totalNumberOfSeconds != ts.totalNumberOfSeconds);
}
// compare the signs and values to check for greater than other TimeSpan
bool TimeSpan::operator>(const TimeSpan &ts) const {
  bool otherSign;
  otherSign = ts.getSign();
  // if ts is negative, return true
  if ((sign == true) && (otherSign == false)) {
    return true;
    // if ts is positive, return false
  } else if ((sign == false) && (otherSign == true)) {
    return false;
    // if they're both positive, return result of totalNumberOfSeconds
  } else if ((sign == true) && (otherSign == true)) {
    return (totalNumberOfSeconds > ts.totalNumberOfSeconds);
    // if they're both negative, return smaller totalNumberOfSeconds because it
    // is closer to zero (while sign is negative)
  } else {
    return (totalNumberOfSeconds < ts.totalNumberOfSeconds);
  }
}
// compare the signs and values to check for less than other TimeSpan
bool TimeSpan::operator<(const TimeSpan &ts) const {
  bool otherSign;
  otherSign = ts.getSign();
  // if this object is negative and ts is positive, return true
  if ((sign == false) && (otherSign == true)) {
    return true;
    // if this object is positive and ts is negative, return false
  } else if ((sign == true) && (otherSign == false)) {
    return true;
    // if they're both positive, return result of smaller totalNumberOfSeconds
  } else if ((sign == true) && (otherSign == true)) {
    return (totalNumberOfSeconds < ts.totalNumberOfSeconds);
    // if they're both negative, return bigger number of totalNumberOfSeconds
    // because it is further from 0 (while sign is negative)
  } else {
    return (totalNumberOfSeconds > ts.totalNumberOfSeconds);
  }
}
// compare the signs and values to check for greater than OR equal to other
// TimeSpan
bool TimeSpan::operator>=(const TimeSpan &ts) const {
  bool otherSign;
  otherSign = ts.getSign();
  if ((sign == false) && (otherSign == false)) {
    return (totalNumberOfSeconds <= ts.totalNumberOfSeconds);
  } else if ((sign == true) && (otherSign == false)) {
    return true;
  } else if ((sign == false) && (otherSign == true)) {
    return false;
  } else {
    return (totalNumberOfSeconds >= ts.totalNumberOfSeconds);
  }
}
// compare the signs and values to check for less than OR equal to other
// TimeSpan
bool TimeSpan::operator<=(const TimeSpan &ts) const {
  bool otherSign;
  otherSign = ts.getSign();
  if ((sign == false) && (otherSign == false)) {
    return (totalNumberOfSeconds >= ts.totalNumberOfSeconds);
  } else if ((sign == true) && (otherSign == false)) {
    return false;
  } else if ((sign == false) && (otherSign == true)) {
    return true;
  } else {
    return (totalNumberOfSeconds <= ts.totalNumberOfSeconds);
  }
}

// ostream overload for easy printing using streams such as: cout <<
// TimeSpanName
ostream &operator<<(ostream &Out, const TimeSpan &ts) {

  if (ts.getSign() == false) {
    Out << "-";
  }
  Out << ts.getHour() << ":";
  if (ts.getMinute() < 10) {
    Out << '0';
  }
  Out << ts.getMinute() << ":";
  if (ts.getSecond() < 10) {
    Out << '0';
  }
  Out << ts.getSecond();

  return Out;
}

// private getter for sign
bool TimeSpan::getSign() const { return sign; }

// private setter for sign, if the value is less than 0, set sign to false.
// if value is greater than OR equal to 0, set sign to true;
void TimeSpan::setSign() {
  if (totalNumberOfSeconds < 0) {
    sign = false;
  } else {
    sign = true;
  }
}
