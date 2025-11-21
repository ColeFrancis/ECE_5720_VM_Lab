#include <iostream>

int log2(unsigned int num) {
  if (num == 0) {
    return -1;
  }

  int count = 0;
  for (; num > 1; num >>= 1) {
    count++;
  }

  return count;
}

int main(){
    int test_values[50] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        25, 30, 35, 40, 45, 50, 60, 70, 80, 90,
        100, 110, 120, 130, 140, 150, 200, 256, 300, 400,
        500, 600, 700, 800, 900, 1000, 1024, 2048, 4096, 8192
    };
    int log2_values[50] = {
        0, 1, 1, 2, 2, 2, 2, 3, 3, 3,
        3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
        4, 4, 5, 5, 5, 5, 5, 6, 6, 6,
        6, 6, 6, 7, 7, 7, 7, 8, 8, 8,
        8, 9, 9, 9, 9, 9, 10, 11, 12, 13
    };

    for (int i = 0; i < 50; i++){
        if (log2(test_values[i]) != log2_values[i]){
            std::cout << "failed on " 
                      << test_values[i] 
                      << ". Expected " 
                      << log2_values[i]
                      << " got "
                      << log2(test_values[i])
                      << std::endl;
        }
    }
}