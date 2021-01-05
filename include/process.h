#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
    Process(int);
  int Pid();                                 
  std::string User();                        
  std::string Command();                     
  float CpuUtilization();                    
  std::string Ram();                         
  long int UpTime();                         
  bool operator<(Process const& a) const;    

  // TODO: Declare any necessary private members
 private:
 int pid_;
 std::string user_;
 std::string cmd_;
 std::string ram_;
 float cpu_;
 long int uptime_;

};

#endif