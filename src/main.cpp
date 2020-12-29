#include "ncurses_display.h"
#include "system.h"
#include  "linux_parser.h"
#include <iostream>

int main() {
  System system;
  //std::cout<<"\n\n";LinuxParser::Pids();
  //std::cout << LinuxParser::MemoryUtilization()<<"\n\n";

  NCursesDisplay::Display(system);
}