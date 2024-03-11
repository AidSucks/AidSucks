// Specification B2 - Source File Header
// assign1_pig.cpp
// Aidan Anderson, CISP 400
// 9-3-23

#include <iostream>
#include <random>
#include <string>

using namespace std;

//Function prototypes
void program_greeting();
void run(string);
void start_game(string, int*);
bool end_game();
bool player_turn(string, int&);
void computer_turn(int&);
int D6();
int random_number(int, int);
void display_stats(string, int);

int main() {

  program_greeting();

  cout << "\nEnter your name:" << endl;
  //Specification C2 - Student Name
  string full_name = "";
  getline(cin, full_name);

  //Specification C1 - Fixed Seed
  uint32_t seed = 500;
  srand(seed);

  run(full_name);
  
  return 0;
}

void run(string player_name) {

  bool is_running = true;

  // Specification B3 - hiScore on Heap
  int* hiScore = new int;
  *hiScore = 0;

  while(is_running) {

    start_game(player_name, hiScore);

    bool exit_game = end_game();

    if(exit_game) is_running = false;
  }

  delete hiScore;
}

void start_game(string player_name, int* hiScore) {

  bool continue_game = true;

  int player_total_points = 0;
  int computer_total_points = 0;

  while(continue_game) {

    cout << "\n" << player_name << "'s turn\n=========" << endl;
    bool result = player_turn(player_name, player_total_points);

    if(!result) {
      continue_game = false;
      continue;
    }

    display_stats(player_name, player_total_points);

    cout << "\nCPU's turn\n=========" << endl;
    computer_turn(computer_total_points);

    display_stats("CPU", computer_total_points);
  }

  // Specification B4 – Display hiScore
  if(player_total_points > *hiScore) {
    *hiScore = player_total_points;
    cout << "New Highscore: " << *hiScore << endl;
  }

}

bool end_game() {

  cout << "Play again? (y/n):" << endl;
  int c = getchar();
  char answer = (char) c;

  if(answer == 'y' || answer == 'Y') return false;

  return true;
}

bool player_turn(string player_name, int& player_total_points) {

  bool player_turn = true;
  int turn_points = 0;

  while(player_turn) {

    // Specification A4 - Input Validation
    cout << "Actions:\n1.Roll 2.Hold 3.Quit" << endl;
    string s;
    getline(cin, s);
    int input = 0;

    try {
      input = stoi(s, nullptr, 0);
    }catch(invalid_argument ia) {
      cout << "Invalid Number!" << endl;
      continue;
    }

    // Specification C3 - Numeric Menu
    if(input == 1) {

      int r = D6();

      cout << "You rolled a " << r << endl;

      if(r == 1) return true;

      turn_points += r;
      continue;
    }

    if(input == 2) {

      player_total_points += turn_points;
      return true;

    }

    if(input == 3) return false;

    cout << "Invalid Selection!" << endl;
  }

  return true;
}

void computer_turn(int& computer_total_points) {

  bool computer_turn = true;
  int turn_points = 0;

  while(computer_turn) {

    int decision = D6();

    if(decision <= 3) {

      computer_total_points += turn_points;

      computer_turn = false;

      cout << "CPU holds" << endl;

    }else {
      int roll = D6();

      cout << "CPU rolled a " << roll << endl;

      if(roll == 1) {
        computer_turn = false;
        continue;
      }

      turn_points += roll;
    }
  }

}

// Specification A1 - D6() function
int D6() {
  return random_number(1, 6);
}

// Specification A2 - RandomNumber() function
int random_number(int lo, int hi) {

  // Specification A3 - Protect RandomNumber() input
  if(hi < lo || lo < 1 || hi > 100) return -1; 

  return rand() % hi + lo;
}

// Specification B1 - Display Turn Stats
void display_stats(string name, int points) {
  cout << "\n" << name << " total points: " << points << endl; 
}

//Specification C4 - ProgramGreeting
void program_greeting() {
  cout << "Program Greeting!" << endl;

  cout << "Running tests..." << endl;
  cout << "Less than 1: " << (random_number(0, 2) == -1 ? "Passed" : "Failed") << endl;
  cout << "Greater than 100: " << (random_number(1, 101) == -1 ? "Passed" : "Failed") << endl;
  cout << "Lo greater than hi: " << (random_number(10, 5) == -1 ? "Passed" : "Failed") << endl;
}