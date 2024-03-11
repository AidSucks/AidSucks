#include <iostream>
#include <chrono>

template <class T> class LinkedList {

  private:
    struct Node {
      T value;
      Node *next;
    };

    int size;
    Node *start;
    
  public:

    LinkedList(T val) {
      size = 1;
      start = new Node();
      start->value = val;
      start->next = nullptr;
    }

    ~LinkedList() {

      Node *curr = start;

      for(int i = 0; i < size; i++) {
        Node *next = curr->next;
        delete curr;
        curr = next;
      }

      start = nullptr;
    }

    void add(T val) {

      Node *n = new Node();
      n->value = val;
      n->next = nullptr;

      Node *previous = start;

      for(int i = 0; i < size - 1; i++) previous = previous->next;

      previous->next = n;
      size += 1;
    }

    void remove(int index) {

      if(index >= size || index < 0 || size == 1) return;

      Node *prev = nullptr;
      Node *curr = start;
      Node *after = curr->next;

      for(int i = 0; i < index; i++) {
        prev = curr;
        curr = curr->next;
        after = curr->next;
      }

      delete curr;
      curr = nullptr;

      if(index == 0) {
        start = after;
      }else {
        prev->next = after;
      }
    }

    T get(int index) {


      Node *curr = start;
      for(int i = 0; i < index; i++) {

        if(curr->next == nullptr) return start->value;

        curr = curr->next;
      }

      return curr->value;
    }

    int length() {
      return size;
    }
};

int main() {

  LinkedList<int> list(1);

  list.remove(0);

  list.add(6);

  std::cout << list.get(1) << std::endl;
}