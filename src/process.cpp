#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

int Process::Pid() { return pid_; }

float Process::CpuUtilization() { return cpu_; }

string Process::Command() { return cmd_; }

string Process::Ram() { return ram_; }

string Process::User() { return user_; }

long int Process::UpTime() { return uptime_; }

bool Process::operator<(Process const& a) const { return a.cpu_ < cpu_ ? true : false; }

Process::Process(int pid){
    pid_ = pid;
    cmd_ = LinuxParser::Command(pid);
    ram_ = LinuxParser::Ram(pid);
    user_ = LinuxParser::User(pid);
    uptime_ = LinuxParser::UpTime(pid);
    cpu_ = (float)LinuxParser::ActiveJiffies(pid)/uptime_;


}