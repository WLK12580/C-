#include <iostream>

int main() {
  int n = 0;
  std::cout<<"请输入参数:";
  std::cin >> n;
  int f0 = 1;
  int f1 = 2;
  int fi=0;
  if (n < 2) {
    if (n == 0) {
      std::cout << "f0="<<f0 << std::endl;
    }
    if (n == 1) {
      std::cout <<"f1="<<f1 << std::endl;
    }
  } else if (n >= 2) {
    for (int i = 2; i <= n; i++) {
      fi = 2 * f1;
      f1 = fi;
    }
    std::cout <<"fi=" <<fi << std::endl;
  }
  return 0;
}