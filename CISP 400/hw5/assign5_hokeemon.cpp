// assign5_hokeemon.cpp
// Aidan Anderson, CISP 400
// 11-26-23

#include <iostream>
#include <string>

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

    void comp_test() {

      Array<int> arr1;

      for(int i = 0; i < 10; i++) arr1.add(i + 1);

      cout << "Array Component Test\n====================" << endl;
      cout << "Not Empty: " << (!arr1.is_empty() ? "Passed" : "Failed") << endl;
      cout << "Array Size: " << (arr1.length() == 10 ? "Passed" : "Failed") << endl;

      arr1.clear();

      cout << "Array Empty: " << (arr1.is_empty() ? "Passed" : "Failed") << endl << endl;

    }

};

// Specification C2 - Creature class
class Creature {

  protected:
    string name = "", type = "";
    int hunger = 0, boredom = 0;
    float h_multiplier = 0;
    float b_multiplier = 0;

    Creature() {
      generate_stats();
    }

    // Specification A2 - Copy Constructor
    Creature(const Creature& copy) {
      name = copy.name;
      type = copy.type;
      hunger = copy.hunger;
      boredom = copy.boredom;
      h_multiplier = copy.h_multiplier;
      b_multiplier = copy.b_multiplier; 
    }

  public:

    int get_hunger() { return hunger; }
    int get_boredom() { return boredom; }
    string get_name() { return name; }
    string get_type() { return type; }

    void set_name(string s) { name = s; }

    void generate_stats() {
      hunger = rand() % 6;
      boredom = rand() % 6;
    }

    void play() {
      // Random number 4-8
      int rn = rand() % 5 + 4;
      rn *= b_multiplier;

      boredom -= rn;

      cout << "Played with \"" << name << "\" (-" << rn << " Boredom)" << endl;
    }

    void feed() {
      //Random number 3-6
      int rn = rand() % 4 + 3;
      rn *= h_multiplier;

      hunger += rn;

      cout << "Fed \"" << name << "\" (+" << rn << " Food)" << endl;
    };

    void pass() {
      hunger -= 1;
      boredom += 1;
    }

    // Specification B2 - Virtual Class Creature
    virtual void listen() = 0;

    // Specification C4 - Overload «
    friend ostream& operator<<(ostream& os, const Creature& cr) {
      os << "Type: " << cr.type << endl;
      os << "Name: \"" << cr.name << "\"" << endl;
      os << "Food: " << cr.hunger << endl;
      os << "Boredom: " << cr.boredom << endl;
      return os;
    }

    //Specification B3 - Overload Assignment Operator
    Creature& operator=(const Creature& cr) {
      name = cr.name;
      type = cr.type;
      hunger = cr.hunger;
      boredom = cr.boredom;
      h_multiplier = cr.h_multiplier;
      b_multiplier = cr.b_multiplier;
      return *this;
    }

    virtual void comp_test() = 0;

};

// Specification B1 - Child Class
class Snek : public Creature {

  public:

    Snek() : Snek("Unnamed Snek") {}

    Snek(string n) { 
      name = n;
      type = "Snek";
      h_multiplier = 1;
      b_multiplier = 1; 
    }

    void listen() {
      cout << *this << "\"Remember, no step on snek!!\"" << endl << endl;
    }

    Snek operator+(const Snek& other) {
      Snek s;

      //Averages
      s.h_multiplier = (h_multiplier + other.h_multiplier) / 2.0;
      s.b_multiplier = (b_multiplier + other.b_multiplier) / 2.0;

      s.hunger = (hunger + other.hunger) / 2;
      s.boredom = (boredom + other.boredom) / 2;

      return s;
    }

    void comp_test() {
      cout << "Snek Component Test\n====================" << endl;

      Snek s1;
      Snek s2 = s1;
      Snek s3 = s1 + s2;

      cout << "Copy Name: " << (s1.get_name() == s2.get_name() ? "Passed" : "Failed") << endl;
      cout << "Average Boredom: " << (s3.get_boredom() == ((s1.get_boredom() + s2.get_boredom()) / 2) ? "Passed" : "Failed") << endl;
      cout << "Average Hunger: " << (s3.get_hunger() == ((s1.get_hunger() + s2.get_hunger()) / 2) ? "Passed" : "Failed") << endl << endl;

    }
};

// Specification A3 - Second Child Class
class Tortle : public Creature {

  public:

    Tortle() : Tortle("Unnamed Tortle") {}
    
    Tortle(string n) { 
      name = n;
      type = "Tortle";
      h_multiplier = 1;
      b_multiplier = 1;
    }

    void listen() {
      cout << *this << "\"I like tortles\"" << endl << endl;
    }

    //Specification B4 - Overload + Operator
    Tortle operator+(const Tortle& other) {
      Tortle t;

      //Averages
      t.h_multiplier = (h_multiplier + other.h_multiplier) / 2.0;
      t.b_multiplier = (b_multiplier + other.b_multiplier) / 2.0;

      t.hunger = (hunger + other.hunger) / 2;
      t.boredom = (boredom + other.boredom) / 2;

      return t;
    }

    void comp_test() {
      cout << "Tortle Component Test\n====================" << endl;

      Tortle s1;
      Tortle s2(s1);
      Tortle s3 = s1 + s2;

      cout << "Copy Name: " << (s1.get_name() == s2.get_name() ? "Passed" : "Failed") << endl;
      cout << "Average Boredom: " << (s3.get_boredom() == ((s1.get_boredom() + s2.get_boredom()) / 2) ? "Passed" : "Failed") << endl;
      cout << "Average Hunger: " << (s3.get_hunger() == ((s1.get_hunger() + s2.get_hunger()) / 2) ? "Passed" : "Failed") << endl << endl;
    }
};



