// assign2_gpaanalyzer.cpp
// Aidan Anderson, CISP 400
// 9-24-23

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Array {
  private:
    int size;
    // Specification B1 - Dynamic Array
    int *elements;

  public:

    Array() {
      size = 0;
      elements = new int[size];
    }

    Array(Array &arr) {
      size = arr.size;

      elements = new int[size];

      for(int i = 0; i < size; i++) elements[i] = arr.elements[i];
    }

    ~Array() {
      delete [] elements;
      elements = nullptr;
    }

    int length() {
      return size;
    }

    //Specification B2 - Add Elements
    void add(int element) {
      size += 1;
      int *new_array = new int[size];

      for(int i = 0; i < size - 1; i++) new_array[i] = elements[i];

      new_array[size - 1] = element;

      delete [] elements;
      elements = new_array;

      new_array = nullptr;
    }

    int get(int index) {
      if(index > size - 1 || index < 0) return elements[0];

      return elements[index];
    }
};

// Specification B4 - Highlight Failing Grades
class FancyText {

  public:

    string colorize_text(string raw, string color) {
      return "\e[" + color + "m" + raw + "\e[0m";
    }

};

// Specification A1 - Date class
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

    int get_day() {
      return day;
    }

    int get_month() {
      return month;
    }

    int get_year() {
      return year;
    }

    // Specification A3 - Component Test Method in Date
    void comp_test() {

      cout << "Date Class Component Test:\n==========================" << endl;

      Date test;
      test.set_date(day, month, year);

      FancyText ft;
      string pass = ft.colorize_text("Passed", "92");
      string fail = ft.colorize_text("Failed", "91");

      cout << "Test Day: " << (test.get_day() == day ? pass : fail) << endl;
      cout << "Test Month: " << (test.get_month() == month ? pass : fail) << endl;
      cout << "Test Year: " << (test.get_year() == year ? pass : fail) << endl;
      cout << endl;
    }

    // Specification A2 - External date initialization
    void set_date(int d, int m, int y) {
      day = d;
      month = m;
      year = y;
    }

    void print() {
      cout << month << "/" << day << "/" << year << endl;
    }
};

//Function Prototypes
void program_greeting();
void unit_test();
void start();
void add_grade(Array&);
void display_grades(Array);
void process_grades(Array);
char grade_to_letter(int);

int main() {

  program_greeting();
  unit_test();

  start();

  return 0;
}

void start() {

  bool is_running = true;

  Array grades;

  do {

    cout << "Main Menu:\n==========\n1.Add Grade\n2.Display Grades\n3.Process Grades\n4.Quit" << endl;
    int answer;
    cin >> answer;
    cout << endl;

    // Specification B3 - Menu Input Validation
    switch(answer) {
      case 1:
        add_grade(grades);
        break;

      case 2:
        display_grades(grades);
        break;

      case 3:
        process_grades(grades);
        break;

      case 4:
        is_running = false;
        break;

      default:
        cout << "Invalid Selection" << endl;
        break;
    }

  }while(is_running);
}

void add_grade(Array& grades) {

  bool is_invalid = false;

  int grade = 0;

  do {

    cout << "Enter a score to add:" << endl;
    cin >> grade;
    cout << endl;

    if(grade < 0 || grade > 100) {
      is_invalid = true;
      cout << "Invalid Input!" << endl;
    }

  }while(is_invalid);

  grades.add(grade);
}

// Specification C2 - Print Scores
void display_grades(Array grades) {
  
  cout << "Current Grades:" << endl;

  FancyText ft;

  for(int i = 0; i < grades.length(); i++) {
    int g = grades.get(i);
    char c = grade_to_letter(g);
    string s = "";
    s += c;
    string out = "";

    if(g < 70) {
      out = ft.colorize_text(s, "31");
    }else if(g < 80) {
      out = ft.colorize_text(s, "33");
    }else {
      out = ft.colorize_text(s, "32");
    }

    cout << g << " " << out << endl;
  }

  cout << endl;
}

// Specification C4 - Compute GPA
void process_grades(Array grades) {

  FancyText ft;

  int total = 0;

  for(int i = 0; i < grades.length(); i++) total += grades.get(i);

  int gpa = total / grades.length();
  
  char c = grade_to_letter(gpa);
  
  string s = "";
  s += c;

  string out = "";

    if(gpa < 70) {
      out = ft.colorize_text(s, "31");
    }else if(gpa < 80) {
      out = ft.colorize_text(s, "33");
    }else {
      out = ft.colorize_text(s, "32");
    }

  cout << "GPA: " << gpa << " " << out << endl << endl;
}

// Specification C3 - Letter Grades
char grade_to_letter(int grade) {

  if(grade < 0 || grade > 100) return 'X';

  if(grade < 60) return 'F';
  if(grade < 70) return 'D';
  if(grade < 80) return 'C';
  if(grade < 90) return 'B';

  return 'A';
}

// Specification C1 - Program Greeting Function
void program_greeting() {
  cout << "Welcome! This program will calculate your GPA given scores ranging from 0 to 100" << endl;
  cout << "Author: Aidan Anderson" << endl;
  cout << "Due: September 24, 2023" << endl << endl;
}

// Specification A4 - Unit Test
void unit_test() {

  FancyText ft;

  string pass = ft.colorize_text("Passed", "92");
  string fail = ft.colorize_text("Failed", "91");

  cout << "Unit Tests:" << endl << endl;

  cout << "Letter Grade Conversion:\n========================" << endl;
  cout << "Test High: " << (grade_to_letter(101) == 'X' ? pass : fail) << endl;
  cout << "Test Low: " << (grade_to_letter(-1) == 'X' ? pass : fail) << endl;
  cout << "Test A: " << (grade_to_letter(90) == 'A' ? pass : fail) << endl;
  cout << "Test B: " << (grade_to_letter(80) == 'B' ? pass : fail) << endl;
  cout << "Test C: " << (grade_to_letter(70) == 'C' ? pass : fail) << endl;
  cout << "Test D: " << (grade_to_letter(60) == 'D' ? pass : fail) << endl;
  cout << "Test F: " << (grade_to_letter(50) == 'F' ? pass : fail) << endl;
  cout << endl;

  Date date;

  date.comp_test();
}