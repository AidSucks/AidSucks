#include <iostream>

template <class T> class Stack {

  private:

    struct StackFrame {
      T value;
      StackFrame *previous;

      StackFrame(StackFrame *prev = nullptr) {
        previous = prev;
      }

      StackFrame(T val, StackFrame *prev = nullptr) {
        value = val;
        previous = prev;
      }
    };

    int size;
    StackFrame *top;

  public:

    Stack() {
      size = 0;
      top = nullptr;
    }

    bool is_empty() {
      return size == 0;
    }

    void push(T val) {
      
      StackFrame *frame = new StackFrame(val, top);
      top = frame;

      size += 1;
    }

    void pop() {

      if(is_empty()) return;

      StackFrame *p = top->previous;
      T val = top->value;

      delete top;

      top = p;

      size -= 1;

    }

    T peek() {
      return top->value;
    }

};

int main() {

  Stack<int> stk;
  stk.push(1);
  stk.push(2);
  stk.push(3);

  stk.pop();
  stk.pop();

  return 0;
}