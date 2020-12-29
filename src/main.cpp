#include "ncurses_display.h"
#include "system.h"
#include  "linux_parser.h"
#include <iostream>
#include <vector>

int main() {
  System system;
  //std::cout<<"\n\n";LinuxParser::Pids();
  //std::cout << LinuxParser::MemoryUtilization()<<"\n\n";
  //LinuxParser::User(0);
 /*std:: vector<int> v = LinuxParser::Pids();
 for(int i =0; i<v.size(); i++){
   LinuxParser::User(v[i]);
 }*/

  NCursesDisplay::Display(system);
}