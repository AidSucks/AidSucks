// assign3_invinquiz.cpp
// Aidan Anderson, CISP 400
// 10-22-23

#include <iostream>

using namespace std;

//Dynamically sized array template class
//Coded by yours truly :)
template <class T> class Array {

  private:
    int size;
    // Specification C2 - Dynamic Array
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

    // Specification C3 - Resize Array
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
      if(size <= 0) return;

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

    void pop() {
      remove(size - 1);
    }

};

// Specification B1 - Date class
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
      cout << month << "/" << day << "/" << year << endl;
    }
};

//Specification B2 -RandNo Class
class RandNo {

  private:

    static RandNo* instance;
    
    RandNo() {
      srand(time(NULL));
    }

  public:

    RandNo(const RandNo &obj) = delete;

    // Specification B3 - Singleton Design Pattern
    static RandNo* get_instance() {

      if(instance == NULL) instance = new RandNo();

      return instance;
    }

    float generate_rcost(float w_cost) {
      int a = rand() % 5 + 1;
      float b = a * 0.1;
      return w_cost + (w_cost * b);
    }

    // Specification A3 - Overload operator»
    friend istream& operator>>(istream& is, RandNo& rn) {
      int seed;
      cout << "Enter in seed:" << endl;
      cin >> seed;
      srand(seed);
      return is;
    }

};

struct Item {

  int item_id, quantity;
  float w_cost, r_cost;
  Date date_added;

  Item() {
    Date d;
    d.set_date(99, 99, 99);
    item_id = 0;
    quantity = 0;
    w_cost = 0;
    r_cost = 0;
    date_added = d;
  }

  Item(int id, int q, float wc, float rc, Date date) {
    item_id = id;
    quantity = q;
    w_cost = wc;
    r_cost = rc;
    date_added = date;
  }

  void operator=(const Item &it) {
    item_id = it.item_id;
    quantity = it.quantity;
    w_cost = it.w_cost;
    r_cost = it.r_cost;
    date_added = it.date_added;
  }

  //TODO Prettify this output
  // Specification A2 - Overload operator«
  friend ostream& operator<<(ostream& os, Item item) {
		os << "ID: " << item.item_id << endl;
    os << "Quantity: " << item.quantity << endl;
    os << "Wholesale Cost: " << item.w_cost << endl;
    os << "Retail Cost: " << item.r_cost << endl;
    os << "Date added: ";
    item.date_added.print();
		return os;
	}
};

//Function Prototypes
void program_greeting();
void unit_test();
void run();
void add_inv(Array<Item>&);
void del_inv(Array<Item>&);
void edit_inv(Array<Item>&);
void print_inv(Array<Item>);
bool inval(Item);

RandNo *RandNo::instance = NULL;

int main() {

  program_greeting();
  // Specification A4 - UnitTest() function in main()
  unit_test();

  cin >> *RandNo::get_instance();

  run();

  return 0;
}

void run() {

  Array<Item> inventory;

  bool is_running = true;

  while(is_running) {

    char in;

    cout << "Main Menu\n<A>dd Inventory\n<D>elete Inventory\n<E>dit Inventory\n<P>rint Inventory\n<Q>uit" << endl;
    cin >> in;

    // Specification C1 - Alpha Menu
    switch(in) {
      
      case 'A':
        add_inv(inventory);
        break;

      case 'D':
        del_inv(inventory);
        break;

      case 'E':
        edit_inv(inventory);
        break;

      case 'P':
        print_inv(inventory);
        break;

      case 'Q':
        is_running = false;
        break;
    
      // Specification C4 - Menu Input Validation
      default:
        cout << "Invalid input" << endl;
        break;
    }
  }

}

void add_inv(Array<Item> &arr) {

  Item item_to_add;

  bool invalid = false;

  do {

    if(invalid) cout << "Invalid Input!" << endl;

    invalid = false;

    int id, quantity;
    float w_cost;

    cout << "Input Id: " << endl;
    cin >> id;
    cout << "Input Quantity: " << endl;
    cin >> quantity;
    cout << "Input Wholesale Cost: " << endl;
    cin >> w_cost;

    Date today;
    RandNo *randno = RandNo::get_instance();

    float r_cost = randno->generate_rcost(w_cost);

    item_to_add.item_id = id;
    item_to_add.quantity = quantity;
    item_to_add.w_cost = w_cost;
    item_to_add.r_cost = r_cost;
    item_to_add.date_added = today;

    invalid = inval(item_to_add);

  }while(invalid);

  arr.add(item_to_add); 
  cout << "Item successfully added!" << endl;

}

void del_inv(Array<Item> &arr) {

  if(arr.length() <= 0) {
    cout << "No items available to delete!" << endl;
    return;
  }

  arr.pop();

  cout << "Item successfully deleted!" << endl;
}

// Specification A1 - Edit Inventory
void edit_inv(Array<Item> &arr) {

  if(arr.length() <= 0) {
    cout << "No items available to edit!" << endl;
    return;
  }

  bool invalid_input = false;
  int index;
  Item item;

  do {

    if(invalid_input) cout << "Invalid Index" << endl;

    cout << "Enter the index to edit:" << endl;
    cin >> index;

    if(index < 0 || index >= arr.length()) invalid_input = true;

  }while(invalid_input);

  do {
    
    if(invalid_input) cout << "Invalid input!" << endl;

    cout << "Enter new Id:" << endl;
    cin >> item.item_id;
    cout << "Enter new quantity:" << endl;
    cin >> item.quantity;
    cout << "Enter new wholesale cost:" << endl;
    cin >> item.w_cost;
    cout << "Enter new retail cost:" << endl;
    cin >> item.r_cost;

    invalid_input = inval(item);

  }while(invalid_input);

  arr[index].item_id = item.item_id;
  arr[index].quantity = item.quantity;
  arr[index].w_cost = item.w_cost;
  arr[index].r_cost = item.r_cost;

  Date d;
  arr[index].date_added = d;

  cout << "Item successfully edited" << endl;

}

void print_inv(Array<Item> arr) {

  cout << "Current Inventory Items:" << endl;
  for(int i = 0; i < arr.length(); i++) cout << "Index: " << i << endl << arr.get(i) << endl;

}

// Specification B4 - Inventory Entry Input Validation
bool inval(Item item) {

  int count = 0;
  do {
    item.item_id /= 10;
    count++;
  }while(item.item_id != 0);

  if(count != 5 || item.quantity < 0 || item.w_cost < 0) return true;

  return false;
}

void unit_test() {
  Date d;
  d.comp_test();
}

void program_greeting() {
  cout << "Program Greeting! This program is an inventory management program that allows you to add, edit, delete, and print out a list of stored items" << endl;
}