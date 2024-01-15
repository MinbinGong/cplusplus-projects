// io/timemanipulator1.cpp

#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  // process and print current data and time;
  auto now = chrono::system_clock::now();
  time_t t = chrono::system_clock::to_time_t(now);
  tm* nowTM = localtime(&t);
  cout << put_time(nowTM, "data: %x\ntime: %X\n") << endl;

  // read date;
  tm* date;
  cout << "new date: ";
  cin >> get_time(date, "%x");
  if (!cin) {
    cerr << "invalid format read" << endl;
  }
}