#include "./headers.h"


int main(char* argv, int argc){
  std::cout << dstr::strings::MSG_WELCOME << '\n';
  dstr::cli_start(std::cin, std::cout, argv, argc);
  return 0;
}
