#include "ncurses_display.h"
#include "system.h"
#include  "linux_parser.h"
#include <iostream>
#include <vector>

int main() {
  System system;
  //std::cout << LinuxParser::filterPrettyName;
  NCursesDisplay::Display(system);
}