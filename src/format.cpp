#include <string>

#include "format.h"

using std::string;
using std::to_string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
    int seconds_, minutes_, hours_;
    string s, m, h;

    seconds_ = seconds%60;
    minutes_ = (seconds/60)%60;
    hours_ = seconds/60/60;
    s = seconds_<10? "0" + to_string(seconds_) : to_string(seconds_);
    m = minutes_<10? "0" + to_string(minutes_) : to_string(minutes_);
    h = to_string(hours_);
    //string result = string(); result = to_string(seconds_);
    string result = h + ":"+m+":"+s;
    return result; }