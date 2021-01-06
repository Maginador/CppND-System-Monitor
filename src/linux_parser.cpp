#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"


//using namespace std;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterPrettyName) {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, trash;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> trash >>kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {  
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  
  long menfree=1;
  long mentotal=1;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
     
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterMemoryFree) {
         menfree = std::stol(value);
          
        }
        if (key == filterMemoryTotal) {
         mentotal = std::stol(value);
          
        }
        
      }

    }

    return static_cast<float>(mentotal - menfree)/mentotal;
  } 
  return 0;
  }

long LinuxParser::UpTime() { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory+kUptimeFilename);
        
  if (filestream.is_open()) {
    long uptime;
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
     linestream >> uptime;
          return uptime;
        }
      }
      return 0;
 }

float LinuxParser::CPUTilization() { 
  string line;
  string key;
  float user,nice,system,idle,iowait,irq,softirq,steal,guest,guest_nice;
  std::ifstream filestream(kProcDirectory+kStatFilename);
        
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == filterCPU) {
         linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq >>steal >> guest >> guest_nice;
         float idleTime = idle + iowait;
         float nonIdleTime = user + nice + system + irq + softirq + steal;
         float guestTime = guest + guest_nice;
         float total = idleTime + nonIdleTime + guestTime;
         float result = ( total - idleTime)/total;
          return result;
        }
      }
    } 
  return 0;
}

long LinuxParser::ActiveJiffies(int pid) { 
  //use                         14 + 15 + 16 + 17 
  string line, value; float utime, stime, cutime, cstime;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
  std::getline(filestream,line);
  std::istringstream linestream(line);
  for(int i =0; i<18; i++) {
    linestream >> value;
    if(i+1 == 14 ) utime = stof(value);
    else if (i+1 == 15 ) stime = stof(value);
    else if (i+1 == 16 ) cutime = stof(value);
    else if (i+1 == 17 ) cstime = stof(value);
  }

  return ((utime + stime + cutime + cstime)/sysconf(_SC_CLK_TCK));
}

int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory+kStatFilename);
        
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterProcesses) {
         
          return std::stoi(value);
        }
      }
    }
  }
  return 0;
  }

int LinuxParser::RunningProcesses() { string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory+kStatFilename);
        
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterProcessesRunning) {
         
          return std::stoi(value);
        }
      }
    }
  } 
  return 0;
  }

string LinuxParser::Command(int pid) { 
  string key;
  string value;
  string cmd;

  std::ifstream filestream(kProcDirectory+to_string(pid)+kCmdlineFilename);
        
  if (filestream.is_open()) {
    std::getline(filestream,cmd);
  }
  if(cmd.size() > 40){
    cmd.resize(40);
    cmd += "...";

  }
  return cmd; }

string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterRam) {
          
          return to_string(stoi(value)/1000);
        }
      }
    }
  }
  return string();

 }

string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterUID) {
          return value;
        }
      }
    }
  }
  return string();
}

string LinuxParser::User(int pid) { 
  string line;
  string key;
  string value;
  string uid = Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      string garbage;
      std::istringstream linestream(line);
      linestream >> value >> garbage >> key;
      if (key == uid) {
          return value;
      }
    }
    return "error!!";
    
  }else
  return string();
 }

long LinuxParser::UpTime(int pid) { 
  
  string line, value;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
  std::getline(filestream,line);
  std::istringstream linestream(line);
  for(int i =0; i<22; i++) linestream >> value;
  return UpTime() - (stol(value))/sysconf(_SC_CLK_TCK); }