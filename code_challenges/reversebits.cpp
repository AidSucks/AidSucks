#include <iostream>

uint32_t reverseBits(uint32_t);

int main() {

  uint32_t output = reverseBits(2147483648);

  std::cout << output << std::endl;

  return 0;
}

uint32_t reverseBits(uint32_t n) {

  uint32_t reversed = 0;
        
  for(int x = 0; x < 32; x++) {

    reversed <<= 1;

    if(n & 1) reversed += 1;

    n >>= 1;
  }

  return reversed;
}
