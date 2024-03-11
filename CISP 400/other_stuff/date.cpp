#include <iostream>
#include <string>

using namespace std;

class Date {

  private:
    int day, month, year;

  public:

    Date() {
      time_t current = time(NULL);
      tm *local = localtime(&current);

      day = local->tm_mday;
      month = local->tm_mon + 1;
      year = local->tm_year + 1900;
    }

    int get_day() { return day; }
    int get_month() { return month; }
    int get_year() { return year; }

    string get_string() {
      string a;
      a += to_string(month) + "/";
      a += to_string(day) + "/";
      a += to_string(year);
      return a;
    }

    void comp_test() {
      cout << "Date Class Component Test:\n==========================" << endl;

      Date test;
      test.set_date(day, month, year);

      string pass = "Passed";
      string fail = "Failed";

      cout << "Test Day: " << (test.get_day() == day ? pass : fail) << endl;
      cout << "Test Month: " << (test.get_month() == month ? pass : fail) << endl;
      cout << "Test Year: " << (test.get_year() == year ? pass : fail) << endl;
      cout << endl;
    }

    void set_date(int d, int m, int y) {
      day = d;
      month = m;
      year = y;
    }

    void print() {
      cout << get_string() << endl;
    }
};

int main() {
  Date d;
  d.set_date(9999, 9999, 9999);
  d.print();
  return 0;
}