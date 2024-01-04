#pragma once

#include <string>
using std::string;

struct Request {
    string srcIP;
    string dstIP;
    int time;
};