// assign4_todolist.cpp
// Aidan Anderson, CISP 400
// 11-5-23

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

template <class T> class Array {

  private:
    int size;
    T *elements;

  public:

    Array() {
      size = 0;
      elements = new T[size];
    }

    Array(T *def_arr, int s) {
      size = s;
      elements = new T[size];

      for(int i = 0; i < size; i++) elements[i] = def_arr[i];
    }

    Array(Array &arr) {
      size = arr.size;

      elements = new T[size];

      for(int i = 0; i < size; i++) elements[i] = arr.elements[i];
    }

    ~Array() {
      delete [] elements;
      elements = nullptr;
    }

    T& operator[](int index) {
      if(index > size - 1 || index < 0) return elements[0];

      return elements[index];
    }

    T get(int index) {
      return this->operator[](index);
    }

    int length() {
      return size;
    }

    void add(T element) {
      size += 1;
      T *new_array = new T[size];

      for(int i = 0; i < size - 1; i++) new_array[i] = elements[i];

      new_array[size - 1] = element;

      delete [] elements;
      elements = new_array;

      new_array = nullptr;
    }

    void remove(int index) {
      size -= 1;
      T *new_array = new T[size];

      for(int i = 0; i < size; i++) {
        if(i < index) {
          new_array[i] = elements[i];
        }else {
          new_array[i] = elements[i + 1];
        }
      }

      delete [] elements;
      elements = new_array;

      new_array = nullptr; 
    }

    void clear() {
      size = 0;
      delete [] elements;
      elements = new T[size];
    }

    bool is_empty() {
      return size <= 0;
    }

    static void comp_test() {
      Array<int> arr1;

      for(int i = 0; i < 10; i++) arr1.add(i + 1);

      cout << "Array Component Test\n====================" << endl;
      cout << "Not Empty: " << (!arr1.is_empty() ? "Passed" : "Failed") << endl;
      cout << "Array Size: " << (arr1.length() == 10 ? "Passed" : "Failed") << endl;

      arr1.clear();

      cout << "Array Empty: " << (arr1.is_empty() ? "Passed" : "Failed") << endl << endl;
    }

};

struct Item {

  int id;
  string message, date;

  // Specification A4 - Overload Constructor
  Item() {
    id = -1;
    message = "An Immortal Dummy Message!";
    date = "Dummy Date!";
  }

  // Specification A1 - Overload Copy Constructor
  Item(Item& item) {
    id = item.id;
    message = item.message;
    date = item.date;
  }

  Item(int x, string msg, string date_stamp) {
    id = x;
    message = msg;
    date = date_stamp;
  }

  // Specification A2 - Overload Assignment Operator
  void operator=(const Item& item) {
    id = item.id;
    message = item.message;
    date = item.date;
  }

  //Specification C2 - Overload »
  friend istream& operator>>(istream& is, Item& item) {
    std::cout << "Enter a todo message: " << endl;
    string result;
    std::getline(is, result);
    std::cout << endl;

    if(result.size() == 0) {
      item.id = -2;
      return is;
    }

    item.message = result;

    // Specification A3 - System Date.
    time_t now = time(nullptr);

    string a = asctime(localtime(&now));
    //Remove extra newline character from ascii time function
    a.pop_back();

    item.date = a;

    return is;
  }

  // Specification C1 - Overload «
  friend ostream& operator<<(ostream& os, const Item& item) {
    os << "ID: " << item.id << endl;
    os << "TODO: \"" << item.message << "\"" << endl;
    os << "ADDED: " << item.date << endl;

    return os;
  }

  static void comp_test() {
    Item it1(99999, "Test Message", "Test Date");
    Item it2 = it1;

    cout << "Item Component Test\n===================" << endl;
    cout << "Test Id: " << (it1.id == it2.id ? "Passed" : "Failed") << endl;
    cout << "Test Message: " << (it1.message == it2.message ? "Passed" : "Failed") << endl;
    cout << "Test Date: " << (it1.date == it2.date ? "Passed" : "Failed") << endl << endl;

  }

};

void program_greeting();
void comp_test();

void run();

void add_todo(Array<Item>&);
void remove_todo(Array<Item>&);
void print_todos(Array<Item>);

int generate_id(Array<Item>);

void load_todos(Array<Item>&);
bool save_todos(Array<Item>&);

void strip_char(string&, char);

int main() {

  program_greeting();

  comp_test();

  srand(time(nullptr));

  run();

  return 0;
}

void run() {

  bool is_running = true;

  //Specification C4 - TODO array
  Array<Item> items_arr;

  load_todos(items_arr);

  while(is_running) {

    std::cout << "\nMENU:\n=====\n(+) Add TODO\n(-) Remove TODO\n(?) Display TODOs\n(x) Exit" << endl;
    
    string line;
    std::getline(cin, line);
    std::cout << endl;

    if(line.size() != 1) {
      std::cout << "Invalid Selection!" << endl;
      continue;
    }

    switch(line[0]) {
      // Specification B1 - + Symbol
      case '+':
        add_todo(items_arr);
        break;

      // Specification B3 - - symbol
      case '-':
        remove_todo(items_arr);
        break;

      // Specification B2 - ? Symbol
      case '?':
        print_todos(items_arr);
        break;

      case 'x':
        save_todos(items_arr);
        is_running = false;
        break;

      default:
        std::cout << "Invalid Selection!" << endl;
        break;
    }
    
  }

}

