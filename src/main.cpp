#include "ncurses_display.h"
#include "system.h"
#include  "linux_parser.h"
#include <iostream>

int main() {
  System system;
  std::cout<<"\n\n";
  std::cout << LinuxParser::TotalProcesses()<<"\n\n";

  //NCursesDisplay::Display(system);
}