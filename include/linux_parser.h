#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};


// Filters
const std::string filterPrettyName ("PRETTY_NAME");
const std::string filterMemoryFree ("MemFree:");
const std::string filterMemoryTotal ("MemTotal:");
const std::string filterCPU ("cpu");
const std::string filterProcesses ("processes");
const std::string filterProcessesRunning ("procs_running");
//used VmData instead of VmSize following recomendation in the documentation because VmSize represents virtual memory and VmData physical memory (followed mentor review)
//https://man7.org/linux/man-pages/man5/proc.5.html
const std::string filterRam ("VmData:");
const std::string filterUID ("Uid:");

// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
std::vector<std::string> CpuUtilization();
float CPUTilization();
long ActiveJiffies(int pid);

// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
};  // namespace LinuxParser

#endif