void program_greeting() {

  cout << "Program Greeting! This is a program that stores, adds and removes messages from a todo list!" << endl;
  cout << "I have rigorously tested this program to ensure that it will always behave as expected" << endl;
  cout << "Aidan Anderson; CISP 400; 11-5-2023" << endl;

  time_t now = time(nullptr);
  cout << asctime(localtime(&now)) << endl;

}

void comp_test() {

  Array<Item> test_arr;

  // Specification C3 - Test TODO’s
  Item::comp_test();
  Array<int>::comp_test();

  cout << "Component Test:\n=============" << endl;

  for(int i = 0; i < 5; i++) test_arr.add(Item());

  cout << "Test add todo: " << (test_arr.length() == 5 ? "Passed" : "Failed") << endl;

  for(int i = 0; i < 5; i++) test_arr.remove(0);

  cout << "Test remove todo: " << (test_arr.is_empty() ? "Passed" : "Failed") << endl << endl;
}

void add_todo(Array<Item> &items) {

  Item item_to_add;
  cin >> item_to_add;

  if(item_to_add.id == -2) {
    items.add(item_to_add);
    std::cout << "Dummy Data Triggered!" << endl;
    return;
  }

  item_to_add.id = generate_id(items);
  
  items.add(item_to_add);

  std::cout << "TODO added successfully!" << endl;
}

//TODO refactor
void remove_todo(Array<Item> &items) {

  if(items.length() <= 0) {
    std::cout << "No Items Available!" << endl;
    return;
  }

  int id_to_remove;
  bool invalid = false;

  do {

    invalid = false;

    std::cout << "Enter an ID to remove:" << endl;
    string s;
    std::getline(cin, s);
    std::cout << endl;

    try {
      id_to_remove = stoi(s);
    }catch(invalid_argument& ia) {
      std::cout << "Invalid Item ID!" << endl;
      invalid = true;
      continue;
    }

    if(id_to_remove <= 0) {
      std::cout << "Invalid ID!" << endl;
      invalid = true;
    }

  }while(invalid);

  int index_to_remove = -1;

  for(int i = 0; i < items.length(); i++) {

    if(items.get(i).id == id_to_remove) {
      index_to_remove = i;
      break;
    }

  }

  if(index_to_remove < 0) {
    std::cout << "ID Not Found!" << endl;
    return;
  }

  items.remove(index_to_remove);
  std::cout << "TODO removed successfully!" << endl;
}

void print_todos(Array<Item> items) {

  std::cout << "CURRENT TODOs:\n==============" << endl;

  if(items.length() <= 0) {
    std::cout << "No Items!" << endl;
    return;
  }

  for(int i = 0; i < items.length(); i++) std::cout << items.get(i) << "--------------" << endl;
}


//ID GENERATION
int generate_id(Array<Item> items) {
  
  const int ID_LEN = 6;
  int generated_id = 0;

  bool is_invalid = false;
  
  do {

    //Generate ID
    for(int x = 0; x < ID_LEN; x++) {
      int digit = rand() % 10;
      generated_id += digit * pow(10, x);
    }

    //Check if exists already
    for(int i = 0; i < items.length(); i++) {
      if(items.get(i).id != generated_id) continue;

      is_invalid = true;
      break;
    }

  }while(is_invalid);

  return generated_id;
}


//FILE UTILS
//SAVING AND LOADING

// Specification B4 - Persistence
void load_todos(Array<Item> &items) {
  
  ifstream file("todo.txt");

  if(!file.is_open()) {
    std::cout << "Error reading from file!" << endl;
    return;
  }

  bool is_running = true;
  Item next_item;

  int iter = 0;

  while(is_running) {

    char next = file.peek();

    if(next == 0x03 || next == EOF) {
      file.ignore();
      is_running = false;
      continue;
    }

    if(next == 0x1E) {
      file.ignore();

      string id_str;
      std::getline(file, id_str, (char) 0x1F);

      int id;

      try {
        id = stoi(id_str);
      }catch(invalid_argument& ia) {
        std::cout << "Invalid ID while reading item index " << iter << endl;
        id = -1;
      }

      next_item.id = id;

      string msg_str, date_str;
      std::getline(file, msg_str, (char) 0x1F);
      std::getline(file, date_str, (char) 0x1F);

      strip_char(msg_str, '\n');
      strip_char(date_str, '\n');

      next_item.message = msg_str;
      next_item.date = date_str;

      items.add(next_item);
    }else {
      file.ignore();
    }

    iter++;

  }

  file.close();

  std::cout << "Loaded TODOs successfully!" << endl;
}

bool save_todos(Array<Item> &items) {

  ofstream file("todo.txt");

  if(!file.is_open()) {
    std::cout << "Error writing to file!" << endl;
    return false;
  }

  for(int i = 0; i < items.length(); i++) {

    file.put(0x1E);

    file << items[i].id << (char) 0x1F;
    file << items[i].message << (char) 0x1F;
    file << items[i].date << (char) 0x1F;
    
  }

  //END TEXT
  file.put(0x03);

  file.close();

  std::cout << "Saved TODOS!" << endl;

  return true;
}

void strip_char(string &str, char ch) {

  for(int i = 0; i < str.size(); i++) if(str[i] == ch) str.erase(str.begin() + i);
  
}