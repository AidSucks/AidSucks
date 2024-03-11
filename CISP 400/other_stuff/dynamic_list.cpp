#include <iostream>

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

};

int main() {

  Array<int> arr;
  arr.add(1);
  arr.add(2);
  arr.add(3);

  for(int i = 0; i < arr.length(); i++) std::cout << arr[i] << std::endl;

  return 0;
}