//Function Prototypes
void start();
Creature* prompt_starter();
void pass_time(Array<Creature*>&);
bool check_death(Array<Creature*>&);

void catch_mon(Array<Creature*>&);
void listen(Array<Creature*>&);
void play(Array<Creature*>&);
void feed(Array<Creature*>&);
void prompt_name(Creature*);
int prompt_num();

void program_greeting();
void comp_test();

//Main
int main() {

  srand(time(nullptr));

  program_greeting();

  comp_test();

  start();

  return 0;
}

//Function implementations

//Main game loop
void start() {

  Creature* starter = prompt_starter();
  
  Array<Creature*> hokee_deck;
  hokee_deck.add(starter);

  bool is_running = true;

  while(is_running) {

    cout << "MENU\n(L)isten (C)atch (P)lay (F)eed (Q)uit" << endl;
    string input;
    getline(cin, input);

    if(input.size() != 1) {
      cout << "Invalid Input!" << endl;
      continue;
    }

    // Specification C3 - Validate Input
    switch (input[0]) {
      
      case 'L':
        listen(hokee_deck);
        continue;

      case 'C':
        catch_mon(hokee_deck);
        break;
      
      case 'P':
        play(hokee_deck);
        break;

      case 'F':
        feed(hokee_deck);
        break;
      
      case 'Q':
        is_running = false;
        continue;
    
    default:
      cout << "Invalid Selection!" << endl;
      break;
    }

    pass_time(hokee_deck);

    bool all_dead = check_death(hokee_deck);

    if(all_dead) cout << "All of your Hokeemon have died. You lose!" << endl;

    is_running = !all_dead;
  }

}

Creature* prompt_starter() {

  bool invalid;
  Creature* c;

  cout << "Choose your starter Hokeemon:\n(1) Snek\n(2) Tortle" << endl;

  do {

    invalid = false;
    
    int deserialized = prompt_num();

    //Use different method
    switch(deserialized) {

      case 1:
        c = new Snek();
        break;

      case 2:
         c = new Tortle();
         break;

      default:
        cout << "Invalid Selection! Try again:" << endl;
        invalid = true;
    }

  }while(invalid);

  prompt_name(c);
  
  return c;
}

// Specification C1 - PassTime()
void pass_time(Array<Creature*>& deck) {
  cout << "Time Passes" << endl << endl;
  for(int i = 0; i < deck.length(); i++) deck[i]->pass();
}

bool check_death(Array<Creature*>& deck) {

  // Specification A4 - Write a Lambda
  auto is_dead = [] (Creature* c) {
    return c->get_boredom() > 20 || c->get_hunger() < 0;
  };

  for(int i = 0; i < deck.length(); i++) {
    Creature *c;
    c = deck[i];

    if(!is_dead(c)) continue;

    cout << "\"" << c->get_name() << "\" has died!" << endl;

    deck.remove(i);
  }

  return deck.is_empty();
}

void catch_mon(Array<Creature*>& deck) {

  int chance = rand() % 100 + 1;

  //50 percent chance
  if(chance > 50) {
    cout << "You didn't catch anything!" << endl;
    return;
  }

  Creature *c;

  int pick = rand() % 2;

  if(pick == 0) {
    c = new Snek();
  }else {
    c = new Tortle();
  }

  cout << "You caught a " << c->get_type() << "!" << endl;

  prompt_name(c);

  deck.add(c);
}

void listen(Array<Creature*>& deck) {

  cout << "YOUR HOKEEMON DECK:\n============" << endl;

  for(int i = 0; i < deck.length(); i++) { 
    cout << "Index: " << i << endl;
    deck[i]->listen();
  }

}

void play(Array<Creature*>& deck) {

  cout << "Type the index of the Hokeemon you want to play with:" << endl;

  bool invalid;
  int index;

  do {

    invalid = false;
    index = prompt_num();

    if(index < 0 || index >= deck.length()) {
      cout << "Invalid index!" << endl;
      invalid = true;
    }

  }while(invalid);

  deck.get(index)->play();
}

void feed(Array<Creature*>& deck) {
  
  cout << "Type the index of the Hokeemon you want to feed:" << endl;

  bool invalid;
  int index;

  do {

    invalid = false;
    index = prompt_num();

    if(index < 0 || index >= deck.length()) {
      cout << "Invalid index!" << endl;
      invalid = true;
    }

  }while(invalid);

  deck.get(index)->feed();
}

// Specification A1 - Critter Name
void prompt_name(Creature* c) {

  cout << "Type a name for your new Hokeemon:" << endl;
  string s;
  getline(cin, s);

  if(s.size() > 0) c->set_name(s);

  cout << "Name set!" << endl;
}

int prompt_num() {
  
  bool invalid;
  int deserialized;

  do {

    invalid = false;

    string line;
    getline(cin, line);

    try {
      deserialized = stoi(line);
    }catch(invalid_argument& ia) {
      invalid = true;
      cout << "Invalid number! Try again:" << endl;
      continue;
    }

  } while(invalid);

  return deserialized;
}

void program_greeting() {

  cout << "Program greeting! This is a small mini game where you have to keep your hokeemon alive." << endl;
  cout << "How to play: Listening doesn't pass time and gives you information about your hokeemon," << endl;
  cout << "playing and feeding increase or decrease food/boredom, and catching has a 50 percent" << endl;
  cout << "chance of adding a new hokeemon to your deck." << endl;
  cout << "Aidan Anderson; CISP 400; 11-26-2023" << endl << endl;

}

void comp_test() {

  Array<Creature*> arr;
  Snek s;
  Tortle t;

  arr.comp_test();
  s.comp_test();
  t.comp_test();

}